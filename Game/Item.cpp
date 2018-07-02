#include <math.h>
#include "Item.h"
#include "Player.h"
#include "Defines.h"

Item item[ITEM_NUM];
double item_rad[ITEM_NUM];
// グラフィックハンドル / 0:スコア 1:パワーアップ 2:ボム 3:残機
static HGRP gh[4], ghs[4];


void InitItem(void)
{
	int i;

	// とりあえず 0 にしておく
	for (i = 0; i < ITEM_NUM; i++)
	{
		item[i].type = 0;
		item[i].count = 0;
		item[i].fall_flag = FALSE;
		item[i].flag = FALSE;
		item[i].pos = { 0,0 };
		item[i].rad = 0;

		item_rad[i] = 0;
	}

	gh[0] = LoadGraph("Resources/Textures/item_s.png");
	gh[1] = LoadGraph("Resources/Textures/item_p.png");
	gh[2] = LoadGraph("Resources/Textures/item_b.png");
	gh[3] = LoadGraph("Resources/Textures/item_h.png");
	ghs[0] = LoadGraph("Resources/Textures/items_s.png");
	ghs[1] = LoadGraph("Resources/Textures/items_p.png");
	ghs[2] = LoadGraph("Resources/Textures/items_b.png");
	ghs[3] = LoadGraph("Resources/Textures/items_h.png");

}
void MoveItem(void)
{
	int i;
	double tempy;

	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item[i].flag)
		{
			item[i].rad = 0.04 * item[i].count;
			item[i].count++;

			if (GetPlayerPosY() < (GAME_SCREEN_CENTER_Y / 2))
			{
				item_rad[i] = atan2(item[i].pos.y - GetPlayerPosY(), item[i].pos.x - GetPlayerPosX());

				item[i].pos.x -= cos(item_rad[i]) * 5;
				item[i].pos.y -= sin(item_rad[i]) * 5;
			}
			else
			{
				if (!item[i].fall_flag)
				{
					tempy = item[i].pos.y;
					item[i].pos.y -= (item[i].pos.y - item[i].top_y) + 1;

					if (((item[i].pos.y - item[i].top_y) + 1) == 0)
					{
						item[i].fall_flag = TRUE;
					}
					item[i].top_y = tempy;
				}
				else
				{
					item[i].pos.y++;
				}
			}
		}

		if (OutCheck(item[i].pos.x, item[i].pos.y))
		{
			ItemDelete(i);
		}

	}
}
void DrawItem(void)
{
	int i;

	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item[i].flag)
		{
			DrawRotaGraph(item[i].pos.x, item[i].pos.y, 1.0, item[i].rad, gh[item[i].type], TRUE);
			DrawRotaGraph(item[i].pos.x, item[i].pos.y, 1.0, 0.0, ghs[item[i].type], TRUE);
		}
	}
}

void ItemDelete(int i)
{
	item[i].count = 0;
	item[i].flag = FALSE;
	item[i].fall_flag = FALSE;
}

int GetItemNum(void)
{
	return ITEM_NUM;
}

void SetItemFlag(int type, int x, int y)
{
	int i;

	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item[i].flag == FALSE)	// 出現中じゃないアイテムを探す
		{
			item[i].pos.x = x;
			item[i].pos.y = y;
			item[i].top_y = y + 10;
			item[i].type = type;
			item[i].flag = TRUE;
			break;
		}
	}
}