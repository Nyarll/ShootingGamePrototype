#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Back.h"
#include "Score.h"
#include "Item.h"
#include "Graze.h"
#include "Defines.h"

#define PLAYER_R (PLAYER_SIZE / 14)

static int game_stage;
static BOOL stage_clear_flag;

static HGRP game_logo;

static BOOL debug_flag;


void InitPlay(void)
{
	if (game_stage == 0)
	{
		game_stage = 1;
	}

	stage_clear_flag = TRUE;

	debug_flag = FALSE;

	game_logo = LoadGraph("Resources/Textures/sample.png");

	InitBack("Resources/Textures/Stage1_back.png");
	player_bom_type = 1;	// デフォ
	InitPlayer();		// プレイヤーの初期化
	InitPlayerShot();	// プレイヤーの弾の初期化
	InitScore();
	InitItem();
	InitGraze();
}
void UpdatePlay(void)
{
	int i;

	InitStage();

	MovePlayer();
	MoveBack();
	MovePlayerShot();
	PlayBom();
	if (bom_flag)
	{
		MoveBom(player_bom_type);
	}
	else
	{
		InitBomShot();
	}
	MoveEnemy();

	for (i = 0; i < GetEnemyNum(); i++)
	{
		SetEnemyShot(i);
	}

	MoveEnemyShot();

	PlayerShot_EnemyCollision();
	EnemyShot_PlayerCollision();
	GrazeCollision();
	Player_ItemCollision();

	MoveItem();
	MoveGraze();
	UpdateScore();

	UseDebug();

	GameOverCheck();
	StageClearCheck();

	UpdateKeyOld();

}
void RenderPlay(void)
{
	int i;
	SetDrawBright(255, 255, 255);

	DrawGameObject();

	for (i = 0; i < GetEnemyNum(); i++)
	{
		DrawEnemyShot(i);
	}
	DrawBox(GAME_SCREEN_RIGHT, 0, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_BLACK, TRUE);
	DrawBox(GAME_SCREEN_RIGHT, 0, GAME_SCREEN_RIGHT + 10, GAME_SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	DrawScore();

	DrawDebug();
}

void FinalPlay(void)
{

}

void DrawGameObject(void)
{
	DrawBack();

	if (bom_flag)
	{
		DrawBom(1);
	}

	SetDrawBright(255, 255, 255);
	DrawPlayerShot();
	DrawItem();
	DrawGraze();
	DrawPlayer();
	DrawEnemy();
}

void InitStage(void)
{
	if (stage_clear_flag)
	{
		InitEnemy(game_stage);
		stage_clear_flag = FALSE;
		InitGameCount();
		/*switch (game_stage)
		{
		case 1:
		InitBack("Resources/Textures/Stage1_back.png");
		break;

		case 2:
		InitBack("Resources/Textures/Stage1_back.png");
		break;

		default:
		MSG("Not Found")
		EXIT
		break;
		}*/
	}
}
void StageClearCheck(void)
{
	switch (game_stage)
	{
	case 1:
		if (GetGameCount() > GAME_TIME)
		{
			stage_clear_flag = TRUE;
			InitGameCount();
			game_stage++;
		}
		break;

	case 2:
		if (GetGameCount() > GAME_TIME)
		{
			stage_clear_flag = TRUE;
			InitGameCount();
			game_stage++;
		}
		break;
	}
}
void GameOverCheck(void)
{
	if (player_life < 0)
	{
		MSG("残機が無くなりました");
		EXIT;
	}
}

void PlayerShot_EnemyCollision(void)
{
	int i, j;
	int enemy_num = GetEnemyNum();

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		for (j = 0; j < GetEnemyNum(); j++)

			if (GetPlayerShotFlag(i))
			{
				if (GetEnemyDeadFlag(j))
				{
					if (CircleCollision(PLAYER_SHOT_SIZE, ENEMY_SIZE, GetPlayerShotPosX(i), GetEnemyPosX(j), GetPlayerShotPosY(i), GetEnemyPosY(j)))
					{
						SetEnemyDeadFlag(j);
						SetEnemyKillScore();
						SetItemFlag(enemy[j].item, enemy[j].x, enemy[j].y);
					}

				}
			}
	}
}
void EnemyShot_PlayerCollision(void)
{
	int i;

	if (!GetPlayerDeadFlag())
	{
		for (i = 0; i < ENEMY_SHOT_NUM; i++)
		{
			if (enemy_shot[i].flag)
			{
				if (CircleCollision(enemy_shot[i].r, PLAYER_R, enemy_shot[i].base.pos.x, GetPlayerPosX(), enemy_shot[i].base.pos.y, GetPlayerPosY()))
				{
					SetPlayerDeadFlag();
					player_life -= 1;
					player_bom = 3;
					break;
				}
			}
		}
	}
}
void GrazeCollision(void)
{
	int i;

	if (!GetPlayerDeadFlag())
	{
		for (i = 0; i < ENEMY_SHOT_NUM; i++)
		{
			if (enemy_shot[i].flag)
			{
				if (CircleCollision(enemy_shot[i].r, (PLAYER_SIZE / 4), enemy_shot[i].base.pos.x, GetPlayerPosX(), enemy_shot[i].base.pos.y, GetPlayerPosY()))
				{
					SetGrazeFlag();
					break;
				}
			}
		}
	}
}
void Player_ItemCollision(void)
{
	int i;

	for (i = 0; i < GetItemNum(); i++)
	{
		if (item[i].flag)
		{
			if (CircleCollision(PLAYER_R, ITEM_R, GetPlayerPosX(), item[i].pos.x, GetPlayerPosY(), item[i].pos.y))
			{
				ItemDelete(i);
				SetItemGet(item[i].type);
			}
		}
	}
}

void UseDebug(void)
{
	if (GetInputKeyData(KEY_INPUT_1) == 1)
	{
		SetShotPower1();
	}
	else if (GetInputKeyData(KEY_INPUT_2) == 1)
	{
		SetShotPower2();
	}
	else if (GetInputKeyData(KEY_INPUT_3) == 1)
	{
		SetShotPower3();
	}

	if ((GetInputKeyData(KEY_INPUT_D)) && (!GetInputKeyOldData(KEY_INPUT_D)))
	{
		if (debug_flag)
		{
			debug_flag = FALSE;
		}
		else
		{
			debug_flag = TRUE;
		}
	}
}
void DrawDebug(void)
{
	if (debug_flag)
	{

		DrawFormatString((SCREEN_CENTER_X + 200), 0, COLOR_WHITE, "Now : %d", GetGameCount());
		DrawFormatString((SCREEN_CENTER_X + 140), 20, COLOR_WHITE, "player_pos_x : %.1lf", GetPlayerPosX());
		DrawFormatString((SCREEN_CENTER_X + 140), 40, COLOR_WHITE, "player_pos_y : %.1lf", GetPlayerPosY());
		DrawFormatString((SCREEN_CENTER_X + 140), 70, COLOR_WHITE, "shot_power : %d", GetShotPower());

		DrawFormatString((SCREEN_CENTER_X + 140), 100, COLOR_WHITE, "shot_speed : %.1lf", GetEnemyShotSpeedY());
		DrawFormatString((SCREEN_CENTER_X + 140), 120, COLOR_WHITE, "shot_Vel   : %.1lf", GetEnemyShotVelY());

		DrawGraph((GAME_SCREEN_RIGHT + 10), (GAME_SCREEN_BOTTOM - 390), game_logo, TRUE);

		// 当たり判定の表示
		DrawCircle(GetPlayerPosX(), GetPlayerPosY(), PLAYER_R, COLOR_RED, FALSE, 3);

		// グレイズ判定の表示
		DrawCircle(GetPlayerPosX(), GetPlayerPosY(), (PLAYER_SIZE / 4), COLOR_PURPLE, FALSE, 2);

		//
		DrawBox((GetPlayerPosX() - PLAYER_SIZE / 4), (GetPlayerPosY() - PLAYER_SIZE * 4), (GetPlayerPosX() + PLAYER_SIZE / 4), GetPlayerPosY(), COLOR_RED, FALSE);
	}
}
