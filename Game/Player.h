#pragma once

void InitPlayer(void);		// �v���C���[�̏�����
void MovePlayer(void);		// �v���C���[�̈ړ�
void DrawPlayer(void);		// �v���C���[�̕`��

void InitPlayerShot(void);	// �v���C���[�̒e�̏�����
void MovePlayerShot(void);	// �v���C���[�̒e�̈ړ�
void DrawPlayerShot(void);	// �v���C���[�̒e�̕`��

double GetPlayerPosX(void);
double GetPlayerPosY(void);

BOOL GetPlayerShotFlag(int i);
BOOL GetPlayerDeadFlag(void);

int GetPlayerShotPosX(int i);
int GetPlayerShotPosY(int i);

int GetShotPower(void);

void SetPlayerDeadFlag(void);

void SetShotPower1(void);
void SetShotPower2(void);
void SetShotPower3(void);