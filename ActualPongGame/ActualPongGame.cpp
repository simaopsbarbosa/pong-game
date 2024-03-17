#include <iostream>
#include <raylib.h>
#include <string>

using namespace std;

const int screenWidth = 900;
const int screenHeight = 600;
Color MAINCOLOR = {255,255,255,230};
Color BACKGROUNDCOLOR = BLACK;

class Ball {
public:
    float x;
    float y;
    int speedX;
    int speedY;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, MAINCOLOR);
    };

    void Update() {
        x += speedX;
        y += speedY;
    };

    void CheckCollision() {
        if (y - radius <= 0) {
            // hits top
            speedY = -speedY;
        }
        if (y + radius >= screenHeight) {
            // hits bottom
            speedY = -speedY;
        }
    }

    bool GameOver() {
        if (x + radius > screenWidth) {
            // hits right
            return true;
        }
        if (x - radius < 0) {
            // hits left
            return true;
        }
        return false;
    }

};

class Player {
public:
    float x;
    float y;
    int points;
    int speed;
    float width;
    float height;

    void Draw() {
        DrawRectangleRounded({x - (width / 2), y - (height / 2), width, height}, 1, 100, MAINCOLOR);
    };

    void Update(int player) {
        
            if (player == 1) {
                
                if (y - (height / 2) >= 0) {
                    if (IsKeyDown(KEY_W)) {
                        // move up
                        y -= speed;
                    }
                }
                
                if (y + (height / 2) <= screenHeight) {
                    if (IsKeyDown(KEY_S)) {
                        // move down
                        y += speed;
                    }
                }
            }
            else if (player == 2) {
                if (y - (height / 2) >= 0) {
                    if (IsKeyDown(KEY_UP)) {
                        // move up
                        y -= speed;
                    }
                }

                if (y + (height / 2) <= screenHeight) {
                    if (IsKeyDown(KEY_DOWN)) {
                        // move down
                        y += speed;
                    }
                }
            }
        
        
    }
};

int main() {
    InitWindow(screenWidth, screenHeight, "[PONG]");
    InitAudioDevice();
    SetTargetFPS(60);

    Sound hit = LoadSound("C:\\Users\\simao\\source\\repos\\pong-game\\hit.mp3");
   

    Ball ball;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.radius = 10;
    ball.speedX = 5;
    ball.speedY = 6;

    int playersSpacing = 30;

    Player p1;
    p1.width = 20;
    p1.height = 140;
    p1.x = playersSpacing;
    p1.y = (screenHeight / 2); 
    p1.points = 0;
    p1.speed = 7;

    Player p2;
    p2.width = 20;
    p2.height = 140;
    p2.x = screenWidth - playersSpacing;
    p2.y = (screenHeight / 2);
    p2.points = 0;
    p2.speed = 7;


    while (!WindowShouldClose()) {
        // main loop
        
        if (not ball.GameOver()) {
            ball.Update();
            ball.CheckCollision();
            p1.Update(1);
            p2.Update(2);
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {p1.x - (p1.width / 2), p1.y - (p1.height / 2), p1.width, p1.height})) {
            ball.speedX *= -1;
            p1.points++;
            PlaySound(hit);
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {p2.x - (p2.width / 2), p2.y - (p2.height / 2), p2.width, p2.height})) {
            ball.speedX *= -1;
            p2.points++;
            PlaySound(hit);
        }



        BeginDrawing();
        ClearBackground(BACKGROUNDCOLOR);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, { 255,255,255,30 });
        DrawCircleLines(screenWidth / 2, screenHeight / 2, 120, { 255,255,255,30 });
        ball.Draw();
        p1.Draw();
        p2.Draw();
        DrawText(std::to_string(p1.points).c_str(), 15, 15, 25, MAINCOLOR);
        DrawText(std::to_string(p2.points).c_str(), screenWidth - 15 - MeasureText(std::to_string(p2.points).c_str(), 25), 15, 25, MAINCOLOR);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}