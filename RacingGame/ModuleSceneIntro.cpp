#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ground = new Plane(0, 1, 0, 0);
	ground->axis = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	start2 = true;
	reachedCheckpoint = 0;

	limits[10].SetPos(0, 0, 256);
	limits[10].size.x = 9;
	limits[10].size.y = 6;
	limits[10].size.z = 542;
	limits[10].axis = false;
	limits[10].color.Set(0, 255, 255);
	App->physics->AddBody(limits[10], 0);

	limits[11].SetPos(512, 0, 256);
	limits[11].size.x = 9;
	limits[11].size.y = 6;
	limits[11].size.z = 542;
	limits[11].axis = false;
	limits[11].color.Set(0, 255, 255);
	App->physics->AddBody(limits[11], 0);

	limits[12].SetPos(256, 0, 0);
	limits[12].size.x = 542;
	limits[12].size.y = 6;
	limits[12].size.z = 9;
	limits[12].axis = false;
	limits[12].color.Set(0, 255, 255);
	App->physics->AddBody(limits[12], 0);

	limits[13].SetPos(256, 0, 532);
	limits[13].size.x = 512;
	limits[13].size.y = 6;
	limits[13].size.z = 9;
	limits[13].axis = false;
	limits[13].color.Set(0, 255, 255);
	App->physics->AddBody(limits[13], 0);

	limits[35].SetPos(16, 0, 213);
	limits[35].size.x = 1;
	limits[35].size.y = 15;
	limits[35].size.z = 1;
	limits[35].axis = false;
	limits[35].color = White;
	App->physics->AddBody(limits[35], 0);

	limits[36].SetPos(72, 0, 213);
	limits[36].size.x = 1;
	limits[36].size.y = 15;
	limits[36].size.z = 1;
	limits[36].axis = false;
	limits[36].color = White;
	App->physics->AddBody(limits[36], 0);


	//Sensors
	limits[39].SetPos(255, 0, 122);
	limits[39].size.x = 1;
	limits[39].size.y = 15;
	limits[39].size.z = 1;
	limits[39].axis = false;
	limits[39].color = White;
	App->physics->AddBody(limits[39], 0);

	limits[40].SetPos(255, 0, 178);
	limits[40].size.x = 1;
	limits[40].size.y = 15;
	limits[40].size.z = 1;
	limits[40].axis = false;
	limits[40].color = White;
	App->physics->AddBody(limits[40], 0);

	limits[43].SetPos(355, 0, 365);
	limits[43].size.x = 1;
	limits[43].size.y = 15;
	limits[43].size.z = 1;
	limits[43].axis = false;
	limits[43].color = White;
	App->physics->AddBody(limits[43], 0);

	limits[44].SetPos(355, 0, 295);
	limits[44].size.x = 1;
	limits[44].size.y = 15;
	limits[44].size.z = 1;
	limits[44].axis = false;
	limits[44].color = White;
	App->physics->AddBody(limits[44], 0);

	limits[47].SetPos(400, 0, 520);
	limits[47].size.x = 1;
	limits[47].size.y = 15;
	limits[47].size.z = 1;
	limits[47].axis = false;
	limits[47].color = White;
	App->physics->AddBody(limits[47], 0);

	limits[48].SetPos(400, 0, 388);
	limits[48].size.x = 1;
	limits[48].size.y = 15;
	limits[48].size.z = 1;
	limits[48].axis = false;
	limits[48].color = White;
	App->physics->AddBody(limits[48], 0);


	sensor[0].SetPos(44, 0, 213);
	sensor[0].size.x = 50;
	sensor[0].size.y = 5;
	sensor[0].size.z = 1;
	sensor[0].axis = false;
	sensor[0].wire = true;
	sensor[0].color.Set(128, 128, 128);
	physSensor = App->physics->AddBody(sensor[0], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(2);

	sensor[1].SetPos(248, 0, 150);
	sensor[1].size.x = 1;
	sensor[1].size.y = 5;
	sensor[1].size.z = 50;
	sensor[1].axis = false;
	sensor[1].wire = false;
	sensor[1].color.Set(128, 128, 128);
	physSensor = App->physics->AddBody(sensor[1], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(3);

	sensor[2].SetPos(348, 0, 330);
	sensor[2].size.x = 1;
	sensor[2].size.y = 5;
	sensor[2].size.z = 55;
	sensor[2].axis = false;
	sensor[2].wire = true;
	sensor[2].color.Set(128, 128, 128);
	physSensor = App->physics->AddBody(sensor[2], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(4);

	sensor[3].SetPos(407, 0, 476);
	sensor[3].size.x = 1;
	sensor[3].size.y = 5;
	sensor[3].size.z = 50;
	sensor[3].axis = false;
	sensor[3].wire = true;
	sensor[3].color.Set(128, 128, 128);
	physSensor = App->physics->AddBody(sensor[3], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(5);

	sensor[4].SetPos(407, 0, 415);
	sensor[4].size.x = 1;
	sensor[4].size.y = 5;
	sensor[4].size.z = 50;
	sensor[4].axis = false;
	sensor[4].wire = true;
	sensor[4].color.Set(128, 128, 128);
	physSensor = App->physics->AddBody(sensor[4], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(6);


	//Slope
	slope[0].SetPos(407, 0, 476);
	slope[0].SetRotation(-20.0f, { 0,0,1 });
	slope[0].size.x = 45;
	slope[0].size.y = 2;
	slope[0].size.z = 40;
	slope[0].axis = false;
	slope[0].color = Blue;
	App->physics->AddBody(slope[0], 0);

	slope[1].SetPos(407, 0, 415);
	slope[1].SetRotation(-20.0f, { 0,0,1 });
	slope[1].size.x = 45;
	slope[1].size.y = 2;
	slope[1].size.z = 40;
	slope[1].axis = false;
	slope[1].color = Red;
	App->physics->AddBody(slope[1], 0);

	slope[3].SetPos(270, 8, 476);
	slope[3].SetRotation(1.0f, { 0,0,1 });
	slope[3].size.x = 200;
	slope[3].size.y = 2;
	slope[3].size.z = 40;
	slope[3].axis = false;
	slope[3].color = Blue;
	App->physics->AddBody(slope[3], 0);

	slope[4].SetPos(307, 0, 415);
	slope[4].SetRotation(20.0f, { 0,0,1 });
	slope[4].size.x = 45;
	slope[4].size.y = 2;
	slope[4].size.z = 40;
	slope[4].axis = false;
	slope[4].color = Red;
	App->physics->AddBody(slope[4], 0);

	slope[5].SetPos(257, 0, 415);
	slope[5].SetRotation(-20.0f, { 0,0,1 });
	slope[5].size.x = 45;
	slope[5].size.y = 2;
	slope[5].size.z = 40;
	slope[5].axis = false;
	slope[5].color = Red;
	App->physics->AddBody(slope[5], 0);

	slope[6].SetPos(157, 0, 415);
	slope[6].SetRotation(20.0f, { 0,0,1 });
	slope[6].size.x = 45;
	slope[6].size.y = 2;
	slope[6].size.z = 40;
	slope[6].axis = false;
	slope[6].color = Red;
	App->physics->AddBody(slope[6], 0);

	slope[7].SetPos(107, 0, 415);
	slope[7].SetRotation(-20.0f, { 0,0,1 });
	slope[7].size.x = 45;
	slope[7].size.y = 2;
	slope[7].size.z = 40;
	slope[7].axis = false;
	slope[7].color = Red;
	App->physics->AddBody(slope[7], 0);
	
	// Out of Bounds

	sensor[30].SetPos(-70, 1.3, 250);
	sensor[30].size.x = 120;
	sensor[30].size.y = 100.5;
	sensor[30].size.z = 600;
	sensor[30].axis = false;
	sensor[30].wire = true;
	sensor[30].color = Black;
	physSensor = App->physics->AddBody(sensor[30], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(9);

	sensor[31].SetPos(580, 1.3, 250);
	sensor[31].size.x = 120;
	sensor[31].size.y = 100.5;
	sensor[31].size.z = 600;
	sensor[31].axis = false;
	sensor[31].wire = true;
	sensor[31].color = Black;
	physSensor = App->physics->AddBody(sensor[31], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(9);

	sensor[32].SetPos(250, 1.3, 580);
	sensor[32].size.x = 600;
	sensor[32].size.y = 100.5;
	sensor[32].size.z = 120;
	sensor[32].axis = false;
	sensor[32].wire = true;
	sensor[32].color = Black;
	physSensor = App->physics->AddBody(sensor[32], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(9);

	sensor[33].SetPos(250, 1.3, -70);
	sensor[33].size.x = 600;
	sensor[33].size.y = 100.5;
	sensor[33].size.z = 120;
	sensor[33].axis = false;
	sensor[33].wire = true;
	sensor[33].color = Black;
	physSensor = App->physics->AddBody(sensor[33], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(9);

	// Floor

	sensor[9].SetPos(256, 1.3, 56);
	sensor[9].size.x = 70;
	sensor[9].size.y = 0.5;
	sensor[9].size.z = 120;
	sensor[9].axis = false;
	sensor[9].wire = false;
	sensor[9].color = Black;
	physSensor = App->physics->AddBody(sensor[9], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[10].SetPos(396, 1.3, 135);
	sensor[10].size.x = 71;
	sensor[10].size.y = 0.5;
	sensor[10].size.z = 98;
	sensor[10].axis = false;
	sensor[10].wire = false;
	sensor[10].color = Black;
	physSensor = App->physics->AddBody(sensor[10], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[11].SetPos(109, 1.3, 232);
	sensor[11].size.x = 71;
	sensor[11].size.y = 0.5;
	sensor[11].size.z = 316;
	sensor[11].axis = false;
	sensor[11].wire = false;
	sensor[11].color = Black;
	physSensor = App->physics->AddBody(sensor[11], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[13].SetPos(255, 1.3, 376);
	sensor[13].size.x = 359;
	sensor[13].size.y = 0.5;
	sensor[13].size.z = 28;
	sensor[13].axis = false;
	sensor[13].wire = false;
	sensor[13].color = Black;
	physSensor = App->physics->AddBody(sensor[13], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[14].SetPos(255, 1.3, 480);
	sensor[14].size.x = 354;
	sensor[14].size.y = 0.5;
	sensor[14].size.z = 90;
	sensor[14].axis = false;
	sensor[14].wire = false;
	sensor[14].color = Black;
	physSensor = App->physics->AddBody(sensor[14], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[15].SetPos(462, 1.3, 260);
	sensor[15].size.x = 124;
	sensor[15].size.y = 0.5;
	sensor[15].size.z = 42;
	sensor[15].axis = false;
	sensor[15].wire = false;
	sensor[15].color = Black;
	physSensor = App->physics->AddBody(sensor[15], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[16].SetPos(369, 1.3, 267);
	sensor[16].size.x = 111;
	sensor[16].size.y = 0.5;
	sensor[16].size.z = 28;
	sensor[16].axis = false;
	sensor[16].wire = false;
	sensor[16].color = Black;
	physSensor = App->physics->AddBody(sensor[16], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[17].SetPos(328, 1.3, 280);
	sensor[17].size.x = 29;
	sensor[17].size.y = 0.5;
	sensor[17].size.z = 36;
	sensor[17].axis = false;
	sensor[17].wire = false;
	sensor[17].color = Black;
	physSensor = App->physics->AddBody(sensor[17], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[18].SetPos(285, 1.3, 286);
	sensor[18].size.x = 105;
	sensor[18].size.y = 0.5;
	sensor[18].size.z = 24;
	sensor[18].axis = false;
	sensor[18].wire = false;
	sensor[18].color = Black;
	physSensor = App->physics->AddBody(sensor[18], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[19].SetPos(182, 1.3, 202);
	sensor[19].size.x = 129;
	sensor[19].size.y = 0.5;
	sensor[19].size.z = 40;
	sensor[19].axis = false;
	sensor[19].wire = false;
	sensor[19].color = Black;
	physSensor = App->physics->AddBody(sensor[19], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[20].SetPos(289, 1.3, 196);
	sensor[20].size.x = 133;
	sensor[20].size.y = 0.5;
	sensor[20].size.z = 28;
	sensor[20].axis = false;
	sensor[20].wire = false;
	sensor[20].color = Black;
	physSensor = App->physics->AddBody(sensor[20], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[21].SetPos(353, 1.3, 180);
	sensor[21].size.x = 63;
	sensor[21].size.y = 0.5;
	sensor[21].size.z = 43;
	sensor[21].axis = false;
	sensor[21].wire = false;
	sensor[21].color = Black;
	physSensor = App->physics->AddBody(sensor[21], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[22].SetPos(0, 1.3, 256);
	sensor[22].size.x = 29;
	sensor[22].size.y = 0.5;
	sensor[22].size.z = 512;
	sensor[22].axis = false;
	sensor[22].wire = false;
	sensor[22].color = Black;
	physSensor = App->physics->AddBody(sensor[22], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[23].SetPos(512, 1.3, 256);
	sensor[23].size.x = 55;
	sensor[23].size.y = 0.5;
	sensor[23].size.z = 512;
	sensor[23].axis = false;
	sensor[23].wire = false;
	sensor[23].color = Black;
	physSensor = App->physics->AddBody(sensor[23], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[24].SetPos(256, 1.3, 0);
	sensor[24].size.x = 512;
	sensor[24].size.y = 0.5;
	sensor[24].size.z = 50;
	sensor[24].axis = false;
	sensor[24].wire = false;
	sensor[24].color = Black;
	physSensor = App->physics->AddBody(sensor[24], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[25].SetPos(256, 1.3, 522);
	sensor[25].size.x = 512;
	sensor[25].size.y = 0.5;
	sensor[25].size.z = 24;
	sensor[25].axis = false;
	sensor[25].wire = false;
	sensor[25].color = Black;
	physSensor = App->physics->AddBody(sensor[25], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);

	sensor[26].SetPos(445, 1.3, 286);
	sensor[26].size.x = 230;
	sensor[26].size.y = 0.5;
	sensor[26].size.z = 24;
	sensor[26].axis = false;
	sensor[26].wire = false;
	sensor[26].color = Black;
	physSensor = App->physics->AddBody(sensor[26], 0);
	physSensor->SetAsSensor(true);
	physSensor->SetId(8);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	ground->Render();
	

	SecondsPassed = INITIAL_TIME - timer;
	for (int i = 0; i < 50; i++)
	{
		slope[i].Render();
	}

	for (int i = 0; i < 100; i++)
	{
		limits[i].Render();
	}

	for (int i = 0; i < 50; i++)
	{
		sensor[i].Render();
	}

	if (frames % 60 == 0 && timer > 0 && App->camera->end == false)
	{
		if (App->player->Step > 0)
		{
			App->player->Step--;
		}
		App->player->TimeUp = true;
		timer--;
	}

	frames++;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

