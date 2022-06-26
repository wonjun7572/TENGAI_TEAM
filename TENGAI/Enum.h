#pragma once
enum KEY_MANAGER
{
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F'
};

enum DIR
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFTUP,
	DIR_LEFTDOWN,		// �߰�
	DIR_RIGHTUP,
	DIR_RIGHTDOWN,		// �߰�

	DIR_END,
};

enum OBJID
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_BULLET_PLAYER,
	OBJ_BULLET_MONSTER,
	OBJ_ITEM,
	OBJ_END,
};

enum ITEM_STYLE
{
	ITEM_STYLE_ATTACK,
	ITEM_STYLE_HEAL,


	ITEM_STYLE_END,
};

enum SCENE_NAME
{
	SCENE_NAME_FIRST,
	SCENE_NAME_SECOND,

	SCENE_NAME_END,
};