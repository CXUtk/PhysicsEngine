#include "BVHKDTree.h"

#include <iostream>


BVHKDTree::BVHKDTree(const std::vector<Object*>& objs) {
    _objects = objs;
    _root = _build(0, _objects.size() - 1, 0);
}

BVHKDTree::~BVHKDTree() {
    _destroy(_root);
}


glm::vec2 _dummyPoint;
float _curNearest;
QueryResult result;
int cnt = 0;
QueryResult BVHKDTree::QueryNearest(glm::vec2 pos) {
    result.distance = POS_INF;
    result.target = nullptr;
    _dummyPoint = pos;
    cnt = 0;
    _queryNearest(_root, 0);
    std::cout << cnt << std::endl;
    return result;
}

BVHKDTree::Node* BVHKDTree::_build(int l, int r, bool dim) {
    if (l > r)return nullptr;
    auto cmp = [dim](const Object* a, const Object* b) {
        return a->centric()[dim] < b->centric()[dim];
    };
    int mid = (l + r) / 2;
    std::nth_element(_objects.begin() + l, _objects.begin() + mid, _objects.begin() + r + 1, cmp);
    auto cur = _objects[mid];
    auto p = new Node(cur);
    p->ch[0] = _build(l, mid - 1, !dim);
    p->ch[1] = _build(mid + 1, r, !dim);
    p->push_up();
    return p;
}


float distanceMin(glm::vec2 pos, const AABB& box) {
    if (box.contains(pos))return 0;
    glm::vec2 unit = glm::normalize(((box.pMax + box.pMin) / 2.f - pos));
    float aX = (box.pMin.x - pos.x) / unit.x, bX = (box.pMax.x - pos.x) / unit.x;
    float aY = (box.pMin.y - pos.y) / unit.y, bY = (box.pMax.y - pos.y) / unit.y;
    if (aX > bX) std::swap(aX, bX);
    if (aY > bY) std::swap(aY, bY);
    return std::max(aX, aY);
}

void BVHKDTree::_queryNearest(Node* node, bool dim) {
    cnt++;
    if (!node)
        return;

    float dis = glm::distance(node->target->centric(), _dummyPoint);
    if (result.distance > dis) {
        result.distance = dis;
        result.target = node->target;
    }
    int d = _dummyPoint[dim] > node->target->centric()[dim];
    float dl = node->ch[d] ? distanceMin(_dummyPoint, node->ch[d]->box) : POS_INF;
    float dr = node->ch[!d] ? distanceMin(_dummyPoint, node->ch[!d]->box) : POS_INF;
    if (dl < result.distance)
        _queryNearest(node->ch[d], !dim);
    if (dr < result.distance)
        _queryNearest(node->ch[!d], !dim);
}

void BVHKDTree::_destroy(Node* node) {
    if (!node)return;
    _destroy(node->ch[0]);
    node->ch[0] = nullptr;
    _destroy(node->ch[1]);
    node->ch[1] = nullptr;
    delete node;
}
