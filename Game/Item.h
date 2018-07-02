#pragma once

typedef struct Item
{
	int type;		// �A�C�e���̎�� / 0:���_ 1:�p���[�A�b�v
	Vector2D pos;	// ���W
	int top_y;		// �A�C�e�����㏸����ꏊ
	double rad;		// ��]�p�x

	int count;		// �J�E���g

	BOOL fall_flag;	// �������n�߂�t���O
	BOOL flag;		// �o�������ǂ���
}Item;

void InitItem(void);
void MoveItem(void);
void DrawItem(void);

void ItemDelete(int i);

void SetItemFlag(int type, int x, int y);