#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Back.h"
#include "Score.h"
#include "Item.h"
#include "Defines.h"

#define PLAYER_R (PLAYER_SIZE / 12)

static int game_stage;
static BOOL stage_clear_flag;

static HGRP game_logo;


void InitPlay(void)
{
	if (game_stage == 0)
	{
		game_stage = 1;
	}

	stage_clear_flag = TRUE;

	game_logo = LoadGraph("Resources/Textures/sample.png");

	InitBack("Resources/Textures/Stage1_back.png");
	InitPlayer();		// プレイヤーの初期化
	InitPlayerShot();	// プレイヤーの弾の初期化
	InitScore();
	InitItem();
}
void UpdatePlay(void)
{
	int i;

	InitStage();

	MovePlayer();
	MoveBack();
	MovePlayerShot();
	MoveEnemy();

	for (i = 0; i < GetEnemyNum(); i++)
	{
		SetEnemyShot(i);
	}

	MoveEnemyShot();
	
	PlayerShot_EnemyCollision();
	EnemyShot_PlayerCollision();

	MoveItem();
	UpdateScore();

	UseDebug();

	StageClearCheck();

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

	//DrawDebug();
}

void FinalPlay(void)
{

}


void DrawGameObject(void)
{
	DrawBack();
	DrawPlayerShot();
	DrawItem();
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
						SetItemFlag(enemy[j].item, &enemy[j].x, &enemy[j].y);
					}

				}
			}
	}
}
void EnemyShot_PlayerCollision(void)
{
	int i;

	for (i = 0; i < ENEMY_SHOT_NUM; i++)
	{
		if (CircleCollision(enemy_shot[i].r, PLAYER_R, enemy_shot[i].base.pos.x, GetPlayerPosX(), enemy_shot[i].base.pos.y, GetPlayerPosY()))
		{
			SetPlayerDeadFlag();
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
}
void DrawDebug(void)
{
	static BOOL debug_flag = TRUE;

	if ((GetInputKeyData(KEY_INPUT_F6)) && (!GetInputKeyOldData(KEY_INPUT_F6)) && (debug_flag == FALSE))
	{
		debug_flag = TRUE;
	}
	else if ((GetInputKeyData(KEY_INPUT_F6)) && (!GetInputKeyOldData(KEY_INPUT_F6)) && (debug_flag == TRUE))
	{
		debug_flag = FALSE;
	}

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
