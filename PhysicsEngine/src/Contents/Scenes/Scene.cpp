#include <iostream>

#include "Scene.h"
#include "MassSpringScene.h"


std::shared_ptr<Scene> Scene::makeScene(const std::string& name) {
    if (name == "Mass Spring") {
        return std::make_shared<MassSpringScene>();
    }
}

Scene::~Scene() {
    std::cout << "Scene has been released" << std::endl;
}
