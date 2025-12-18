#pragma once

#include "core/Scene.h"

class BouncingBallGame;

// 간단한 Bouncing Ball 씬 구현
class BouncingBallScene : public Scene {
private:
    BouncingBallGame* ballGame;
    int screenWidth;
    int screenHeight;

public:
    BouncingBallScene(Game* gameInstance);
    ~BouncingBallScene() override;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};