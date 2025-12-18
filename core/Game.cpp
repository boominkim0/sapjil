#include "Game.h"
#include "Scene.h"
#include <iostream>

Game::Game(int width, int height, const std::string& windowTitle)
    : screenWidth(width), screenHeight(height), title(windowTitle), isRunning(false) {
}

Game::~Game() {
    if (currentScene) {
        currentScene->Shutdown();
    }
    CloseWindow();
}

bool Game::Initialize() {
    InitWindow(screenWidth, screenHeight, title.c_str());
    if (!IsWindowReady()) {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    SetTargetFPS(60);
    isRunning = true;
    return true;
}

void Game::Run() {
    if (!isRunning) {
        std::cerr << "Game not initialized!" << std::endl;
        return;
    }

    while (!WindowShouldClose() && isRunning) {
        float deltaTime = GetFrameTime();

        // 현재 씬 업데이트
        if (currentScene) {
            currentScene->Update(deltaTime);
        }

        // 렌더링 시작
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 현재 씬 렌더링
        if (currentScene) {
            currentScene->Render();
        }

        EndDrawing();
    }

    isRunning = false;
}

void Game::Quit() {
    isRunning = false;
}