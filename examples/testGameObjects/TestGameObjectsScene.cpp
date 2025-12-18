#include "TestGameObjectsScene.h"
#include <iostream>

TestGameObjectsScene::TestGameObjectsScene(Game* gameInstance) : Scene(gameInstance) {
    screenWidth = game->GetScreenWidth();
    screenHeight = game->GetScreenHeight();
}

void TestGameObjectsScene::Initialize() {
    std::cout << "Initializing Test Game Objects Scene..." << std::endl;

    // Circle 생성
    auto circle = std::unique_ptr<GameObject>(new Circle());
    circle->SetPosition(100, 100);
    static_cast<Circle*>(circle.get())->SetRadius(30);
    circle->SetTint(RED);
    circle->SetName("Red Circle");
    gameObjects.push_back(std::move(circle));

    // Rectangle 생성
    auto rectangle = std::unique_ptr<GameObject>(new RectShape());
    rectangle->SetPosition(200, 100);
    static_cast<RectShape*>(rectangle.get())->SetSize(60, 40);
    rectangle->SetTint(BLUE);
    rectangle->SetName("Blue Rectangle");
    gameObjects.push_back(std::move(rectangle));

    // Image 생성 (로컬 파일 사용, URL 예시 주석)
    auto image = std::unique_ptr<GameObject>(new SpriteImage());
    // For web builds, you can use URLs like "https://example.com/logo.png"
    // But for desktop, use local paths like "./logo.png"
    if (static_cast<SpriteImage*>(image.get())->LoadFromFile("./logo.png")) {
        image->SetPosition(300, 100);
        image->SetName("Logo Image");
        gameObjects.push_back(std::move(image));
    } else {
        std::cout << "Failed to load image from ./logo.png" << std::endl;
        // 이미지 로드 실패 시 텍스트로 대체
        auto textImage = std::unique_ptr<GameObject>(new Text());
        textImage->SetPosition(300, 100);
        static_cast<Text*>(textImage.get())->SetText("Image not loaded");
        static_cast<Text*>(textImage.get())->SetFontSize(16);
        textImage->SetTint(RED);
        textImage->SetName("Image Placeholder");
        gameObjects.push_back(std::move(textImage));
    }

    // Text 생성
    auto text = std::unique_ptr<GameObject>(new Text());
    text->SetPosition(100, 200);
    static_cast<Text*>(text.get())->SetText("Hello, Sapjil!");
    static_cast<Text*>(text.get())->SetFontSize(20);
    text->SetTint(GREEN);
    text->SetName("Sample Text");
    gameObjects.push_back(std::move(text));

    // Line 생성
    auto line = std::unique_ptr<GameObject>(new Line());
    static_cast<Line*>(line.get())->SetStartPoint({400, 100});
    static_cast<Line*>(line.get())->SetEndPoint({500, 150});
    static_cast<Line*>(line.get())->SetThickness(3);
    line->SetTint(PURPLE);
    line->SetName("Purple Line");
    gameObjects.push_back(std::move(line));

    std::cout << "Test Game Objects Scene initialized with " << gameObjects.size() << " objects" << std::endl;
}

void TestGameObjectsScene::Update(float deltaTime) {
    // 오브젝트들 업데이트 (필요시)
    for (auto& obj : gameObjects) {
        obj->Update(deltaTime);
    }
}

void TestGameObjectsScene::Render() {
    // 배경
    ClearBackground(RAYWHITE);

    // 타이틀
    DrawText("Test Game Objects Example", 10, 10, 20, DARKGRAY);

    // 모든 오브젝트 렌더링
    for (const auto& obj : gameObjects) {
        obj->Render();
    }

    // 정보 표시
    DrawText(TextFormat("Objects: %d", (int)gameObjects.size()), 10, screenHeight - 30, 16, GRAY);
}