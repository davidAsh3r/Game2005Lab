/*
This project uses the Raylib framework to provide us functionality for math, graphics, GUI, input etc.
See documentation here: https://www.raylib.com/, and examples here: https://www.raylib.com/examples.html
*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"
#include <string>
#include <vector>

using namespace std;

const unsigned int TARGET_FPS = 50; //frames/second
float dt = 1.0f / TARGET_FPS; //seconds/frame
float time = 0;

class PhysicsObject
{
	public:
		Vector2 position = { 0,0 };
		Vector2 velocity = { 0,0 };
		float mass = 1.0f;
		
		float radius = 15; // circle radius in pixels
		string name = "physicsObject";
		Color color = RED;

		void draw()
		{
			DrawCircle(position.x, position.y, radius, color);

			DrawText(name.c_str(), position.x, position.y, radius * 2, color);

			DrawLineEx(position, position + velocity, 1, color);
		}
		
};

class PhysicsSimulator
{
private:
	unsigned int objectCount = 0;
	public:
		vector<PhysicsObject> objects;
		Vector2 accelerationGravity = { 0, 9 };
		
		void add(PhysicsObject newObject)
		{
			newObject.name = to_string(objectCount);
			objects.push_back(newObject);
			objectCount++;
		}

		void update(float dt)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				//vel = change in position / time, therefore     change in position = vel * time 
				objects[i].position = objects[i].position + objects[i].velocity * dt;

				//accel = deltaV / time (change in velocity over time) therefore     deltaV = accel * time
				objects[i].velocity = objects[i].velocity + accelerationGravity * dt;

			}
		}
};
float speed = 100;
float angle = 0;

vector<PhysicsObject> objects ;

PhysicsSimulator world;
//Changes world state

void cleanUp()
{
	// Remove objects that are off screen
	for (int i = 0; i < world.objects.size(); i++)
	{
		if (world.objects[i].position.y - world.objects[i].radius > GetScreenHeight() ||
			world.objects[i].position.y + world.objects[i].radius < 0 ||
			world.objects[i].position.x + world.objects[i].radius < 0 ||
			world.objects[i].position.x - world.objects[i].radius > GetScreenWidth())
		{
			world.objects.erase(world.objects.begin() + i);
			i--;
		}
	}
}
void update()
{
	dt = 1.0f / TARGET_FPS;
	time += dt;

	cleanUp();
	world.update(dt);
	

	if (IsKeyPressed(KEY_SPACE))
	{
		PhysicsObject newBird;
		newBird.position = { 100, (float)GetScreenHeight() - 100 };
		newBird.velocity = { speed * (float)cos(angle * DEG2RAD), -speed * (float)sin(angle * DEG2RAD) };
		
		newBird.radius = (rand() % 26) + 5; //random radius between 5 and 30
		Color randomColor = { rand() % 256, rand() % 256, rand() % 256, 255 };
		newBird.color = randomColor;
		world.add(newBird);
	}
}

//Display world state
void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("David Asher 101448950", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);


	GuiSliderBar(Rectangle{ 100, 15, 500, 20 }, "Time", TextFormat("%.2f", time), &time, 0, 240);

	GuiSliderBar(Rectangle{ 100, 40, 500, 30 }, "Speed", TextFormat("Speed: %.0f", speed), &speed, -1000, 1000);

	GuiSliderBar(Rectangle{ 100, 80, 500, 30 }, "Angle", TextFormat("Angle: %.0f Degrees", angle), &angle, -180, 180);

	GuiSliderBar(Rectangle{ 100, 120, 500, 30 }, "Gravity Y", TextFormat("Gravity Y: %.0f Px/sec^2", world.accelerationGravity.y), &world.accelerationGravity.y, -1000, 1000);

	DrawText(TextFormat("T: %6.2f", time), GetScreenWidth() - 140, 10, 30, LIGHTGRAY);

	DrawText(TextFormat("Objects: %d", world.objects.size()), 10, 150, 30, LIGHTGRAY);


	//Draw all physics objects
	for(int i = 0; i < world.objects.size(); i++)
	{
		world.objects[i].draw();
	}

	EndDrawing();

}

int main()
{
	InitWindow(InitialWidth, InitialHeight, "GAME2005 David Asher 101448950");
	SetTargetFPS(TARGET_FPS);

	while (!WindowShouldClose()) // Loops TARGET_FPS times per second
	{
		update();
		draw();
	}

	CloseWindow();
	return 0;
}