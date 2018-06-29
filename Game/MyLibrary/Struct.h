// ============================================================
// �쐬�� : 2018 / 06 / 07
// �p�r   : �\���̂̒�`
// ���l   : ���Ɨp�ł����Ԃ�g����
// ============================================================

#pragma once

// �\���̂̒�` ===============================================

// x,y ���� / double�^, double�^
struct Vector2D
{
	double x, y;
};
typedef struct Vector2D Vector2D;

// �񎟌��̎l�p�p / int�^, int�^, int�^, int�^
struct Box
{
	int x1, y1;
	int x2, y2;
};
typedef struct Box Box;

// �񎟌��̎l�p�` / Vector2D�^, int�^, int�^, Box�^
// ���S���W, �ӂ̒���, ����ƉE���̍��W
struct Square
{
	Vector2D pos;
	int side_x,side_y;
	Box box;

};
typedef struct Square Square;

// �񎟌��̉~ / Vector2D�^, int�^
struct Circle
{
	Vector2D pos;
	int r;
};
typedef struct Circle Circle;

// �`��p / int x,y , int width,height
struct Sprite
{
	int texture;
	int x, y;
	int width, height;
};
typedef struct Sprite Sprite;

// �f�O���[�ƃ��W�A��
struct DegRad
{
	double deg, rad;
};
typedef struct DegRad DegRad;

// ��
struct GameObject
{
	Vector2D pos;
	Vector2D vel;
	Vector2D speed;
	Sprite sprite;
};
typedef struct GameObject GameObject;

// �V���b�g
struct Shot
{
	GameObject base;
	BOOL flag;
	double rad;
	int pattern;
	double r;
	double angle;
	Vector2D center;
};
typedef struct Shot Shot;

// �G�̃f�[�^�ǂݍ��ݗp
struct EnemyData
{
	int type;	//�G���
	int shot_type;	//�e���

	int move_pattern;	//�ړ��p�^�[��
	int shot_pattern;	//���˃p�^�[��

	int in_time;	//�o������
	int stop_time;	//��~����
	int shot_time;	//�e���ˎ���
	int out_time;	//�A�Ҏ���

	int x;	//x���W
	int y;	//y���W

	int speed;	//�e���x

	int hp;	//�GHP

	int item;	//�h���b�v�A�C�e��
};
typedef struct EnemyData EnemyData;
