#include "examples/bouncingBall/BouncingBallGame.h"
#include <iostream>

int main() {
    std::cout << "Starting Sapjil Game Engine..." << std::endl;

    try {
        // Bouncing Ball 게임 실행
        BouncingBallGame game;
        std::cout << "BouncingBallGame created successfully" << std::endl;

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