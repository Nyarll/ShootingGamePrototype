#include "Defines.h"

static int game_count;
static char keys[256];
static char key_old[256];

void InitGameCount(void)
{
	game_count = 0;
}

void UpdateGameCount(void)
{
	GetHitKeyStateAll(keys);
	game_count++;
}

void UpdateKeyOld(void)
{
	GetHitKeyStateAll(key_old);
}

int GetGameCount(void)
{
	return game_count;
}

BOOL GetInputKeyData(unsigned char in)
{
	if (keys[in] == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL GetInputKeyOldData(unsigned char in)
{
	if (key_old[in] == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}