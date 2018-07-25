#pragma warning (disable:4244)

#include <math.h>
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Score.h"
#include "Item.h"
#include "Defines.h"

#define BOM_SHOT_NUM 8

static GameObject player;			// プレイヤーオブジェクト
static HGRP player_tex[12];			// プレイヤーのグラフィックハンドル
static double circle_count = 0;

static BOOL right_move_flag, left_move_flag;

static HGRP player_collision;		// 当たり判定用の円を画像で描画する用
static DegRad player_angle[2];

static Shot player_shot[PLAYER_SHOT_NUM];	// プレイヤーの弾オブジェクト
static HGRP player_shot_gh[4];
static int shot_power;		// ショットの強さ
static BOOL ps[PLAYER_SHOT_NUM] = { FALSE };

static Vector2D magic_ball[3];

LIFE player_life;
BOMB player_bom;
BOMB player_bom_type;
Shot bom_shot[BOM_SHOT_NUM];
BOOL bom_flag;

static Vector2D cutin_pos;
static Vector2D cutin_bar_pos[2];
static HGRP cutin_gh;
static HGRP cutin_bar_gh[2];
static double cutin_bright;

static HGRP bom_gh[5];
static double bom_deg[5];
static double bom_rad[5];
static double bright[5];

static int bom_count;

static int dead_count;

static BOOL dead_flag;
static BOOL player_dead_effect_flag;
static HGRP player_dead_effect_gh;
static int dead_effect_cnt;
static double dead_effect_deg;

void InitPlayer(void)
{
	int i;

	// 最初の中心座標
	player.pos.x = GAME_SCREEN_CENTER_X;
	player.pos.y = GAME_SCREEN_CENTER_Y + GAME_SCREEN_CENTER_Y / 2;

	player.speed.x = 1;	player.speed.y = 1;
	player.vel.x = PLAYER_SPEED;	player.vel.y = PLAYER_SPEED;

	player_life = 5;
	player_bom = 3;

	shot_power = 1;

	bom_flag = FALSE;

	dead_flag = FALSE;
	dead_count = 0;

	player_dead_effect_flag = FALSE;

	player_dead_effect_gh = LoadGraph("Resources/Textures/dead_effect.png");

	player_collision = LoadGraph("Resources/Textures/atari.png");

	LoadDivGraph("Resources/Textures/huto.png", 12, 4, 3, 48, 48, player_tex);

	bom_gh[0] = LoadGraph("Resources/Textures/MagicCircle1.png");
	bom_gh[1] = LoadGraph("Resources/Textures/MagicCircle2.png");
	bom_gh[2] = LoadGraph("Resources/Textures/MagicCircle3.png");
	bom_gh[3] = LoadGraph("Resources/Textures/MagicCircle4.png");
	bom_gh[4] = LoadGraph("Resources/Textures/MagicCircle5.png");

	cutin_gh = LoadGraph("Resources/Textures/cutin.png");
	cutin_bar_gh[0] = LoadGraph("Resources/Textures/bom_title0.png");	// 横
	cutin_bar_gh[1] = LoadGraph("Resources/Textures/bom_title1.png");	// 縦

	for (i = 0; i < BOM_SHOT_NUM; i++)
	{
		bom_shot[i].base.sprite.texture = LoadGraph("Resources/Textures/Particle.png");
	}

	player_angle[0].deg = 0;
	player_angle[1].deg = 360;

	right_move_flag = FALSE, left_move_flag = FALSE;

}
void MovePlayer(void)
{
	int power = GetPowerUpItemNum() % 100;

	if (power > 3)
	{
		if (shot_power < 4)
		{
			shot_power += 1;
		}
	}

	player_angle[0].deg++;
	player_angle[1].deg--;

	if (player_angle[0].deg == 360)
	{
		player_angle[0].deg = 0;
	}
	if (player_angle[1].deg == 0)
	{
		player_angle[1].deg = 360;
	}

	player_angle[0].rad = DEG_TO_RAD(player_angle[0].deg);
	player_angle[1].rad = DEG_TO_RAD(player_angle[1].deg);

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
			left_move_flag = TRUE;
		}
		else
		{
			left_move_flag = FALSE;
		}

		if (GetInputKeyData(KEY_INPUT_RIGHT))
		{
			player.pos.x += player.vel.x * player.speed.x;
			right_move_flag = TRUE;
		}
		else
		{
			right_move_flag = FALSE;
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

	if (player_dead_effect_flag)
	{
		dead_effect_cnt++;
		if (dead_effect_cnt > 10)
		{
			player_dead_effect_flag = FALSE;
			dead_effect_cnt = 0;
			dead_effect_deg = 0;
		}
	}
}
void DrawPlayer(void)
{
	static int player_count = 0;

	static int temp = 0;
	static int temp_l = 4;
	static int temp_r = 8;



	double p_rota = 1.5;

	DrawPlayerDeadEffect();

	if (!dead_flag)
	{
		temp = player_count % 40 / 10;

		if (temp == 4) { temp = 0; player_count = 0; }
		if (temp == 8) { temp = 4; player_count = 0; }
		if (temp == 12) { temp = 8; player_count = 0; }

		if ((!left_move_flag) && (!right_move_flag))
		{
			DrawMagicCircle();
			DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
		}
		else
		{
			DrawMagicCircle();
			if (left_move_flag)
			{
				temp += 4;
				DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
			}
			if (right_move_flag)
			{
				temp += 8;
				DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
			}
		}
		player_count++;
	}
	else
	{
		temp = player_count % 20 / 10;

		if (temp == 2) { temp = 0; player_count = 0; }

		if (player_count % 2 == 0)
		{

			if ((!left_move_flag) && (!right_move_flag))
			{
				DrawMagicCircle();
				DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
			}
			else
			{
				DrawMagicCircle();
				if (left_move_flag)
				{
					temp += 4;
					DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
				}
				if (right_move_flag)
				{
					temp += 8;
					DrawRotaGraph(player.pos.x, player.pos.y, p_rota, 0, player_tex[temp], TRUE);
				}
			}

		}

		player_count++;
	}
	circle_count += 2;
	DrawRotaGraph(player.pos.x, player.pos.y, 1.0, player_angle[0].rad, player_collision, TRUE);
	DrawRotaGraph(player.pos.x, player.pos.y, 1.0, player_angle[1].rad, player_collision, TRUE);

}

void MoveMagicCircle(void)
{
	static DegRad pdr1 = { 270,0 }, pdr2 = { 30,0 }, pdr3 = { 150,0 };

	if (pdr1.deg == 360)
	{
		pdr1.deg = 0;
	}
	if (pdr2.deg == 360)
	{
		pdr2.deg = 0;
	}
	if (pdr3.deg == 360)
	{
		pdr3.deg = 0;
	}

	pdr1.rad = DEG_TO_RAD(pdr1.deg);
	pdr2.rad = DEG_TO_RAD(pdr2.deg);
	pdr3.rad = DEG_TO_RAD(pdr3.deg);

	magic_ball[0].x = (GetPlayerPosX() + (3 * (PLAYER_SIZE / 4)) * cos(pdr1.rad));
	magic_ball[1].x = (GetPlayerPosX() + (3 * (PLAYER_SIZE / 4)) * cos(pdr2.rad));
	magic_ball[2].x = (GetPlayerPosX() + (3 * (PLAYER_SIZE / 4)) * cos(pdr3.rad));

	magic_ball[0].y = (GetPlayerPosY() + (3 * (PLAYER_SIZE / 4)) * sin(pdr1.rad));
	magic_ball[1].y = (GetPlayerPosY() + (3 * (PLAYER_SIZE / 4)) * sin(pdr2.rad));
	magic_ball[2].y = (GetPlayerPosY() + (3 * (PLAYER_SIZE / 4)) * sin(pdr3.rad));

	// デバッグ用
	/*DrawCircle(magic_ball[0].x, magic_ball[0].y, 3, COLOR_RED, TRUE, 2);
	DrawCircle(magic_ball[1].x, magic_ball[1].y, 3, COLOR_RED, TRUE, 2);
	DrawCircle(magic_ball[2].x, magic_ball[2].y, 3, COLOR_RED, TRUE, 2);*/

	pdr1.deg += 2;
	pdr2.deg += 2;
	pdr3.deg += 2;
}
void DrawMagicCircle(void)
{
	int red, green, blue;

	red = 64;	green = 64;	blue = 255;

	if (circle_count == 360)
	{
		circle_count = 0;
	}

	SetDrawBright(red, green, blue);
	DrawRotaGraph(player.pos.x, player.pos.y, 0.5, 1 * (DEG_TO_RAD(circle_count)), bom_gh[3], TRUE);
	SetDrawBright(255, 255, 255);

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

	LoadDivGraph("Resources/Textures/player_bullet.png", 4, 1, 4, 48, 48, player_shot_gh);
}
void MovePlayerShot(void)
{
	int i;
	int temp = 0;


	if (!dead_flag)
	{
		// Ｚキーが押されて, 4フレームに一発発射する
		if ((GetInputKeyData(KEY_INPUT_Z)) && (GetGameCount() % 5 == 0))
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
						player_shot[i].base.sprite.texture = player_shot_gh[1];
						break;

					case 2:
						player_shot[i].base.sprite.texture = player_shot_gh[1];
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
						player_shot[i].base.sprite.texture = player_shot_gh[1];
						if (temp == 0)
						{
							player_shot[i].base.pos.x = magic_ball[0].x;
							player_shot[i].base.pos.y = magic_ball[0].y;
							player_shot[i].base.vel.x = 0;
							temp = 1;
						}
						else if (temp == 1)
						{
							player_shot[i].base.pos.x = magic_ball[1].x;
							player_shot[i].base.pos.y = magic_ball[1].y;
							player_shot[i].base.vel.x = 0;
							temp = 2;
						}
						else
						{
							player_shot[i].base.pos.x = magic_ball[2].x;
							player_shot[i].base.pos.y = magic_ball[2].y;
							player_shot[i].base.vel.x = 0;
							//player_shot[i].base.speed.x = player_shot[i].base.speed.y = 12.0 / 13.0;
							temp = 3;
						}
						break;

					case 4:
						if (temp == 0)
						{
							player_shot[i].base.pos.x = player.pos.x;
							player_shot[i].base.pos.y = player.pos.y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.sprite.texture = player_shot_gh[2];
							temp = 1;
						}
						else if (temp == 1)
						{
							player_shot[i].base.pos.x = magic_ball[0].x;
							player_shot[i].base.pos.y = magic_ball[0].y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.sprite.texture = player_shot_gh[1];
							temp = 2;
						}
						else if (temp == 2)
						{
							player_shot[i].base.pos.x = magic_ball[1].x;
							player_shot[i].base.pos.y = magic_ball[1].y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.sprite.texture = player_shot_gh[1];
							temp = 3;
						}
						else
						{
							player_shot[i].base.pos.x = magic_ball[2].x;
							player_shot[i].base.pos.y = magic_ball[2].y;
							player_shot[i].base.vel.x = 0;
							player_shot[i].base.sprite.texture = player_shot_gh[1];
							//player_shot[i].base.speed.x = player_shot[i].base.speed.y = 12.0 / 13.0;
							temp = 4;
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
						if (shot_power == 4)
						{
							if (temp == 1)
							{
								continue;
							}
							else if (temp == 2)
							{
								continue;
							}
							else if (temp == 3)
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
			switch (shot_power)
			{
			case 4:
				player_shot[i].base.pos.x += player_shot[i].base.vel.x * player_shot[i].base.speed.x;
				player_shot[i].base.pos.y -= player_shot[i].base.vel.y * player_shot[i].base.speed.y;
				break;

			default:
				player_shot[i].base.pos.x += player_shot[i].base.vel.x * player_shot[i].base.speed.x;
				player_shot[i].base.pos.y -= player_shot[i].base.vel.y * player_shot[i].base.speed.y;
				break;
			}
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
			DrawRotaGraph(player_shot[i].base.pos.x, player_shot[i].base.pos.y,
				1.0, 0.0, player_shot[i].base.sprite.texture, TRUE);
		}
	}
}

void PlayBom(void)
{
	if ((GetInputKeyData(KEY_INPUT_X)) && (!GetInputKeyOldData(KEY_INPUT_X)))
	{
		if ((player_bom > 0) && (!bom_flag))
		{
			player_bom -= 1;
			bom_flag = TRUE;
		}
	}
}
void InitBomShot(void)
{
	int i;

	for (i = 0; i < BOM_SHOT_NUM; i++)
	{
		bom_shot[i].r = 64;
		bom_shot[i].base.pos = player.pos;
		bom_shot[i].base.vel = { 0,0 };
		bom_shot[i].angle = bom_shot[i].rad = 0;
	}
}
void MoveBom(BOMB type)
{
	int i, j;
	switch (type)
	{
	case 1:
		for (i = 0; i < BOM_SHOT_NUM; i++)
		{
			bom_shot[i].base.vel.x = cos(DEG_TO_RAD(180 - (i * 45)));
			bom_shot[i].base.vel.y = -sin(DEG_TO_RAD(180 - (i * 45)));

			bom_shot[i].base.pos.x += bom_shot[i].base.vel.x * 5;
			bom_shot[i].base.pos.y += bom_shot[i].base.vel.y * 5;
		}
		for (i = 0; i < GetEnemyNum(); i++)
		{
			if ((enemy_flag[i]) && (GetGameCount() > enemy[i].in_time))
			{
				if (CircleCollision(ENEMY_SIZE, (127 * 3), enemy[i].x, player.pos.x, enemy[i].y, player.pos.y))
				{
					SetEnemyDeadFlag(i);
					SetDeadEffect(i);
					SetEnemyKillScore();
					SetItemFlag(enemy[i].item, enemy[i].x, enemy[i].y);
				}
				for (j = 0; j < BOM_SHOT_NUM; j++)
				{
					if (CircleCollision(ENEMY_SIZE, bom_shot[j].r, enemy[i].x, bom_shot[j].base.pos.x, enemy[i].y, bom_shot[j].base.pos.y))
					{
						SetEnemyDeadFlag(i);
						SetDeadEffect(i);
						SetEnemyKillScore();
						SetItemFlag(enemy[i].item, enemy[i].x, enemy[i].y);
					}
				}
			}
		}
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			if (enemy_shot[j].flag)
			{
				if (CircleCollision(enemy_shot[j].r, (127 * 3), enemy_shot[j].base.pos.x, player.pos.x, enemy_shot[j].base.pos.y, player.pos.y))
				{
					SetItemFlag(0, enemy_shot[j].base.pos.x, enemy_shot[j].base.pos.y);
					enemy_shot[j].flag = FALSE;
				}
				for (i = 0; i < BOM_SHOT_NUM; i++)
				{
					if (CircleCollision(enemy_shot[j].r, bom_shot[i].r, enemy_shot[j].base.pos.x, bom_shot[i].base.pos.x, enemy_shot[j].base.pos.y, bom_shot[i].base.pos.y))
					{
						SetItemFlag(0, enemy_shot[j].base.pos.x, enemy_shot[j].base.pos.y);
						enemy_shot[j].flag = FALSE;
					}
				}
			}
		}
		if (GetBossFlag())
		{
			if (CircleCollision(BOSS_SIZE, (127 * 3), GetBossPosX(), player.pos.x, GetBossPosY(), player.pos.y))
			{
				BossDamage(1);
			}
			
		}

		if (GetBossFlag())
		{
			for (j = 0; j < BOSS_SHOT_NUM; j++)
			{
				for (i = 0; i < BOM_SHOT_NUM; i++)
				{
					if (boss_shot[j].flag)
					{
						if (CircleCollision(boss_shot[j].r, bom_shot[i].r, boss_shot[j].pos.x, bom_shot[i].base.pos.x, boss_shot[j].pos.y, bom_shot[i].base.pos.y))
						{
							SetItemFlag(0, boss_shot[j].pos.x, boss_shot[j].pos.y);
							boss_shot[j].flag = FALSE;
						}
					}
				}

				if (CircleCollision(boss_shot[j].r, (127 * 3), boss_shot[j].pos.x, player.pos.x, boss_shot[j].pos.y, player.pos.y))
				{
					if (boss_shot[j].flag)
					{
						SetItemFlag(0, boss_shot[j].pos.x, boss_shot[j].pos.y);
						boss_shot[j].flag = FALSE;
					}
				}
			}
		}
		break;
	}
	if (bom_count > 180)
	{
		bom_flag = FALSE;
		InitBomShot();
		bom_deg[0] = 0;
		bom_count = 0;
	}
	else
	{
		bom_count++;
	}
}
void DrawBom(BOMB type)
{
	int i;
	switch (type)
	{
	case 1:
		bom_rad[0] = DEG_TO_RAD(bom_deg[0]);
		if (bom_deg[0] < 90)
		{
			bright[0] += 9;
		}
		if (bom_deg[0] >= 90)
		{
			bright[0] -= 9;
		}


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright[0]);
		SetDrawBright(64, 64, 255);
		DrawRotaGraph(player.pos.x, player.pos.y, 3.0, bom_rad[0], bom_gh[0], TRUE);
		DrawRotaGraph(player.pos.x, player.pos.y, 2.0, -bom_rad[0], bom_gh[3], TRUE);
		for (i = 0; i < BOM_SHOT_NUM; i++)
		{
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(bom_shot[i].base.pos.x, bom_shot[i].base.pos.y, 1.0, bom_rad[0], bom_shot[i].base.sprite.texture, TRUE);
		}
		SetDrawBright(255, 255, 255);
		bom_deg[0]++;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
}

void DrawCutin(void)
{
	static int bar_bright = 0;

	if (cutin_pos.x == 0 || cutin_pos.y == 0)
	{
		cutin_pos.x = (GAME_SCREEN_CENTER_X / 2);
		cutin_pos.y = (GAME_SCREEN_CENTER_Y / 2 * 3);
		cutin_bar_pos[0] = { cutin_pos.x,cutin_pos.y + 80 };
		cutin_bar_pos[1] = { cutin_pos.x + 300,cutin_pos.y };
	}

	if (bom_deg[0] < 90)
	{
		bar_bright += 9;
	}
	if (bom_deg[0] >= 90)
	{
		bar_bright -= 9;
	}

	if (bright[0] <= 0)
	{
		cutin_pos = { 0,0 };
		bar_bright = 0;
	}
	else
	{
		cutin_pos.x += 0.5;
		cutin_bar_pos[0].x -= 0.5;
		cutin_bar_pos[1].y += 0.5;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright[0]);
	DrawRotaGraph(cutin_pos.x, cutin_pos.y, 0.5, 0.0, cutin_gh, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bar_bright);
	DrawRotaGraph(cutin_bar_pos[0].x + 300, cutin_bar_pos[0].y, 2.0, 0.0, cutin_bar_gh[0], TRUE);
	DrawRotaGraph(cutin_bar_pos[1].x, cutin_bar_pos[1].y - 200, 2.0, 0.0, cutin_bar_gh[1], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawPlayerDeadEffect(void)
{
	static Vector2D p_pos = { 0,0 };

	if (player_dead_effect_flag)
	{
		if (p_pos.x == 0)
		{
			p_pos = player.pos;
		}
		DrawRotaGraph(p_pos.x, p_pos.y, 0.75, DEG_TO_RAD(dead_effect_deg), player_dead_effect_gh, TRUE);
		dead_effect_deg += 20;

	}
	else
	{
		p_pos = { 0,0 };
	}
}
void SetPlayerDeadEffectFlag(void)
{
	player_dead_effect_flag = TRUE;
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
BOOL GetPlayerDeadFlag(void)
{
	return dead_flag;
}

int GetPlayerShotPosX(int i)
{
	return player_shot[i].base.pos.x;
}
int GetPlayerShotPosY(int i)
{
	return player_shot[i].base.pos.y;
}

void SetPlayerShotFALSE(int i)
{
	player_shot[i].flag = FALSE;
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
void SetShotPower4(void)
{
	shot_power = 4;
}
