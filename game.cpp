#include <iostream>
#include <SDL.h>
#include <vector>
#include <random>
#include <ctime>

const int GRID_SIZE = 20;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;

const int SCREEN_WIDTH = GRID_WIDTH * GRID_SIZE;
const int SCREEN_HEIGHT = GRID_HEIGHT * GRID_SIZE;

const int SNAKE_SPEED = 200;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Colors
const SDL_Color BG_COLOR = { 0, 0, 0, 255 };
const SDL_Color SNAKE_COLOR = { 0, 255, 0, 255 };
const SDL_Color FOOD_COLOR = { 255, 0, 0, 255 };

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct SnakeSegment {
    int x, y;
};

std::vector<SnakeSegment> snake;
SDL_Point food;
Direction snakeDirection = Direction::RIGHT;

void GenerateFood() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> randomX(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<int> randomY(0, GRID_HEIGHT - 1);

    int foodX, foodY;
    do {
        foodX = randomX(eng);
        foodY = randomY(eng);
    } while (std::find(snake.begin(), snake.end(), SnakeSegment{ foodX, foodY }) != snake.end());

    food.x = foodX;
    food.y = foodY;
}

bool CheckCollision() {
    int headX = snake[0].x;
    int headY = snake[0].y;

    if (headX < 0 || headX >= GRID_WIDTH || headY < 0 || headY >= GRID_HEIGHT) {
        return true; // Hit the wall
    }

    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == headX && snake[i].y == headY) {
            return true; // Collided with itself
        }
    }

    return false;
}

void MoveSnake() {
    int newHeadX = snake[0].x;
    int newHeadY = snake[0].y;

    if (snakeDirection == Direction::UP) {
        newHeadY--;
    } else if (snakeDirection == Direction::DOWN) {
        newHeadY++;
    } else if (snakeDirection == Direction::LEFT) {
        newHeadX--;
    } else if (snakeDirection == Direction::RIGHT) {
        newHeadX++;
    }

    snake.insert(snake.begin(), SnakeSegment{ newHeadX, newHeadY });

    if (newHeadX == food.x && newHeadY == food.y) {
        GenerateFood();
    } else {
        snake.pop_back();
    }
}

void Render() {
    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);

    // Draw Snake
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR.r, SNAKE_COLOR.g, SNAKE_COLOR.b, SNAKE_COLOR.a);
    for (const SnakeSegment& segment : snake) {
        SDL_Rect rect{ segment.x * GRID_SIZE, segment.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw Food
    SDL_SetRenderDrawColor(renderer, FOOD_COLOR.r, FOOD_COLOR.g, FOOD_COLOR.b, FOOD_COLOR.a);
    SDL_Rect foodRect{ food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &foodRect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    snake.push_back({ GRID_WIDTH / 2, GRID_HEIGHT / 2 });
    GenerateFood();

    bool quit = false;
    SDL_Event e;
    unsigned int lastMoveTime = 0;

    while (!quit) {
        unsigned int currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (snakeDirection != Direction::DOWN) {
                        snakeDirection = Direction::UP;
                    }
                    break;
                case SDLK_DOWN:
                    if (snakeDirection != Direction::UP) {
                        snakeDirection = Direction::DOWN;
                    }
                    break;
                case SDLK_LEFT:
                    if (snakeDirection != Direction::RIGHT) {
                        snakeDirection = Direction::LEFT;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snakeDirection != Direction::LEFT) {
                        snakeDirection = Direction::RIGHT;
                    }
                    break;
                }
            }
        }

        if (currentTime - lastMoveTime >= SNAKE_SPEED) {
            lastMoveTime = currentTime;
            MoveSnake();
            if (CheckCollision()) {
                break;
            }
            Render();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
