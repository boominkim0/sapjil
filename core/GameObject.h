#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <memory>
#include <string>
#include <vector>

class GameObject {
protected:
    Vector2 position;
    Vector2 scale;
    float rotation;
    Color tint;
    bool visible;
    std::string name;

public:
    GameObject();
    virtual ~GameObject() = default;

    // 기본 속성 설정
    void SetPosition(float x, float y) { position = {x, y}; }
    void SetPosition(const Vector2& pos) { position = pos; }
    const Vector2& GetPosition() const { return position; }

    void SetScale(float x, float y) { scale = {x, y}; }
    void SetScale(const Vector2& s) { scale = s; }
    const Vector2& GetScale() const { return scale; }

    void SetRotation(float rot) { rotation = rot; }
    float GetRotation() const { return rotation; }

    void SetTint(Color color) { tint = color; }
    Color GetTint() const { return tint; }

    void SetVisible(bool vis) { visible = vis; }
    bool IsVisible() const { return visible; }

    void SetName(const std::string& n) { name = n; }
    const std::string& GetName() const { return name; }

    // 변환 행렬 계산 (최적화를 위해)
    Matrix GetTransformMatrix() const;

    // 가상 함수들 - 각 서브클래스에서 구현
    virtual void Update(float deltaTime) {}
    virtual void Render() const = 0;
    virtual Rectangle GetBounds() const = 0;

    // 충돌 감지 헬퍼
    bool CheckCollision(const GameObject& other) const;
    bool ContainsPoint(const Vector2& point) const;
};