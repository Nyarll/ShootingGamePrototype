#pragma warning (disable:4244)

#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "Defines.h"

double enemy_angle[256] = { 0 };
static double enemy_rad[256] = { 0 };
Vector2D enemy_vel[256];

// �G�l�~�[�ړ��p�^�[�� //
void EnemyMovePatternDebug(int i)
{
	enemy[i].y = GAME_SCREEN_CENTER_Y / 2;
	enemy[i].x = GAME_SCREEN_CENTER_X;
}
// �ォ��o�Ă���, ��֖߂�
void EnemyMovePattern0(int i)
{
	//�o�Ă��Ă���~�܂鎞�Ԃ܂ŉ��Ɉړ�
	if (enemy[i].in_time < GetGameCount() && GetGameCount() < enemy[i].stop_time)
	{
		enemy[i].y += 2;
	}
	else if (GetGameCount() > enemy[i].out_time)
	{
		enemy[i].y -= 2;
	}
}
// �v���C���[��x,y���W�ɏd�Ȃ�悤�Ɉړ���, �d�Ȃ������֓�����
void EnemyMovePattern1(int i)
{

	if (!enemy_cross_flag[i])
	{
		if (((GetPlayerPosX() - PLAYER_SIZE / 4) < enemy[i].x) && ((GetPlayerPosX() + PLAYER_SIZE / 4) > enemy[i].x) &&
			((GetPlayerPosY() - PLAYER_SIZE * 4) < enemy[i].y))
		{
			enemy_cross_flag[i] = TRUE;
		}
		else if (enemy[i].x > GetPlayerPosX())
		{
			enemy[i].x -= (3 * 0.707);
		}
		else if (enemy[i].x < GetPlayerPosX())
		{
			enemy[i].x += (3 * 0.707);
		}
		enemy[i].y += (3 * 0.707);
	}
	else
	{
		enemy[i].y -= 4;
	}


}
// �ォ��o�Ă��Ĉ�ԉ��܂�
void EnemyMovePattern2(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].y += 2;
	}
}
// �ォ��o�Ă��ĉ�ʍ��ɏ�����
void EnemyMovePattern3(int i)
{
	if (enemy_angle[i] == 0)
	{
		enemy_angle[i] = 90;
	}

	if (enemy[i].in_time < GetGameCount())
	{
		if (enemy[i].stop_time < GetGameCount())
		{
			enemy[i].x += cos(DEG_TO_RAD(enemy_angle[i])) * 2;
			enemy[i].y += sin(DEG_TO_RAD(enemy_angle[i])) * 2;

			enemy_angle[i] += 0.5;
		}
		else
		{
			enemy[i].y += 2;
		}
	}
}
// �ォ��o�Ă��ĉ�ʉE��ɏ�����
void EnemyMovePattern4(int i)
{
	if (enemy_angle[i] == 0)
	{
		enemy_angle[i] = 90;
	}

	if (enemy[i].in_time < GetGameCount())
	{
		if (enemy[i].stop_time < GetGameCount())
		{
			enemy[i].x -= cos(DEG_TO_RAD(enemy_angle[i])) * 2;
			enemy[i].y += sin(DEG_TO_RAD(enemy_angle[i])) * 2;

			enemy_angle[i] += 0.5;
		}
		else
		{
			enemy[i].y += 2;
		}
	}
}
// ���ォ��E���֒���
void EnemyMovePattern5(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].x += cos(DEG_TO_RAD(45.0)) * 2;
		enemy[i].y += sin(DEG_TO_RAD(45.0)) * 2;
	}
}
// �E�ォ�獶���֒���
void EnemyMovePattern6(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].x -= cos(DEG_TO_RAD(45.0)) * 2;
		enemy[i].y += sin(DEG_TO_RAD(45.0)) * 2;
	}
}