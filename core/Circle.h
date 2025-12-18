#pragma once

#include "GameObject.h"

class Circle : public GameObject {
private:
    float radius;

public:
    Circle();
    explicit Circle(float r);

    // 반지름 설정
    void SetRadius(float r) { radius = r; }
    float GetRadius() const { return radius; }

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;
};