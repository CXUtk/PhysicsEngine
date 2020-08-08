#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
class UIElement {
public:
    UIElement();
    virtual ~UIElement() = 0 {};

private:
    // 代表这个UI元素是否是激活状态，如果不是激活状态则不会更新这个元素
    bool _active;

    // 这个UI元素的父节点
    std::shared_ptr<UIElement> _parent;

    // 这个UI元素的子节点
    std::vector<std::shared_ptr<UIElement>> _children;


};
