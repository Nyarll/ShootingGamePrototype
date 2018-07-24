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

BOSS_SHOT boss_shot[BOSS_SHOT_NUM];

// �Y��Ȉړ��p�̌v�Z��(����)
// y = (((2 * ymax) / ty) * t) - ((ymax / (ty * ty)) * (t * t))
// ty : �w�莞��(�ړ��J�n����)	// tx = cos(rad)  ty = sin(rad)
// ymax : �ړ�����
// t : �J�E���^
// ���ꂼ�ꐅ������(x����), ��������(y����)�Ōv�Z���� (����y�Ɋ��蓖�Ă�)

void InitBoss(void)
{
	srand((unsigned int)time(NULL));

	memset(&boss, 0, sizeof(BOSS));

	boss.flag = FALSE;
	boss.pos = { GAME_SCREEN_CENTER_X,-20 };
	boss.vel = { 0,0 };
	boss.spd = { 3,3 };
	boss.tex;

	boss.rad = 0;

	boss.move_pattern = 0;
	boss.shot_pattern = 0;

	boss_intime = 0;	// �{�X�o���^�C�~���O
	boss_movecount = 300;
	boss_moveflag = 0;

	boss.shot_flag = FALSE;

	boss.hp = MAX_BOSS_HP;
	boss.life = 10;

	boss_back = LoadGraph("Resources/Textures/bossback3.png");

	InputPhy(60);

	InitBossShot();
}
void MoveBoss(void)
{
	boss.vel.x = 0;
	boss.vel.y = 0;

	// �{�X�o���^�C�~���O�ɂȂ�����
	if (boss_intime < GetGameCount())
	{
		boss.flag = TRUE;	// �o��������
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
		}
	}
	boss.pos.x += boss.vel.x;
	boss.pos.y += boss.vel.y;

	boss.cnt++;

	if (boss.hp <= 0)
	{
		boss.life -= 1;
		boss.shot_cnt = 0;
	}

#ifdef DEBUG
	if (boss.hp <= 0)
	{
		boss.hp = MAX_BOSS_HP;
	}
#endif

	if (boss.shot_flag)
	{
		MoveBossShot();
	}
}
void MoveBossManager(void)
{
	static int inicnt = 0;
	switch (boss.move_pattern)
	{
	case 0:
		break;

	case 1:
		//BossMovePattern1();
		
		break;
	}

	if (boss.phy.flag)
	{
		CalcPhy();
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
		//BossShotPattern1();
		BossSpecialShot0();
		break;
	}
	boss.shot_flag = TRUE;

	switch (boss.life)	// �{�X�c�@�ōs���̕ω�
	{
	case 10:
		boss.shot_pattern = 0;
		break;

	case 9:
		boss.shot_pattern = 1;
		break;
	}

	//
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

// �����_���Ȋp�x (���W�A���ŕԂ�)
// �ړ��p�x�͈̔�, �͈�
double rang(int deg, int range)
{
	double angle, rad;

	angle = rand() % deg + range;
	rad = DEG_TO_RAD(angle);

	return rad;
}

//�����I�v�Z��������o�^������(�w�莞��t�Œ�ʒu�ɖ߂�)
void InputPhy(int t)   //t=�ړ��ɂ����鎞��
{
	double ymax_x, ymax_y;

	if (t == 0)
	{
		t = 1;
	}

	boss.phy.flag = TRUE;                //�o�^�I��
	boss.phy.cnt = 0;                 //�J�E���^������
	boss.phy.set_t = t;               //�ړ��ɂ����鎞�Ԃ��Z�b�g
	ymax_x = boss.pos.x - BOSS_POS_X;       //�ړ���������������
	boss.phy.v0x = 2 * ymax_x / t;        //���������̏����x
	boss.phy.ax = 2 * ymax_x / (t * t);    //���������̉����x
	boss.phy.prex = boss.pos.x;           //����x���W
	ymax_y = boss.pos.y - BOSS_POS_Y;       //�ړ���������������
	boss.phy.v0y = 2 * ymax_y / t;        //���������̏����x
	boss.phy.ay = 2 * ymax_y / (t * t);    //���������̉����x
	boss.phy.prey = boss.pos.y;           //����y���W
}

//�����I�v�Z��_�Ƌ����w��œo�^������(�w�莞��t�Œ�ʒu�ɖ߂�)
void InputPhyPos(double x, double y, int t)     //t=�ړ��ɂ����鎞��
{
	double ymax_x, ymax_y;

	if (t == 0)
	{
		t = 1;
	}

	boss.phy.flag = TRUE;//�o�^�I��
	boss.phy.cnt = 0;//�J�E���^������
	boss.phy.set_t = t;//�ړ��ɂ����鎞�Ԃ��Z�b�g
	ymax_x = boss.pos.x - x;//�ړ���������������
	boss.phy.v0x = 2 * ymax_x / t;//���������̏����x
	boss.phy.ax = 2 * ymax_x / (t * t);//���������̉����x
	boss.phy.prex = boss.pos.x;//����x���W
	ymax_y = boss.pos.y - y;//�ړ���������������
	boss.phy.v0y = 2 * ymax_y / t;//���������̏����x
	boss.phy.ay = 2 * ymax_y / (t * t);//���������̉����x
	boss.phy.prey = boss.pos.y;//����y���W
}

//�����I�L�����N�^�ړ��v�Z
void CalcPhy(void)
{
	double t = boss.phy.cnt;

	boss.pos.x = boss.phy.prex - ((boss.phy.v0x * t) - 0.5 * boss.phy.ax * t * t);//���݂���ׂ�x���W�v�Z
	boss.pos.y = boss.phy.prey - ((boss.phy.v0y * t) - 0.5 * boss.phy.ay * t * t);//���݂���ׂ�y���W�v�Z
	boss.phy.cnt++;

	if (boss.phy.cnt >= boss.phy.set_t)//�ړ��ɂ����鎞�ԕ��ɂȂ�����
	{
		boss.phy.flag = FALSE;//�I�t
	}
}

double BossPlayerATAN(void)
{
	return atan2(boss.pos.y - GetPlayerPosY(), boss.pos.x - GetPlayerPosX());
}