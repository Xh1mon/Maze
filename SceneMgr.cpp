#include "SceneMgr.h"
#include "Game.h"
#include "Menu.h"
#include "Dxlib.h"
#include "main.h"
#include "Goal.h"

static eScene mScene = eScene_Menu;
static eScene mNextScene = eScene_None;

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

void SceneMgr_Update() {

	if (mNextScene != eScene_None) {
		SceneMgr_ChangeScene(mNextScene);
	}

	switch (mScene) {
	case eScene_Menu:
		Menu_Update();
		break;
	case eScene_Game:
		Game_Update();
		break;
	case eScene_Goal:
		Goal_Update();
		break;
	}
}

void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Menu:
		Menu_Draw();
		break;
	case eScene_Game:
		Game_Draw();
		break;
	case eScene_Goal:
		Goal_Draw();
		break;
	}
}

void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

void SceneMgr_ChangeScene(eScene nextScene) {
	SceneMgr_Finalize();
	mScene = nextScene;
	mNextScene = eScene_None;
	SceneMgr_Initialize();
}

static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {
	case eScene_Menu:
		Menu_Initialize();
		break;
	case eScene_Game:
		Game_Initialize();
		break;
	case eScene_Goal:
		Goal_Initialize();
		break;
	}
}

static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {
	case eScene_Menu:
		Menu_Finalize();
		break;
	case eScene_Game:
		Game_Finalize();
		break;
	case eScene_Goal:
		Goal_Finalize();
		break;
	}
}