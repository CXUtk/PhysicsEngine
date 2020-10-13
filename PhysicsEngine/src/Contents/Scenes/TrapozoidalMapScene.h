#pragma once
#include "Scene.h"
#include "Physics/Physics.h"
#include <vector>
#include <iostream>

constexpr double EPS = 1e-9;
constexpr int MAXN = 5005;
int dcmp(double x);
struct Vector2 {
    double x, y;
    Vector2() {}
    Vector2(double x, double y) : x(x), y(y) {}
    Vector2(double rad) : x(cos(rad)), y(sin(rad)) {}
    friend std::istream& operator>>(std::istream& input, Vector2& v) {
        input >> v.x >> v.y;
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const Vector2& v) {
        output << '(' << v.x << ',' << v.y << ')';
        return output;
    }
    static double dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }
    static double angle(const Vector2& a, const Vector2& b) {
        return acos(dot(a, b) / a.length() / b.length());
    }
    static double cross(const Vector2& a, const Vector2& b) {
        return a.x * b.y - a.y * b.x;
    }
    static double area2(const Vector2& a, const Vector2& b, const Vector2& c) {
        return cross(b - a, c - a);
    }

    double length() const { return sqrt(x * x + y * y); }
    double lengthSq() const { return x * x + y * y; }
    double getRad() const { return atan2(y, x); }
    Vector2 rotate(double rad) const {
        return Vector2(x * cos(rad) - y * sin(rad),
            x * sin(rad) + y * cos(rad));
    }
    Vector2 unit() const {
        double l = this->length();
        return Vector2(x / l, y / l);
    }
    Vector2 normal() const {
        double l = this->length();
        return Vector2(-y / l, x / l);
    }

    bool operator<(const Vector2& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    bool operator==(const Vector2& other) const {
        return !dcmp(x - other.x) && !dcmp(y - other.y);
    }

    Vector2& operator+=(const Vector2& vec) {
        this->x += vec.x, this->y += vec.y;
        return *this;
    }
    Vector2 operator+(const Vector2& vec) const {
        return Vector2(this->x + vec.x, this->y + vec.y);
    }
    Vector2& operator-=(const Vector2& vec) {
        this->x -= vec.x, this->y -= vec.y;
        return *this;
    }
    Vector2 operator-(const Vector2& vec) const {
        return Vector2(this->x - vec.x, this->y - vec.y);
    }
    Vector2& operator*=(double v) {
        this->x *= v, this->y *= v;
        return *this;
    }
    Vector2& operator*=(const Vector2& v) {
        this->x *= v.x, this->y *= v.y;
        return *this;
    }
    Vector2 operator*(double v) const {
        return Vector2(this->x * v, this->y * v);
    }
    Vector2 operator*(const Vector2& vec) const {
        return Vector2(this->x * vec.x, this->y * vec.y);
    }
    Vector2& operator/=(double v) {
        this->x /= v, this->y /= v;
        return *this;
    }
    Vector2& operator/=(const Vector2& vec) {
        this->x /= vec.x, this->y /= vec.y;
        return *this;
    }
    Vector2 operator/(double v) const {
        return Vector2(this->x / v, this->y / v);
    }
    Vector2 operator/(const Vector2& vec) const {
        return Vector2(this->x / vec.x, this->y / vec.y);
    }
    Vector2 operator-() const { return Vector2(-this->x, -this->y); }
};
bool segIntersection(const Vector2& A, const Vector2& B, const Vector2& C,
    const Vector2& D, double& t);

enum NodeType {
    SEGMENT,
    POINT,
    TRAPOZOID,
};
struct Segment;
struct EndPoint {
    Vector2 pos;
    int segID;
    Segment* pSeg;
    EndPoint(const Vector2& pos, int id) : pos(pos), segID(id), pSeg(nullptr) {}
};
struct Segment {
    EndPoint* start;
    EndPoint* end;
    Segment(EndPoint* a, EndPoint* b) : start(a), end(b) {
        start->pSeg = this;
        end->pSeg = this;
    }
    int to_left(const Vector2& p) const {
        double d = Vector2::cross(end->pos - start->pos, p - start->pos);
        return dcmp(d);
    }
    bool onSeg(const Vector2& p) const {
        auto v = (p - start->pos) / (end->pos - start->pos);
        return v.x >= 0 && v.x <= 1 && v.y >= 0 && v.y <= 1 && v.x == v.y;
    }
    Vector2 sample(double x) const {
        double t = (x - start->pos.x) / (end->pos.x - start->pos.x);
        return start->pos * (1 - t) + end->pos * t;
    }
    double slope() const {
        return (end->pos.y - start->pos.y) / (end->pos.x - start->pos.x);
    }
};
struct Node;


// Trapozoid structure with DCEL
struct Trapozoid {
    Segment* top;
    Segment* bottom;
    Trapozoid* left[2];
    Trapozoid* right[2];
    Vector2 corner[4];
    Node* attachNode;
    Trapozoid(const Vector2& botLeft, const Vector2& topLeft,
        const Vector2& topRight, const Vector2& botRight, Segment* top,
        Segment* bot)
        : top(top), bottom(bot) {
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        corner[0] = botLeft;
        corner[1] = topLeft;
        corner[2] = topRight;
        corner[3] = botRight;
    }
    Trapozoid(const Vector2& botLeft, const Vector2& topRight, Segment* top,
        Segment* bot)
        : top(top), bottom(bot) {
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        corner[0] = botLeft;
        corner[1] = Vector2(botLeft.x, topRight.y);
        corner[2] = topRight;
        corner[3] = Vector2(topRight.x, botLeft.y);
    }

    Vector2 getTop(double x) const { return top->sample(x); }
    Vector2 getBottom(double x) const { return bottom->sample(x); }
    bool getIntersection(const Segment* segment, Vector2& pos) const {
        double t;
        bool f = segIntersection(segment->start->pos, segment->end->pos,
            corner[0], corner[1], t);
        if (f && t != 1) {
            pos = segment->start->pos * (1 - t) + segment->end->pos * t;
            return true;
        }
        return false;
    }
    bool pointIn(const Vector2& pos) {
        for (int i = 0; i < 4; i++) {
            if (Vector2::cross(corner[(i + 1) % 4] - corner[i],
                pos - corner[i]) > 0)
                return false;
        }
        return true;
    }

    void linkLeft(Trapozoid* upper, Trapozoid* lower) {
        left[0] = upper;
        left[1] = lower;
    }
    void linkRight(Trapozoid* upper, Trapozoid* lower) {
        right[0] = upper;
        right[1] = lower;
    }

    void doubleLinkLeft(Trapozoid* upper, Trapozoid* lower) {
        left[0] = upper;
        left[1] = lower;
        if (upper) upper->right[0] = this;
        if (lower) lower->right[0] = this;
    }
    void doubleLinkRight(Trapozoid* upper, Trapozoid* lower) {
        right[0] = upper;
        right[1] = lower;
        if (upper) upper->left[0] = this;
        if (lower) lower->left[0] = this;
    }
    void inheritLinkRight(Trapozoid* upper, Trapozoid* lower, Trapozoid* target) {
        if (upper) {
            for (int i = 0; i < 2; i++) {
                if (upper->left[i] == target) upper->left[i] = this;
            }
        }
        if (lower) {
            for (int i = 0; i < 2; i++) {
                if (lower->left[i] == target) lower->left[i] = this;
            }
        }
    }
    void inheritLinkLeft(Trapozoid* upper, Trapozoid* lower, Trapozoid* target) {
        if (upper) {
            for (int i = 0; i < 2; i++) {
                if (upper->right[i] == target) upper->left[i] = this;
            }
        }
        if (lower) {
            for (int i = 0; i < 2; i++) {
                if (lower->right[i] == target) lower->left[i] = this;
            }
        }
    }

    bool zeroArea()const {
        return !dcmp(corner[0].x - corner[3].x) || !dcmp(corner[0].y - corner[1].y);
    }
};
struct Node {
    NodeType type;
    Node* ch[2];
    union {
        Trapozoid* trapozoid;
        EndPoint* point;
        Segment* segment;
    };
};

struct TrapozoidalMap {
    int _tot;
    Node* _root;
    Trapozoid* _holdingTrap;

    Node nodes[MAXN];
    std::vector<Segment> segments;
    std::vector<EndPoint> endPoints;
    std::vector<Trapozoid> trapozoids;


    TrapozoidalMap() {
        memset(nodes, 0, sizeof(nodes));
        _tot = 0;
        _root = nullptr;
    }
    Node* createTrapozoid(const Trapozoid& trap) {
        trapozoids.push_back(trap);
        auto p = &nodes[++_tot];
        p->type = NodeType::TRAPOZOID;
        p->trapozoid = &trapozoids.back();
        p->trapozoid->attachNode = p;
        return p;
    }
    Node* createTrapozoidReferenceNode(Trapozoid* trapozoid) {
        auto p = &nodes[++_tot];
        p->type = NodeType::TRAPOZOID;
        p->trapozoid = trapozoid;
        trapozoid->attachNode = p;
        return p;
    }

    Node* createSegmentReferenceNode(Segment* segment) {
        auto p = &nodes[++_tot];
        p->type = NodeType::SEGMENT;
        p->segment = segment;
        return p;
    }

    Node* createPointReferenceNode(EndPoint* point) {
        auto p = &nodes[++_tot];
        p->type = NodeType::POINT;
        p->point = point;
        return p;
    }

    Segment* createSegment(const Vector2& a, const Vector2& b) {
        int id = segments.size();
        endPoints.push_back(EndPoint(a, id));
        auto aptr = &endPoints.back();
        endPoints.push_back(EndPoint(b, id));
        auto bptr = &endPoints.back();
        segments.push_back(Segment(aptr, bptr));
        return &segments.back();
    }

    void modifyCase1(Node* P1, Segment* segment) {
        // P1 is the left point
        auto pointA = segment->start->pos;
        auto pointB = segment->end->pos;
        Trapozoid oldCopy = *P1->trapozoid;

        // A is the Trapozoid area on the left
        Trapozoid* A = P1->trapozoid;
        A->corner[2] = oldCopy.getTop(pointA.x);
        A->corner[3] = oldCopy.getBottom(pointA.x);

        // Turn P to point node
        P1->type = NodeType::POINT;
        P1->point = segment->start;
        P1->ch[0] = createTrapozoidReferenceNode(A);

        // P2 is the right point
        Node* P2 = createPointReferenceNode(segment->end);
        // B is the right Trapozoid
        Node* B = createTrapozoid(
            Trapozoid(oldCopy.getBottom(pointB.x), oldCopy.getTop(pointB.x),
                oldCopy.getTop(oldCopy.corner[2].x),
                oldCopy.getBottom(oldCopy.corner[2].x), oldCopy.top,
                oldCopy.bottom));
        P2->ch[1] = B;
        P1->ch[1] = P2;

        // S1 is the middle segment node
        Node* S1 = createSegmentReferenceNode(segment);
        P2->ch[0] = S1;

        // C is the middle top Trapozoid
        Node* C = createTrapozoid(Trapozoid(pointA, oldCopy.getTop(pointA.x),
            oldCopy.getTop(pointB.x), pointB,
            oldCopy.top, segment));
        S1->ch[0] = C;
        // C is the middle bottom Trapozoid
        Node* D = createTrapozoid(Trapozoid(oldCopy.getBottom(pointA.x), pointA,
            pointB, oldCopy.getBottom(pointB.x),
            segment, oldCopy.bottom));
        S1->ch[1] = D;

        // A - (CD) - B
        // Link them together
        A->doubleLinkRight(C->trapozoid, D->trapozoid);
        B->trapozoid->doubleLinkLeft(C->trapozoid, D->trapozoid);

        B->trapozoid->linkRight(oldCopy.right[0], oldCopy.right[1]);
        B->trapozoid->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
    }

    void modifyCase2(Node* P1, Segment* segment) {
        // L - (A|B)
        auto pointA = segment->start->pos;
        auto pointB = segment->end->pos;

        // Modify A to shrink
        Trapozoid oldCopy = *P1->trapozoid;
        Trapozoid* A = P1->trapozoid;
        A->corner[2] = oldCopy.getTop(pointA.x);
        A->corner[3] = oldCopy.getBottom(pointA.x);

        Node* B[2];
        // Top one
        B[0] = createTrapozoid(Trapozoid(pointA, oldCopy.getTop(pointA.x),
            oldCopy.corner[2], segment->sample(oldCopy.corner[2].x),
            oldCopy.top, segment));

        // Bottom one
        B[1] = createTrapozoid(
            Trapozoid(oldCopy.getBottom(pointA.x), pointA,
                segment->sample(oldCopy.corner[2].x), oldCopy.corner[3],
                segment, oldCopy.bottom));

        bool extend = false;
        // If bounded on top
        if (oldCopy.corner[2] == oldCopy.top->end->pos) {
            extend = 1;
        }
        else if (oldCopy.corner[3] == oldCopy.bottom->end->pos) {
            // If bounded bottom
            extend = 0;
        }
        else {
            extend = segment->sample(oldCopy.corner[2].x).y < oldCopy.right[0]->corner[0].y;
        }
        // S1 is the right segment
        Node* S1 = createSegmentReferenceNode(segment);

        // B[extendTop] is the immutable Trapozoid 
        S1->ch[0] = B[0];
        S1->ch[1] = B[1];

        // P1 is the left point
        P1->type = NodeType::POINT;
        P1->point = segment->start;
        P1->ch[0] = createTrapozoidReferenceNode(A);
        P1->ch[1] = S1;

        // A -- B0/B1 -- E -- null
        Trapozoid* oldRight[2];
        memcpy(oldRight, A->right, sizeof(oldRight));
        A->doubleLinkRight(B[0]->trapozoid, B[1]->trapozoid);
        B[!extend]->trapozoid->linkRight(oldCopy.right[0], oldCopy.right[1]);
        B[!extend]->trapozoid->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);

        _holdingTrap = B[extend]->trapozoid;
    }


    void modifyCase3(Node* P1, Segment* segment) {
        auto pointA = segment->start->pos;
        auto pointB = segment->end->pos;


        Trapozoid oldCopy = *P1->trapozoid;
        int CASE = 0;
        // If has bound on the top left
        // segment->sample(oldCopy.corner[0].x).y is the left intersection point
        if (oldCopy.corner[1] == oldCopy.top->start->pos || segment->sample(oldCopy.corner[0].x).y < oldCopy.left[0]->corner[3].y) {
            CASE |= 1;
        }
        else if (oldCopy.corner[0] == oldCopy.bottom->start->pos || segment->sample(oldCopy.corner[0].x).y > oldCopy.left[0]->corner[3].y) {
            CASE |= 0;
        }
        else {
            std::cerr << "Impossible Condition" << std::endl;
        }
        if (oldCopy.corner[2] == oldCopy.top->end->pos || segment->sample(oldCopy.corner[2].x).y < oldCopy.right[0]->corner[0].y) {
            CASE |= 2;
        }
        else if (oldCopy.corner[3] == oldCopy.bottom->end->pos || segment->sample(oldCopy.corner[0].x).y > oldCopy.left[0]->corner[3].y) {
            CASE |= 0;
        }
        else {
            std::cerr << "Impossible Condition" << std::endl;
        }


        Trapozoid* A = P1->trapozoid;
        P1->type = NodeType::SEGMENT;
        P1->segment = segment;
        // Both end is bounding on the bottom
        if (CASE == 0) {
            A->corner[1] = segment->sample(oldCopy.corner[0].x);
            A->corner[2] = segment->sample(oldCopy.corner[3].x);
            A->top = segment;
            // Connect

            P1->ch[0] = _holdingTrap->attachNode;
            P1->ch[1] = createTrapozoidReferenceNode(A);

            A->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
            A->inheritLinkLeft(oldCopy.left[0], oldCopy.left[1], A);
        }
        else if (CASE == 1) {
            // Top left and Bottom Right

            // End this holdingTrap
            _holdingTrap->corner[2] = segment->sample(oldCopy.corner[3].x);
            _holdingTrap->corner[3] = oldCopy.corner[3];

            A->corner[0] = segment->sample(oldCopy.corner[0].x);
            A->corner[3] = segment->sample(oldCopy.corner[3].x);
            A->bottom = segment;

            P1->ch[0] = createTrapozoidReferenceNode(A);
            P1->ch[1] = _holdingTrap->attachNode;

            // Connect
            _holdingTrap->linkRight(oldCopy.right[0], oldCopy.right[1]);
            _holdingTrap->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
            A->linkLeft(oldCopy.left[0], oldCopy.left[1]);
            A->inheritLinkLeft(oldCopy.left[0], oldCopy.left[1], A);

            // Switch holdingTrap
            _holdingTrap = A;

        }
        else if (CASE == 2) {
            // Top Right and Bottom Left

            // End this holdingTrap
            _holdingTrap->corner[2] = oldCopy.corner[2];
            _holdingTrap->corner[3] = segment->sample(oldCopy.corner[3].x);

            A->corner[1] = segment->sample(oldCopy.corner[0].x);
            A->corner[2] = segment->sample(oldCopy.corner[3].x);
            A->top = segment;

            P1->ch[0] = _holdingTrap->attachNode;
            P1->ch[1] = createTrapozoidReferenceNode(A);

            // Connect
            _holdingTrap->linkRight(oldCopy.right[0], oldCopy.right[1]);
            _holdingTrap->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
            A->linkLeft(oldCopy.left[0], oldCopy.left[1]);
            A->inheritLinkLeft(oldCopy.left[0], oldCopy.left[1], A);

            // Switch holdingTrap
            _holdingTrap = A;

        }
        else {
            // Both end is bounding top
            A->corner[0] = segment->sample(oldCopy.corner[0].x);
            A->corner[3] = segment->sample(oldCopy.corner[3].x);
            A->bottom = segment;

            P1->ch[0] = createTrapozoidReferenceNode(A);
            P1->ch[1] = _holdingTrap->attachNode;
            // Connect
            A->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
            A->inheritLinkLeft(oldCopy.left[0], oldCopy.left[1], A);
        }

    }

    void modifyCase4(Node* P1, Segment* segment) {
        auto pointA = segment->start->pos;
        auto pointB = segment->end->pos;

        // Modify A to shrink
        Trapozoid oldCopy = *P1->trapozoid;

        int extend;
        // If bounded on top
        if (oldCopy.corner[1] == oldCopy.top->start->pos) {
            extend = 1;
        }
        else if (oldCopy.corner[0] == oldCopy.bottom->start->pos) {
            // If bounded bottom
            extend = 0;
        }
        else {
            extend = segment->sample(oldCopy.corner[0].x).y < oldCopy.left[0]->corner[3].y;
        }
        Trapozoid* A = P1->trapozoid;
        // If extension on the top
        if (!extend) {
            // A->corner[0] = oldCopy.corner[0];
            A->corner[1] = segment->sample(oldCopy.corner[0].x);
            A->corner[2] = pointB;
            A->corner[3] = oldCopy.getBottom(pointB.x);
            A->top = segment;

            _holdingTrap->corner[2] = oldCopy.getTop(pointB.x);
            _holdingTrap->corner[3] = pointB;
        }
        else {
            A->corner[0] = segment->sample(oldCopy.corner[0].x);
            // A->corner[1] = oldCopy.corner[1];
            A->corner[2] = oldCopy.getTop(pointB.x);
            A->corner[3] = pointB;
            A->bottom = segment;

            _holdingTrap->corner[2] = pointB;
            _holdingTrap->corner[3] = oldCopy.getBottom(pointB.x);
        }
        Node* D = createTrapozoidReferenceNode(A);
        Node* E = createTrapozoid(Trapozoid(oldCopy.getBottom(pointB.x), oldCopy.getTop(pointB.x),
            oldCopy.corner[2], oldCopy.corner[3],
            oldCopy.top, oldCopy.bottom));


        // S1 is the right segment
        Node* S1 = createSegmentReferenceNode(segment);
        S1->ch[0] = (extend == 0) ? _holdingTrap->attachNode : D;
        S1->ch[1] = (extend == 0) ? D : _holdingTrap->attachNode;

        P1->type = NodeType::POINT;
        P1->point = segment->end;
        P1->ch[1] = E;
        P1->ch[0] = S1;

        _holdingTrap->linkRight(E->trapozoid, nullptr);
        A->linkRight(E->trapozoid, nullptr);
        E->trapozoid->linkLeft((extend == 0) ? _holdingTrap : A, (extend == 0) ? A : _holdingTrap);

        E->trapozoid->linkRight(oldCopy.right[0], oldCopy.right[1]);
        E->trapozoid->inheritLinkRight(oldCopy.right[0], oldCopy.right[1], A);
    }


    void insert(const Vector2& a, const Vector2& b, bool end) {
        auto seg = createSegment(a, b);
        auto leftT = _queryStart(_root, seg);
        auto rightT = _queryEnd(_root, seg);
        // CASE 1
        if (leftT == rightT) {
            modifyCase1(leftT, seg);
        }
        else {
            // CASE 2 and 3
            auto p = leftT;

            // Do middles first, then head and tail
            while (true) {
                if (!p)break;
                Vector2 pos;
                Node* nxtP = nullptr;
                for (int i = 0; i < 2; i++) {
                    auto nxt = p->trapozoid->right[i];
                    if (!nxt) continue;
                    if (nxt->getIntersection(seg, pos)) {
                        nxtP = nxt->attachNode;
                    }
                }
                if (p->trapozoid->pointIn(seg->start->pos)) {
                    modifyCase2(p, seg);
                }
                else if (p->trapozoid->pointIn(seg->end->pos)) {
                    if (end)
                        modifyCase4(p, seg);
                    break;
                }
                else {
                    modifyCase3(p, seg);
                }
                p = nxtP;
            }
        }
    }


    Node* _queryStart(Node* node, const Segment* seg) {
        if (node->type == NodeType::TRAPOZOID)
            return node;
        else if (node->type == NodeType::POINT) {
            // 0 if to the left, 1 if to the right
            int d = dcmp(seg->start->pos.x - node->point->pos.x);
            // If they are the same then force to the right
            if (d == -1) d = 0;
            else d = 1;
            return _queryStart(node->ch[d], seg);
        }
        else if (node->type == NodeType::SEGMENT) {
            // 0 if above, 1 if below
            int d = node->segment->to_left(seg->start->pos);
            if (d == 1) d = 0;
            else if (d == -1) d = 1;
            else {
                // if the slope of seg is greater than the slope of judging seg then it is above
                d = dcmp(seg->slope() - node->segment->slope()) < 0;
            }
            return _queryStart(node->ch[d], seg);
        }
        return node;
    }

    Node* _queryEnd(Node* node, const Segment* seg) {
        if (node->type == NodeType::TRAPOZOID)
            return node;
        else if (node->type == NodeType::POINT) {
            // 0 if to the left, 1 if to the right
            int d = dcmp(seg->end->pos.x - node->point->pos.x);
            // If they are the same then force to the left
            if (d == 1) d = 1;
            else d = 0;
            return _queryEnd(node->ch[d], seg);
        }
        else if (node->type == NodeType::SEGMENT) {
            // 0 if above, 1 if below
            int d = node->segment->to_left(seg->end->pos);
            if (d == 1) d = 0;
            else if (d == -1) d = 1;
            else {
                // if the slope of seg is less than the slope of judging seg then it is above
                d = dcmp(seg->slope() - node->segment->slope()) > 0;
            }
            return _queryEnd(node->ch[d], seg);
        }
        return node;
    }


    Node* query(Node* node, const Vector2& pos) {
        if (node->type == NodeType::TRAPOZOID)
            return node;
        else if (node->type == NodeType::POINT) {
            int d = dcmp(pos.x - node->point->pos.x);
            if (d == 1) d = 1;
            else d = 0;
            return query(node->ch[d], pos);
        }
        else if (node->type == NodeType::SEGMENT) {
            int d = node->segment->to_left(pos);
            if (d == 1) d = 0;
            else d = 1;
            return query(node->ch[d], pos);
        }
        return node;
    }

    void init(const Vector2& botLeft, const Vector2& topRight) {
        // Reserve enough space for object pool
        endPoints.reserve(1024);
        segments.reserve(1024);
        trapozoids.reserve(1024);

        // Create global top and bottom segment, and the global Trapozoid
        auto gTop = createSegment(Vector2(botLeft.x, topRight.y), topRight);
        auto gBot = createSegment(botLeft, Vector2(topRight.x, botLeft.y));
        _root = createTrapozoid(Trapozoid(botLeft, topRight, gTop, gBot));
    }


    void report() {
        for (auto t : trapozoids) {
            if (t.zeroArea()) std::cout << "ERROR" << std::endl;
            std::cout << "{";
            for (int i = 0; i < 4; i++) std::cout << t.corner[i] << " ";
            std::cout << "}\n";
        }
    }
};

class TrapozoidalMapScene : public Scene {
public:
    TrapozoidalMapScene();
    ~TrapozoidalMapScene() override;

    void simulate(float delta);
    void update(float delta) override;
    void draw(float delta) override;

private:
    TrapozoidalMap _map;
};
