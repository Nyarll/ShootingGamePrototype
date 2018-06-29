#include "SceneManager.h"
#include "PlayScene.h"
#include "Defines.h"

// グローバル変数

static SceneID active_scene;
static SceneID next_scene;

static int scene_count;

static HGRP logo_handle;


// シーンの初期化
void InitScene(void)
{
	active_scene = SCENE_NONE;
	next_scene = SCENE_PLAY;

	scene_count = 0;

	logo_handle = LoadGraph("Resources/Textures/gunnmaken.png");

	InitGameCount();
	InitPlay();

	if (next_scene != SCENE_NONE)
	{
		active_scene = next_scene;
		next_scene = SCENE_TITLE;
	}
}

// シーンの更新
void UpdateScene(void)
{
	
	UpdateGameCount();

	switch (active_scene)
	{
	case SCENE_LOGO:
		if (scene_count > 180)
		{
			active_scene = next_scene;
			next_scene = SCENE_MENU;
		}
		scene_count++;
		break;

	case SCENE_TITLE:
		if (GetInputKeyData(KEY_INPUT_SPACE) && (!GetInputKeyOldData(KEY_INPUT_SPACE)))
		{
			active_scene = next_scene;
			next_scene = SCENE_PLAY;
		}
		break;

	case SCENE_MENU:
		if (GetInputKeyData(KEY_INPUT_SPACE) && (!GetInputKeyOldData(KEY_INPUT_SPACE)))
		{
			active_scene = next_scene;
			next_scene = SCENE_RESULT;
		}
		break;

	case SCENE_PLAY:
		UpdatePlay();
		break;

	case SCENE_RESULT:
		break;
	}
	UpdateKeyOld();
}

// シーンの描画
void RenderScene(void)
{
	switch (active_scene)
	{
	case SCENE_LOGO:
		DrawLogo("Resources/Textures/MyLogo_1000_800.png");
		break;

	case SCENE_TITLE:
		SetDrawBright(255, 255, 255);
		DrawGraph(0, 0, logo_handle, TRUE);
		break;

	case SCENE_MENU:
		SetDrawBright(255, 255, 255);
		DrawBox(0, 0, 40, 40, COLOR_RED, TRUE);
		break;

	case SCENE_PLAY:
		RenderPlay();
		break;

	case SCENE_RESULT:
		DrawFormatString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, COLOR_WHITE, "リザルト");
		break;
	}
	
}


// シーンの終了処理
void FinalScene(void)
{

}

void RequestScene(SceneID scene_id)
{

}