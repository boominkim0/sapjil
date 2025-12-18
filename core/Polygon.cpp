#include "Polygon.h"

Polygon::Polygon() : closed(true) {
}

Polygon::Polygon(const std::vector<Vector2>& verts, bool isClosed)
    : points(verts), closed(isClosed) {
}

void Polygon::SetPoints(const std::vector<Vector2>& verts) {
    points = verts;
}

void Polygon::AddPoint(const Vector2& point) {
    points.push_back(point);
}

void Polygon::ClearPoints() {
    points.clear();
}

void Polygon::Render() const {
    if (!visible || points.size() < 2) return;

    if (rotation != 0.0f || scale.x != 1.0f || scale.y != 1.0f) {
        // 변환 적용
        rlPushMatrix();
        rlTranslatef(position.x, position.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlScalef(scale.x, scale.y, 1);

        // 변환된 점들 계산
        std::vector<Vector2> transformedPoints;
        for (const auto& point : points) {
            transformedPoints.push_back(point);
        }

        if (closed && points.size() >= 3) {
            DrawTriangleFan(&transformedPoints[0], (int)transformedPoints.size(), tint);
        } else {
            for (size_t i = 0; i < transformedPoints.size() - 1; ++i) {
                DrawLineEx(transformedPoints[i], transformedPoints[i + 1], 1.0f, tint);
            }
        }

        rlPopMatrix();
    } else {
        // 단순 이동만 적용
        std::vector<Vector2> transformedPoints;
        for (const auto& point : points) {
            transformedPoints.push_back({point.x + position.x, point.y + position.y});
        }

        if (closed && points.size() >= 3) {
            DrawTriangleFan(&transformedPoints[0], (int)transformedPoints.size(), tint);
        } else {
            for (size_t i = 0; i < transformedPoints.size() - 1; ++i) {
                DrawLineEx(transformedPoints[i], transformedPoints[i + 1], 1.0f, tint);
            }
        }
    }
}

Rectangle Polygon::GetBounds() const {
    if (points.empty()) return {position.x, position.y, 0, 0};

    float minX = points[0].x + position.x;
    float minY = points[0].y + position.y;
    float maxX = minX;
    float maxY = minY;

    for (const auto& point : points) {
        float px = point.x + position.x;
        float py = point.y + position.y;

        minX = std::min(minX, px);
        minY = std::min(minY, py);
        maxX = std::max(maxX, px);
        maxY = std::max(maxY, py);
    }

    return {
        minX,
        minY,
        maxX - minX,
        maxY - minY
    };
}