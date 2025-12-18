#pragma once

#include "raylib.h"
#include "core/Game.h"
#include "TestGameObjectsScene.h"

class TestGameObjectsGame {
public:
    TestGameObjectsGame();
    ~TestGameObjectsGame() = default;

    // 게임 실행 (Game 엔진을 내부적으로 관리)
    void Run();
};