#pragma once

#include "raylib.h"

class Game;

class Scene {
protected:
    Game* game;

public:
    Scene(Game* gameInstance) : game(gameInstance) {}
    virtual ~Scene() = default;

    // 씬 초기화 (필요시 오버라이드)
    virtual void Initialize() {}

    // 매 프레임 업데이트
    virtual void Update(float deltaTime) = 0;

    // 렌더링
    virtual void Render() = 0;

    // 씬 종료 (필요시 오버라이드)
    virtual void Shutdown() {}
};