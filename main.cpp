#include "examples/bouncingBall/BouncingBallGame.h"
#include "examples/testGameObjects/TestGameObjectsGame.h"
#include <iostream>

int main() {
    std::cout << "Starting Sapjil Game Engine..." << std::endl;

    try {
        // Test Game Objects 게임 실행
        // BouncingBallGame game;
        TestGameObjectsGame game;
        std::cout << "TestGameObjectsGame created successfully" << std::endl;

        game.Run();
        std::cout << "Game finished successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        return 1;
    }

    return 0;
}