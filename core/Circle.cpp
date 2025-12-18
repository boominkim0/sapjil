#include "Circle.h"

Circle::Circle() : radius(50.0f) {
}

Circle::Circle(float r) : radius(r) {
}

void Circle::Render() const {
    if (!visible) return;

    // 간단하게 DrawCircleV만 사용 (스케일과 회전은 나중에 개선)
    DrawCircleV(position, radius * std::max(scale.x, scale.y), tint);
}

Rectangle Circle::GetBounds() const {
    float scaledRadius = radius * std::max(scale.x, scale.y);
    return {
        position.x - scaledRadius,
        position.y - scaledRadius,
        scaledRadius * 2,
        scaledRadius * 2
    };
}