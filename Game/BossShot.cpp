#include "Boss.h"

int boss_shot_cnt = 0;

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

			case 1:
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
	boss.shot_cnt++;
}
void DrawBossShot(void)
{
	int i;

	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		if (boss_shot[i].flag)
		{
			DrawRotaGraph(boss_shot[i].pos.x, boss_shot[i].pos.y, 1.4, boss_shot[i].rad + DEG_TO_RAD(90), boss_shot[i].tex, TRUE);
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
		while (1)
		{
			if ((j = SearchBossShot()) != -1)
			{
				//flagのない弾を探して座標セット
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
				}
			}
			if (sum > 36)
			{
				sum = 0;
				break;
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

int SearchBossShot(void)
{
	int i;
	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		// flagのない弾を探す
		if (boss_shot[i].flag == FALSE)
		{
			return i;
		}
	}
	// 空きがなければ
	return -1;
}

//サイレントセレナ / やさしい
void BossSpecialShot0(void)
{
#define TM001 60
	int i, j;
	int t = boss.shot_cnt % TM001, t2 = boss.shot_cnt;
	static int cnum = 0;
	double angle;
	static double shot_angle = 0;
	if (t2 == 0)	// 最初の初期化
	{
		cnum = 0;
	}
	if (t == 0)	// 1ターンの最初の初期化
	{
		shot_angle = BossPlayerATAN();	// 自機とボスの角度
		if (cnum % 4 == 3)	// 4ターンに１回移動
		{
			BossMoveRandom(20, 20, GAME_SCREEN_RIGHT - 40, GAME_SCREEN_CENTER_Y, 120, 60);	//ランダム移動
		}
	}
	// 1ターンの最初は自機狙い、半分からは自機狙いからずらす
	if (t == TM001 / 2 - 1)
	{
		shot_angle += (PI * 2) / 20 / 2;
	}
	// 1ターンに10回円形発射の弾をうつ
	if (t % (TM001 / 10) == 0)
	{
		angle = BossPlayerATAN();	//自機-ボスの成す角
		for (i = 0; i < 20; i++)		//20個
		{
			if ((j = SearchBossShot()) != -1)	// 空き弾をサーチ
			{
				boss_shot[j].flag = TRUE;	// フラグを立てる

				boss_shot[j].pos.x = boss.pos.x;
				boss_shot[j].pos.y = boss.pos.y;

				// ベース角度から20個回転して発射
				boss_shot[j].rad = shot_angle + (PI * 2) / 20 * i;

				boss_shot[j].cnt = 0;
				boss_shot[j].spd.x = 2.7;
				boss_shot[j].spd.y = 2.7;

				boss_shot[j].vel.x = cos(boss_shot[j].rad) * boss_shot[j].spd.x;
				boss_shot[j].vel.y = sin(boss_shot[j].rad) * boss_shot[j].spd.y;

				boss_shot[j].tex = enemy_shot_graph[146];
				//se_flag[0] = 1;
			}
		}
	}
	//4カウントに1回下に落ちる弾を登録
	/*
	if (t % 4 == 0) 
	{
		if ((j = SearchBossShot()) != -1)
		{
			boss_shot[j].flag = TRUE;

			boss_shot[j].pos.x = GetRand(GAME_SCREEN_RIGHT);
			boss_shot[j].pos.y = GetRand(200);
			boss_shot[j].rad = PI / 2;	//真下の角度

			boss_shot[j].cnt = 0;
			boss_shot[j].spd.x = 1 + rang(180, 0);
			boss_shot[j].spd.y = 1 + rang(180, 0);

			boss_shot[j].vel.x = cos(boss_shot[j].rad) * boss_shot[j].spd.x;
			boss_shot[j].vel.y = sin(boss_shot[j].rad) * boss_shot[j].spd.y;

			boss_shot[j].tex = enemy_shot_graph[140];
			//se_flag[0] = 1;
		}
	}
	*/
	if (t == TM001 - 1)
	{
		cnum++;
	}
}
