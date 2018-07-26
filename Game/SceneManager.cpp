#include "SceneManager.h"
#include "PlayScene.h"
#include "Result.h"
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
	next_scene = SCENE_LOGO;

	scene_count = 0;

	logo_handle = LoadGraph("Resources/Textures/極東陰陽録.png");

	InitGameCount();
	InitPlay();
	InitResult();

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
	UpdateKey();

	switch (active_scene)
	{
	case SCENE_LOGO:
		if (scene_count > 180)
		{
			active_scene = next_scene;
			next_scene = SCENE_PLAY;
		}
		scene_count++;
		break;

	case SCENE_TITLE:
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
		UpdateResult();
		if (GetInputKeyData(KEY_INPUT_SPACE) && (!GetInputKeyOldData(KEY_INPUT_SPACE)))
		{
			InitGameCount();
			InitPlay();
			InitResult();
			active_scene = next_scene;
			next_scene = SCENE_PLAY;
		}
		break;
	}
	UpdateKeyOld();
}

void SetResultScene(void)
{
	active_scene = next_scene;
	next_scene = SCENE_TITLE;
}

// シーンの描画
void RenderScene(void)
{
	static int cnt = 0;
	switch (active_scene)
	{
	case SCENE_LOGO:
		DrawLogo("Resources/Textures/MyLogo_1000_800.png");
		break;

	case SCENE_TITLE:
		SetDrawBright(255, 255, 255);
		DrawGraph(0, 0, logo_handle, TRUE);
		if ((cnt % 80) / 40)
		{
			SetFontSize(30);
			DrawFormatString(SCREEN_CENTER_X - 140, SCREEN_CENTER_Y / 2 * 3, COLOR_RED, "Push to SPACE KEY !");
		}
		cnt++;
		break;

	case SCENE_PLAY:
		RenderPlay();
		if (cnt != 0)
		{
			cnt = 0;
		}
		break;

	case SCENE_RESULT:
		//DrawFormatString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, COLOR_WHITE, "リザルト");
		RenderResult();
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