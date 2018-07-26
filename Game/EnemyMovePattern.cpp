#pragma warning (disable:4244)

#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "Defines.h"

double enemy_angle[256] = { 0 };
static double enemy_rad[256] = { 0 };
Vector2D enemy_vel[256];

// エネミー移動パターン //
void EnemyMovePatternDebug(int i)
{
	enemy[i].y = GAME_SCREEN_CENTER_Y / 2;
	enemy[i].x = GAME_SCREEN_CENTER_X;
}
// 上から出てきて, 上へ戻る
void EnemyMovePattern0(int i)
{
	//出てきてから止まる時間まで下に移動
	if (enemy[i].in_time < GetGameCount() && GetGameCount() < enemy[i].stop_time)
	{
		enemy[i].y += 2;
	}
	else if (GetGameCount() > enemy[i].out_time)
	{
		enemy[i].y -= 2;
	}
}
// プレイヤーのx,y座標に重なるように移動し, 重なったら上へ逃げる
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
// 上から出てきて一番下まで
void EnemyMovePattern2(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].y += 2;
	}
}
// 上から出てきて画面左に消える
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
// 上から出てきて画面右上に消える
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
// 左上から右下へ直線
void EnemyMovePattern5(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].x += cos(DEG_TO_RAD(45.0)) * 2;
		enemy[i].y += sin(DEG_TO_RAD(45.0)) * 2;
	}
}
// 右上から左下へ直線
void EnemyMovePattern6(int i)
{
	if (enemy[i].in_time < GetGameCount())
	{
		enemy[i].x -= cos(DEG_TO_RAD(45.0)) * 2;
		enemy[i].y += sin(DEG_TO_RAD(45.0)) * 2;
	}
}