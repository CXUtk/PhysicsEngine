#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
class UIElement {
public:
    UIElement();
    virtual ~UIElement() = 0 {};

    virtual void drawSelf(float delta);
    virtual void drawChildren(float delta);
    void draw(float delta);
    virtual void updateSelf(float delta);
    virtual void updateChildren(float delta);
    void update(float delta);

private:
    // 代表这个UI元素是否是激活状态，如果不是激活状态则不会更新这个元素
    bool _active;

    // 这个UI元素的父节点
    std::shared_ptr<UIElement> _parent;

    // 这个UI元素的子节点
    std::vector<std::shared_ptr<UIElement>> _children;

    // 基准点，代表这个UI元素的绘制中心相对于自身的位置
    glm::vec2 _pivot;

    // 锚点，代表这个UI元素的位置相对于父容器的偏移
    glm::vec2 _anchorPoint;

    glm::vec2 _size;

    glm::vec2 _position;


};
