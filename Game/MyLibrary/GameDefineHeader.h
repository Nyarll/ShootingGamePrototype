#pragma once

//���b�Z�[�W�{�b�N�X / NULL, m(�\�����b�Z�[�W), "window name", MB_OK
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("�Q�[�����I�����܂�") PostQuitMessage(0);}

#define PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / PI))


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (1000)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (800)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

// �ȉ��Q�[���ɂ���ĕύX����

#define GAME_SCREEN_LEFT	(SCREEN_LEFT)
#define GAME_SCREEN_TOP		(SCREEN_TOP)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 10)	// �v���C���[��������͈� X 600
#define GAME_SCREEN_BOTTOM	(SCREEN_HEIGHT)							// �v���C���[��������͈� Y 800
#define GAME_SCREEN_CENTER_X (GAME_SCREEN_RIGHT / 2)
#define GAME_SCREEN_CENTER_Y (GAME_SCREEN_BOTTOM / 2)

#define GAME_TIME 4000

#define GAME_STAGE_MAX 2	// �X�e�[�W�̍ő吔


#define PLAYER_SIZE 64
#define PLAYER_SPEED 6
#define PLAYER_SHOT_NUM 128
#define PLAYER_SHOT_SIZE 5

#define ENEMY_SIZE 10

#define ENEMY_SHOT_NUM 4096
#define ENEMY_TYPE_NUM 1

// �X�e�[�W���Ƃ̃G�l�~�[�̐�
#define ENEMY_NUM1 (61)
#define ENEMY_NUM2 (5)

typedef int LIFE;
typedef int BOMB;

typedef enum
{
	SCENE_NONE = -1,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_PLAY,
	SCENE_RESULT

}SceneID;
