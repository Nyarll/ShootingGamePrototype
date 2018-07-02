#include "Score.h"

#define SCORE_X (SCREEN_CENTER_X + 140)

static HGRP score_gh[10];
static char buf[100];
static int score;
static int num;

void InitScore(void)
{
	score = 0;
	LoadDivGraph("Resources/Textures/num_white.png", 10, 10, 1, 19, 27, score_gh);
}
void UpdateScore(void)
{

}
void DrawScore(void)
{
	num = sprintf(buf, "%d", score);

	for (int i = 0; i < num; ++i) {

		DrawGraph(SCORE_X + 20 + i * 19, 95, score_gh[(buf[i] - '0')], TRUE);

	}

}

void SetEnemyKillScore(void)
{
	score += 20;
}
void SetItemGetScore(int index = 1)
{
	score += 10 * index;
}