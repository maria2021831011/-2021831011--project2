//game over and score show terminal

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 20;
struct SnakeSegment {
    int x, y;
};
// Class to Snake Game

class SnakeGame {
public:
    SnakeGame();
    void run();
private:
    void handleInput();
    void update();
    void render();
    void spawnFood();
    bool checkCollision();
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SnakeSegment> snake;
    SnakeSegment food;
    int direction; 
    int score;
    bool gameOver;
};
// Constructor initializes SDL and sets up the game
SnakeGame::SnakeGame() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    snake.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    direction = 3; 
    score = 0;
    gameOver = false;
    srand(time(NULL)); 
    spawnFood();
}
// Main game loop running
void SnakeGame::run() {
    SDL_Event e;
    while (!gameOver) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gameOver = true;
            }
        }
        handleInput();
        update();
        render();
        SDL_Delay(190);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
 //Handle keyboard input to change the direction of the snake
void SnakeGame::handleInput() {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP] && direction != 1) {
        direction = 0;
    }
    else if (keys[SDL_SCANCODE_DOWN] && direction != 0) {
        direction = 1;
    }
    else if (keys[SDL_SCANCODE_LEFT] && direction != 3) {
        direction = 2;
    }
    else if (keys[SDL_SCANCODE_RIGHT] && direction != 2) {
        direction = 3;
    }
}
// Update the game 
void SnakeGame::update() {
    if (gameOver) {
        return;
    }
    SnakeSegment newHead = snake.front();
    switch (direction) {
        case 0:
            newHead.y -= GRID_SIZE;
            break;
        case 1:
            newHead.y += GRID_SIZE;
            break;
        case 2:
            newHead.x -= GRID_SIZE;
            break;
        case 3:
            newHead.x += GRID_SIZE;
            break;
    }
    snake.insert(snake.begin(), newHead);
    if (newHead.x == food.x && newHead.y == food.y) {
        spawnFood();
        score++;
    } else {
        snake.pop_back();
    }
    if (checkCollision()) {
        std::cout << "Game Over! Your score: " << score << std::endl;
        SDL_Delay(2000); 
        gameOver = true;
    }
}
// Render the game on the screen
void SnakeGame::render() {
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (const auto& segment : snake) {
        SDL_Rect rect = {segment.x, segment.y, GRID_SIZE, GRID_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect foodRect = {food.x, food.y, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(renderer, &foodRect);
    SDL_RenderPresent(renderer);
}
//food position and create
void SnakeGame::spawnFood() {
    int maxX = (SCREEN_WIDTH / GRID_SIZE - 1) * GRID_SIZE;
    int maxY = (SCREEN_HEIGHT / GRID_SIZE - 1) * GRID_SIZE;
    int randX = GRID_SIZE * (1 + rand() % (maxX / GRID_SIZE));
    int randY = GRID_SIZE * (1 + rand() % (maxY / GRID_SIZE));
    food = {randX, randY};
}
bool SnakeGame::checkCollision() {
    // Check collision with walls
    if (snake.front().x < 0 || snake.front().x >= SCREEN_WIDTH || snake.front().y < 0 || snake.front().y >= SCREEN_HEIGHT) {
        return true;
    }
    // Check collision with itself
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == snake.front().x && snake[i].y == snake.front().y) {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[]) {
    SnakeGame game;
    game.run();
    return 0;
}