#pragma once

// �X�e�[�W�N���A�̏���
void InitStage(void);		// �N���A�����Ȃ珉����
void StageClearCheck(void);	// �N���A�������ǂ���
void GameOverCheck(void);	// �c�@���Ȃ��Ȃ������ǂ���

// �v���C���̏���
void InitPlay(void);
void UpdatePlay(void);
void RenderPlay(void);
void FinalPlay(void);

// �����蔻��
void PlayerShot_EnemyCollision(void);
void EnemyShot_PlayerCollision(void);
void GrazeCollision(void);
void Player_ItemCollision(void);

void PlayerShot_BossCollision(void);
void BossShot_PlayerCollison(void);

void DrawGameObject(void);


// �f�o�b�O�p
void UseDebug(void);
void DrawDebug(void);