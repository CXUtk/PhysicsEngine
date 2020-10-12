#include <iostream>

#include "Scene.h"
#include "MassSpringScene.h"
#include "Contents/Scenes/TrapozoidalMapScene.h"


std::shared_ptr<Scene> Scene::makeScene(const std::string& name) {
    if (name == "Mass Spring") {
        return std::make_shared<TrapozoidalMapScene>();
    }
}

Scene::~Scene() {
    std::cout << "Scene has been released" << std::endl;
}
