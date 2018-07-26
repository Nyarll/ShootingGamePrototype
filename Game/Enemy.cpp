#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "Defines.h"

FILE *fp;					// �G�l�~�[�f�[�^��csv�t�@�C������ǂݍ��ޗp
EnemyData enemy[256];		// �G�l�~�[�I�u�W�F�N�g
EnemyData data[256];		// �o�b�t�@
int enemy_num;				// �G�l�~�[�̐�
BOOL enemy_flag[256];		// ���񂾂�FALSE
BOOL enemy_cross_flag[256];	// �v���C���[�Əd�Ȃ�����
HGRP enemy_gh[8];
int enemy_count[256];

Shot enemy_shot[ENEMY_SHOT_NUM];	// �G�l�~�[�̒e�I�u�W�F�N�g
double shot_speed_data[ENEMY_SHOT_NUM];
BOOL shot_flag[ENEMY_SHOT_NUM];
int shot_count[ENEMY_SHOT_NUM];
int shotwait_count[ENEMY_SHOT_NUM];
int s[256];	// ���˒��̒e�̐�
double rad[ENEMY_SHOT_NUM];

HGRP dead_effect;
BOOL enemy_dead_effect_flag[256];
double effect_rad[256];
Vector2D effect_pos[256];
int effect_cnt[256];
double effect_deg[256] = { 0 };

void InitEnemy(int stage)
{
	int i;
	char file_name[MAX_PATH];

	dead_effect = LoadGraph("Resources/Textures/dead_effect.png");

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

	// �G�l�~�[�I�u�W�F�N�g�̏�����
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

		LoadDivGraph("Resources/Textures/enemy.png", 8, 4, 2, 32, 32, enemy_gh);

		enemy_vel[i] = { 0,0 };
		enemy_angle[i] = 0;

		enemy_flag[i] = TRUE;
		enemy_cross_flag[i] = FALSE;
		shot_flag[i] = FALSE;
		shot_count[i] = 0;
		s[i] = { 0 };
		rad[i] = 0;

		effect_rad[i] = 0;
		effect_pos[i] = { 0,0 };
		enemy_dead_effect_flag[i] = FALSE;
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
		MSG("�G���[����");
		EXIT
	}

	// �ŏ���ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);

			// �����Ȃ烋�[�v���甲����
			if (c == EOF)
			{
				return;
			}
			// �J���}�����s�łȂ��Ȃ當���Ƃ��ēǂ�
			if ((c != ',') && (c != '\n'))
			{
				strcat_s(buf, (const char*)&c);
			}
			// �J���}�����s�Ȃ甲����
			else
			{
				break;
			}
		}
		// 1�Z�����̕�����ɂȂ���
		switch (col)
		{
			//1��ڂ͓G��� atoi�֐��Ő��l�Ƃ��đ������
		case 1:	data[row].type = atoi(buf);	break;
			//2��ڂ͒e���
		case 2:	data[row].shot_type = atoi(buf);	break;
			//3��ڂ͈ړ��p�^�[��
		case 3:	data[row].move_pattern = atoi(buf);	break;
			//4��ڂ̓V���b�g�p�^�[��
		case 4:	data[row].shot_pattern = atoi(buf);	break;
			//5��ڂ͏o������
		case 5:	data[row].in_time = atoi(buf);	break;
			//6��ڂ͒�~����
		case 6:	data[row].stop_time = atoi(buf);	break;
			//7��ڂ͔��ˎ���
		case 7:	data[row].shot_time = atoi(buf);	break;
			//8��ڂ͋A�Ҏ���
		case 8:	data[row].out_time = atoi(buf);	break;
			//9��ڂ͂����W
		case 9:	data[row].x = atoi(buf);	break;
			//10��ڂ͂����W
		case 10: data[row].y = atoi(buf);	break;
			//11��ڂ͒e���x
		case 11: data[row].speed = atoi(buf);	break;
			//12��ڂ�HP
		case 12: data[row].hp = atoi(buf); break;
			//13��ڂ̓A�C�e��
		case 13: data[row].item = atoi(buf);	break;
		}

		// �o�b�t�@�̏�����
		memset(buf, 0, sizeof(buf));
		// ��
		++col;
		// �ǂ񂾕��������s�Ȃ�
		if (c == '\n')
		{
			col = 1;
			++row;
		}
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
				// �r���Œ�~�A���̂܂܌��ɋA��
			case 0:
				EnemyMovePattern0(i);
				break;

				// �v���C���[�̂����W�Əd�Ȃ����瓦����
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

			case 5:
				EnemyMovePattern5(i);
				break;

			case 6:
				EnemyMovePattern6(i);
				break;

			case 999:	// �f�o�b�O���[�h
				EnemyMovePatternDebug(i);
				break;
			}



			if (OutCheck(enemy[i].x, enemy[i].y))
			{
				enemy_flag[i] = FALSE;
			}
		}
	}

	for (i = 0; i < enemy_num; i++)
	{
		if (enemy_dead_effect_flag[i])
		{
			effect_cnt[i]++;

			if (effect_cnt[i] > 10)
			{
				effect_rad[i] = 0;
				effect_deg[i] = 0;
				effect_pos[i] = { 0,0 };
				enemy_dead_effect_flag[i] = FALSE;
			}
		}
	}
}
void DrawEnemy(void)
{
	int i;
	static int temp[256] = { 0 };

	for (i = 0; i < enemy_num; i++)
	{
		if (enemy_flag[i])
		{
			switch (enemy[i].type)
			{
			case 1:
				temp[i] = enemy_count[i] % 70 / 10;
				if (temp[i] == 4)
				{
					temp[i] = 3;
				}
				if (temp[i] == 5)
				{
					temp[i] = 2;
				}
				if (temp[i] == 6)
				{
					temp[i] = 1;
				}
				DrawRotaGraph(enemy[i].x, enemy[i].y, 1.0, 0.0, enemy_gh[temp[i]], TRUE);
				enemy_count[i]++;
				break;
			}
		}
	}

	DrawEnemyDeadEffect();
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

void DrawEnemyDeadEffect(void)
{
	int i;

	for (i = 0; i < GetEnemyNum(); i++)
	{
		if (enemy_dead_effect_flag[i])
		{
			DrawRotaGraph(effect_pos[i].x, effect_pos[i].y, 0.5, effect_rad[i], dead_effect, TRUE);
			effect_rad[i] = DEG_TO_RAD(effect_deg[i]);
			effect_deg[i] += 20;
		}
	}
}
void SetDeadEffect(int index)
{
	effect_pos[index].x = enemy[index].x;
	effect_pos[index].y = enemy[index].y;
	enemy_dead_effect_flag[index] = TRUE;
}