#include "TrapozoidalMapScene.h"
#include "Main/Game.h"
#include "Controls/InputControls.h"

TrapozoidalMapScene::TrapozoidalMapScene() {
    // memset(&_map, 0, sizeof(_map));
    Vector2 low(0, 0), hi(100, 100);
    _map.init(low, hi);

    Vector2 seg1A(30, 60), seg1B(70, 60);
    _map.insert(seg1A, seg1B, true);

    Vector2 seg2A(5, 40), seg2B(55, 20);
    _map.insert(seg2A, seg2B, true);


    Vector2 seg3A(60, 55), seg3B(95, 15);
    _map.insert(seg3A, seg3B, true);

    Vector2 seg4A(40, 5), seg4B(95, 15);
    _map.insert(seg4A, seg4B, true);

    Vector2 seg5A(5, 40), seg5B(25, 20);
    _map.insert(seg5A, seg5B, true);

    _map.report();
}

TrapozoidalMapScene::~TrapozoidalMapScene() {
}

void TrapozoidalMapScene::simulate(float delta) {
}

void TrapozoidalMapScene::update(float delta) {
}

void TrapozoidalMapScene::draw(float delta) {
    std::vector<glm::vec2> segments;
    std::vector<glm::vec2> traplines;
    std::vector<glm::vec2> points;

    std::vector<glm::vec2> specSeg;
    for (auto endpoint : _map.endPoints) {
        points.push_back(glm::vec2(endpoint.pos.x, endpoint.pos.y));
    }
    auto mousepos = InputControls::GetInstance().getMousePos();
    int topID = _map.query(_map._root, Vector2(mousepos.x, mousepos.y))->trapozoid->top->start->segID;
    for (auto segment : _map.segments) {
        if (segment.start->segID == topID) {
            specSeg.push_back(glm::vec2(segment.start->pos.x, segment.start->pos.y));
            specSeg.push_back(glm::vec2(segment.end->pos.x, segment.end->pos.y));
        }
        else {
            segments.push_back(glm::vec2(segment.start->pos.x, segment.start->pos.y));
            segments.push_back(glm::vec2(segment.end->pos.x, segment.end->pos.y));
        }
    }
    for (int j = 0; j < _map.trapozoids.size(); j++) {
        auto& trap = _map.trapozoids[j];
        for (int i = 0; i < 4; i++) {
            points.push_back(glm::vec2(trap.corner[i].x, trap.corner[i].y));
        }
        for (int i = 0; i < 4; i++) {
            traplines.push_back(glm::vec2(trap.corner[i].x, trap.corner[i].y));
            traplines.push_back(glm::vec2(trap.corner[(i + 1) % 4].x, trap.corner[(i + 1) % 4].y));
        }
    }
    Game::GetInstance().getGraphics()->drawLines(segments, glm::vec3(1), 5);
    Game::GetInstance().getGraphics()->drawLines(traplines, glm::vec3(1, 1, 0), 1);
    Game::GetInstance().getGraphics()->drawLines(specSeg, glm::vec3(1, 0, 0), 5);
    for (auto m : points) {
        Game::GetInstance().getGraphics()->drawCircle(m, 2, glm::vec3(1, 0, 0));
        //points.push_back(m._pos);
    }
    Game::GetInstance().getGraphics()->drawCircle(mousepos, 2, glm::vec3(1, 0, 0));
}

int dcmp(double x) {

    if (fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;

}

bool segIntersection(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, double& t) {
    Vector2 a = A - B;
    Vector2 b = D - C;
    auto d = Vector2::cross(a, b);
    if (!d) return false;
    Vector2 c = D - B;
    t = Vector2::cross(c, b) / (double)d;
    if (t < 0 || t > 1) return false;
    double t2 = Vector2::cross(c, -a) / (double)d;
    if (t2 < 0 || t2 > 1) return false;
    return true;
}
