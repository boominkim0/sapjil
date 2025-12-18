#include "BouncingBallScene.h"
#include "BouncingBallGame.h"

BouncingBallScene::BouncingBallScene(Game* gameInstance) : Scene(gameInstance) {
    screenWidth = game->GetScreenWidth();
    screenHeight = game->GetScreenHeight();
    ballGame = new BouncingBallGame();
}

BouncingBallScene::~BouncingBallScene() {
    delete ballGame;
}

void BouncingBallScene::Initialize() {
    ballGame->Initialize(screenWidth, screenHeight);
}

void BouncingBallScene::Update(float deltaTime) {
    ballGame->HandleInput();
    ballGame->Update(deltaTime, screenWidth, screenHeight);
}

void BouncingBallScene::Render() {
    DrawText("Simple Bouncing Ball Game", 10, 10, 20, DARKGRAY);
    DrawCircleV(ballGame->GetBallPosition(), ballGame->GetBallRadius(), ballGame->GetBallColor());
}