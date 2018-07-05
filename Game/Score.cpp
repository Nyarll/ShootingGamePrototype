#include "Score.h"
#include "Player.h"

#define SCORE_X (SCREEN_CENTER_X + 140)

static HGRP score_gh[10];
static char buf[100];
static int score;
static int graze_num;
static int num;

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
	// ハイスコア
	num = sprintf(buf, "%d", score);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 35, score_gh[(buf[i] - '0')], TRUE);
	}

	// スコア
	num = sprintf(buf, "%d", score);
	for (int i = 0; i < num; ++i) 
	{
		DrawGraph(SCORE_X + 20 + i * 19, 95, score_gh[(buf[i] - '0')], TRUE);
	}

	// グレイズ
	num = sprintf(buf, "%d", graze_num);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 155, score_gh[(buf[i] - '0')], TRUE);
	}

	// 残機
	num = sprintf(buf, "%d", player_life);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 215, score_gh[(buf[i] - '0')], TRUE);
	}

	// 残ボム
	num = sprintf(buf, "%d", player_bom);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 275, score_gh[(buf[i] - '0')], TRUE);
	}
}

void SetEnemyKillScore(void)
{
	score += 20;
}
void SetItemGet(int index = 1)
{
	switch (index)
	{
	case 0:	// スコアアイテム
		score += 10;
		break;

	case 1:	// パワーアップ
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