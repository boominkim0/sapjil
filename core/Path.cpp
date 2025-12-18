#include "Path.h"

Path::Path() : smooth(false) {
}

Path::Path(const std::vector<Vector2>& points, bool isSmooth)
    : smooth(isSmooth) {
    for (const auto& point : points) {
        pathPoints.emplace_back(point);
    }
}

void Path::SetPoints(const std::vector<Vector2>& points) {
    pathPoints.clear();
    for (const auto& point : points) {
        pathPoints.emplace_back(point);
    }
}

void Path::AddPoint(const Vector2& point, float thickness, Color color) {
    pathPoints.emplace_back(point, thickness, color);
}

void Path::AddPoint(const PathPoint& point) {
    pathPoints.push_back(point);
}

void Path::ClearPoints() {
    pathPoints.clear();
}

void Path::Render() const {
    if (!visible || pathPoints.size() < 2) return;

    if (smooth && pathPoints.size() >= 3) {
        // 베지어 곡선으로 부드럽게 렌더링
        rlPushMatrix();
        rlTranslatef(position.x, position.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlScalef(scale.x, scale.y, 1);

        for (size_t i = 0; i < pathPoints.size() - 2; i += 2) {
            if (i + 2 < pathPoints.size()) {
                DrawLineBezier(pathPoints[i].position, pathPoints[i + 2].position,
                            pathPoints[i + 1].thickness, pathPoints[i + 1].color);
            }
        }

        rlPopMatrix();
    } else {
        // 직선으로 렌더링
        if (rotation != 0.0f || scale.x != 1.0f || scale.y != 1.0f) {
            rlPushMatrix();
            rlTranslatef(position.x, position.y, 0);
            rlRotatef(rotation, 0, 0, 1);
            rlScalef(scale.x, scale.y, 1);

            for (size_t i = 0; i < pathPoints.size() - 1; ++i) {
                DrawLineEx(pathPoints[i].position, pathPoints[i + 1].position,
                         pathPoints[i].thickness, pathPoints[i].color);
            }

            rlPopMatrix();
        } else {
            for (size_t i = 0; i < pathPoints.size() - 1; ++i) {
                Vector2 start = {
                    pathPoints[i].position.x + position.x,
                    pathPoints[i].position.y + position.y
                };
                Vector2 end = {
                    pathPoints[i + 1].position.x + position.x,
                    pathPoints[i + 1].position.y + position.y
                };

                DrawLineEx(start, end, pathPoints[i].thickness, pathPoints[i].color);
            }
        }
    }
}

Rectangle Path::GetBounds() const {
    if (pathPoints.empty()) return {position.x, position.y, 0, 0};

    float minX = pathPoints[0].position.x + position.x;
    float minY = pathPoints[0].position.y + position.y;
    float maxX = minX;
    float maxY = minY;

    for (const auto& point : pathPoints) {
        float px = point.position.x + position.x;
        float py = point.position.y + position.y;

        minX = std::min(minX, px);
        minY = std::min(minY, py);
        maxX = std::max(maxX, px);
        maxY = std::max(maxY, py);
    }

    // 선의 두께를 고려한 bounds 확장
    float maxThickness = 1.0f;
    for (const auto& point : pathPoints) {
        maxThickness = std::max(maxThickness, point.thickness);
    }

    float halfThickness = maxThickness * 0.5f;
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