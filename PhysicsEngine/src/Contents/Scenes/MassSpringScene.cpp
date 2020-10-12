#include <iostream>
#include <sstream>
#include <iomanip>

#include "MassSpringScene.h"
#include "Controls/InputControls.h"
#include "Main/Game.h"
#include <Graphics\Renderer\TextRenderer.h>

MassSpringScene::MassSpringScene() {
    PhysicsConfig config;
    config.gravity = glm::vec2(0, -900);
    config.stepsPerFrame = 64;

    _physics = std::make_shared<Physics>(config);
    _groundY = 100;

    _gravityGenerater = std::make_shared<GravityForceGenerator>(config.gravity);
    _dragGenerater = std::make_shared<DragForceGenerator>(1);
}

MassSpringScene::~MassSpringScene() {
}

//glm::vec2 getForceImplict(Particle& a, Particle& b, float delta, float rest_length, float elasticity) {
//    glm::vec2 p0 = a._pos - b._pos;
//    glm::vec2 unit = glm::normalize(p0);
//    p0 -= unit * 50.f;
//    float damping = 1.f;
//    float gamma = 0.5f * sqrt(4 * elasticity - damping * damping);
//    glm::vec2 c = p0 * damping / (2 * gamma) + a._velocity * (1 / gamma);
//    glm::vec2 target = p0 * cos(gamma * delta) + c * sin(gamma * delta);
//    target *= exp(-0.5f * delta * damping);
//
//    return (target - p0) * (1 / delta / delta) - a._velocity * 1.f / delta;
//}
//
//glm::vec2 getForceExplict(Particle& a, Particle& b, float delta, float rest_length, float elasticity) {
//    float dis = glm::length(b._pos - a._pos);
//    glm::vec2 n = glm::normalize(b._pos - a._pos);
//    return n * (dis - rest_length) * elasticity - a._velocity * 1.f;
//}

float _elasticity = 5000;
void MassSpringScene::simulate(float delta) {
    //int sz = _masses.size();
    _physics->updateForces(delta);
    for (auto& m : _masses) m->update(delta);
    //for (auto& m : _masses) {
    //    if (m->getPosition().y < _groundY) {
    //        m._pos.y = _groundY;
    //        m._velocity.y = 0;
    //    }
    //    m.update(delta, _physics);
    //}
}


bool isMouseDown;
void MassSpringScene::update(float delta) {
    int step = _physics->getStepsPerFrame();
    for (int i = 0; i < step; i++) {
        simulate(delta / step);
    }
    float dis = 100;

    auto& input = InputControls::GetInstance();
    if (input.isLeftClicked()) {
        int k = _masses.size();
        std::vector<std::shared_ptr<Particle>> links;
        for (int i = 0; i < k; i++) {
            if (glm::distance(_masses[i]->getPosition(), input.getMousePos()) < 50) {
                _adjancent[i].push_back(k);
                _adjancent[k].push_back(i);
                links.push_back(_masses[i]);
            }
        }
        _masses.push_back(makeNode(input.getMousePos(), false, links));
    }
    else if (input.isRightClicked()) {
        _selectedParticle.reset();
        float distance = 10;
        for (auto m : _masses) {
            float d = glm::distance(m->getPosition(), input.getMousePos());
            if (d < distance) {
                distance = d;
                _selectedParticle = m;
            }
        }
        if (!_selectedParticle) {
            std::vector<std::shared_ptr<Particle>> links;
            _masses.push_back(makeNode(input.getMousePos(), true, links));
        }
    }
    if (input.isKeyJustPress(GLFW_KEY_A)) {
        _elasticity *= 1.1f;
        std::cout << _elasticity << std::endl;
    }
    else if (input.isKeyJustPress(GLFW_KEY_D)) {
        _elasticity *= 0.9f;
        std::cout << _elasticity << std::endl;
    }
    if (input.isMouseRightDown() && _selectedParticle != nullptr) {
        _selectedParticle->setFixed(true);
        _selectedParticle->setPosition(input.getMousePos());
    }
    if (input.isMouseRightUp() && _selectedParticle != nullptr) {
        _selectedParticle->setFixed(false);
    }
}

void MassSpringScene::draw(float delta) {
    auto& input = InputControls::GetInstance();
    auto mousePos = input.getMousePos();

    auto& game = Game::GetInstance();
    game.getGraphics()->drawLine(glm::vec2(0, _groundY - 4), glm::vec2(game.getWidth(), _groundY - 4), glm::vec3(0, 0, 0), 3);

    std::vector<glm::vec2> lines;
    for (auto& m : _masses) {
        if (glm::distance(m->getPosition(), mousePos) < 50) {
            lines.push_back(mousePos);
            lines.push_back(m->getPosition());
        }
    }
    Game::GetInstance().getGraphics()->drawLines(lines, glm::vec3(1, 0, 0), 1);

    lines.clear();
    int sz = _masses.size();
    for (int i = 0; i < sz; i++) {
        for (auto j : _adjancent[i]) {
            if (j < i) continue;
            lines.push_back(_masses[i]->getPosition());
            lines.push_back(_masses[j]->getPosition());

        }
    }
    Game::GetInstance().getGraphics()->drawLines(lines, glm::vec3(1), 1);
    for (auto& m : _masses) {
        m->draw(delta);
    }

    std::vector<glm::vec2> points;
    for (auto& m : _masses) {
        Game::GetInstance().getGraphics()->drawCircle(m->getPosition(), 8, m->isFixed() ? glm::vec3(1, 1, 0) : glm::vec3(0, 1, 0));
        //points.push_back(m._pos);
    }

    auto width = Game::GetInstance().getWidth();
    auto height = Game::GetInstance().getHeight();

    std::stringstream ss;
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2);
    ss << _elasticity;
    Game::GetInstance().getGraphics()->drawText(glm::vec2(0, height - 70), ss.str(), 1, glm::vec3(0, 1, 0));
}

std::shared_ptr<Particle> MassSpringScene::makeNode(glm::vec2 pos, bool fixed, const std::vector<std::shared_ptr<Particle>>& links) {
    auto ptr = new Particle(pos, 1, fixed);
    for (auto p : links) {
        _physics->registerForce(ptr, std::make_shared<SpringForceGenerator>(p.get(), &_elasticity, 50));
        _physics->registerForce(p.get(), std::make_shared<SpringForceGenerator>(ptr, &_elasticity, 50));
    }
    _physics->registerForce(ptr, std::make_shared<GravityForceGenerator>(_physics->getGravity()));
    _physics->registerForce(ptr, std::make_shared<DragForceGenerator>(1));
    return std::shared_ptr<Particle>(ptr);
}
