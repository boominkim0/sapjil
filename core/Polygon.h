#pragma once

#include "GameObject.h"
#include <vector>

class Polygon : public GameObject {
private:
    std::vector<Vector2> points;
    bool closed;

public:
    Polygon();
    Polygon(const std::vector<Vector2>& verts, bool isClosed = true);

    // 점들 설정
    void SetPoints(const std::vector<Vector2>& verts);
    void AddPoint(const Vector2& point);
    void ClearPoints();

    const std::vector<Vector2>& GetPoints() const { return points; }
    size_t GetPointCount() const { return points.size(); }

    // 폐곡선 여부
    void SetClosed(bool isClosed) { closed = isClosed; }
    bool IsClosed() const { return closed; }

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;
};