#pragma once

typedef struct
{
	Vector2D pos;
	Vector2D vel;
	BOOL flag;

	HGRP tex;
}BOSS;

extern BOSS boss;

void InitBoss(void);
void MoveBoss(void);
void DrawBoss(void);