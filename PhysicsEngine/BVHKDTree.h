#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>

#include "Object.h"


constexpr float POS_INF = std::numeric_limits<float>::infinity();

struct QueryResult {
    const Object* target;
    float distance;

    QueryResult() {
        target = nullptr;
        distance = POS_INF;
    }
};
class BVHKDTree {
public:
    struct Node {
        const Object* target;
        AABB box;
        Node* ch[2];
        int sz, num;

        Node(const Object* obj) {
            target = obj;
            box = obj->getBoundingBox();
            ch[0] = ch[1] = nullptr;
            sz = num = 1;
        }
        void push_up() {
            int ls = num;
            AABB tmp = target->getBoundingBox();
            if (ch[0]) ls += ch[0]->sz, tmp = tmp.Union(ch[0]->box);
            if (ch[1]) ls += ch[1]->sz, tmp = tmp.Union(ch[1]->box);
            sz = ls;
            box = tmp;
        }
    };

    BVHKDTree(const std::vector<Object*>& objs);
    ~BVHKDTree();
    QueryResult QueryNearest(glm::vec2 pos);

private:

    std::vector<Object*> _objects;
    Node* _root;
    Node* _build(int l, int r, bool dim);
    void _queryNearest(Node* node, bool dim);
    void _destroy(Node* node);

};
