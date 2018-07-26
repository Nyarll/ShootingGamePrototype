#pragma once

extern FILE *fp;					// �G�l�~�[�f�[�^��csv�t�@�C������ǂݍ��ޗp
extern EnemyData enemy[256];		// �G�l�~�[�I�u�W�F�N�g
extern EnemyData data[256];		// �o�b�t�@
extern int enemy_num;				// �G�l�~�[�̐�
extern BOOL enemy_flag[256];		// ���񂾂�FALSE
extern BOOL enemy_cross_flag[256];	// �v���C���[�Əd�Ȃ�����

extern Shot enemy_shot[ENEMY_SHOT_NUM];	// �G�l�~�[�̒e�I�u�W�F�N�g
extern double shot_speed_data[ENEMY_SHOT_NUM];
extern BOOL shot_flag[ENEMY_SHOT_NUM];
extern int shot_count[ENEMY_SHOT_NUM];
extern int shotwait_count[ENEMY_SHOT_NUM];
extern int s[256];	// ���˒��̒e�̐�
extern double rad[ENEMY_SHOT_NUM];

extern double enemy_angle[256];
extern Vector2D enemy_vel[256];

extern HGRP enemy_shot_graph[384];

void InitEnemy(int stage);		// �G�l�~�[�̏�����
void FileStreamEnemy(const TCHAR *file_name);	// �G�l�~�[�f�[�^�̓ǂݍ���
void SetEnemyNum(int stage);	// �G�l�~�[�̐��̐ݒ�
void MoveEnemy(void);		// �G�l�~�[�̈ړ�
void DrawEnemy(void);		// �G�l�~�[�̕`��

void EnemyMovePatternDebug(int i);	// �ړ��p�^�[��Debug mode
void EnemyMovePattern0(int i);	// �ړ��p�^�[��0
void EnemyMovePattern1(int i);	// �ړ��p�^�[��1
void EnemyMovePattern2(int i);	// �ړ��p�^�[��2
void EnemyMovePattern3(int i);	// �ړ��p�^�[��3
void EnemyMovePattern4(int i);	// �ړ��p�^�[��4
void EnemyMovePattern5(int i);
void EnemyMovePattern6(int i);

void InitEnemyShot(void);	// �G�l�~�[�̒e�̏�����
void SetEnemyShot(int index);	// �G�l�~�[�̒e�̃Z�b�g
void MoveEnemyShot(void);	// �G�l�~�[�̒e�̈ړ�
void DrawEnemyShot(int o);	// �G�l�~�[�̒e�̕`��

void SetEnemyShotGraph(int e_index, int j);

// �V���b�g�p�^�[��

void EnemyShotPattern0(int i);		// �V���b�g�p�^�[�� 0
void EnemyShotPattern1(int i);		// �V���b�g�p�^�[�� 1
void EnemyShotPattern2(int i);		// �V���b�g�p�^�[�� 2
void EnemyShotPattern3(int i);		// �V���b�g�p�^�[�� 3
void EnemyShotPattern4(int i);		// �V���b�g�p�^�[�� 4
void EnemyShotPattern5(int i);		// �V���b�g�p�^�[�� 5
void EnemyShotPattern6(int i);		// �V���b�g�p�^�[�� 6
void EnemyShotPattern7(int i);		// �V���b�g�p�^�[�� 7
void EnemyShotPattern8(int i);		// �V���b�g�p�^�[�� 8
void EnemyShotPattern9(int i);		// �V���b�g�p�^�[�� 9
void EnemyShotPattern10(int i);		// �V���b�g�p�^�[�� 10
void EnemyShotPattern11(int i);		// �V���b�g�p�^�[�� 11
void EnemyShotPattern12(int i);		// �V���b�g�p�^�[�� 12
void EnemyShotPattern13(int i);		// �V���b�g�p�^�[�� 13
void EnemyShotPattern14(int i, int num);		// �V���b�g�p�^�[�� 14
void EnemyShotPattern15(int i);		// �V���b�g�p�^�[�� 15

void SetEnemyDeadFlag(int i);
BOOL GetEnemyDeadFlag(int i);

int GetEnemyPosX(int i);
int GetEnemyPosY(int i);

int GetEnemyNum(void);

BOOL GetEnemyShotFlag(int i);
double GetEnemyShotSpeedY(void);
double GetEnemyShotVelY(void);

void DrawEnemyDeadEffect(void);
void SetDeadEffect(int index);