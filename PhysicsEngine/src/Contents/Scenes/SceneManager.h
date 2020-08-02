#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "Scene.h"


class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void update(float dt);
    void draw(float dt);

private:
    std::shared_ptr<Scene> _currentScene;
    std::map<std::string, std::shared_ptr<Scene>> _sceneMap;
};
