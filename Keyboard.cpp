#include "Keyboard.h" 
#include "DxLib.h"

static int key[256];

int gpUpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
	return 0;
}

int gpGetKeyDown(int _key) {
	return key[_key];
}