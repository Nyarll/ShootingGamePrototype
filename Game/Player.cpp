#include "Player.h"
#include "Defines.h"

static GameObject player;			// プレイヤーオブジェクト
static HGRP player_tex[2];			// プレイヤーのグラフィックハンドル

static Shot player_shot[PLAYER_SHOT_NUM];	// プレイヤーの弾オブジェクト
static int shot_power;		// ショットの強さ

static LIFE player_life;

static int dead_count;

static BOOL dead_flag;

void InitPlayer(void)
{
	// 最初の中心座標
	player.pos.x = GAME_SCREEN_CENTER_X;
	player.pos.y = GAME_SCREEN_CENTER_Y + GAME_SCREEN_CENTER_Y / 2;

	player.speed.x = 1;	player.speed.y = 1;
	player.vel.x = PLAYER_SPEED;	player.vel.y = PLAYER_SPEED;

	player_life = 3;

	shot_power = 1;

	dead_flag = FALSE;
	dead_count = 0;

	LoadDivGraph("Resources/Textures/player.png", 2, 2, 1, 64, 64, player_tex);

}
void MovePlayer(void)
{

	if (!dead_flag)
	{
		// UP か DOWN が押されているなら
		if (GetInputKeyData(KEY_INPUT_UP) || GetInputKeyData(KEY_INPUT_DOWN))
		{
			if ((GetInputKeyData(KEY_INPUT_LEFT)) || (GetInputKeyData(KEY_INPUT_RIGHT)))
			{
				player.speed.x = player.speed.y = 0.71;
			}
			else
			{
				player.speed.x = player.speed.y = 1.0;
			}
		}
		else if ((GetInputKeyData(KEY_INPUT_LEFT) == 1) || (GetInputKeyData(KEY_INPUT_RIGHT) == 1))
		{
			player.speed.x = player.speed.y = 1.0;
		}
		// ---------------------------------------------------------------

		if (GetInputKeyData(KEY_INPUT_LSHIFT) == 1)
		{
			player.vel.x = PLAYER_SPEED / 2;
			player.vel.y = PLAYER_SPEED / 2;
		}
		else
		{
			player.vel.x = PLAYER_SPEED;	player.vel.y = PLAYER_SPEED;
		}

		// ----------------------------------------------------------------

		if (GetInputKeyData(KEY_INPUT_LEFT))
		{
			player.pos.x -= player.vel.x * player.speed.x;
		}

		if (GetInputKeyData(KEY_INPUT_RIGHT))
		{
			player.pos.x += player.vel.x * player.speed.x;
		}

		if (GetInputKeyData(KEY_INPUT_UP))
		{
			player.pos.y -= player.vel.y * player.speed.y;
		}

		if (GetInputKeyData(KEY_INPUT_DOWN))
		{
			player.pos.y += player.vel.y * player.speed.y;
		}
	}
	else
	{
		if (dead_count == 0)
		{
			player.pos.x = GAME_SCREEN_CENTER_X;
			player.pos.y = GAME_SCREEN_CENTER_Y + GAME_SCREEN_CENTER_Y / 2;
		}
		dead_count++;
		if (dead_count > 60)
		{
			dead_flag = FALSE;
			dead_count = 0;
		}
	}
	// ----------------------------------------------------------------

	if (player.pos.x < SCREEN_LEFT)
	{
		player.pos.x = SCREEN_LEFT;
	}
	if (player.pos.x > GAME_SCREEN_RIGHT)
	{
		player.pos.x = GAME_SCREEN_RIGHT;
	}
	if ((player.pos.y - PLAYER_SIZE / 2) < SCREEN_TOP)
	{
		player.pos.y = PLAYER_SIZE / 2;
	}
	if ((player.pos.y + PLAYER_SIZE / 2) > GAME_SCREEN_BOTTOM)
	{
		player.pos.y = GAME_SCREEN_BOTTOM - PLAYER_SIZE / 2;
	}
}
void DrawPlayer(void)
{
	static int player_count = 0;
	static int temp = 0;

	if (!dead_flag)
	{
		temp = player_count % 20 / 10;

		if (temp == 2) { temp = 0; player_count = 0; }

		DrawGraph((player.pos.x - PLAYER_SIZE / 2), (player.pos.y - PLAYER_SIZE / 2),
			player_tex[temp], TRUE);
		player_count++;
	}
	else
	{
		temp = player_count % 20 / 10;

		if (temp == 2) { temp = 0; player_count = 0; }

		if (player_count % 2 == 0)
		{
			DrawGraph((player.pos.x - PLAYER_SIZE / 2), (player.pos.y - PLAYER_SIZE / 2),
				player_tex[temp], TRUE);
		}
		player_count++;
	}
}

// プレイヤーの弾
void InitPlayerShot(void)
{
	int i;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		player_shot[i].base.pos.x = player.pos.x;
		player_shot[i].base.pos.y = player.pos.y;
		player_shot[i].base.vel.x = 0;
		player_shot[i].base.vel.y = 12;
		player_shot[i].base.speed.x = 1;
		player_shot[i].base.speed.y = 1;

		player_shot[i].flag = FALSE;
	}
}
void MovePlayerShot(void)
{
	int i;
	int temp = 0;

	if (!dead_flag)
	{
		// Ｚキーが押されて, ６フレームに一発発射する
		if ((GetInputKeyData(KEY_INPUT_Z)) && (GetGameCount() % 4 == 0))
		{
			for (i = 0; i < PLAYER_SHOT_NUM; i++)
			{
				// フラグがFALSEの弾を探す
				if (player_shot[i].flag == FALSE)
				{
					// フラグをTRUEにする
					player_shot[i].flag = TRUE;

					// shot_power に応じて弾道を変える
					switch (shot_power)
					{
					case 1:
						player_shot[i].base.pos.x = player.pos.x;
						player_shot[i].base.pos.y = player.pos.y;
						player_shot[i].base.vel.x = 0;
						player_shot[i].base.speed.x = player_shot[i].base.speed.y = 1;
						break;

					case 2:
						if (temp == 0)
						{
							player_shot[i].base.pos.x = player.pos.x + 16;
							player_shot[i].base.pos.y = player.pos.y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.speed.x = player_shot[i].base.speed.y = 1;
							temp = 1;
						}
						else
						{
							player_shot[i].base.pos.x = player.pos.x - 16;
							player_shot[i].base.pos.y = player.pos.y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.speed.x = player_shot[i].base.speed.y = 1;
							temp = 2;
						}
						break;

					case 3:
						if (GetInputKeyData(KEY_INPUT_LSHIFT) == 1)
						{
							if (temp == 0)
							{
								player_shot[i].base.pos.x = player.pos.x;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = 0;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 1;
								temp = 1;
							}
							else if (temp == 1)
							{
								player_shot[i].base.pos.x = player.pos.x + 8;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = 1;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 0.96;
								temp = 2;
							}
							else
							{
								player_shot[i].base.pos.x = player.pos.x - 8;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = -1;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 0.96;
								temp = 3;
							}
						}
						else
						{
							if (temp == 0)
							{
								player_shot[i].base.pos.x = player.pos.x;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = 0;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 1;
								temp = 1;
							}
							else if (temp == 1)
							{
								player_shot[i].base.pos.x = player.pos.x + 16;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = 2;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 12.0 / 13.0;
								temp = 2;
							}
							else
							{
								player_shot[i].base.pos.x = player.pos.x - 16;
								player_shot[i].base.pos.y = player.pos.y;
								player_shot[i].base.vel.x = -2;
								player_shot[i].base.speed.x = player_shot[i].base.speed.y = 12.0 / 13.0;
								temp = 3;
							}
						}
						break;
					}
					// ------------------------------------------
					{
						if (shot_power == 1)
						{
							break;
						}
						if (shot_power == 2)
						{
							if (temp == 1)
							{
								continue;
							}
							else
							{
								break;
							}
						}
						if (shot_power == 3)
						{
							if (temp == 1)
							{
								continue;
							}
							else if (temp == 2)
							{
								continue;
							}
							else
							{
								break;
							}
						}
					}
					//
				}
			}
		}
	}
	// フラグがTRUEの弾だけ移動させる
	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		if (player_shot[i].flag)
		{
			player_shot[i].base.pos.x += player_shot[i].base.vel.x * player_shot[i].base.speed.x;
			player_shot[i].base.pos.y -= player_shot[i].base.vel.y * player_shot[i].base.speed.y;

			// 画面外に出たらフラグを戻す
			if ((player_shot[i].base.pos.x < SCREEN_LEFT - 20) ||
				(player_shot[i].base.pos.x > GAME_SCREEN_RIGHT + 20) ||
				(player_shot[i].base.pos.y < SCREEN_TOP - 20))
			{
				player_shot[i].flag = FALSE;
			}
		}
	}
}
void DrawPlayerShot(void)
{
	int i;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		if (player_shot[i].flag)
		{
			DrawCircle(player_shot[i].base.pos.x, player_shot[i].base.pos.y,
				PLAYER_SHOT_SIZE, COLOR_BLACK, TRUE);
		}
	}
}

double GetPlayerPosX(void)
{
	return player.pos.x;
}
double GetPlayerPosY(void)
{
	return player.pos.y;
}

BOOL GetPlayerShotFlag(int i)
{
	return player_shot[i].flag;
}

int GetPlayerShotPosX(int i)
{
	return player_shot[i].base.pos.x;
}
int GetPlayerShotPosY(int i)
{
	return player_shot[i].base.pos.y;
}

int GetShotPower(void)
{
	return shot_power;
}

void SetPlayerDeadFlag(void)
{
	dead_flag = TRUE;
}

void SetShotPower1(void)
{
	shot_power = 1;
}
void SetShotPower2(void)
{
	shot_power = 2;
}
void SetShotPower3(void)
{
	shot_power = 3;
}
