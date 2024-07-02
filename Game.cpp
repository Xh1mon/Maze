#include "Game.h"
#include <stdio.h>
#include "Keyboard.h"
#include "Dxlib.h"
#include "SceneMgr.h"
#include <time.h>
#include "main.h"

#define STAGE_SIZE 15
#define STAGE_WIDTH STAGE_SIZE
#define STAGE_HEIGHT STAGE_SIZE

#define START_X 1
#define START_Y 0

#define BLOCK_SIZE 32

static int playerSizeX = 0;
static int playerSizeY = 0;

static block_t blockData[STAGE_WIDTH][STAGE_HEIGHT];
static int direction = direction_None;
static bool isGoal = false;

static player_t player = { 0, 0, 0, false, 0};
static int image[16];


void Game_Initialize() {
	SetBackgroundColor(70, 130, 180);
	Game_StageGenerator();
	player.x = START_X * BLOCK_SIZE;
	player.y = START_Y * BLOCK_SIZE;
	isGoal = false;
	LoadDivGraph("char.png", 16, 4, 4, 32, 32, image);
	GetGraphSize(image[0], &playerSizeX, &playerSizeY);
}

void Game_Update() {

	if (gpGetKeyDown(KEY_INPUT_ESCAPE) == 1) {
		gpSetQuit();
	}
	if (player.x % BLOCK_SIZE == 0 && player.y % BLOCK_SIZE == 0) {
		player.walkFlag = true;
		if (gpGetKeyDown(KEY_INPUT_UP) == 1) {
			if (blockData[player.x / BLOCK_SIZE][player.y / BLOCK_SIZE - 1].isWall == true) {
				player.walkFlag = false;
			}
			player.dir = 0;
		}
		else if (gpGetKeyDown(KEY_INPUT_LEFT) == 1) {
			if (blockData[player.x / BLOCK_SIZE - 1][player.y / BLOCK_SIZE].isWall == true) {
				player.walkFlag = false;
			}
			player.dir = 1;
		}
		else if (gpGetKeyDown(KEY_INPUT_DOWN) == 1) {
			if (blockData[player.x / BLOCK_SIZE][player.y / BLOCK_SIZE + 1].isWall == true) {
				player.walkFlag = false;
			}
			player.dir = 2;
		}
		else if (gpGetKeyDown(KEY_INPUT_RIGHT) == 1) {
			if (blockData[player.x / BLOCK_SIZE + 1][player.y / BLOCK_SIZE].isWall == true) {
				player.walkFlag = false;
			}
			player.dir = 3;
		}
		else {
			player.walkFlag = false;
		}
	}
	if(player.walkFlag == true) {
		switch (player.dir) {
		case 0:
			player.y--;
			break;
		case 1:
			player.x--;
			break;
		case 2:
			player.y++;
			break;
		case 3:
			player.x++;
			break;
		}
	}

	if (player.x ==( STAGE_WIDTH - 2) * BLOCK_SIZE && player.y == (STAGE_HEIGHT - 1) * BLOCK_SIZE) {
		isGoal = true;
	}

	if (isGoal) {
		SceneMgr_ChangeScene(eScene_Goal);
	}
}

void Game_Draw() {
	player.img = image[(player.x % BLOCK_SIZE + player.y % BLOCK_SIZE) / 8 + player.dir * 4];

	Game_StageDraw();

	DrawGraph(player.x, player.y, player.img, TRUE);

}

void Game_Finalize() {
	for (int i = 0; i < 16; i++) {
		DeleteGraph(image[i]);
	}
}


void Game_StageGenerator() {

	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			blockData[x][y].x = x;
			blockData[x][y].y = y;
			blockData[x][y].isWall = false;
		}
	}

	srand((unsigned int)time(NULL));

	//周りの壁----------------------------------
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			blockData[x][y].isWall = false;  //初期化
			if (x == 0 ||
				x == STAGE_WIDTH - 1 ||
				y == 0 ||
				y == STAGE_HEIGHT - 1) {
				blockData[x][y].isWall = true;
			}
		}
	}
	//------------------------------------------

	//・(x, y)がともに偶数かつ周りの壁以外に壁を作る
	//・作った壁の四方向のいずれかにランダムに壁を1マス伸ばす（y = 2とそうでない時で分ける）

	//y = 2でないとき、上には伸ばさない
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if ((x % 2 == 0 && y % 2 == 0) &&
				!(x == 0 ||
					x == STAGE_WIDTH - 1 ||
					y == 2 ||
					y == 0 ||
					y == STAGE_HEIGHT - 1)) {
				//方向をランダムに決め、決めた方向1マスに壁があったらもう一度方向を取得を繰り返す
				do {
					direction = rand() % 4;
					switch (direction) {
					case RIGHT:
						if (blockData[x + 1][y].isWall == false) {
							blockData[x + 1][y].isWall = true;
						}
						else {
							direction = direction_None;
						}
						break;
					case LEFT:
						if (blockData[x - 1][y].isWall == false) {
							blockData[x - 1][y].isWall = true;
						}
						else {
							direction = direction_None;
						}
						break;
					case UP:
						direction = direction_None;
						break;
					case DOWN:
						if (blockData[x][y + 1].isWall == false) {
							blockData[x][y + 1].isWall = true;
						}
						else {
							direction = direction_None;
						}
						break;
					}
				} while (direction == direction_None);
				blockData[x][y].isWall = true;
			}
		}
	}
	//--------------------------------------------

	//y = 2のとき全方位伸ばせる
	int y = 2;
	for (int x = 2; x < STAGE_WIDTH - 2; x += 2) {
		do {
			direction = rand() % 4;
			switch (direction) {
			case RIGHT:
				if (blockData[x + 1][y].isWall == false) {
					blockData[x + 1][y].isWall = true;
				}
				else {
					direction = direction_None;
				}
				break;
			case LEFT:
				if (blockData[x - 1][y].isWall == false) {
					blockData[x - 1][y].isWall = true;
				}
				else {
					direction = direction_None;
				}
				break;
			case UP:
				if (blockData[x][y - 1].isWall == false) {
					blockData[x][y - 1].isWall = true;
				}
				else {
					direction = direction_None;
				}
				break;
			case DOWN:
				if (blockData[x][y + 1].isWall == false) {
					blockData[x][y + 1].isWall = true;
				}
				else {
					direction = direction_None;
				}
				break;
			}
		} while (direction == direction_None);
		blockData[x][y].isWall = true;
	}
	//------------------------------------

	//ゴールとスタートを通路にする
	blockData[START_X][START_Y].isWall = false;
	blockData[STAGE_WIDTH - 2][STAGE_HEIGHT - 1].isWall = false;

}

void Game_StageDraw() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (blockData[x][y].isWall == true) {
				DrawBox(blockData[x][y].x * BLOCK_SIZE, blockData[x][y].y * BLOCK_SIZE, blockData[x][y].x * BLOCK_SIZE + BLOCK_SIZE, blockData[x][y].y * BLOCK_SIZE + BLOCK_SIZE, GetColor(245, 222, 179), TRUE);
			}
		}
	}
}

void Game_GetBlock(block_t* p[STAGE_WIDTH]) {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			p[x][y] = blockData[x][y];
		}
	}
}

