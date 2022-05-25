/*ゲームシーン切り替え*/
#include "sceen.h"

void (*init[])() = { StartInit, FieldInit, BattleInit };
void (*draw[])() = { StartDraw, FieldDraw, BattleStart, GameOver };
void (*del[])() = { StartDelete, FieldDelete, BattleDelete, EndDelete };
void (*keycheck[])(WPARAM) = { StartHitKey, PlayerMove, BattleCommand };

/*シーン毎の初期化処理*/
void SceenInit(int f) {
	init[f]();
	return;
}

/*シーン毎の描画処理*/
void SceenDraw(int f) {
	draw[f]();
	return;
}

/*シーン毎のデストラクタ*/
void SceenDelete() {
	for (int f = 0; f <= 3; f++) {
		del[f]();
	}
	return;
}

/*シーン毎のキー入力受付*/
void SceenKeyCheck(WPARAM wp, int f) {
	keycheck[f](wp);
	return;
}