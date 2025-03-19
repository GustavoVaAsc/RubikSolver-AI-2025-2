#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "search.cpp"

const int CUBE_SIZE = 3;



// Colors for the cube
SDL_Color green = {0, 255, 0, 255};     // Green - 0
SDL_Color white = {255, 255, 255, 255}; // White - 1
SDL_Color blue = {0, 0, 255, 255};      // Blue - 2
SDL_Color yellow = {255, 255, 0, 255};  // Yellow - 3
SDL_Color orange = {255, 165, 0, 255};  // Orange - 4
SDL_Color red = {255, 0, 0, 255};       // Red - 5

SDL_Color colorMap[6] = {
    green,   // 0: green
    white,   // 1: white
    blue,    // 2: blue
    yellow,  // 3: yellow 
    orange,  // 4: orange
    red      // 5: red
};

// Matrix for transform color to number
SDL_Color cube[6][CUBE_SIZE][CUBE_SIZE];
int cube_number[6][CUBE_SIZE][CUBE_SIZE];



// Function to draw a square with a specific color
void drawSquare(SDL_Renderer* renderer, int x, int y, int size, SDL_Color color) {
    SDL_Rect rect = {x, y, size, size};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

// Function to draw a face (a 3x3 grid of squares)
void drawFace(SDL_Renderer* renderer, int startX, int startY, int squareSize, SDL_Color colors[CUBE_SIZE][CUBE_SIZE]) {
    for (int row = 0; row < CUBE_SIZE; ++row) {
        for (int col = 0; col < CUBE_SIZE; ++col) {
            drawSquare(renderer, startX + col * squareSize, startY + row * squareSize, squareSize, colors[row][col]);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int row = 1; row < CUBE_SIZE; ++row) {
        SDL_RenderDrawLine(renderer, startX, startY + row * squareSize, startX + squareSize * CUBE_SIZE, startY + row * squareSize);
    }

    for (int col = 1; col < CUBE_SIZE; ++col) {
        SDL_RenderDrawLine(renderer, startX + col * squareSize, startY, startX + col * squareSize, startY + squareSize * CUBE_SIZE);
    }
}

// Function to check if the mouse click is inside a square
bool isInside(int x, int y, int mouseX, int mouseY, int squareSize) {
    return mouseX >= x && mouseX <= x + squareSize && mouseY >= y && mouseY <= y + squareSize;
}

// Function to check if the mouse is hovering over the button
bool isButtonHovered(int buttonX, int buttonY, int buttonSize, int mouseX, int mouseY) {
    return mouseX >= buttonX && mouseX <= buttonX + buttonSize && mouseY >= buttonY && mouseY <= buttonY + buttonSize;
}

// Function to convert color to
int getColorIndex(SDL_Color color) {
    if (color.r == green.r && color.g == green.g && color.b == green.b && color.a == green.a) {
        return 0;
    } else if (color.r == white.r && color.g == white.g && color.b == white.b && color.a == white.a) {
        return 1;
    } else if (color.r == blue.r && color.g == blue.g && color.b == blue.b && color.a == blue.a) {
        return 2;
    } else if (color.r == yellow.r && color.g == yellow.g && color.b == yellow.b && color.a == yellow.a) {
        return 3;
    } else if (color.r == orange.r && color.g == orange.g && color.b == orange.b && color.a == orange.a) {
        return 4;
    } else if (color.r == red.r && color.g == red.g && color.b == red.b && color.a == red.a) {
        return 5;
    }
    return -1;
}

// Add before main()
void updateUICube(Cube& cube, 
    SDL_Color frontFace[CUBE_SIZE][CUBE_SIZE],
    SDL_Color backFace[CUBE_SIZE][CUBE_SIZE],
    SDL_Color leftFace[CUBE_SIZE][CUBE_SIZE],
    SDL_Color rightFace[CUBE_SIZE][CUBE_SIZE],
    SDL_Color topFace[CUBE_SIZE][CUBE_SIZE],
    SDL_Color bottomFace[CUBE_SIZE][CUBE_SIZE]) {
    // Map solver cube faces to UI components
    const int faceMap[6] = {0, 4, 2, 5, 1, 3}; // Adjust based on your cube's face orientation

    for(int face = 0; face < 6; face++) {
        for(int row = 0; row < CUBE_SIZE; row++) {
            for(int col = 0; col < CUBE_SIZE; col++) {
                int colorIdx = cube.cube[face][row][col].color;
                SDL_Color color = colorMap[colorIdx];
            
                switch(faceMap[face]) {
                    case 0: frontFace[row][col] = color; break;
                    case 1: backFace[row][col] = color; break;
                    case 2: leftFace[row][col] = color; break;
                    case 3: rightFace[row][col] = color; break;
                    case 4: topFace[row][col] = color; break;
                    case 5: bottomFace[row][col] = color; break;
                }
            }
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window* window = SDL_CreateWindow("Rubik Cube by ChatGPI",
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           900, 700, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Error creating the window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Error creating the renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load button images
    SDL_Surface* buttonSurface = IMG_Load("RubikNotSolveButton.jpg");
    if (buttonSurface == nullptr) {
        std::cerr << "Error loading button image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* buttonHoverSurface = IMG_Load("RandomFace.jpg");
    if (buttonHoverSurface == nullptr) {
        std::cerr << "Error loading hover button image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* buttonSurfaceSolve = IMG_Load("RubikSolveButton.jpg");
    if (buttonSurface == nullptr) {
        std::cerr << "Error loading button image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* buttonHoverSolve = IMG_Load("SolveFace.jpg");
    if (buttonSurface == nullptr) {
        std::cerr << "Error loading button image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create textures from surfaces
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    if (buttonTexture == nullptr) {
        std::cerr << "Error creating texture for button: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(buttonSurface);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* buttonHoverTexture = SDL_CreateTextureFromSurface(renderer, buttonHoverSurface);
    if (buttonHoverTexture == nullptr) {
        std::cerr << "Error creating hover texture for button: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(buttonSurface);
        SDL_FreeSurface(buttonHoverSurface);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* buttonTextureSolve = SDL_CreateTextureFromSurface(renderer, buttonSurfaceSolve);
    if (buttonTexture == nullptr) {
        std::cerr << "Error creating texture for button: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(buttonSurfaceSolve);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* buttonHoverTextureSolve = SDL_CreateTextureFromSurface(renderer, buttonHoverSolve);
    if (buttonHoverTexture == nullptr) {
        std::cerr << "Error creating hover texture for button: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(buttonSurfaceSolve);
        SDL_FreeSurface(buttonHoverSolve);
        SDL_Quit();
        return 1;
    }

    // Free surfaces after creating textures
    SDL_FreeSurface(buttonSurface);
    SDL_FreeSurface(buttonHoverSurface);
    SDL_FreeSurface(buttonSurfaceSolve);
    SDL_FreeSurface(buttonHoverSolve);

    // Initialize the colors for the cube
    SDL_Color leftFace[CUBE_SIZE][CUBE_SIZE] = { {green, green, green}, {green, green, green}, {green, green, green} };  // Green - 0
    SDL_Color frontFace[CUBE_SIZE][CUBE_SIZE] = { {white, white, white}, {white, white, white}, {white, white, white} };  // White - 1
    SDL_Color rightFace[CUBE_SIZE][CUBE_SIZE] = { {blue, blue, blue}, {blue, blue, blue}, {blue, blue, blue} };  // Blue - 2
    SDL_Color backFace[CUBE_SIZE][CUBE_SIZE] = { {yellow, yellow, yellow}, {yellow, yellow, yellow}, {yellow, yellow, yellow} };  // Yellow - 3
    SDL_Color topFace[CUBE_SIZE][CUBE_SIZE] = { {orange, orange, orange}, {orange, orange, orange}, {orange, orange, orange} };  // Orange - 4
    SDL_Color bottomFace[CUBE_SIZE][CUBE_SIZE] = { {red, red, red}, {red, red, red}, {red, red, red} };  // Red - 5

    // Define the list of colors to cycle through
    std::vector<SDL_Color> colorCycle = {red, green, blue, yellow, orange, white};

    // Keep track of the current color index for each face
    int colorIndex[CUBE_SIZE][CUBE_SIZE] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

    bool running = true;
    SDL_Event event;
    int squareSize = 40;

    // Calculate the center of the window (900x700) and center the cube
    int startX = (900 / 2) - (squareSize * 3.5);
    int startY = (700 / 2) - (squareSize * 4);

    int buttonSize = 150;
    int buttonX = (1050 - buttonSize) / 2; // Center horizontally
    int buttonY = 500; // Place the button at the bottom

    int buttonSizeSolve = 150;
    int buttonXSolve = (700 - buttonSize) / 2;
    int buttonYSolve = 500;

    // Inside main(), before the main loop:
    Cube initialCube;
    updateUICube(initialCube, frontFace, backFace, leftFace, rightFace, topFace, bottomFace);
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Detect if the click was on a square
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Inside SDL_MOUSEBUTTONDOWN event handler:
                if (isButtonHovered(buttonX, buttonY, buttonSize, mouseX, mouseY)) {
                    // Initialize and randomize cube
                    Graph rubiksCube = Graph();
                    rubiksCube.game.reset();
                    rubiksCube.randomize();
                    
                    // Update UI with new cube state
                    updateUICube(rubiksCube.game, frontFace, backFace, leftFace, rightFace, topFace, bottomFace);
                    
                    // Print numerical representation (optional)
                    for(int f = 0; f < 6; f++) {
                        std::cout << "Face " << f << ":\n";
                        for(int r = 0; r < CUBE_SIZE; r++) {
                            for(int c = 0; c < CUBE_SIZE; c++) {
                                std::cout << rubiksCube.game.cube[f][r][c].color << " ";
                            }
                            std::cout << "\n";
                        }
                    }
                }
            }
        }

        // Get the mouse coordinates
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Render the scene
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw all faces
        drawFace(renderer, startX, startY, squareSize, frontFace);   // White face
        drawFace(renderer, startX + 300, startY, squareSize, backFace);   // Yellow face
        drawFace(renderer, startX - 150, startY, squareSize, leftFace);   // Green face
        drawFace(renderer, startX + 150, startY, squareSize, rightFace);  // Blue face
        drawFace(renderer, startX, startY - 150, squareSize, topFace);    // Orange face
        drawFace(renderer, startX, startY + 150, squareSize, bottomFace);  // Red face

        // Define the rectangle for the button
        SDL_Rect buttonRect = {buttonX, buttonY, buttonSize, buttonSize};
        SDL_Rect buttonRectSolve = {buttonXSolve, buttonYSolve, buttonSizeSolve, buttonSizeSolve};

        // Draw the button
        if (isButtonHovered(buttonX, buttonY, buttonSize, mouseX, mouseY)) {
            SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
        } else {
            SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        }

        if (isButtonHovered(buttonXSolve, buttonYSolve, buttonSizeSolve, mouseX, mouseY)) {
            SDL_RenderCopy(renderer, buttonHoverTextureSolve, NULL, &buttonRectSolve);
        } else {
            SDL_RenderCopy(renderer, buttonTextureSolve, NULL, &buttonRectSolve);
        }

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
