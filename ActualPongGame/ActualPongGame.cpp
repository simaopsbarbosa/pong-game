#include <iostream>
#include <raylib.h>

#define PIE 3.14159265

using namespace std;

const int screenWidth = 900;
const int screenHeight = 600;
Color MAINCOLOR = {255,255,255,230};
Color BACKGROUNDCOLOR = BLACK;

class Ball {
public:
    float x;
    float y;
    int angle; 
    int speed;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, MAINCOLOR);
    };

    void Update() {
        x += cos(angle * PIE / 180.0) * speed;
        y += sin(angle * PIE / 180.0) * speed;
    };

    void CheckCollision() {
        if (y + radius < 0) {
            // hits top
            angle = -angle;
        }
        if (y + radius > screenHeight) {
            // hits bottom
            angle = -angle;
        }
    }

    void CheckPlayerCollision() {
        if ()
    }

    bool GameOver() {
        if (x + radius > screenWidth) {
            // hits right
            return true;
        }
        if (y - radius < 0) {
            // hits left
            return true;
        }
        return false;
    }

};

class Player {
public:
    int x;
    float y;
    int speed;
    int width;
    int height;

    void Draw() {
        DrawRectangle(x - (width / 2), y - (height / 2), width, height, MAINCOLOR);
    };
};

int main() {

    cout << "Starting Game" << endl;
    InitWindow(screenWidth, screenHeight, "[PONG]");
    SetTargetFPS(60);

    Ball ball;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.radius = 10;
    ball.speed = 5;
    ball.angle = 60;

    int playersSpacing = 30;

    Player p1;
    p1.width = 20;
    p1.height = 140;
    p1.x = playersSpacing;
    p1.y = (screenHeight / 2); 

    Player p2;
    p2.width = 20;
    p2.height = 140;
    p2.x = screenWidth - playersSpacing;
    p2.y = (screenHeight / 2);


    while (!WindowShouldClose()) {
        // main loop
        
        if (not ball.GameOver()) {
            ball.Update();
            ball.CheckCollision();
        }

        BeginDrawing();
        ClearBackground(BACKGROUNDCOLOR);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, { 255,255,255,30 });
        DrawCircleLines(screenWidth / 2, screenHeight / 2, 120, { 255,255,255,30 });
        ball.Draw();
        p1.Draw();
        p2.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}