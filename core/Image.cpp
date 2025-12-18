#include "Image.h"

SpriteImage::SpriteImage() : textureLoaded(false) {
    sourceRect = {0, 0, 0, 0};
}

SpriteImage::SpriteImage(const std::string& imagePath) : SpriteImage() {
    LoadFromFile(imagePath);
}

SpriteImage::~SpriteImage() {
    Unload();
}

bool SpriteImage::LoadFromFile(const std::string& imagePath) {
    if (textureLoaded) {
        Unload();
    }

    ::Image img = LoadImage(imagePath.c_str());
    if (img.data == nullptr) {
        return false;
    }

    texture = LoadTextureFromImage(img);
    textureLoaded = (texture.id > 0);

    if (textureLoaded) {
        sourceRect = {0, 0, (float)texture.width, (float)texture.height};
    }

    UnloadImage(img);
    return textureLoaded;
}

void SpriteImage::Unload() {
    if (textureLoaded) {
        UnloadTexture(texture);
        textureLoaded = false;
        sourceRect = {0, 0, 0, 0};
    }
}

void SpriteImage::Render() const {
    if (!visible || !textureLoaded) return;

    Rectangle destRect = {
        position.x, position.y,
        sourceRect.width * scale.x,
        sourceRect.height * scale.y
    };

    Vector2 origin = {sourceRect.width * scale.x * 0.5f, sourceRect.height * scale.y * 0.5f};

    DrawTexturePro(texture, sourceRect, destRect, origin, rotation, tint);
}

Rectangle SpriteImage::GetBounds() const {
    if (!textureLoaded) return {position.x, position.y, 0, 0};

    return {
        position.x - (sourceRect.width * scale.x * 0.5f),
        position.y - (sourceRect.height * scale.y * 0.5f),
        sourceRect.width * scale.x,
        sourceRect.height * scale.y
    };
}

void SpriteImage::SetSourceRect(float x, float y, float width, float height) {
    sourceRect = {x, y, width, height};
}

void SpriteImage::SetSourceRect(const Rectangle& rect) {
    sourceRect = rect;
}