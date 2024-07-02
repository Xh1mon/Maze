#include "Goal.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "main.h"
#include "SceneMgr.h"

int window_x = 0;
int window_y = 0;

void Goal_Initialize() {
	gpGetWindowSize(&window_x, &window_y);
}

void Goal_Update() {
	if (gpGetKeyDown(KEY_INPUT_ESCAPE) == 1) {
		gpSetQuit();
	}
	if (gpGetKeyDown(KEY_INPUT_RETURN) == 1) {
		SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Goal_Draw() {
	DrawString(window_x / 2 - GetDrawStringWidth("GOAL!!", 6), 200, "GOAL!!", GetColor(255, 255, 255));
	DrawString(window_x / 2 - GetDrawStringWidth("Press Enter To Menu", 11), 300, "Press Enter To Menu", GetColor(255, 255, 255));
}

void Goal_Finalize() {

}