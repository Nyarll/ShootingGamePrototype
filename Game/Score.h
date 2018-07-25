#pragma once

extern int high_score;
extern int score;

void InitScore(void);
void UpdateScore(void);
void DrawScore(void);

void SetEnemyKillScore(void);
void SetItemGet(int index);

void SetGrazeScore(void);

int GetPowerUpItemNum(void);