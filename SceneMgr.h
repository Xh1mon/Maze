#pragma once

typedef enum {
	eScene_None,
	eScene_Menu,
	eScene_Game,
	eScene_Goal,
}eScene;

void SceneMgr_Initialize();

void SceneMgr_Update();

void SceneMgr_Draw();

void SceneMgr_Finalize();

void SceneMgr_ChangeScene(eScene nextScene);


