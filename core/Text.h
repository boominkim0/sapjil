#pragma once

#include "GameObject.h"
#include <string>

class Text : public GameObject {
private:
    std::string text;
    int fontSize;
    Font font;
    bool customFont;

public:
    Text();
    Text(const std::string& content, int size = 20);
    ~Text() override;

    // 텍스트 설정
    void SetText(const std::string& content);
    const std::string& GetText() const { return text; }

    // 폰트 설정
    void SetFontSize(int size);
    int GetFontSize() const { return fontSize; }

    // 커스텀 폰트 로드
    bool LoadFont(const std::string& fontPath, int size = 20);
    void UseDefaultFont();

    // 렌더링
    void Render() const override;
    Rectangle GetBounds() const override;

    // 텍스트 측정
    Vector2 MeasureText() const;
};