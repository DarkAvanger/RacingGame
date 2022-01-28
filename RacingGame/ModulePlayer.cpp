#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	// Load Assets -------------------------------------------
	checkpointSFX = App->audio->LoadFx("Assets/checkpoint.ogg");
	startSFX = App->audio->LoadFx("Assets/start.ogg");
	Move = false;
	playM = true;
	TimeUp = true;

	App->audio->PlayFx(startSFX);

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 0.5, 12);
	car.chassis_size2.Set(5.5, 1.7, 7);
	car.chassis_size3.Set(2, 0.7, 8);
	car.chassis_size4.Set(3, 0.5, 14);
	car.chassis_size5.Set(4, 1.3, 5);
	car.chassis_size6.Set(2.3, 2.5, 3);

	car.chassis_offset.Set(0, 1.8, 0);
	car.chassis_offset2.Set(0, 2.4, -3);
	car.chassis_offset3.Set(0, 2.2, 3);
	car.chassis_offset4.Set(0, 1.8, 1.5);
	car.chassis_offset5.Set(0, 2.2, 0);
	car.chassis_offset6.Set(0, 3, -4);

	car.mass = 130.0f;
	car.suspensionStiffness = 26.10f;
	car.suspensionCompression = 1.42f;
	car.suspensionDamping = 2.35f;
	car.maxSuspensionTravelCm = 510.0f;
	car.frictionSlip = 100.5;
	car.maxSuspensionForce = 1000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 3.0f;
	float wheel_radius = 1.2f;
	float wheel_width = 1.5f;
	float suspensionRestLength = 1.5f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0.9f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = true;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.9f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = true;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.9f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = false;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0.9f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = false;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(45, 0, 235);
	vehicle->collision_listeners.add(this);
	vehicle->SetId(1);
	btQuaternion q;
	q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
	vehicle->SetRotation(q);

	Step = 0;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (INITIAL_TIME - App->scene_intro->timer == 3)
	{
		Move = true;
		if (playM) App->audio->PlayMusic("Assets/bgmusic.ogg", 0.0f);
		playM = false;
	}

	if (App->camera->end == false)
	{

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && Move == true)
		{
			if (Slow == true)
			{
				vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.03f);
			}
			acceleration = MAX_ACCELERATION * 5;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && Move == true)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && Move == true)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && Move == true)
		{
			if (vehicle->GetKmh() > 0)
			{
				brake = BRAKE_POWER / 2;
			}
			else
			{
				if (Slow == true)
				{
					vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.03f);
				}
				acceleration = -MAX_ACCELERATION * 5;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

			if ((jump_cd.Read() * 0.001) >= JUMP_CD)
			{
				vehicle->Push(0.0f, JUMP_FORCE * 3, 0.0f);
				jump_cd.Start();

			}
		}

		
		if (App->scene_intro->LapNumber == 4)
		{
			App->camera->end = true;
			App->audio->PlayMusic("Assets/win.ogg", 0.0f);
			Restart();
		}
		if (App->scene_intro->timer <= 0)
		{
			App->camera->end = true;
			App->audio->PlayMusic("Assets/lose.ogg", 0.0f);
			Restart();
		}

		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) Restart();
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) checkpointRespawn(App->scene_intro->reachedCheckpoint);

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE) || App->camera->end == true)
		{
			btVector3 vel = vehicle->body->getLinearVelocity();
			float friction = 0.99f;
			vehicle->body->setLinearVelocity(btVector3(vel.getX() * friction, vel.getY(), vel.getZ() * friction));
		}

		vehicle->ApplyEngineForce(acceleration);
		vehicle->Turn(turn);
		vehicle->Brake(brake);

		vehicle->Render();

		char title[80];
		if (App->scene_intro->LapNumber != 4)
		{
			sprintf_s(title, "Speed: %.1f Km/h     Lap: %d     Time Left: %d s  Checkpoints %d  ", vehicle->GetKmh(), App->scene_intro->LapNumber, App->scene_intro->timer, App->scene_intro->reachedCheckpoint);
		}
		if (App->scene_intro->LapNumber == 4)
		{
			sprintf_s(title, "Time left --> %d", (App->scene_intro->timer));
		}
		App->window->SetTitle(title);

		return UPDATE_CONTINUE;
	}
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->id == 2 && App->scene_intro->sensor[0].wire == false)
	{
		if (App->scene_intro->reachedCheckpoint == 3)
		{
			App->scene_intro->LapNumber++;
			App->scene_intro->sensor[0].wire = true;
			App->scene_intro->timer += 5;
			App->scene_intro->reachedCheckpoint = 0;
			App->scene_intro->sensor[1].wire = false;
		}
	}
	else if (body2->id == 3 && App->scene_intro->sensor[1].wire == false)
	{
		App->audio->PlayFx(checkpointSFX);
		App->scene_intro->reachedCheckpoint++;
		App->scene_intro->sensor[1].wire = true;
		App->scene_intro->timer += 5;
		App->scene_intro->sensor[2].wire = false;
	}
	else if (body2->id == 4 && App->scene_intro->sensor[2].wire == false)
	{
		App->audio->PlayFx(checkpointSFX);
		App->scene_intro->reachedCheckpoint++;
		App->scene_intro->sensor[2].wire = true;
		App->scene_intro->timer += 5;
		App->scene_intro->sensor[3].wire = false;
		App->scene_intro->sensor[4].wire = false;
	}
	else if (body2->id == 5 && App->scene_intro->sensor[3].wire == false)
	{
		App->audio->PlayFx(checkpointSFX);
		App->scene_intro->reachedCheckpoint++;
		App->scene_intro->sensor[3].wire = true;
		App->scene_intro->timer += 5;
		App->scene_intro->sensor[4].wire = true;
		App->scene_intro->sensor[0].wire = false;

	}
	else if (body2->id == 6 && App->scene_intro->sensor[4].wire == false)
	{
		App->audio->PlayFx(checkpointSFX);
		App->scene_intro->reachedCheckpoint++;
		App->scene_intro->sensor[4].wire = true;
		App->scene_intro->timer += 5;
		App->scene_intro->sensor[3].wire = true;
		App->scene_intro->sensor[0].wire = false;
	}
	else if (body2->id == 8)
	{
		Slow = true;
	}
	else if (body2->id == 9)
	{
		checkpointRespawn(App->scene_intro->reachedCheckpoint);
		App->scene_intro->timer -= 5;
	}
}

void ModulePlayer::Restart()
{
	turn = 0;
	App->scene_intro->start2 = true;
	acceleration = 0;
	vehicle->SetPos(40, 0, 230);
	btQuaternion q;
	q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
	vehicle->SetRotation(q);
	App->scene_intro->LapNumber = 1;
	App->scene_intro->reachedCheckpoint = 0;
	App->scene_intro->timer = INITIAL_TIME;
	App->scene_intro->sensor[0].wire = true;
	App->scene_intro->sensor[1].wire = false;
	App->scene_intro->sensor[2].wire = true;
	App->scene_intro->sensor[3].wire = true;
	App->scene_intro->sensor[4].wire = true;
	vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
	Move = false;

	App->camera->end = false;
	playM = true;
	App->audio->PlayFx(startSFX);
}

void ModulePlayer::checkpointRespawn(int checkpointReached)
{
	btQuaternion q;

	switch (checkpointReached)
	{
	case 0:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(39, 0, 213);
		q.setEuler(btScalar(180 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 1:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(235, 0, 150);
		q.setEuler(btScalar(90 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 2:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(335, 0, 338);
		q.setEuler(btScalar(90 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	case 3:
		turn = 0;
		acceleration = 0;
		vehicle->SetPos(475, 0, 442);
		q.setEuler(btScalar(270 * DEGTORAD), btScalar(0), btScalar(0));
		vehicle->SetRotation(q);
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		break;
	}
}

