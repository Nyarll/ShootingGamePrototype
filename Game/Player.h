#pragma once

extern LIFE player_life;
extern BOMB player_bom;

extern BOMB player_bom_type;
extern BOOL bom_flag;

void InitPlayer(void);		// プレイヤーの初期化
void MovePlayer(void);		// プレイヤーの移動
void DrawPlayer(void);		// プレイヤーの描画

void MoveMagicCircle(void);	// 魔法陣の周囲の●
void DrawMagicCircle(void);

void InitPlayerShot(void);	// プレイヤーの弾の初期化
void MovePlayerShot(void);	// プレイヤーの弾の移動
void DrawPlayerShot(void);	// プレイヤーの弾の描画

void PlayBom(void);

void InitBomShot(void);
void MoveBom(BOMB type);
void DrawBom(BOMB type);

void DrawCutin(void);

void DrawPlayerDeadEffect(void);
void SetPlayerDeadEffectFlag(void);

double GetPlayerPosX(void);
double GetPlayerPosY(void);

BOOL GetPlayerShotFlag(int i);
BOOL GetPlayerDeadFlag(void);

int GetPlayerShotPosX(int i);
int GetPlayerShotPosY(int i);

void SetPlayerShotFALSE(int i);

int GetShotPower(void);

void SetPlayerDeadFlag(void);

void SetShotPower1(void);
void SetShotPower2(void);
void SetShotPower3(void);
void SetShotPower4(void);