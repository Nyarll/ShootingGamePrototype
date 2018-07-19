#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Defines.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define BOSS_SHOT_NUM 2048

#define BOSS_SIZE 30

typedef struct
{
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	BOOL flag;

	int move_pattern;
	int shot_pattern;

	int shot_wait;
	int cnt;

	int hp;
	int life;

	double rad;

	HGRP tex;
}BOSS;

typedef struct
{
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;

	int cnt;

	BOOL flag;
	double rad;
	int pattern;
	double r;
	double angle;

	HGRP tex;

}BOSS_SHOT;

extern BOSS boss;
extern BOSS_SHOT boss_shot[BOSS_SHOT_NUM];

void InitBoss(void);
void MoveBoss(void);
void MoveBossManager(void);
void ShotBossManager(void);
void DrawBoss(void);

void DrawBossHP(void);

BOOL GetBossFlag(void);
double GetBossPosX(void);
double GetBossPosY(void);

void DrawBossEffect(void);

void BossDamage(int damage);

double rang(int deg, int range);

// 

void BossMovePattern0(void);		// 出現動作
void BossMovePattern1(void);		// 通常動作 / 待機
void BossMovePattern2(void);

//

void InitBossShot(void);
void MoveBossShot(void);
void DrawBossShot(void);

void BossShotPattern0(void);		// 円形ショット
void BossShotPattern1(void);		// 


double BossPlayerATAN(void);