#include "Text.h"

Text::Text() : fontSize(20), customFont(false) {
    font = GetFontDefault();
}

Text::Text(const std::string& content, int size)
    : text(content), fontSize(size), customFont(false) {
    font = GetFontDefault();
}

Text::~Text() {
    if (customFont) {
        UnloadFont(font);
    }
}

void Text::SetText(const std::string& content) {
    text = content;
}

void Text::SetFontSize(int size) {
    fontSize = size;
}

bool Text::LoadFont(const std::string& fontPath, int size) {
    if (customFont) {
        UnloadFont(font);
    }

    font = LoadFontEx(fontPath.c_str(), size, nullptr, 0);
    customFont = (font.texture.id > 0);
    fontSize = size;

    return customFont;
}

void Text::UseDefaultFont() {
    if (customFont) {
        UnloadFont(font);
        customFont = false;
    }
    font = GetFontDefault();
}

void Text::Render() const {
    if (!visible || text.empty()) return;

    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);

    // 중앙 정렬을 위한 오프셋 계산
    Vector2 renderPos = {
        position.x - textSize.x * 0.5f * scale.x,
        position.y - textSize.y * 0.5f * scale.y
    };

    // 스케일과 회전 적용
    if (scale.x != 1.0f || scale.y != 1.0f || rotation != 0.0f) {
        rlPushMatrix();
        rlTranslatef(position.x, position.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlScalef(scale.x, scale.y, 1);

        DrawTextEx(font, text.c_str(), {-textSize.x * 0.5f, -textSize.y * 0.5f},
                  (float)fontSize, 1.0f, tint);

        rlPopMatrix();
    } else {
        DrawTextEx(font, text.c_str(), renderPos, (float)fontSize, 1.0f, tint);
    }
}

Rectangle Text::GetBounds() const {
    if (text.empty()) return {position.x, position.y, 0, 0};

    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);

    return {
        position.x - textSize.x * 0.5f * scale.x,
        position.y - textSize.y * 0.5f * scale.y,
        textSize.x * scale.x,
        textSize.y * scale.y
    };
}

Vector2 Text::MeasureText() const {
    return MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
}