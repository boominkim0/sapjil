#include "TestGameObjectsGame.h"
#include <iostream>

TestGameObjectsGame::TestGameObjectsGame() {
}

void TestGameObjectsGame::Run() {
    // Game 엔진 생성 및 초기화 (하드코딩된 값 사용)
    const int screenWidth = 800;
    const int screenHeight = 450;
    const std::string title = "Sapjil Game Engine - Test Game Objects";

    std::cout << "Creating Game instance..." << std::endl;
    Game game(screenWidth, screenHeight, title);

    std::cout << "Initializing game..." << std::endl;
    if (!game.Initialize()) {
        std::cout << "Game initialization failed!" << std::endl;
        return;
    }
    std::cout << "Game initialized successfully" << std::endl;

    // Test Game Objects 씬 생성 및 설정
    std::cout << "Creating TestGameObjectsScene..." << std::endl;
    auto testScene = std::make_unique<TestGameObjectsScene>(&game);
    std::cout << "TestGameObjectsScene created successfully" << std::endl;

    std::cout << "Changing scene..." << std::endl;
    game.ChangeScene(std::move(testScene));
    std::cout << "Scene changed successfully" << std::endl;

    // 게임 실행
    std::cout << "Starting game loop..." << std::endl;
    game.Run();
    std::cout << "Game loop finished" << std::endl;
}