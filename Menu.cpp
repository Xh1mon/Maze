#include "Menu.h"
#include <stdio.h>
#include "Keyboard.h"
#include "Dxlib.h"
#include "SceneMgr.h"
#include "main.h"

static int selectNum = eMenuElement_Game;

MenuElement_t menuElement[eMenuElement_Sum] = {
	{80, 100, "ゲーム"},
	{100, 200, "終了"},
};

void Menu_Initialize() {
	SetBackgroundColor(70, 130, 180);
}

void Menu_Update() {
	//下に選択------------------------------
	if (gpGetKeyDown(KEY_INPUT_DOWN) == 1) {
		selectNum = (selectNum + 1) % eMenuElement_Sum;

		for (int i = 0; i < eMenuElement_Sum; i++) {
			if (i == selectNum) {
				menuElement[i].x = 80;
			}
			else {
				menuElement[i].x = 100;
			}
		}

	}
	//上に選択------------------------------
	if (gpGetKeyDown(KEY_INPUT_UP) == 1) {
		selectNum = (selectNum + eMenuElement_Sum - 1) % eMenuElement_Sum;

		for (int i = 0; i < eMenuElement_Sum; i++) {
			if (i == selectNum) {
				menuElement[i].x = 80;
			}
			else {
				menuElement[i].x = 100;
			}
		}
	}

	if (gpGetKeyDown(KEY_INPUT_RETURN) == 1) {
		switch (selectNum) {
		case eMenuElement_Game:
			SceneMgr_ChangeScene(eScene_Game);
			break;
		case eMenuElement_Quit:
			gpSetQuit();
			break;
		}
	}

	if (gpGetKeyDown(KEY_INPUT_ESCAPE) == 1) {
		gpSetQuit();
	}

}

void Menu_Draw() {
	for (int i = 0; i < eMenuElement_Sum; i++) {
		DrawFormatString(menuElement[i].x, menuElement[i].y, GetColor(255, 255, 255), menuElement[i].name);
	}
}

void Menu_Finalize() {

}

