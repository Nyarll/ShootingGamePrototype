#include "Boss.h"

void BossMovePattern0(void)
{
	boss.rad = atan2((GAME_SCREEN_CENTER_Y / 4 * 3) - boss.pos.y, GAME_SCREEN_CENTER_X - boss.pos.x);

	if (((GAME_SCREEN_CENTER_Y / 8) * 5) < boss.pos.y)
	{
		boss.spd.x -= 0.25 /2;
		boss.spd.y -= 0.25 /2;
	}
	else
	{
		boss.spd.x += 0.005;
		boss.spd.y += 0.005;
	}

	boss.vel.x = cos(boss.rad) * boss.spd.x;
	boss.vel.y = sin(boss.rad) * boss.spd.y;


	//if (boss.vel.x < 0.01 && boss.vel.y < 0.01)
	if(boss.pos.y >= GAME_SCREEN_CENTER_Y / 4 * 3 - 10)
	{
		boss.vel.x = 0;
		boss.vel.y = 0;
	}

	if (boss.vel.x == 0.0)
	{
		boss.move_pattern = 1;
	}
}
void BossMovePattern1(void)
{
	static double deg = 0;
	double rad = 0;

	if (deg == 360)
	{
		deg = 0;
	}
	rad = DEG_TO_RAD(deg);

	boss.vel.y = cos(rad) / 2;

	deg += 5;
}
void BossMovePattern2(void)
{
	boss.rad = rang(180, -90);

	if (((GAME_SCREEN_CENTER_Y / 8) * 5) < boss.pos.y)
	{
		boss.spd.x -= 0.25 / 2;
		boss.spd.y -= 0.25 / 2;
	}
	else
	{
		boss.spd.x += 0.005;
		boss.spd.y += 0.005;
	}

	boss.vel.x = cos(boss.rad) * boss.spd.x;
	boss.vel.y = sin(boss.rad) * boss.spd.y;
}

// �ړ��������͈�, �ړ��ɂ����鎞��, �H
BOOL BossMoveRandom(double x1, double y1, double x2, double y2, double dist, int t)
{
	int i = 0;
	double x, y, angle;
	for (i = 0; i<1000; i++)
	{
		x = boss.pos.x, y = boss.pos.y;	//���̃{�X�̈ʒu���Z�b�g
		angle = rang(360, 0);	//�K���Ɍ��������������߂�
		x += cos(angle) * dist;	//������Ɉړ�������
		y += sin(angle) * dist;
		if (x1 <= x && x <= x2 && y1 <= y && y <= y2)	//���̓_���ړ��\�͈͂Ȃ�
		{
			InputPhyPos(x, y, t);       // �ړ��������
			return TRUE;
		}
	}
	return FALSE;
}