#include "start.h"

HINSTANCE hInst_st;
int st_w, st_h;
HBITMAP hBmp_st;
BITMAP st_inf;
HDC hdc_st, hdc_dr;
HFONT hFont;

/*�X�^�[�g��ʏ�����*/
void StartInit() {

	hBmp_st = (HBITMAP)LoadImage(hInst_st, TEXT("resource\\start.bmp"), 
		IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	GetObject(hBmp_st, (int)sizeof(st_inf), &st_inf);
	st_w = st_inf.bmWidth;
	st_h = st_inf.bmHeight;
	hdc_st = CreateCompatibleDC(NULL);
	SelectObject(hdc_st, hBmp_st);

	SetWH(st_w, st_h);

	return;
}

/*�X�^�[�g��ʕ`��*/
void StartDraw() {
	hdc_dr = GetHdc();
	BitBlt(hdc_dr, 0, 0, st_w, st_h, hdc_st, 0, 0, SRCCOPY);

	hFont = CreateFont(32, 24, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("�l�r�@�S�V�b�N"));
	SetBkMode(hdc_dr, TRANSPARENT);
	SelectObject(hdc_dr, hFont);
	SetTextColor(hdc_dr, RGB(255,255,255));
	LPCTSTR word = TEXT("HIT A SPACE KEY !!!");
	TextOut(hdc_dr, 96, 448, word, lstrlen(word));

	return;
}

/*�X�^�[�g��ʃL�[���͎�t*/
void StartHitKey(WPARAM wp) {
	if (wp == VK_SPACE) ChengeSceen(1, true);
}

/*�X�^�[�g��ʃf�X�g���N�^*/
void StartDelete() {
	DeleteObject(hBmp_st);
	DeleteObject(hFont);
	DeleteDC(hdc_st);
	DeleteDC(hdc_dr);
	return;
}