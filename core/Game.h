#pragma once

#include "raylib.h"
#include <memory>
#include <string>
#include "Scene.h"

class Game {
private:
    int screenWidth;
    int screenHeight;
    std::string title;
    std::unique_ptr<Scene> currentScene;
    bool isRunning;

public:
    Game(int width, int height, const std::string& windowTitle);
    ~Game();

    // 게임 초기화
    bool Initialize();

    // 메인 게임 루프
    void Run();

    // 씬 변경 (템플릿을 사용해서 다형성 지원)
    template<typename T>
    void ChangeScene(std::unique_ptr<T> newScene) {
        static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
        currentScene = std::unique_ptr<Scene>(std::move(newScene));
        if (currentScene) {
            currentScene->Initialize();
        }
    }

    // 게임 종료
    void Quit();

    // Getter들
    int GetScreenWidth() const { return screenWidth; }
    int GetScreenHeight() const { return screenHeight; }
    const std::string& GetTitle() const { return title; }
    bool IsRunning() const { return isRunning; }
};