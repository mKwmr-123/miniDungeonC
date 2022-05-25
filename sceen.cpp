/*�Q�[���V�[���؂�ւ�*/
#include "sceen.h"

void (*init[])() = { StartInit, FieldInit, BattleInit };
void (*draw[])() = { StartDraw, FieldDraw, BattleStart, GameOver };
void (*del[])() = { StartDelete, FieldDelete, BattleDelete, EndDelete };
void (*keycheck[])(WPARAM) = { StartHitKey, PlayerMove, BattleCommand };

/*�V�[�����̏���������*/
void SceenInit(int f) {
	init[f]();
	return;
}

/*�V�[�����̕`�揈��*/
void SceenDraw(int f) {
	draw[f]();
	return;
}

/*�V�[�����̃f�X�g���N�^*/
void SceenDelete() {
	for (int f = 0; f <= 3; f++) {
		del[f]();
	}
	return;
}

/*�V�[�����̃L�[���͎�t*/
void SceenKeyCheck(WPARAM wp, int f) {
	keycheck[f](wp);
	return;
}