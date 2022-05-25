#include "end.h"

HDC hdc_go;
HFONT hFont_go;
HBRUSH hBrsh_go;
LPCTSTR word;

/*ゲーム終了処理*/
void GameOver() {

	static bool soundFlg = true;
	static bool clearFlg = GetClearFlg();

	hdc_go = GetHdc();
	hBrsh_go = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc_go, hBrsh_go);
	Rectangle(hdc_go, 10, 10, 630, 502);

	hFont_go = CreateFont(52, 32, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("ＭＳ　ゴシック"));
	SetBkMode(hdc_go, TRANSPARENT);
	SelectObject(hdc_go, hFont_go);
	SetTextColor(hdc_go, RGB(255, 255, 255));

	if (clearFlg)
		//ゲームクリア
		word = TEXT("GAME CLEAR");
	else
		//ゲームオーバー
		word = TEXT("GAME OVER");

	TextOut(hdc_go, 180, 220, word, lstrlen(word));

	if (soundFlg) {
		//音が繰り返し鳴らないようにする
		soundFlg = false;
		if (clearFlg)
			SetSound(SOUNDEFFECT::GAMECLEAR);
		else
			SetSound(SOUNDEFFECT::GAMEOVER);
	}

	return;
}

/*ゲーム終了デストラクタ*/
void EndDelete() {
	DeleteObject(hFont_go);
	DeleteDC(hdc_go);
}