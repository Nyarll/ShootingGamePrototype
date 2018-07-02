#pragma once

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

void InitItem(void);
void MoveItem(void);
void DrawItem(void);

void ItemDelete(int i);

void SetItemFlag(int type, int x, int y);