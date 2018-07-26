#pragma once

extern FILE *fp;					// エネミーデータをcsvファイルから読み込む用
extern EnemyData enemy[256];		// エネミーオブジェクト
extern EnemyData data[256];		// バッファ
extern int enemy_num;				// エネミーの数
extern BOOL enemy_flag[256];		// 死んだらFALSE
extern BOOL enemy_cross_flag[256];	// プレイヤーと重なったか

extern Shot enemy_shot[ENEMY_SHOT_NUM];	// エネミーの弾オブジェクト
extern double shot_speed_data[ENEMY_SHOT_NUM];
extern BOOL shot_flag[ENEMY_SHOT_NUM];
extern int shot_count[ENEMY_SHOT_NUM];
extern int shotwait_count[ENEMY_SHOT_NUM];
extern int s[256];	// 発射中の弾の数
extern double rad[ENEMY_SHOT_NUM];

extern double enemy_angle[256];
extern Vector2D enemy_vel[256];

extern HGRP enemy_shot_graph[384];

void InitEnemy(int stage);		// エネミーの初期化
void FileStreamEnemy(const TCHAR *file_name);	// エネミーデータの読み込み
void SetEnemyNum(int stage);	// エネミーの数の設定
void MoveEnemy(void);		// エネミーの移動
void DrawEnemy(void);		// エネミーの描画

void EnemyMovePatternDebug(int i);	// 移動パターンDebug mode
void EnemyMovePattern0(int i);	// 移動パターン0
void EnemyMovePattern1(int i);	// 移動パターン1
void EnemyMovePattern2(int i);	// 移動パターン2
void EnemyMovePattern3(int i);	// 移動パターン3
void EnemyMovePattern4(int i);	// 移動パターン4
void EnemyMovePattern5(int i);
void EnemyMovePattern6(int i);

void InitEnemyShot(void);	// エネミーの弾の初期化
void SetEnemyShot(int index);	// エネミーの弾のセット
void MoveEnemyShot(void);	// エネミーの弾の移動
void DrawEnemyShot(int o);	// エネミーの弾の描画

void SetEnemyShotGraph(int e_index, int j);

// ショットパターン

void EnemyShotPattern0(int i);		// ショットパターン 0
void EnemyShotPattern1(int i);		// ショットパターン 1
void EnemyShotPattern2(int i);		// ショットパターン 2
void EnemyShotPattern3(int i);		// ショットパターン 3
void EnemyShotPattern4(int i);		// ショットパターン 4
void EnemyShotPattern5(int i);		// ショットパターン 5
void EnemyShotPattern6(int i);		// ショットパターン 6
void EnemyShotPattern7(int i);		// ショットパターン 7
void EnemyShotPattern8(int i);		// ショットパターン 8
void EnemyShotPattern9(int i);		// ショットパターン 9
void EnemyShotPattern10(int i);		// ショットパターン 10
void EnemyShotPattern11(int i);		// ショットパターン 11
void EnemyShotPattern12(int i);		// ショットパターン 12
void EnemyShotPattern13(int i);		// ショットパターン 13
void EnemyShotPattern14(int i, int num);		// ショットパターン 14
void EnemyShotPattern15(int i);		// ショットパターン 15

void SetEnemyDeadFlag(int i);
BOOL GetEnemyDeadFlag(int i);

int GetEnemyPosX(int i);
int GetEnemyPosY(int i);

int GetEnemyNum(void);

BOOL GetEnemyShotFlag(int i);
double GetEnemyShotSpeedY(void);
double GetEnemyShotVelY(void);

void DrawEnemyDeadEffect(void);
void SetDeadEffect(int index);