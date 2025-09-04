/*
This project uses the Raylib framework to provide us functionality for math, graphics, GUI, input etc.
See documentation here: https://www.raylib.com/, and examples here: https://www.raylib.com/examples.html
*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"

const unsigned int TARGET_FPS = 50; // frames per second
float dt = 1.0f / TARGET_FPS;// you can also use 1.f... seconds per frame... delta time (time between frames), used for movement interpolation and physics
float time = 0;
float x = 500;
float y = 500;
float frequency = 1.0f;
float amplitude = 100.0f;

void update()
{
    dt = 1.0f / TARGET_FPS;
    time += dt;

    y = y + (cos(time * frequency)) * frequency * amplitude * dt;

    x = x + (-sin(time * frequency)) * frequency * amplitude * dt;
}

void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("David Asher 101448950", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);



    GuiSliderBar(Rectangle{ 30,15, 1000, 20 }, "Time", TextFormat("%.2f", time), &time, 0, 240);
    DrawText(TextFormat("T: %6.2f seconds", time), GetScreenWidth() - 200, 10, 20, LIGHTGRAY);
	DrawCircle(x, y, 70, RED);
	DrawCircle(500 + cos(time * frequency) * amplitude,500 + sin(time * frequency) * amplitude, 70 , BLUE);


    EndDrawing();
}

int main()
{
    InitWindow(InitialWidth, InitialHeight, "GAME2005 David Asher 101448950");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
		update();
		draw();
    }

    CloseWindow();
    return 0;
}
