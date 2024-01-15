//REG:2021831011
//NAME:MARIA
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

// Function to draw a filled circle on the SDL renderer
void drawFilledCircle(SDL_Renderer* renderer, int centerpointX, int centerpointY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Loop through the x and y coordinates within the bounding box of the circle
    for (int x = centerpointX - radius; x <= centerpointX + radius; x++) {
        for (int y = centerpointY - radius; y <= centerpointY + radius; y++) {
            // Calculate the distance^2=(x1-x2)^2 +(y1-y2)^2 from the center to the current point (x, y)
            int d = (x - centerpointX) * (x - centerpointX) + (y - centerpointY) * (y - centerpointY);

            // If the distance is less than or equal to the radius squared, it's inside the circle
            if (d <= radius * radius) {
                // Draw a point at (x, y)
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    // Present the renderer to update the screen
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create an SDL window and renderer
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    // Set the clear color for the renderer (background color)
    SDL_SetRenderDrawColor(renderer, 255,0 , 250, 255);

    // Clear the renderer with the background color
    SDL_RenderClear(renderer);

    // Define a rectangle
    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 640 / 2;
    rect.y = 480 / 2;

    // Set the draw color for the renderer (rectangle color)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Define a color for the circle
    SDL_Color color = {0, 0, 255};

    // Call the function to draw a filled circle
    drawFilledCircle(renderer, 320, 240, 100, color);

    // Present the renderer to update the screen
    SDL_RenderPresent(renderer);

    // Delay for 10 seconds before exiting
    SDL_Delay(10000);

    // Clean up and exit
    return 0;
}