#pragma once

#include "core/Scene.h"
#include "core/Game.h"
#include "core/GameObject.h"
#include "core/Circle.h"
#include "core/Rectangle.h"
#include "core/Image.h"
#include "core/Text.h"
#include "core/Line.h"
#include <vector>
#include <memory>

class TestGameObjectsScene : public Scene {
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    int screenWidth;
    int screenHeight;

public:
    TestGameObjectsScene(Game* gameInstance);
    ~TestGameObjectsScene() = default;

    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};