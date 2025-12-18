#pragma once

#include "raylib.h"
#include "core/Game.h"
#include "BouncingBallScene.h"

class BouncingBallGame {
private:
    Vector2 ballPosition;
    Vector2 ballSpeed;
    float ballRadius;
    Color ballColor;

public:
    BouncingBallGame();
    ~BouncingBallGame() = default;

    // 게임 초기화
    void Initialize(int screenWidth, int screenHeight);

    // 게임 업데이트
    void Update(float deltaTime, int screenWidth, int screenHeight);

    // 입력 처리
    void HandleInput();

    // 게임 실행 (Game 엔진을 내부적으로 관리)
    void Run();

    // Getter들
    const Vector2& GetBallPosition() const { return ballPosition; }
    float GetBallRadius() const { return ballRadius; }
    const Color& GetBallColor() const { return ballColor; }
};