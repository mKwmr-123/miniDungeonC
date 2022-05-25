#include "end.h"

HDC hdc_go;
HFONT hFont_go;
HBRUSH hBrsh_go;
LPCTSTR word;

/*�Q�[���I������*/
void GameOver() {

	static bool soundFlg = true;
	static bool clearFlg = GetClearFlg();

	hdc_go = GetHdc();
	hBrsh_go = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc_go, hBrsh_go);
	Rectangle(hdc_go, 10, 10, 630, 502);

	hFont_go = CreateFont(52, 32, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("�l�r�@�S�V�b�N"));
	SetBkMode(hdc_go, TRANSPARENT);
	SelectObject(hdc_go, hFont_go);
	SetTextColor(hdc_go, RGB(255, 255, 255));

	if (clearFlg)
		//�Q�[���N���A
		word = TEXT("GAME CLEAR");
	else
		//�Q�[���I�[�o�[
		word = TEXT("GAME OVER");

	TextOut(hdc_go, 180, 220, word, lstrlen(word));

	if (soundFlg) {
		//�����J��Ԃ���Ȃ��悤�ɂ���
		soundFlg = false;
		if (clearFlg)
			SetSound(SOUNDEFFECT::GAMECLEAR);
		else
			SetSound(SOUNDEFFECT::GAMEOVER);
	}

	return;
}

/*�Q�[���I���f�X�g���N�^*/
void EndDelete() {
	DeleteObject(hFont_go);
	DeleteDC(hdc_go);
}