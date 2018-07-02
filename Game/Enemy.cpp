#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "Defines.h"

FILE *fp;					// エネミーデータをcsvファイルから読み込む用
EnemyData enemy[256];		// エネミーオブジェクト
EnemyData data[256];		// バッファ
int enemy_num;				// エネミーの数
BOOL enemy_flag[256];		// 死んだらFALSE
BOOL enemy_cross_flag[256];	// プレイヤーと重なったか

Shot enemy_shot[ENEMY_SHOT_NUM];	// エネミーの弾オブジェクト
double shot_speed_data[ENEMY_SHOT_NUM];
BOOL shot_flag[ENEMY_SHOT_NUM];
int shot_count[ENEMY_SHOT_NUM];
int shotwait_count[ENEMY_SHOT_NUM];
int s[256];	// 発射中の弾の数
double rad[ENEMY_SHOT_NUM];

void InitEnemy(int stage)
{
	int i;
	char file_name[MAX_PATH];

	SetEnemyNum(stage);
	InitEnemyShot();
	if (stage <= GAME_STAGE_MAX)
	{
		sprintf(file_name, "Resources/EnemyData/stage%d.csv", stage);
		FileStreamEnemy(file_name);
	}
	else
	{
		MSG("Not Found");
		EXIT
	}

	// エネミーオブジェクトの初期化
	for (i = 0; i < enemy_num; i++)
	{
		enemy[i].type = data[i].type;
		enemy[i].shot_type = data[i].shot_type;
		enemy[i].move_pattern = data[i].move_pattern;
		enemy[i].shot_pattern = data[i].shot_pattern;
		enemy[i].in_time = data[i].in_time;
		enemy[i].stop_time = data[i].stop_time;
		enemy[i].shot_time = data[i].shot_time;
		enemy[i].out_time = data[i].out_time;
		enemy[i].x = data[i].x;
		enemy[i].y = data[i].y;
		enemy[i].speed = data[i].speed;
		enemy[i].hp = data[i].hp;
		enemy[i].item = data[i].item;

		enemy_vel[i] = { 0,0 };
		enemy_angle[i] = 0;

		enemy_flag[i] = TRUE;
		enemy_cross_flag[i] = FALSE;
		shot_flag[i] = FALSE;
		shot_count[i] = 0;
		s[i] = { 0 };
		rad[i] = 0;
	}

	fclose(fp);
}
void FileStreamEnemy(const TCHAR *file_name)
{
	char buf[100];

	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));

	if (-1 == fopen_s(&fp, file_name, "r"))
	{
		MSG("エラー発生");
		EXIT
	}

	// 最初を読み飛ばす
	while (fgetc(fp) != '\n');

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);

			// 末尾ならループから抜ける
			if (c == EOF)
			{
				return;
			}
			// カンマか改行でないなら文字として読む
			if ((c != ',') && (c != '\n'))
			{
				strcat_s(buf, (const char*)&c);
			}
			// カンマか改行なら抜ける
			else
			{
				break;
			}
		}
		// 1セル分の文字列になった
		switch (col)
		{
			//1列目は敵種類 atoi関数で数値として代入する
		case 1:	data[row].type = atoi(buf);	break;
			//2列目は弾種類
		case 2:	data[row].shot_type = atoi(buf);	break;
			//3列目は移動パターン
		case 3:	data[row].move_pattern = atoi(buf);	break;
			//4列目はショットパターン
		case 4:	data[row].shot_pattern = atoi(buf);	break;
			//5列目は出現時間
		case 5:	data[row].in_time = atoi(buf);	break;
			//6列目は停止時間
		case 6:	data[row].stop_time = atoi(buf);	break;
			//7列目は発射時間
		case 7:	data[row].shot_time = atoi(buf);	break;
			//8列目は帰還時間
		case 8:	data[row].out_time = atoi(buf);	break;
			//9列目はｘ座標
		case 9:	data[row].x = atoi(buf);	break;
			//10列目はｙ座標
		case 10: data[row].y = atoi(buf);	break;
			//11列目は弾速度
		case 11: data[row].speed = atoi(buf);	break;
			//12列目はHP
		case 12: data[row].hp = atoi(buf); break;
			//13列目はアイテム
		case 13: data[row].item = atoi(buf);	break;
		}

		// バッファの初期化
		memset(buf, 0, sizeof(buf));
		// 列
		++col;
		// 読んだ文字が改行なら
		if (c == '\n')
		{
			col = 1;
			++row;
		}
	}
}
BOOL OutCheck(int x, int y)
{
	if ((x < SCREEN_LEFT - 50) || (x > GAME_SCREEN_RIGHT + 50) || (y < SCREEN_TOP - 50) || (y > GAME_SCREEN_BOTTOM + 50))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void SetEnemyNum(int stage)
{
	switch (stage)
	{
	case 1:
		enemy_num = ENEMY_NUM1;
		break;

	case 2:
		enemy_num = ENEMY_NUM2;
		break;
	}
}
void MoveEnemy(void)
{
	int i;

	for (i = 0; i < enemy_num; i++)
	{
		if (enemy_flag[i])
		{
			switch (enemy[i].move_pattern)
			{
				// 途中で停止、そのまま後ろに帰る
			case 0:
				EnemyMovePattern0(i);
				break;

				// プレイヤーのｙ座標と重なったら逃げる
			case 1:
				EnemyMovePattern1(i);
				break;

			case 2:
				EnemyMovePattern2(i);
				break;

			case 3:
				EnemyMovePattern3(i);
				break;

			case 4:
				EnemyMovePattern4(i);
				break;

			case 999:	// デバッグモード
				EnemyMovePatternDebug(i);
				break;
			}



			if (OutCheck(enemy[i].x, enemy[i].y))
			{
				enemy_flag[i] = FALSE;
			}
		}
	}
}
void DrawEnemy(void)
{
	int i;

	for (i = 0; i < enemy_num; i++)
	{
		if (enemy_flag[i])
		{
			switch (enemy[i].type)
			{
			case 1:
				DrawCircle(enemy[i].x, enemy[i].y, ENEMY_SIZE, COLOR_RED, TRUE);
				break;
			}
		}
	}
}

double GetEnemyShotSpeedY(void)
{
	return enemy_shot[0].base.speed.y;
}
double GetEnemyShotVelY(void)
{
	return enemy_shot[0].base.vel.y;
}

void SetEnemyDeadFlag(int i)
{
	enemy_flag[i] = FALSE;
}
BOOL GetEnemyDeadFlag(int i)
{
	return enemy_flag[i];
}

int GetEnemyPosX(int i)
{
	return enemy[i].x;
}
int GetEnemyPosY(int i)
{
	return enemy[i].y;
}

int GetEnemyNum(void)
{
	return enemy_num;
}

BOOL GetEnemyShotFlag(int i)
{
	return enemy_shot[i].flag;
}
