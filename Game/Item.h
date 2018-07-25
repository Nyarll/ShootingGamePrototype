#pragma once

#define ITEM_NUM 2048
#define ITEM_TYPE_NUM 4
#define ITEM_R 16

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

extern Item item[ITEM_NUM];

void InitItem(void);
void MoveItem(void);
void DrawItem(void);

void ItemDelete(int i);

int GetItemNum(void);

void SetItemFlag(int type, int x, int y);