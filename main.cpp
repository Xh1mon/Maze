#include "DxLib.h"
#include "SceneMgr.h"
#include"Keyboard.h"
#include"main.h"

const int window_x = 640;
const int window_y = 480;

//�I�������֌W--------------------------------
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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSize(window_x, window_y);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && gpMainQuit() == 0) {

		SceneMgr_Update();
		SceneMgr_Draw();

	}

	SceneMgr_Finalize();

	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void gpGetWindowSize(int* x, int* y) {
	*x = window_x;
	*y = window_y;
}