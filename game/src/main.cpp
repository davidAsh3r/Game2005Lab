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
//float x = 500;
//float y = 500;
//float frequency = 1.0f;
//float amplitude = 100.0f;
float launchAngle = 45.0f;   // degrees
float launchSpeed = 180.0f;
Vector2 launchPosition = { 100, 400 };
Vector2 velocity;
Vector2 endPosition;

void update()
{
	dt = 1.0f / TARGET_FPS;

	time += dt;

	/*y = y + (cos(time * frequency)) * frequency * amplitude * dt;

	x = x + (-sin(time * frequency)) * frequency * amplitude * dt;*/

	velocity = { launchSpeed * (float)cos(launchAngle * DEG2RAD), -launchSpeed * (float)sin(launchAngle * DEG2RAD) };

	endPosition = launchPosition + velocity;
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("David Asher 101448950", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);
	DrawText(TextFormat("T: %6.2f seconds", time), GetScreenWidth() - 200, 20, 20, LIGHTGRAY);
	// Draw adjustable variables
	GuiSliderBar(Rectangle{ 100,15, 480, 30 }, "Time", TextFormat("%.2f", time), &time, 0, 240);
	GuiSliderBar(Rectangle{ 100,45, 480, 30 }, "Launch PositionX:", TextFormat("%.2f", launchPosition.x), &launchPosition.x, 70, GetScreenWidth() - 70);
	GuiSliderBar(Rectangle{ 100,75, 480, 30 }, "Launch PositionY:", TextFormat("%.2f", launchPosition.y), &launchPosition.y, 70, GetScreenHeight() - 70);
	GuiSliderBar(Rectangle{ 100,105, 480, 30 }, "Launch Angle: ", TextFormat("%.2f deg", launchAngle), &launchAngle, 0, 360);
	GuiSliderBar(Rectangle{ 100,135, 480, 30 }, "Launch Speed: ", TextFormat("%.2f", launchSpeed), &launchSpeed, 0, 480);
	
	/*DrawText(TextFormat("Launch Position: (%.1f, %.1f)", launchPosition.x, launchPosition.y), 10, 50, 20, RED);
	DrawText(TextFormat("Launch Angle: %.1f deg", launchAngle), 10, 80, 20, RED);
	DrawText(TextFormat("Launch Speed: %.1f", launchSpeed), 10, 110, 20, RED);*/

	/*DrawCircle(x, y, 70, RED);
	DrawCircle(500 + cos(time * frequency) * amplitude, 500 + sin(time * frequency) * amplitude, 70, BLUE);*/
	// Draw launch position
	DrawCircleV(launchPosition, 70, GREEN);

	// Draw velocity vector with red line
	DrawLineEx(launchPosition, endPosition, 5, RED);

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