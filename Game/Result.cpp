#include "Result.h"
#include "Score.h"

void InitResult(void)
{
	FILE *fp = NULL;

	fopen_s(&fp, "Game/HighScore.txt", "r");
	fscanf_s(fp, "%d", &high_score);
	fclose(fp);
}
void UpdateResult(void)
{
	FILE *fp = NULL;
	static BOOL check = FALSE;

	if ((score > high_score))
	{
		fopen_s(&fp, "Game/HighScore.txt", "w");
		fprintf(fp, "%d", score);
		fclose(fp);
		check = TRUE;
	}
}
void RenderResult(void)
{
	static int cnt = 0;

	if (cnt > 400)
	{
		cnt = 0;
	}
	SetFontSize(40);
	DrawFormatString(SCREEN_CENTER_X / 2 + 70, SCREEN_CENTER_Y / 2, COLOR_WHITE, "Your Score : %d", score);
	DrawFormatString(SCREEN_CENTER_X / 2 + 70, SCREEN_CENTER_Y, COLOR_WHITE, "High Score : %d", high_score);

	if ((cnt % 80) / 40)
	{
		SetFontSize(30);
		DrawFormatString(SCREEN_CENTER_X - 140, SCREEN_CENTER_Y / 2 * 3, COLOR_RED, "Push to SPACE KEY !\nGame End is ESC");
	}
	cnt++;
}