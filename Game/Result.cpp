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

	if ((score > high_score) && (!check))
	{
		fopen_s(&fp, "HighScore.txt", "w");
		fprintf(fp, "%d", score);
		fclose(fp);
		check = TRUE;
	}
}
void RenderResult(void)
{
	SetFontSize(40);
	DrawFormatString(SCREEN_CENTER_X / 2 + 70, SCREEN_CENTER_Y / 2, COLOR_WHITE, "Your Score : %d", score);
	DrawFormatString(SCREEN_CENTER_X / 2 + 70, SCREEN_CENTER_Y, COLOR_WHITE, "High Score : %d", high_score);
}