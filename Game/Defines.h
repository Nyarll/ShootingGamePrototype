#pragma once

void InitGameCount(void);
void UpdateGameCount(void);

void UpdateKeyOld(void);

int GetGameCount(void);

BOOL GetInputKeyData(unsigned char in);
BOOL GetInputKeyOldData(unsigned char in);

BOOL OutCheck(int x, int y);// 画面外に出たかどうか	