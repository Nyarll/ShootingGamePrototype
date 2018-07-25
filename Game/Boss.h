#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Defines.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define BOSS_SHOT_NUM 3072

#define BOSS_SIZE 30

typedef struct {
	int flag, cnt, set_t;
	double ax, v0x, ay, v0y, vx, vy, prex, prey;
}Phy;

typedef struct
{
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	BOOL flag;
	BOOL shot_flag;

	int move_pattern;
	int shot_pattern;

	int shot_wait;
	int cnt;
	int shot_cnt;

	int hp;
	int life;

	double rad;

	Phy phy;

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

	short state;

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

BOOL GetBossShotFlag(int i);

void DrawBossEffect(void);

void BossDamage(int damage);

double rang(int deg, int range);

void BossMovePattern0(void);		// 出現動作
void BossMovePattern1(void);		// 通常動作 / 待機
void BossMovePattern2(void);

BOOL BossMoveRandom(double x1, double y1, double x2, double y2, double dist, int t);

void InputPhy(int t);
void InputPhyPos(double x, double y, int t);
void CalcPhy(void);

void InitBossShot(void);
void MoveBossShot(void);
void DrawBossShot(void);

int SearchBossShot(void);

void BossShotPattern0(void);		// 円形ショット
void BossShotPattern1(void);		// 

void BossShotCircle1(double spd, double deg, int interval);
void BossShotCircle2(double spd, double deg, int interval);

void BossSpecialShot0(void);
void BossSpecialShot1(void);
void BossSpecialShot2(void);

void BossSpecialShotMove1(int i);

double BossPlayerATAN(void);