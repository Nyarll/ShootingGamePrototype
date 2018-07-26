#pragma once

void InitGameCount(void);
void UpdateGameCount(void);

void UpdateKey(void);
void UpdateKeyOld(void);

int GetGameCount(void);

BOOL GetInputKeyData(unsigned char in);
BOOL GetInputKeyOldData(unsigned char in);

BOOL OutCheck(int x, int y);// âÊñ äOÇ…èoÇΩÇ©Ç«Ç§Ç©	