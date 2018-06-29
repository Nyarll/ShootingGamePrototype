#include "Back.h"

static Sprite back;				// îwåióp

void InitBack(const TCHAR *file_name)
{
	back.texture = LoadGraph(file_name);
	back.x = 0;	back.y = 0;
}
void MoveBack(void)
{
	back.y++;

	if (back.y == GAME_SCREEN_BOTTOM * 4)
	{
		back.y = 0;
	}
}
void DrawBack(void)
{
	DrawGraph(back.x, back.y, back.texture, TRUE);
	DrawGraph(back.x, back.y - GAME_SCREEN_BOTTOM * 4, back.texture, TRUE);
}
