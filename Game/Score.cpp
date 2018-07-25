#include "Score.h"
#include "Player.h"

#define SCORE_X (SCREEN_CENTER_X + 140)

static HGRP score_gh[10];
static char buf[100];
int score;
static int graze_num;
static int num;

int high_score;

static int powerup_itemnum = 0;

void InitScore(void)
{
	score = 0;
	graze_num = 0;
	LoadDivGraph("Resources/Textures/num_white.png", 10, 10, 1, 19, 27, score_gh);
}
void UpdateScore(void)
{

}
void DrawScore(void)
{
	SetFontSize(20);

	// ハイスコア
	if (high_score > score)
	{
		num = sprintf(buf, "%d", high_score);
	}
	else
	{
		num = sprintf(buf, "%d", score);
	}
	DrawFormatString(SCORE_X, 15, COLOR_WHITE, "High Score");
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 35, score_gh[(buf[i] - '0')], TRUE);
	}

	// スコア
	num = sprintf(buf, "%d", score);
	DrawFormatString(SCORE_X, 75, COLOR_WHITE, "Score");
	for (int i = 0; i < num; ++i) 
	{
		DrawGraph(SCORE_X + 20 + i * 19, 95, score_gh[(buf[i] - '0')], TRUE);
	}

	// グレイズ
	num = sprintf(buf, "%d", graze_num);
	DrawFormatString(SCORE_X, 135, COLOR_WHITE, "Graze");
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 155, score_gh[(buf[i] - '0')], TRUE);
	}

	// power up item num
	num = sprintf(buf, "%d", powerup_itemnum);
	DrawFormatString(SCORE_X, 195, COLOR_WHITE, "Power UP items");
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 215, score_gh[(buf[i] - '0')], TRUE);
	}

	// 残機
	num = sprintf(buf, "%d", player_life);
	DrawFormatString(SCORE_X, 255, COLOR_WHITE, "Life");
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 275, score_gh[(buf[i] - '0')], TRUE);
	}

	// 残ボム
	num = sprintf(buf, "%d", player_bom);
	DrawFormatString(SCORE_X, 315, COLOR_WHITE, "Bom");
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 335, score_gh[(buf[i] - '0')], TRUE);
	}
}

void SetEnemyKillScore(void)
{
	score += 20;
}
void SetItemGet(int index)
{
	switch (index)
	{
	case 0:	// スコアアイテム
		score += 10;
		break;

	case 1:	// パワーアップ
		powerup_itemnum += 10;
		break;

	case 2:	// ボム
		player_bom += 1;
		break;

	case 3:	// 残機
		player_life += 1;
		break;

	}
}

void SetGrazeScore(void)
{
	score += 5;
	graze_num += 1;
}

int GetPowerUpItemNum(void)
{
	return powerup_itemnum;
}