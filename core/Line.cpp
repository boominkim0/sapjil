#include "Line.h"

Line::Line() : thickness(1.0f) {
    startPoint = {0, 0};
    endPoint = {100, 0};
}

Line::Line(const Vector2& start, const Vector2& end, float thick)
    : startPoint(start), endPoint(end), thickness(thick) {
}

void Line::SetPoints(const Vector2& start, const Vector2& end) {
    startPoint = start;
    endPoint = end;
}

void Line::Render() const {
    if (!visible) return;

    // 부모 변환 적용
    Vector2 transformedStart = startPoint;
    Vector2 transformedEnd = endPoint;

    if (rotation != 0.0f || scale.x != 1.0f || scale.y != 1.0f) {
        // 회전과 스케일 적용
        rlPushMatrix();
        rlTranslatef(position.x, position.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlScalef(scale.x, scale.y, 1);

        DrawLineEx({0, 0}, {endPoint.x - startPoint.x, endPoint.y - startPoint.y},
                 thickness, tint);

        rlPopMatrix();
    } else {
        // 단순 이동만 적용
        transformedStart.x += position.x;
        transformedStart.y += position.y;
        transformedEnd.x += position.x;
        transformedEnd.y += position.y;

        DrawLineEx(transformedStart, transformedEnd, thickness, tint);
    }
}

Rectangle Line::GetBounds() const {
    float minX = std::min(startPoint.x, endPoint.x) + position.x;
    float minY = std::min(startPoint.y, endPoint.y) + position.y;
    float maxX = std::max(startPoint.x, endPoint.x) + position.x;
    float maxY = std::max(startPoint.y, endPoint.y) + position.y;

    // 선의 두께를 고려한 bounds 확장
    float halfThickness = thickness * 0.5f;
    minX -= halfThickness;
    minY -= halfThickness;
    maxX += halfThickness;
    maxY += halfThickness;

    return {
        minX,
        minY,
        maxX - minX,
        maxY - minY
    };
}