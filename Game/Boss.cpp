#include "Boss.h"

#define DEBUG

#define BOSS_POS_X (GAME_SCREEN_CENTER_X)
#define BOSS_POS_Y (GAME_SCREEN_CENTER_Y / 2)

#define MAX_BOSS_HP 400

BOSS boss;
HGRP boss_back;
int boss_intime;
int boss_movecount;
int boss_moveflag;
BOOL boss_shotflag;

BOSS_SHOT boss_shot[BOSS_SHOT_NUM];

// 綺麗な移動用の計算式(物理)
// y = (((2 * ymax) / ty) * t) - ((ymax / (ty * ty)) * (t * t))
// ty : 指定時間(移動開始時間)	// tx = cos(rad)  ty = sin(rad)
// ymax : 移動距離
// t : カウンタ
// それぞれ水平成分(x成分), 鉛直成分(y成分)で計算する (式のyに割り当てる)

void InitBoss(void)
{
	srand((unsigned int)time(NULL));

	boss.flag = FALSE;
	boss.pos = { GAME_SCREEN_CENTER_X,-20 };
	boss.vel = { 0,0 };
	boss.spd = { 3,3 };
	boss.tex;

	boss.rad = 0;

	boss.move_pattern = 0;
	boss.shot_pattern = 0;

	boss_intime = 0;	// ボス出現タイミング
	boss_movecount = 300;
	boss_moveflag = 0;

	boss_shotflag = FALSE;

	boss.hp = MAX_BOSS_HP;
	boss.life = 10;

	boss_back = LoadGraph("Resources/Textures/bossback3.png");

	InitBossShot();
}
void MoveBoss(void)
{
	boss.vel.x = 0;
	boss.vel.y = 0;

	// ボス出現タイミングになったら
	if (boss_intime < GetGameCount())
	{
		boss.flag = TRUE;	// 出現させる
	}

	if (boss.flag)
	{
		MoveBossManager();

		if (boss.cnt < 200)
		{
			ShotBossManager();
		}
		else
		{
			boss.cnt = 0;
			/*if (boss.cnt > 400)
			{
				boss.cnt = 0;
				boss.shot_pattern = 0;
			}*/
		}
	}
	boss.pos.x += boss.vel.x;
	boss.pos.y += boss.vel.y;

	boss.cnt++;

#ifdef DEBUG
	if (boss.hp <= 0)
	{
		boss.hp = MAX_BOSS_HP;
	}
#endif

	MoveBossShot();
}
void MoveBossManager(void)
{
	switch (boss.move_pattern)
	{
	case 0:
		BossMovePattern0();
		break;

	case 1:
		BossMovePattern1();
		break;
	}
}
void ShotBossManager(void)
{
	switch (boss.shot_pattern)
	{
	case 0:
		BossShotPattern0();
		break;

	case 1:
		BossShotPattern1();
		break;
	}
}
void DrawBoss(void)
{
	if (boss_intime < GetGameCount())
	{
		DrawBossEffect();
		DrawCircle(boss.pos.x, boss.pos.y, BOSS_SIZE, GetColor(128, 0, 255), TRUE);
		DrawBossShot();
		DrawBossHP();
	}
}

void DrawBossHP(void)
{
	// float pos_y = ((SCREEN_HEIGHT - 10) * game_count / GAME_TIME) + 10;
	float bhp_x = ((GAME_SCREEN_RIGHT)* boss.hp / MAX_BOSS_HP);

	DrawBox(0, 2, bhp_x, 12, COLOR_RED, TRUE);
}

BOOL GetBossFlag(void)
{
	return boss.flag;
}
double GetBossPosX(void)
{
	return boss.pos.x;
}
double GetBossPosY(void)
{
	return boss.pos.y;
}

void DrawBossEffect(void)
{
	static double deg = 0;

	if (deg == 360)
	{
		deg = 0;
	}

	DrawRotaGraph(boss.pos.x, boss.pos.y, 2.0, DEG_TO_RAD(deg), boss_back, TRUE);
	deg += 1;
}

void BossDamage(int damage)
{
	boss.hp -= damage;
}

// ランダムな角度 (ラジアンで返す)
// 移動角度の範囲, 範囲
double rang(int deg, int range)
{
	double angle, rad;

	angle = rand() % deg + range;
	rad = DEG_TO_RAD(angle);

	return rad;
}

double BossPlayerATAN(void)
{
	return atan2(boss.pos.y - GetPlayerPosY(), boss.pos.x - GetPlayerPosX());
}