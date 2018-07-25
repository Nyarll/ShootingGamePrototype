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

			case 1:
				break;
			}

			boss_shot[i].pos.x += boss_shot[i].vel.x;
			boss_shot[i].pos.y += boss_shot[i].vel.y;

			boss_shot[i].cnt++;
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

	if (GetGameCount() % 180 == 0)
	{
		BossMoveRandom(20, 20, GAME_SCREEN_RIGHT - 40, GAME_SCREEN_CENTER_Y, 120, 60);	//ランダム移動
	}

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
	int i;
	static int n = 0;
	static short num = 0;
	static int sum = 0;

	double ang = 0.0;

	if (GetGameCount() % 180 == 0)
	{
		BossMoveRandom(20, 20, GAME_SCREEN_RIGHT - 40, GAME_SCREEN_CENTER_Y, 120, 60);	//ランダム移動
	}

	if (GetGameCount() % 14 == 0)
	{
		while (1)
		{
			if ((i = SearchBossShot()) != -1)
			{
				if (n % 2)
				{
					boss_shot[i].flag = TRUE;

					boss_shot[i].spd.x = 6.0;
					boss_shot[i].spd.y = 6.0;

					boss_shot[i].pos.x = boss.pos.x + 30;
					boss_shot[i].pos.y = boss.pos.y;

					boss_shot[i].rad = DEG_TO_RAD(ang);

					boss_shot[i].vel.x = boss_shot[i].spd.x * cos(boss_shot[i].rad);
					boss_shot[i].vel.y = boss_shot[i].spd.y * sin(boss_shot[i].rad);

					boss_shot[i].tex = enemy_shot_graph[99];

					ang += 10.0;
					sum++;
				}
				else
				{
					boss_shot[i].flag = TRUE;

					boss_shot[i].spd.x = 6.0;
					boss_shot[i].spd.y = 6.0;

					boss_shot[i].pos.x = boss.pos.x - 30;
					boss_shot[i].pos.y = boss.pos.y;

					boss_shot[i].rad = DEG_TO_RAD(ang);

					boss_shot[i].vel.x = boss_shot[i].spd.x * cos(boss_shot[i].rad);
					boss_shot[i].vel.y = boss_shot[i].spd.y * sin(boss_shot[i].rad);

					boss_shot[i].tex = enemy_shot_graph[99];

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
		n++;
	}
}

void BossShotCircle1(double spd, double deg, int interval)
{
	int j;
	static int sum = 0;
	int num = 360 / deg;
	double ang = 0;

	if (boss.cnt % interval == 0)// && boss.cnt <= 120)
	{
		while (1)
		{
			if ((j = SearchBossShot()) != -1)
			{
				boss_shot[j].flag = TRUE;

				boss_shot[j].spd.x = spd;
				boss_shot[j].spd.y = spd;

				boss_shot[j].pos.x = boss.pos.x;
				boss_shot[j].pos.y = boss.pos.y;

				boss_shot[j].rad = DEG_TO_RAD(ang) + BossPlayerATAN();

				boss_shot[j].vel.x = boss_shot[j].spd.x * cos(boss_shot[j].rad);
				boss_shot[j].vel.y = boss_shot[j].spd.y * sin(boss_shot[j].rad);

				boss_shot[j].tex = enemy_shot_graph[99];

				ang += deg;
				sum++;

			}
			if (sum > num)
			{
				sum = 0;
				break;
			}
		}
	}
}
void BossShotCircle2(double spd, double deg, int interval)
{
	int j;
	static int sum = 0;
	int num = 360 / deg;
	double ang = 0;

	if (boss.cnt % interval == 0)// && boss.cnt <= 120)
	{
		while (1)
		{
			if ((j = SearchBossShot()) != -1)
			{
				boss_shot[j].flag = TRUE;

				boss_shot[j].spd.x = spd;
				boss_shot[j].spd.y = spd;

				boss_shot[j].pos.x = boss.pos.x;
				boss_shot[j].pos.y = boss.pos.y;

				boss_shot[j].rad = DEG_TO_RAD(ang) - (BossPlayerATAN() * 45);

				boss_shot[j].vel.x = boss_shot[j].spd.x * cos(boss_shot[j].rad);
				boss_shot[j].vel.y = boss_shot[j].spd.y * sin(boss_shot[j].rad);

				boss_shot[j].tex = enemy_shot_graph[99];

				ang += deg;
				sum++;

			}
			if (sum > num)
			{
				sum = 0;
				break;
			}
		}
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

	BossShotCircle1(1.0, 30.0, 20);
	if (t == TM001 - 1)
	{
		cnum++;
	}
}

//パーフェクトフリーズ
void BossSpecialShot1(void)
{
#define TM002 650
	int i, j, t = boss.shot_cnt % TM002;
	double angle;
	if ((t < 210) || (t == 210))
	{
		//40<x<FMX-40  50<y<150　の範囲で100離れた位置に80カウントで移動する
		BossMoveRandom(20, 20, GAME_SCREEN_RIGHT - 40, GAME_SCREEN_CENTER_Y, 160, 80);
	}
	//最初のランダム発射
	if (t < 180)
	{
		for (i = 0; i < 2; i++)
		{//1カウントに2回発射
			if ((j = SearchBossShot()) != -1)
			{
				boss_shot[j].flag = TRUE;

				boss_shot[j].pos.x = boss.pos.x;	//発射初期座標はボスの位置
				boss_shot[j].pos.y = boss.pos.y;

				boss_shot[j].rad = rang(360.0, 0.0) + (PI * 2) / 10 * t;

				boss_shot[j].state = 0;

				boss_shot[j].cnt = 0;
				boss_shot[j].spd.y = boss_shot[j].spd.x = 3.2 + rang(2.1, 0);

				boss_shot[j].vel.x = cos(boss_shot[j].rad) * boss_shot[j].spd.x;
				boss_shot[j].vel.y = sin(boss_shot[j].rad) * boss_shot[j].spd.y;

				boss_shot[j].tex = enemy_shot_graph[99];
			}
		}
		if (t % 10 == 0);
		//se_flag[0] = 1;
	}
	//自機依存による8方向発射
	if ((210 < t) && (t < 270) && (t % 3 == 0))
	{
		angle = DEG_TO_RAD(22.5);
		for (i = 0; i < 8; i++)
		{
			if ((j = SearchBossShot()) != -1)
			{
				boss_shot[j].flag = TRUE;

				boss_shot[j].pos.x = boss.pos.x;
				boss_shot[j].pos.y = boss.pos.y;

				boss_shot[j].rad = angle * (i + 1);

				boss_shot[j].state = 2;

				boss_shot[j].cnt = 0;
				boss_shot[j].spd.y = boss_shot[j].spd.x = 3.0 + rang(RAD_TO_DEG(0.3), 0);

				boss_shot[j].vel.x = cos(boss_shot[j].rad) * boss_shot[j].spd.x;
				boss_shot[j].vel.y = sin(boss_shot[j].rad) * boss_shot[j].spd.y;

				boss_shot[j].tex = enemy_shot_graph[99];
			}
		}
		if (t % 10 == 0);
		//se_flag[0] = 1;
	}

	for (i = 0; i < BOSS_SHOT_NUM; i++)
	{
		if (boss_shot[i].flag)
		{
			//tが190の時に全てストップさせ、白くし、カウントリセット
			if (boss_shot[i].state == 0)
			{
				if (t == 190)
				{

					boss_shot[i].spd.y = boss_shot[i].spd.x = 1.0;

					boss_shot[i].cnt = 0;
					boss_shot[i].state = 1;		//ステータスを１に

					boss_shot[i].vel.x = 0.0;
					boss_shot[i].vel.y = 0.0;

					boss_shot[i].tex = enemy_shot_graph[97];
				}
			}

			//ランダムな方向に移動し始める
			if (boss_shot[i].state == 1)
			{
				if (boss_shot[i].cnt == 200)
				{
					boss_shot[i].rad = rang(360, 0.0);	//全方向ランダム

					boss_shot[i].vel.x = cos(boss_shot[i].rad);
					boss_shot[i].vel.y = sin(boss_shot[i].rad);
				}
				if (boss_shot[i].cnt > 200)
				{
					boss_shot[i].spd.x += 0.0001;	//段々加速
					boss_shot[i].spd.y += 0.0001;

					BossSpecialShotMove1(i);
				}
			}
		}
	}
}

// 恋の迷路
void BossSpecialShot2(void)
{
#define TM003 600
#define DF003 20 

	int i, j, k, t = boss.shot_cnt % TM003, t2 = boss.shot_cnt;
	static int tcnt, cnt, cnum;
	double angle;
	static BOOL f = FALSE;

	static double boss_shot_angle[2] = { 0,0 };

	if (t2 == 0)
	{
		//40<x<FMX-40  50<y<150　の範囲で100離れた位置に80カウントで移動する
		InputPhyPos(GAME_SCREEN_RIGHT / 2, GAME_SCREEN_BOTTOM / 2, 50);
		cnum = 0;
	}
	if ((t == 0) || (!f))
	{
		boss_shot_angle[0] = BossPlayerATAN();
		cnt = 0;
		tcnt = 2;
		f = TRUE;
	}
	if (t < 540 && t % 3)
	{
		angle = BossPlayerATAN();
		if (tcnt - 2 == cnt || tcnt - 1 == cnt)
		{
			if (tcnt - 1 == cnt)
			{
				boss_shot_angle[1] = boss_shot_angle[0] + (PI * 2) / DF003 * cnt * (cnum ? -1 : 1) - (PI * 2) / (DF003 * 6) * 3;
				tcnt += DF003 - 2;
			}
		}
		else
		{
			for (i = 0; i < 6; i++)
			{
				if ((k = SearchBossShot()) != -1)
				{
					//boss_shot.bullet[k].col = cnum ? 1 : 4;

					boss_shot[k].pos.x = boss.pos.x;
					boss_shot[k].pos.y = boss.pos.y;

					boss_shot[k].rad =
						boss_shot_angle[0] + (PI * 2) / DF003 * cnt * (cnum ? -1 : 1) + (PI * 2) / (DF003 * 6) * i * (cnum ? -1 : 1);
					boss_shot[k].flag = 1;
					boss_shot[k].cnt = 0;
					boss_shot[k].spd = { 2,2 };

					boss_shot[k].vel.x = cos(boss_shot[k].rad) * boss_shot[k].spd.x;
					boss_shot[k].vel.y = sin(boss_shot[k].rad) * boss_shot[k].spd.y;

					boss_shot[k].tex = enemy_shot_graph[355];
					//se_flag[0] = 1;
				}
			}
		}
		cnt++;
	}
	if ((40 < t) && (t < 540) && (t % 30 == 0))
	{
		for (j = 0; j < 3; j++)
		{
			angle = boss_shot_angle[1] - (PI * 2) / 36 * 4;
			for (i = 0; i < 27; i++)
			{
				if ((k = SearchBossShot()) != -1)
				{
					//boss_shot.bullet[k].col = cnum ? 6 : 0;

					boss_shot[k].pos.x = boss.pos.x;
					boss_shot[k].pos.y = boss.pos.y;

					boss_shot[k].rad = angle;
					boss_shot[k].flag = TRUE;
					boss_shot[k].cnt = 0;
					boss_shot[k].spd.x = 4 - 1.6 / 3 * j;
					boss_shot[k].spd.y = 4 - 1.6 / 3 * j;

					boss_shot[k].vel.x = cos(boss_shot[k].rad) * boss_shot[k].spd.x;
					boss_shot[k].vel.y = sin(boss_shot[k].rad) * boss_shot[k].spd.y;

					boss_shot[k].tex = enemy_shot_graph[107];
					//se_flag[0] = 1;
				}
				angle -= (PI * 2) / 36;
			}
		}
	}

	if (t == TM003 - 1)
	{
		cnum++;
	}
}

void BossSpecialShotMove1(int i)
{
	boss_shot[i].vel.x *= boss_shot[i].spd.x;
	boss_shot[i].vel.y *= boss_shot[i].spd.y;
}

BOOL GetBossShotFlag(int i)
{
	return boss_shot[i].flag;
}