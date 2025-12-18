#pragma once

#include "GameObject.h"
#include <string>

class SpriteImage : public GameObject {
private:
    Texture2D texture;
    Rectangle sourceRect;
    bool textureLoaded;

public:
    SpriteImage();
    SpriteImage(const std::string& imagePath);
    ~SpriteImage() override;

    // 이미지 로드/언로드
    bool LoadFromFile(const std::string& imagePath);
    void Unload();

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;

    // 이미지 속성
    int GetWidth() const { return textureLoaded ? texture.width : 0; }
    int GetHeight() const { return textureLoaded ? texture.height : 0; }
    bool IsLoaded() const { return textureLoaded; }

    // 소스 영역 설정 (스프라이트 시트용)
    void SetSourceRect(float x, float y, float width, float height);
    void SetSourceRect(const Rectangle& rect);
};