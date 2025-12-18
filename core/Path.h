#pragma once

#include "GameObject.h"
#include <vector>

struct PathPoint {
    Vector2 position;
    float thickness;
    Color color;

    PathPoint() : thickness(1.0f), color(WHITE) {}
    PathPoint(const Vector2& pos, float thick = 1.0f, Color col = WHITE)
        : position(pos), thickness(thick), color(col) {}
};

class Path : public GameObject {
private:
    std::vector<PathPoint> pathPoints;
    bool smooth;

public:
    Path();
    Path(const std::vector<Vector2>& points, bool isSmooth = false);

    // 경로 설정
    void SetPoints(const std::vector<Vector2>& points);
    void AddPoint(const Vector2& point, float thickness = 1.0f, Color color = WHITE);
    void AddPoint(const PathPoint& point);
    void ClearPoints();

    const std::vector<PathPoint>& GetPoints() const { return pathPoints; }
    size_t GetPointCount() const { return pathPoints.size(); }

    // 부드러운 곡선 여부
    void SetSmooth(bool isSmooth) { smooth = isSmooth; }
    bool IsSmooth() const { return smooth; }

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;
};