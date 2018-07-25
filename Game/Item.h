#pragma once

#define ITEM_NUM 2048
#define ITEM_TYPE_NUM 4
#define ITEM_R 16

typedef struct Item
{
	int type;		// アイテムの種類 / 0:得点 1:パワーアップ
	Vector2D pos;	// 座標
	int top_y;		// アイテムが上昇する場所
	double rad;		// 回転角度

	int count;		// カウント

	BOOL fall_flag;	// 落下し始めるフラグ
	BOOL flag;		// 出現中かどうか
}Item;

extern Item item[ITEM_NUM];

void InitItem(void);
void MoveItem(void);
void DrawItem(void);

void ItemDelete(int i);

int GetItemNum(void);

void SetItemFlag(int type, int x, int y);