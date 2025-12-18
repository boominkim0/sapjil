#include "BouncingBallGame.h"
#include <iostream>

BouncingBallGame::BouncingBallGame() : ballRadius(20.0f), ballColor(MAROON) {
}

void BouncingBallGame::Initialize(int screenWidth, int screenHeight) {
    ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
    ballSpeed = {5.0f, 4.0f};
}

void BouncingBallGame::Update(float deltaTime, int screenWidth, int screenHeight) {
    // 공 위치 업데이트
    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    // 벽 충돌 처리
    if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius)) {
        ballSpeed.x *= -1.0f;
    }
    if ((ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius)) {
        ballSpeed.y *= -1.0f;
    }
}

void BouncingBallGame::HandleInput() {
    // 마우스 클릭으로 속도 변경
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ballSpeed.x = (float)GetRandomValue(-10, 10);
        ballSpeed.y = (float)GetRandomValue(-10, 10);
    }
}

void BouncingBallGame::Run() {
    // Game 엔진 생성 및 초기화 (하드코딩된 값 사용)
    const int screenWidth = 800;
    const int screenHeight = 450;
    const std::string title = "Sapjil Game Engine";

    std::cout << "Creating Game instance..." << std::endl;
    Game game(screenWidth, screenHeight, title);

    std::cout << "Initializing game..." << std::endl;
    if (!game.Initialize()) {
        std::cout << "Game initialization failed!" << std::endl;
        return;
    }
    std::cout << "Game initialized successfully" << std::endl;

    // Bouncing Ball 씬 생성 및 설정
    std::cout << "Creating BouncingBallScene..." << std::endl;
    auto bouncingBallScene = std::make_unique<BouncingBallScene>(&game);
    std::cout << "BouncingBallScene created successfully" << std::endl;

    std::cout << "Changing scene..." << std::endl;
    game.ChangeScene(std::move(bouncingBallScene));
    std::cout << "Scene changed successfully" << std::endl;

    // 게임 실행
    std::cout << "Starting game loop..." << std::endl;
    game.Run();
    std::cout << "Game loop finished" << std::endl;
}