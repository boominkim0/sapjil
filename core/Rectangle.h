#pragma once

#include "GameObject.h"

class RectShape : public GameObject {
private:
    float width;
    float height;

public:
    RectShape();
    RectShape(float w, float h);

    // 크기 설정
    void SetSize(float w, float h);
    void SetWidth(float w) { width = w; }
    void SetHeight(float h) { height = h; }

    float GetWidth() const { return width; }
    float GetHeight() const { return height; }

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;
};