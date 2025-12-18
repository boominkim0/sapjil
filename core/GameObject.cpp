#include "GameObject.h"

GameObject::GameObject()
    : position({0, 0}), scale({1, 1}), rotation(0.0f), tint(WHITE), visible(true) {
}

Matrix GameObject::GetTransformMatrix() const {
    // 변환 행렬 계산 (이동 -> 회전 -> 스케일)
    Matrix matrix = MatrixIdentity();

    // 이동
    matrix = MatrixMultiply(matrix, MatrixTranslate(position.x, position.y, 0));

    // 회전 (라디안으로 변환)
    matrix = MatrixMultiply(matrix, MatrixRotateZ(rotation * DEG2RAD));

    // 스케일
    matrix = MatrixMultiply(matrix, MatrixScale(scale.x, scale.y, 1.0f));

    return matrix;
}

bool GameObject::CheckCollision(const GameObject& other) const {
    Rectangle bounds1 = GetBounds();
    Rectangle bounds2 = other.GetBounds();

    return CheckCollisionRecs(bounds1, bounds2);
}

bool GameObject::ContainsPoint(const Vector2& point) const {
    Rectangle bounds = GetBounds();
    return CheckCollisionPointRec(point, bounds);
}