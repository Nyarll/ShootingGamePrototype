#include "Graze.h"
#include "Enemy.h"
#include "Player.h"
#include "Score.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRAZE_BALL_NUM 128

typedef struct GrazeBall
{
	Vector2D pos;
	Vector2D vel;
	DegRad angle;
	HGRP gh;

	int count;

	BOOL flag;
}GrazeBall;

GrazeBall graze_ball[GRAZE_BALL_NUM];

void InitGraze(void)
{
	int i;
	
	srand((unsigned int)time(NULL));
	

	for (i = 0; i < GRAZE_BALL_NUM; i++)
	{
		graze_ball[i].angle.deg = (rand() % 360);
		graze_ball[i].angle.rad = DEG_TO_RAD(graze_ball[i].angle.deg);

		graze_ball[i].pos = { GetPlayerPosX(),GetPlayerPosY() };

		graze_ball[i].vel.x = cos(graze_ball[i].angle.rad);
		graze_ball[i].vel.y = sin(graze_ball[i].angle.rad);

		graze_ball[i].count = 0;

		graze_ball[i].gh = LoadGraph("Resources/Textures/Particle.png");

		graze_ball[i].flag = FALSE;
	}
}
void MoveGraze(void)
{
	int i;

	for (i = 0; i < GRAZE_BALL_NUM; i++)
	{
		if (graze_ball[i].flag)
		{
			graze_ball[i].pos.x += graze_ball[i].vel.x * 5;
			graze_ball[i].pos.y += graze_ball[i].vel.y * 5;

			graze_ball[i].count++;

			if (graze_ball[i].count > 10)
			{
				graze_ball[i].angle.deg = (rand() % 360);
				graze_ball[i].angle.rad = DEG_TO_RAD(graze_ball[i].angle.deg);
				graze_ball[i].pos = { GetPlayerPosX(),GetPlayerPosY() };
				graze_ball[i].vel.x = cos(graze_ball[i].angle.rad);
				graze_ball[i].vel.y = sin(graze_ball[i].angle.rad);
				graze_ball[i].count = 0;
				graze_ball[i].flag = FALSE;
			}
		}
	}
}
void DrawGraze(void)
{
	int i;

	for (i = 0; i < GRAZE_BALL_NUM; i++)
	{
		if (graze_ball[i].flag)
		{
			DrawRotaGraph(graze_ball[i].pos.x, graze_ball[i].pos.y, 0.0625, 0, graze_ball[i].gh, TRUE);
		}
	}
}

void SetGrazeFlag(void)
{

	int i;

	for (i = 0; i < GRAZE_BALL_NUM; i++)
	{
		if (!graze_ball[i].flag)
		{
			graze_ball[i].pos = { GetPlayerPosX(),GetPlayerPosY() };
			graze_ball[i].flag = TRUE;
			SetGrazeScore();
			break;
		}
	}
}