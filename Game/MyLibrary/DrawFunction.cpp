#include "DrawFunction.h" 
#include "GameDefineHeader.h"

// 画像のフェードイン/フェードアウト
// ( *file_name ) / 表示したい画像の場所/名称.拡張子
void DrawLogo(const TCHAR *file_name)
{
	// ローカル変数宣言
	static int bright = 0;
	static int logo_time = 0;
	static HGRP logo_handle;
	static BOOL bright_flag = FALSE;

	if (logo_handle == NULL)
	{
		if (-1 == (logo_handle = LoadGraph(file_name)))
		{
			MSG("Not Found Logo Files")
		}
	}

	// 描画
	SetDrawBright(bright, bright, bright);
	DrawGraph(0, 0, logo_handle, TRUE);
		if (!bright_flag)
	{
		bright += 5;
		if (bright > 255)
		{
			bright_flag = TRUE;
		}
	}
	else
	{
		if (logo_time > 30)
		{
			bright -= 5;
		}
		else
		{
			logo_time++;
		}
		if (bright < 0)
		{
			DeleteGraph(logo_handle);
			return;
		}
	}
}
