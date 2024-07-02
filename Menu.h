#pragma once

typedef enum {
	eMenuElement_Game,
	eMenuElement_Quit,
	eMenuElement_Sum,
}eMenuElement;

typedef struct {
	int x, y;
	char name[128];
}MenuElement_t;

void Menu_Initialize();

void Menu_Update();

void Menu_Draw();

void Menu_Finalize();
