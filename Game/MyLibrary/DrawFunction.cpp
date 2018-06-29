#include "DrawFunction.h" 
#include "GameDefineHeader.h"

// �摜�̃t�F�[�h�C��/�t�F�[�h�A�E�g
// ( *file_name ) / �\���������摜�̏ꏊ/����.�g���q
void DrawLogo(const TCHAR *file_name)
{
	// ���[�J���ϐ��錾
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

	// �`��
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
