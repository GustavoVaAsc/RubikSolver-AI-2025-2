#include <iostream>
#include <SDL2/SDL.h> 

SDL_Color green = {0, 255, 0, 255};     // Green - 0
SDL_Color white = {255, 255, 255, 255}; // White - 1
SDL_Color blue = {0, 0, 255, 255};      // Blue - 2
SDL_Color yellow = {255, 255, 0, 255};  // Yellow - 3
SDL_Color orange = {255, 165, 0, 255};  // Orange - 4
SDL_Color red = {255, 0, 0, 255};       // Red - 5

const int CUBE_SIZE = 3;

int main() {
    SDL_Color bottomFace[CUBE_SIZE][CUBE_SIZE] = {
        {red, green, white},
        {blue, yellow, orange},
        {red, red, blue}
    };

    for (int i = 0; i < CUBE_SIZE; i++) {
        for (int j = 0; j < CUBE_SIZE; j++) {
            SDL_Color color = bottomFace[i][j];

            if (color.r == green.r && color.g == green.g && color.b == green.b && color.a == green.a) {
                std::cout << "0 ";
            } else if (color.r == white.r && color.g == white.g && color.b == white.b && color.a == white.a) {
                std::cout << "1 ";
            } else if (color.r == blue.r && color.g == blue.g && color.b == blue.b && color.a == blue.a) {
                std::cout << "2 ";
            } else if (color.r == yellow.r && color.g == yellow.g && color.b == yellow.b && color.a == yellow.a) {
                std::cout << "3 ";
            } else if (color.r == orange.r && color.g == orange.g && color.b == orange.b && color.a == orange.a) {
                std::cout << "4 ";
            } else if (color.r == red.r && color.g == red.g && color.b == red.b && color.a == red.a) {
                std::cout << "5 ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
