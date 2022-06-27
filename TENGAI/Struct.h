#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;
}INFO;

typedef struct tagStat
{
	int Hp;
	int BulletCount;
	int UltimateCount;
	HBRUSH hOldBrush;
	HBRUSH hNewBrush;
}STAT;