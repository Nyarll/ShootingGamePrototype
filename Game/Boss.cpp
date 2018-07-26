#include "Boss.h"
#include "SceneManager.h"

#define BOSS_POS_X (GAME_SCREEN_CENTER_X)
#define BOSS_POS_Y (GAME_SCREEN_CENTER_Y / 2)

#define MAX_BOSS_HP 800

BOSS boss;
HGRP boss_back;
int boss_intime;
int boss_movecount;
int boss_moveflag;

BOSS_SHOT boss_shot[BOSS_SHOT_NUM];

// 綺麗な移動用の計算式(物理)
// y = (((2 * ymax) / ty) * t) - ((ymax / (ty * ty)) * (t * t))
// ty : 指定時間(移動開始時間)	// tx = cos(rad)  ty = sin(rad)
// ymax : 移動距離
// t : カウンタ
// それぞれ水平成分(x成分), 鉛直成分(y成分)で計算する (式のyに割り当てる)

void InitBoss(void)
{
	srand((unsigned int)time(NULL));

	memset(&boss, 0, sizeof(BOSS));

	boss.flag = FALSE;
	boss.pos = { GAME_SCREEN_CENTER_X,-20 };
	boss.vel = { 0,0 };
	boss.spd = { 3,3 };
	boss.tex;

	boss.rad = 0;

	boss.move_pattern = 0;
	boss.shot_pattern = 0;

	boss_intime = 2200;	// ボス出現タイミング / LastEnemy 1820
	boss_movecount = 300;
	boss_moveflag = 0;

	boss.shot_flag = FALSE;

	boss.hp = MAX_BOSS_HP;
	boss.life = 6;

	boss_back = LoadGraph("Resources/Textures/bossback3.png");
	boss.tex = LoadGraph("Resources/Textures/doraemon.png");

	InputPhy(60);

	InitBossShot();
}
void MoveBoss(void)
{
	boss.vel.x = 0;
	boss.vel.y = 0;

	// ボス出現タイミングになったら
	if (boss_intime < GetGameCount())
	{
		boss.flag = TRUE;	// 出現させる
	}

	if (boss.flag)
	{
		MoveBossManager();

		if (boss.cnt < 200)
		{
			ShotBossManager();
		}
		else
		{
			boss.cnt = 0;
		}
	}
	boss.pos.x += boss.vel.x;
	boss.pos.y += boss.vel.y;

	boss.cnt++;

	if (boss.hp <= 0)
	{
		boss.life -= 1;
		boss.shot_cnt = 0;
		boss.hp = MAX_BOSS_HP;
	}

	if (boss.shot_flag)
	{
		MoveBossShot();
	}
}
void MoveBossManager(void)
{
	static int inicnt = 0;
	switch (boss.move_pattern)
	{
	case 0:
		BossMovePattern1();
		break;

	case 1:
		BossMovePattern1();
		
		break;
	}

	if (boss.phy.flag)
	{
		CalcPhy();
	}
}
void ShotBossManager(void)
{
	static int bosslife_table = boss.life;
	static int wait_change = 0;

	static BOOL initmove = FALSE;

	switch (boss.shot_pattern)
	{
	case 0:
		//BossShotPattern1();
		BossShotPattern0();		// 初手通常
		//BossSpecialShot1();
		break;

	case 1:
		BossSpecialShot0();		// サイレントセレナ
		//BossSpecialShot0();
		//BossSpecialShot1();
		//BossSpecialShot2();
		break;

	case 2:		// 次手通常
		BossShotCircle1(6.0, 30, 10);
		BossShotCircle2(3.0, 30, 20);
		break;

	case 3:
		BossSpecialShot1();		// パーフェクトフリーズ
		break;

	case 4:
		BossShotPattern1();
		break;

	case 5:
		BossSpecialShot2();		// 恋の迷路
		break;
	}
	boss.shot_flag = TRUE;

	if (boss.life != bosslife_table)
	{
		if (!initmove)
		{
			InputPhy(60);
			initmove = TRUE;
		}
		if (wait_change > 180)	// ちょっと待機する
		{
			switch (boss.life)	// ボス残機で行動の変化
			{
			case 6:
				boss.shot_pattern = 0;
				break;

			case 5:
				boss.shot_pattern = 1;
				break;

			case 4:
				boss.shot_pattern = 2;
				break;

			case 3:
				boss.shot_pattern = 3;
				break;

			case 2:
				boss.shot_pattern = 4;
				break;

			case 1:
				boss.shot_pattern = 5;
				break;

			case 0:
				SetResultScene();
				break;
			}
			
		}
		else
		{
			wait_change++;
		}
	}
	/*else */if(wait_change > 181)
	{
		bosslife_table = boss.life;
		initmove = FALSE;;
		wait_change = 0;
	}

	//
}
void DrawBoss(void)
{
	if (boss_intime < GetGameCount())
	{
		DrawBossEffect();
		//DrawCircle(boss.pos.x, boss.pos.y, BOSS_SIZE, GetColor(128, 0, 255), TRUE);
		DrawRotaGraph(boss.pos.x, boss.pos.y, 1.5, 0.0, boss.tex, TRUE);
		DrawBossShot();
		DrawBossHP();
	}
}

void DrawBossHP(void)
{
	// float pos_y = ((SCREEN_HEIGHT - 10) * game_count / GAME_TIME) + 10;
	float bhp_x = ((GAME_SCREEN_RIGHT)* boss.hp / MAX_BOSS_HP);

	DrawBox(0, 2, bhp_x, 12, COLOR_RED, TRUE);
}

BOOL GetBossFlag(void)
{
	return boss.flag;
}
double GetBossPosX(void)
{
	return boss.pos.x;
}
double GetBossPosY(void)
{
	return boss.pos.y;
}

void DrawBossEffect(void)
{
	static double deg = 0;

	if (deg == 360)
	{
		deg = 0;
	}

	DrawRotaGraph(boss.pos.x, boss.pos.y, 2.0, DEG_TO_RAD(deg), boss_back, TRUE);
	deg += 1;
}

void BossDamage(int damage)
{
	boss.hp -= damage;
}

// ランダムな角度 (ラジアンで返す)
// 移動角度の範囲, 範囲
double rang(int deg, int range)
{
	double angle, rad;

	angle = rand() % deg + range;
	rad = DEG_TO_RAD(angle);

	return rad;
}

//物理的計算をさせる登録をする(指定時間tで定位置に戻す)
void InputPhy(int t)   //t=移動にかける時間
{
	double ymax_x, ymax_y;

	if (t == 0)
	{
		t = 1;
	}

	boss.phy.flag = TRUE;                //登録オン
	boss.phy.cnt = 0;                 //カウンタ初期化
	boss.phy.set_t = t;               //移動にかける時間をセット
	ymax_x = boss.pos.x - BOSS_POS_X;       //移動したい水平距離
	boss.phy.v0x = 2 * ymax_x / t;        //水平成分の初速度
	boss.phy.ax = 2 * ymax_x / (t * t);    //水平成分の加速度
	boss.phy.prex = boss.pos.x;           //初期x座標
	ymax_y = boss.pos.y - BOSS_POS_Y;       //移動したい鉛直距離
	boss.phy.v0y = 2 * ymax_y / t;        //鉛直成分の初速度
	boss.phy.ay = 2 * ymax_y / (t * t);    //鉛直成分の加速度
	boss.phy.prey = boss.pos.y;           //初期y座標
}

//物理的計算を点と距離指定で登録をする(指定時間tで定位置に戻す)
void InputPhyPos(double x, double y, int t)     //t=移動にかける時間
{
	double ymax_x, ymax_y;

	if (t == 0)
	{
		t = 1;
	}

	boss.phy.flag = TRUE;//登録オン
	boss.phy.cnt = 0;//カウンタ初期化
	boss.phy.set_t = t;//移動にかける時間をセット
	ymax_x = boss.pos.x - x;//移動したい水平距離
	boss.phy.v0x = 2 * ymax_x / t;//水平成分の初速度
	boss.phy.ax = 2 * ymax_x / (t * t);//水平成分の加速度
	boss.phy.prex = boss.pos.x;//初期x座標
	ymax_y = boss.pos.y - y;//移動したい鉛直距離
	boss.phy.v0y = 2 * ymax_y / t;//鉛直成分の初速度
	boss.phy.ay = 2 * ymax_y / (t * t);//鉛直成分の加速度
	boss.phy.prey = boss.pos.y;//初期y座標
}

//物理的キャラクタ移動計算
void CalcPhy(void)
{
	double t = boss.phy.cnt;

	boss.pos.x = boss.phy.prex - ((boss.phy.v0x * t) - 0.5 * boss.phy.ax * t * t);//現在いるべきx座標計算
	boss.pos.y = boss.phy.prey - ((boss.phy.v0y * t) - 0.5 * boss.phy.ay * t * t);//現在いるべきy座標計算
	boss.phy.cnt++;

	if (boss.phy.cnt >= boss.phy.set_t)//移動にかける時間分になったら
	{
		boss.phy.flag = FALSE;//オフ
	}
}

double BossPlayerATAN(void)
{
	return atan2(boss.pos.y - GetPlayerPosY(), boss.pos.x - GetPlayerPosX());
}