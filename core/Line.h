#pragma once

#include "GameObject.h"

class Line : public GameObject {
private:
    Vector2 startPoint;
    Vector2 endPoint;
    float thickness;

public:
    Line();
    Line(const Vector2& start, const Vector2& end, float thick = 1.0f);

    // 선 설정
    void SetPoints(const Vector2& start, const Vector2& end);
    void SetStartPoint(const Vector2& start) { startPoint = start; }
    void SetEndPoint(const Vector2& end) { endPoint = end; }
    void SetThickness(float thick) { thickness = thick; }

    const Vector2& GetStartPoint() const { return startPoint; }
    const Vector2& GetEndPoint() const { return endPoint; }
    float GetThickness() const { return thickness; }

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;
};