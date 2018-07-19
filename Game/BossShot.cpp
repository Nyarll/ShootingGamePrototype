#include "Boss.h"

void InitBossShot(void)
{
	int i;

	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		boss_shot[i].pos = { 0,0 };
		boss_shot[i].spd = { 0,0 };
		boss_shot[i].vel = { 0,0 };



		boss_shot[i].flag = FALSE;
		boss_shot[i].pattern = 0;
		boss_shot[i].r = 4;
		boss_shot[i].rad = 0;
	}
}
void MoveBossShot(void)
{
	int i;

	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		if (boss_shot[i].flag)
		{
			switch (boss.shot_pattern)
			{
			case 0:
				break;
			}

			boss_shot[i].pos.x += boss_shot[i].vel.x;
			boss_shot[i].pos.y += boss_shot[i].vel.y;
		}

		if ((boss_shot[i].pos.x < (GAME_SCREEN_LEFT - 20)) ||
			(boss_shot[i].pos.x > (GAME_SCREEN_RIGHT + 20)) ||
			(boss_shot[i].pos.y < (GAME_SCREEN_TOP - 20)) ||
			(boss_shot[i].pos.y > (GAME_SCREEN_BOTTOM + 20)))
		{
			boss_shot[i].pos.x = 0;
			boss_shot[i].pos.y = 0;
			boss_shot[i].vel.x = 0;
			boss_shot[i].vel.y = 0;
			boss_shot[i].spd.x = 0;
			boss_shot[i].spd.y = 0;

			boss_shot[i].flag = FALSE;
			boss_shot[i].rad = 0;

			continue;
		}
	}
}
void DrawBossShot(void)
{
	int i;

	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		if (boss_shot[i].flag)
		{
			DrawRotaGraph(boss_shot[i].pos.x, boss_shot[i].pos.y, 1.4, 0, boss_shot[i].tex, TRUE);
		}
	}
}

void BossShotPattern0(void)
{
	int j;
	static int sum = 0;
	double ang = 0.0;

	if (boss.cnt % 10 == 0 && boss.cnt <= 120)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			//flag‚Ì‚È‚¢’e‚ð’T‚µ‚ÄÀ•WƒZƒbƒg
			if (boss_shot[j].flag == FALSE)
			{
				boss_shot[j].flag = TRUE;
				boss_shot[j].pattern = 5;

				boss_shot[j].spd.x = 2.5;
				boss_shot[j].spd.y = 2.5;

				boss_shot[j].pos.x = boss.pos.x;
				boss_shot[j].pos.y = boss.pos.y;

				boss_shot[j].rad = DEG_TO_RAD(ang);

				boss_shot[j].vel.x = boss_shot[j].spd.x * cos(boss_shot[j].rad);
				boss_shot[j].vel.y = boss_shot[j].spd.y * sin(boss_shot[j].rad);

				boss_shot[j].tex = enemy_shot_graph[99];

				ang += 10.0;
				sum++;

				if (sum > 36)
				{
					sum = 0;
					break;
				}
			}
		}
	}
}
void BossShotPattern1(void)
{
	if (GetGameCount() % (60 / 10) == 0)
	{
		
	}
}
