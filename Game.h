#pragma once

typedef struct {
	int x, y;
	bool isWall;
}block_t;

typedef struct {
	int x, y;
	int img;
	bool walkFlag;
	int dir;
}player_t;

typedef enum {
	RIGHT,
	LEFT,
	UP,
	DOWN,
	SUM,
	direction_None = -1,
}eDirection;

void Game_Initialize();

void Game_Update();

void Game_Draw();

void Game_Finalize();

void Game_StageGenerator();

void Game_StageDraw();