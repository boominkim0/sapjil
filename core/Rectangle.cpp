#include "Rectangle.h"

RectShape::RectShape() : width(100.0f), height(100.0f) {
}

RectShape::RectShape(float w, float h) : width(w), height(h) {
}

void RectShape::SetSize(float w, float h) {
    width = w;
    height = h;
}

void RectShape::Render() const {
    if (!visible) return;

    ::Rectangle rect = {
        position.x - width * 0.5f * scale.x,
        position.y - height * 0.5f * scale.y,
        width * scale.x,
        height * scale.y
    };

    if (rotation != 0.0f) {
        Vector2 origin = {width * scale.x * 0.5f, height * scale.y * 0.5f};
        DrawRectanglePro(rect, origin, rotation, tint);
    } else {
        DrawRectangleRec(rect, tint);
    }
}

Rectangle RectShape::GetBounds() const {
    return {
        position.x - width * 0.5f * scale.x,
        position.y - height * 0.5f * scale.y,
        width * scale.x,
        height * scale.y
    };
}