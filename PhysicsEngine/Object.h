#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

struct AABB {
    AABB() = default;
    AABB(glm::vec2 pmin, glm::vec2 pmax) : pMin(pmin), pMax(pmax) {}
    AABB(glm::vec2 pos, float w, float h) : pMin(pos), pMax(pos + glm::vec2(w, h)) {}
    AABB(int x, int y, int w, int h) : pMin(glm::vec2(x, y)), pMax(glm::vec2(x + w, y + h)) {}

    glm::vec2 pMin;
    glm::vec2 pMax;

    bool intersects(const AABB& b) const {
        return std::max(pMin.x, b.pMin.x) <= std::min(pMax.x, b.pMax.x)
            && std::max(pMin.y, b.pMin.y) <= std::min(pMax.y, b.pMax.y);
    }

    bool contains(const glm::vec2& pos) const {
        return pos.x >= pMin.x && pos.x <= pMax.x && pos.y >= pMin.y && pos.y <= pMax.y;
    }

    bool contains(const AABB& b) const {
        return b.pMin.x >= pMin.x && b.pMax.x <= pMax.x && b.pMin.y >= pMin.y && b.pMax.y <= pMax.y;
    }

    AABB Union(const AABB& b)const {
        AABB res;
        res.pMin.x = std::min(pMin.x, b.pMin.x);
        res.pMin.y = std::min(pMin.y, b.pMin.y);
        res.pMax.x = std::max(pMax.x, b.pMax.x);
        res.pMax.y = std::max(pMax.y, b.pMax.y);
        return res;
    }
    AABB Intersect(const AABB& b)const {
        AABB res;
        res.pMin.x = std::max(pMin.x, b.pMin.x);
        res.pMin.y = std::max(pMin.y, b.pMin.y);
        res.pMax.x = std::min(pMax.x, b.pMax.x);
        res.pMax.y = std::min(pMax.y, b.pMax.y);
        return res;
    }

    static AABB getBoundingBox(std::initializer_list<glm::vec2> points) {
        glm::vec2 minn = *points.begin();
        glm::vec2 maxx = *points.begin();
        for (auto v : points) {
            minn.x = std::min(minn.x, v.x);
            minn.y = std::min(minn.y, v.y);
            maxx.x = std::max(minn.x, v.x);
            maxx.y = std::max(minn.y, v.y);
        }
        return AABB(minn, maxx);
    }
};

class Object {
public:
    Object() {}
    virtual ~Object() = 0;
    virtual glm::vec2 centric()const = 0;
    virtual AABB getBoundingBox()const = 0;
private:
};
