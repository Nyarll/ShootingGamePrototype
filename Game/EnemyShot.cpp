#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "Defines.h"

double state[ENEMY_SHOT_NUM];
// 0 - 31 ビーム
// 32 - 63 かまぼこ
// 64 - 95 丸１
// 96 - 127 丸２
// 128 - 159 クリスタル
// 160 - 191 クナイ
// 192 - 223 カード
// 224 - 255 弾丸
// 256 - 287 米粒１
// 288 - 319 米粒２
// 320 - 351 星型
// 352 - 384 ナゲット
HGRP enemy_shot_graph[384];

// エネミーの弾
void InitEnemyShot(void)
{
	int i;

	for (i = 0; i < ENEMY_SHOT_NUM; i++)
	{
		enemy_shot[i].base.pos.x = 0;
		enemy_shot[i].base.pos.y = 0;
		enemy_shot[i].base.vel.x = 0;
		enemy_shot[i].base.vel.y = 0;
		enemy_shot[i].base.speed.x = 0;
		enemy_shot[i].base.speed.y = 0;

		enemy_shot[i].r = 4;

		shot_speed_data[i] = 2;

		enemy_shot[i].flag = FALSE;
		enemy_shot[i].rad = 0;

		shotwait_count[i] = 0;
	}
	LoadDivGraph("Resources/Textures/bullet_11_11_32_12.png", 384, 32, 12, 11, 11, enemy_shot_graph);
}
void SetEnemyShot(int index)
{
	// ショットタイムになったらフラグを立てる
	if (enemy[index].shot_time == GetGameCount())
	{
		shot_flag[index] = TRUE;
	}


	if (shot_flag[index])	// ショットフラグがTRUE
	{
		if (enemy_flag[index])	// まだ死んでない
		{
			//初回だけ実行
			if (shot_count[index] == 0)
			{
				rad[index] = atan2(GetPlayerPosY() - enemy[index].y, GetPlayerPosX() - enemy[index].x);
			}

			// パターンに応じてShotにデータをセット
			switch (enemy[index].shot_pattern)
			{
			case 0:
				EnemyShotPattern0(index);
				break;

			case 1:
				EnemyShotPattern1(index);
				break;

			case 2:
				EnemyShotPattern2(index);
				break;

			case 3:
				EnemyShotPattern3(index);
				break;

			case 4:
				EnemyShotPattern4(index);
				break;

			case 5:
				EnemyShotPattern5(index);
				break;

			case 6:
				EnemyShotPattern6(index);
				break;

			case 7:
				EnemyShotPattern7(index);
				break;

			case 8:
				EnemyShotPattern8(index);
				break;

			case 9:
				EnemyShotPattern9(index);
				break;

			case 10:
				EnemyShotPattern10(index);
				break;

			case 11:
				EnemyShotPattern11(index);
				break;

			case 12:
				EnemyShotPattern12(index);
				break;

			case 13:
				EnemyShotPattern13(index);
				break;

			case 14:
				EnemyShotPattern14(index, 10);
				break;

			case 15:
				EnemyShotPattern15(index);
				break;
			}
		}

		//s == 0 なら発射中の弾が無い
		/*if (s == 0 && (!enemy_flag[I]))
		{
		enemy_flag[I] = FALSE;
		}*/
		shot_count[index]++;


	}

}
void MoveEnemyShot(void)
{
	int i;
	double rad;

	// フラグの立っている弾だけ移動させる

	for (i = 0; i < ENEMY_SHOT_NUM; i++)
	{
		if (enemy_shot[i].flag)
		{
			switch (enemy_shot[i].pattern)
			{
			case 0:
				enemy_shot[i].base.pos.y += (enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y);
				break;

			case 1:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 2:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 3:
				if (shotwait_count[i] > 120)
				{
					enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
					enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				}
				else
				{
					shotwait_count[i]++;
				}
				break;

			case 4:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 5:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 6:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 7:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 8:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 9:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 10:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 11:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 12:
				enemy_shot[i].base.pos.y += (enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y);
				break;

			case 13:
				if ((shotwait_count[i] <= 150) && (shotwait_count[i] >= 60))
				{
					enemy_shot[i].rad += (PI / 2) / 90.0 * state[i];
					enemy_shot[i].base.vel.x = cos(enemy_shot[i].rad);
					enemy_shot[i].base.vel.y = sin(enemy_shot[i].rad);

					enemy_shot[i].base.speed.x -= 0.5 / 90;
					enemy_shot[i].base.speed.y -= 0.5 / 90;
				}


				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				shotwait_count[i]++;
				break;

			case 14:
				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			case 15:
				enemy_shot[i].rad += (PI / 2) / 32.0 * state[i];
				enemy_shot[i].base.vel.x = cos(enemy_shot[i].rad);

				enemy_shot[i].base.speed.x = 5 * state[i];

				enemy_shot[i].base.pos.x += enemy_shot[i].base.vel.x * enemy_shot[i].base.speed.x;
				enemy_shot[i].base.pos.y += enemy_shot[i].base.vel.y * enemy_shot[i].base.speed.y;
				break;

			}

			// 画面外に出たら
			if ((enemy_shot[i].base.pos.x < (GAME_SCREEN_LEFT - 20)) ||
				(enemy_shot[i].base.pos.x > (GAME_SCREEN_RIGHT + 20)) ||
				(enemy_shot[i].base.pos.y < (GAME_SCREEN_TOP - 20)) ||
				(enemy_shot[i].base.pos.y > (GAME_SCREEN_BOTTOM + 20)))
			{
				enemy_shot[i].base.pos.x = 0;
				enemy_shot[i].base.pos.y = 0;
				enemy_shot[i].base.vel.x = 0;
				enemy_shot[i].base.vel.y = 0;
				enemy_shot[i].base.speed.x = 0;
				enemy_shot[i].base.speed.y = 0;

				shot_speed_data[i] = 2;

				enemy_shot[i].flag = FALSE;
				enemy_shot[i].rad = 0;

				shotwait_count[i] = 0;
				continue;
			}
		}

	}

}
void DrawEnemyShot(int o)
{
	int i;

	for (i = 0; i < ENEMY_SHOT_NUM; i++)
	{
		if (enemy_shot[i].flag)
		{

			//DrawCircle(enemy_shot[i].base.pos.x, enemy_shot[i].base.pos.y, enemy_shot[i].r, COLOR_PURPLE, TRUE);
			DrawRotaGraph(enemy_shot[i].base.pos.x, enemy_shot[i].base.pos.y, 1.4, 0, enemy_shot[i].base.sprite.texture, TRUE);

		}
	}
}

void SetEnemyShotGraph(int e_index, int j)
{
	switch (enemy[e_index].shot_type)
	{
	case 0:	// 星型
		enemy_shot[j].base.sprite.texture = enemy_shot_graph[322];
		break;

	case 1:	// 赤い●
		enemy_shot[j].base.sprite.texture = enemy_shot_graph[99];
		break;

	case 2:	//	青
		enemy_shot[j].base.sprite.texture = enemy_shot_graph[108];
		break;
	}
}

// <ショットパターン>

// 直線 / エネミーから直線
void EnemyShotPattern0(int i)
{
	int j;
	//5回に一回発射,20までなので５発
	if (shot_count[i] % 11 == 0 && shot_count[i] <= 50)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 0;
				enemy_shot[j].base.vel.y = 1.0;
				enemy_shot[j].base.speed.y = shot_speed_data[j];
				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;
				SetEnemyShotGraph(i, j);
				break;
			}
		}
	}
}
// 直線 / プレイヤー中心座標に対して収束
void EnemyShotPattern1(int i)
{
	//5回に一回発射,20までなので５発
	if (shot_count[i] % 11 == 0 && shot_count[i] <= 80)
	{
		for (int j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 1;

				enemy_shot[j].rad = atan2((GetPlayerPosY() - enemy[i].y), (GetPlayerPosX() - enemy[i].x));

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				SetEnemyShotGraph(i, j);
				break;
			}
		}
	}
}
// 直線 / プレイヤーを避ける
void EnemyShotPattern2(int i)
{
	int temp = 0;
	if (shot_count[i] % 11 == 0 && shot_count[i] <= 80)
	{
		for (int j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 2;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				if (temp == 0)
				{
					rad[i] = atan2(GetPlayerPosY() - enemy[i].y, (GetPlayerPosX() - 40) - enemy[i].x);
					temp = 1;
					enemy_shot[j].rad = rad[i];

					enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
					enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);
					SetEnemyShotGraph(i, j);
				}
				else
				{
					rad[i] = atan2(GetPlayerPosY() - enemy[i].y, (GetPlayerPosX() + 40) - enemy[i].x);
					temp = 0;
					enemy_shot[j].rad = rad[i];

					enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
					enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);
					SetEnemyShotGraph(i, j);
					break;
				}
			}
		}
	}
}
// 円形 / プレイヤーの中心に対して収束
void EnemyShotPattern3(int i)
{
	static int sum = 0;
	double ang = 0;
	double r = 80;



	if (shot_count[i] % 2 == 1 && shot_count[i] <= 2)
	{
		for (int j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 3;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(ang));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(ang));

				enemy_shot[j].rad = atan2(GetPlayerPosY() - enemy_shot[j].base.pos.y, GetPlayerPosX() - enemy_shot[j].base.pos.x);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				SetEnemyShotGraph(i, j);

				ang += 45;
				sum++;

				if (sum > 8)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
// 円形 / ばらまく / 5 deg ずつ
void EnemyShotPattern4(int i)
{
	int j;
	static int sum = 0;
	double ang = 0.0;

	if (shot_count[i] % 21 == 0 && shot_count[i] <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 4;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				enemy_shot[j].rad = DEG_TO_RAD(ang);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				SetEnemyShotGraph(i, j);

				ang += 5.0;
				sum++;

				if (sum > 72)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
// 円形 / ばらまく / 10 deg ずつ
void EnemyShotPattern5(int i)
{
	int j;
	static int sum = 0;
	double ang = 0.0;

	if (shot_count[i] % 21 == 0 && shot_count[i] <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 5;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				enemy_shot[j].rad = DEG_TO_RAD(ang);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				SetEnemyShotGraph(i, j);

				ang += 10.0;
				sum++;

				if (sum > 36)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
// 円形 / ばらまく / 30 deg ずつ
void EnemyShotPattern6(int i)
{
	int j;
	static int sum = 0;
	double ang = 0.0;

	if (shot_count[i] % 21 == 0 && shot_count[i] <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 6;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				enemy_shot[j].rad = DEG_TO_RAD(ang);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				SetEnemyShotGraph(i, j);

				ang += 30.0;
				sum++;

				if (sum > 12)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
// 円形 / ばらまく / 45 deg ずつ
void EnemyShotPattern7(int i)
{
	int j;
	static int sum = 0;
	double ang = 0.0;

	if (shot_count[i] % 21 == 0 && shot_count[i] <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 7;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				enemy_shot[j].rad = DEG_TO_RAD(ang);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				SetEnemyShotGraph(i, j);

				ang += 45.0;
				sum++;

				if (sum > 8)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
// 紅葉
void EnemyShotPattern8(int i)
{
	int j;
	static int sum = 0;
	double r = 100;
	static double angle_route1 = 90;
	static double angle_route2 = 90;
	double angle_shot = 0;

	if (angle_route1 > 270)
	{
		angle_route1 = 90;
	}
	if (angle_route2 == 0)
	{
		angle_route2 = 360;
	}

	if (shot_count[i] % 10 == 0 && shot_count[i] <= 150)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 8;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle_shot);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle_route1));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle_route1));

				SetEnemyShotGraph(i, j);

				angle_shot += 30;
				sum++;

				if (sum > 12)
				{
					sum = 0;
					break;
				}
			}
		}
		angle_shot = 0;
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 8;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle_shot);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle_route2));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle_route2));

				angle_shot += 30;
				sum++;

				if (sum > 12)
				{
					sum = 0;
					break;
				}
			}
		}
		angle_route1 += 12;
		angle_route2 -= 12;
	}
}
// うずまき / ２つ
void EnemyShotPattern9(int i)
{
	int j;
	static double angle1 = 0;
	static double angle2 = 180 + 8;
	double r = 1;

	if (angle1 == 360)
	{
		angle1 = 0;
	}
	if (angle2 == 360)
	{
		angle2 = 0;
	}

	if (shot_count[i] % 2 == 0 && shot_count[i] <= 360)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 9;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle1);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle1));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle1));

				SetEnemyShotGraph(i, j);

				angle1 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 9;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle2);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle2));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle2));

				SetEnemyShotGraph(i, j);

				angle2 += 15;

				break;
			}
		}
	}
}
// うずまき / ３つ
void EnemyShotPattern10(int i)
{
	int j;
	static double angle1 = 0;
	static double angle2 = 120 + 4;
	static double angle3 = 240 + 6;
	double r = 1;

	if (angle1 == 360)
	{
		angle1 = 0;
	}
	if (angle2 == 360)
	{
		angle2 = 0;
	}

	if (shot_count[i] % 2 == 0 && shot_count[i] <= 360)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 10;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle1);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle1));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle1));

				SetEnemyShotGraph(i, j);

				angle1 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 10;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle2);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle2));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle2));

				SetEnemyShotGraph(i, j);

				angle2 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 10;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle3);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle3));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle3));

				SetEnemyShotGraph(i, j);

				angle3 += 15;

				break;
			}
		}
	}
}
// うずまき / ４つ
void EnemyShotPattern11(int i)
{
	int j;
	static double angle1 = 0;
	static double angle2 = 90 + 2;
	static double angle3 = 180 + 3;
	static double angle4 = 270 + 5;
	double r = 1;

	if (angle1 == 360)
	{
		angle1 = 0;
	}
	if (angle2 == 360)
	{
		angle2 = 0;
	}
	if (angle3 == 360)
	{
		angle3 = 0;
	}
	if (angle4 == 360)
	{
		angle4 = 0;
	}

	if (shot_count[i] % 2 == 0 && shot_count[i] <= 360)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 11;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle1);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle1));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle1));

				SetEnemyShotGraph(i, j);

				angle1 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 11;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle2);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle2));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle2));

				SetEnemyShotGraph(i, j);

				angle2 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 11;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle3);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle3));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle3));

				SetEnemyShotGraph(i, j);

				angle3 += 15;

				break;
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 11;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].rad = DEG_TO_RAD(angle4);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle4));
				enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle4));

				SetEnemyShotGraph(i, j);

				angle4 += 15;

				break;
			}
		}
	}
}
// 直線 / 一回で10発 / それぞれ速度が違う
void EnemyShotPattern12(int i)
{
	int j;
	int sum = 0;

	if (shot_count[i] % 2 == 1 && shot_count[i] <= 2)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 12;

				enemy_shot[j].base.speed.y = shot_speed_data[j];
				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;
				enemy_shot[j].base.vel.y = 1.0;

				SetEnemyShotGraph(i, j);

				switch (sum)
				{
				case 0:
					enemy_shot[j].base.speed.y *= 1.0;
					break;

				case 1:
					enemy_shot[j].base.speed.y *= 0.95;
					break;

				case 2:
					enemy_shot[j].base.speed.y *= 0.90;
					break;

				case 3:
					enemy_shot[j].base.speed.y *= 0.85;
					break;

				case 4:
					enemy_shot[j].base.speed.y *= 0.80;
					break;

				case 5:
					enemy_shot[j].base.speed.y *= 0.75;
					break;

				case 6:
					enemy_shot[j].base.speed.y *= 0.70;
					break;

				case 7:
					enemy_shot[j].base.speed.y *= 0.65;
					break;

				case 8:
					enemy_shot[j].base.speed.y *= 0.60;
					break;

				case 9:
					enemy_shot[j].base.speed.y *= 0.55;
					break;
				}

				if (sum > 10)
				{
					break;
				}
				sum++;
			}
		}
	}
}
// 円形 / 途中で軌道が変わる
void EnemyShotPattern13(int i)
{
	int j;
	int sum = 0;
	double angle = 0;

	if (shot_count[i] % 30 == 0 && shot_count[i] <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 13;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];
				enemy_shot[j].base.pos.x = enemy[i].x + 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.pos.y = enemy[i].y + 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].angle = angle;
				enemy_shot[j].rad = DEG_TO_RAD(angle);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].center = { (double)enemy[i].x , (double)enemy[i].y };

				state[j] = -1;

				SetEnemyShotGraph(i, j);

				angle += 6;
				sum++;

				if (sum == 60)
				{
					break;
				}
			}
		}
		angle = 0;
		sum = 0;
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 13;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];
				enemy_shot[j].base.pos.x = enemy[i].x + 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.pos.y = enemy[i].y + 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].rad = DEG_TO_RAD(angle);

				enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
				enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

				enemy_shot[j].center = { (double)enemy[i].x , (double)enemy[i].y };

				state[j] = 1;

				SetEnemyShotGraph(i, j);

				angle += 6;
				sum++;

				if (sum == 60)
				{
					break;
				}
			}
		}
	}
}
// うずまき / 数が指定できる
void EnemyShotPattern14(int i, int num)
{
	int j, m;
	static double angle[360] = { 0 };
	static BOOL flag = FALSE;
	double r = 1;

	for (j = 0; j < num; j++)
	{
		if (angle[j] == 360)
		{
			angle[j] = 0;
		}
	}
	if (!flag)
	{
		for (j = 1; j < num; j++)
		{
			angle[j] = (360 / num) * j;
		}
		flag = TRUE;
	}
	if (shot_count[i] % 2 == 0 && shot_count[i] <= 360)
	{
		for (m = 0; m < num; m++)
		{
			for (j = 0; j < ENEMY_SHOT_NUM; j++)
			{
				//flagのない弾を探して座標セット
				if (enemy_shot[j].flag == FALSE)
				{
					enemy_shot[j].flag = TRUE;
					enemy_shot[j].pattern = 14;

					enemy_shot[j].base.speed.x = shot_speed_data[j];
					enemy_shot[j].base.speed.y = shot_speed_data[j];

					enemy_shot[j].rad = DEG_TO_RAD(angle[m]);

					enemy_shot[j].base.vel.x = 1 * cos(enemy_shot[j].rad);
					enemy_shot[j].base.vel.y = 1 * sin(enemy_shot[j].rad);

					enemy_shot[j].base.pos.x = enemy[i].x + r * cos(DEG_TO_RAD(angle[m]));
					enemy_shot[j].base.pos.y = enemy[i].y + r * sin(DEG_TO_RAD(angle[m]));

					SetEnemyShotGraph(i, j);

					angle[m] += 15;

					break;
				}
			}
		}
	}
	if (shot_count[i] > 360)
	{
		flag = FALSE;
	}
}
// sin波形
void EnemyShotPattern15(int i)
{
	int j;
	static int num = 0;
	//5回に一回発射,20までなので５発
	if (shot_count[i] % 10 == 0 && shot_count[i] <= 360)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flagのない弾を探して座標セット
			if (enemy_shot[j].flag == FALSE)
			{
				enemy_shot[j].flag = TRUE;
				enemy_shot[j].pattern = 15;

				enemy_shot[j].base.vel.x = 1.0;
				enemy_shot[j].base.vel.y = 1.0;

				enemy_shot[j].base.speed.x = shot_speed_data[j];
				enemy_shot[j].base.speed.y = shot_speed_data[j];

				enemy_shot[j].base.pos.x = enemy[i].x;
				enemy_shot[j].base.pos.y = enemy[i].y;

				SetEnemyShotGraph(i, j);

				num++;

				if (num % 2)
				{
					state[j] = 1;
				}
				else
				{
					state[j] = -1;
				}

				break;
			}
		}
	}
}