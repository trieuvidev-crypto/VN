#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

const int WIDTH = 800, HEIGHT = 600;

void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int delay_ms = 200) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderPresent(renderer);
    delay(delay_ms);
}

void fillRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void drawRectangle(SDL_Renderer* renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White border

    drawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y);
    drawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h);
    drawLine(renderer, rect.x + rect.w, rect.y + rect.h, rect.x, rect.y + rect.h);
    drawLine(renderer, rect.x, rect.y + rect.h, rect.x, rect.y);

    fillRect(renderer, {rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2}, {255, 0, 0});  // Red fill
}

std::vector<SDL_Point> generateStarPoints(int cx, int cy, int outerR, int innerR) {
    std::vector<SDL_Point> pts(10);
    for (int i = 0; i < 10; ++i) {
        double angle = M_PI / 5 * i - M_PI / 2;
        int r = (i % 2 == 0) ? outerR : innerR;
        pts[i].x = cx + r * cos(angle);
        pts[i].y = cy + r * sin(angle);
    }
    return pts;
}

void drawStar(SDL_Renderer* renderer, int cx, int cy, int r) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow
    int innerR = r * sin(M_PI / 10) / sin(7 * M_PI / 10);
    auto pts = generateStarPoints(cx, cy, r, innerR);

    for (size_t i = 0; i < pts.size(); ++i) {
        SDL_RenderDrawLine(renderer, pts[i].x, pts[i].y, pts[(i + 1) % pts.size()].x, pts[(i + 1) % pts.size()].y);
        SDL_RenderPresent(renderer);
        delay(150);
    }

    SDL_RenderDrawLines(renderer, pts.data(), pts.size());
    SDL_RenderPresent(renderer);
    delay(200);
    SDL_RenderDrawLine(renderer, pts.back().x, pts.back().y, pts.front().x, pts.front().y);

    SDL_RenderPresent(renderer);

    // Fill star
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    filledPolygonRGBA(renderer, pts);
}

// Helper to fill polygon (not in SDL by default)
void filledPolygonRGBA(SDL_Renderer* renderer, const std::vector<SDL_Point>& pts) {
    int minY = pts[0].y, maxY = pts[0].y;
    for (auto& p : pts) {
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> nodeX;
        for (size_t i = 0; i < pts.size(); ++i) {
            SDL_Point p1 = pts[i];
            SDL_Point p2 = pts[(i + 1) % pts.size()];
            if ((y >= p1.y && y < p2.y) || (y >= p2.y && y < p1.y)) {
                int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                nodeX.push_back(x);
            }
        }

        std::sort(nodeX.begin(), nodeX.end());
        for (size_t k = 0; k + 1 < nodeX.size(); k += 2) {
            SDL_RenderDrawLine(renderer, nodeX[k], y, nodeX[k + 1], y);
        }
    }
    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Lá cờ Tổ quốc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Rect flag = {150, 150, 500, 300};
    drawRectangle(renderer, flag);

    drawStar(renderer, flag.x + flag.w / 2, flag.y + flag.h / 2, 70);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}