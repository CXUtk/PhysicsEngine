#include "UIElement.h"

UIElement::UIElement() :_active(true), _parent(nullptr),
_children(), _pivot(), _anchorPoint(), _size(), _position() {

}

void UIElement::drawSelf(float delta) {
}

void UIElement::drawChildren(float delta) {
    for (auto child : _children) {
        if (child->_active) child->draw(delta);
    }
}

void UIElement::draw(float delta) {

}

void UIElement::updateSelf(float delta) {

}

void UIElement::updateChildren(float delta) {
    for (auto child : _children) {
        if (child->_active) child->update(delta);
    }
}

void UIElement::update(float delta) {
    updateSelf(delta);
    updateChildren(delta);
}
