#pragma once

//メッセージボックス / NULL, m(表示メッセージ), "window name", MB_OK
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("ゲームを終了します") PostQuitMessage(0);}

#define PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / PI))


// <画面> --------------------------------------------------------------
#define SCREEN_WIDTH    (1000)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (800)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

// 以下ゲームによって変更する

#define GAME_SCREEN_LEFT	(SCREEN_LEFT)
#define GAME_SCREEN_TOP		(SCREEN_TOP)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 10)	// プレイヤーが動ける範囲 X 600
#define GAME_SCREEN_BOTTOM	(SCREEN_HEIGHT)							// プレイヤーが動ける範囲 Y 800
#define GAME_SCREEN_CENTER_X (GAME_SCREEN_RIGHT / 2)
#define GAME_SCREEN_CENTER_Y (GAME_SCREEN_BOTTOM / 2)

#define GAME_TIME 4000

#define GAME_STAGE_MAX 2	// ステージの最大数


#define PLAYER_SIZE 64
#define PLAYER_SPEED 6
#define PLAYER_SHOT_NUM 128
#define PLAYER_SHOT_SIZE 5

#define ENEMY_SIZE 10

#define ENEMY_SHOT_NUM 4096
#define ENEMY_TYPE_NUM 1

// ステージごとのエネミーの数
#define ENEMY_NUM1 (61)
#define ENEMY_NUM2 (5)

typedef int LIFE;
typedef int BOMB;

typedef enum
{
	SCENE_NONE = -1,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_PLAY,
	SCENE_RESULT

}SceneID;
