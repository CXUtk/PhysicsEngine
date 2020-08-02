#include "SceneManager.h"
#include "Game.h"
#include <iostream>

// 场景的名字
std::vector<std::string> SceneNames = {
    "Mass Spring"
};

SceneManager::SceneManager() {
    for (const auto& name : SceneNames) {
        if (_sceneMap.find(name) != _sceneMap.end()) {
            throw std::exception("Repeated elements in scene names");
        }
        _sceneMap[name] = Scene::makeScene(name);
    }
    _currentScene = _sceneMap[SceneNames[0]];
}

SceneManager::~SceneManager() {
    std::cout << "SceneManager has been released" << std::endl;
}

void SceneManager::update(float dt) {
    _currentScene->update(dt);
}

void SceneManager::draw(float dt) {
    _currentScene->draw(dt);
}
