#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 300.0f
#define JUMP_CD 3.0f
#define JUMP_FORCE 600.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2)override;
	void Restart();
	void checkpointRespawn(int checkpointReached);

public:

	Timer jump_cd;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	uint Step;

	bool Move;
	bool playM;
	bool Slow;
	bool TimeUp;

	int checkpointSFX;
	int startSFX;
};