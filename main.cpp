#include "DxLib.h"
#include "SceneMgr.h"
#include"Keyboard.h"
#include"main.h"

const int window_x = 640;
const int window_y = 480;

//終了処理関係--------------------------------
static bool quitFlag = false;

static int gpMainQuit() {
	if (quitFlag) {
		return -1;
	}
}

void gpSetQuit() {
	quitFlag = true;
}
//----------------------------------------------

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウモード
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSize(window_x, window_y);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && gpMainQuit() == 0) {

		SceneMgr_Update();
		SceneMgr_Draw();

	}

	SceneMgr_Finalize();

	DxLib_End();		// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void gpGetWindowSize(int* x, int* y) {
	*x = window_x;
	*y = window_y;
}