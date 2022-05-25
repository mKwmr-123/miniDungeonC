/*�@�퓬���� */
#include "battle.h"
#include <time.h>
#include <tchar.h>

int GetEnemyLevel(int, int);
void BattleDraw();
void BattleWord(int);
void BattleCommand();
void BattleMeter();
int GetAddPower();
void ModPara(int*, int);
void LevelUp(PLAYERINFO*);

HINSTANCE hInst_e;
HBRUSH hBrsh_E, hBrsh_P, hBrsh_C, hBrsh_W;
HDC hdc_b, hdc_e[3], eHdc, hdc_cur;
HBITMAP hBmp_e[3], hBmp_cur;
BITMAP e_inf[3], cur_inf;
int e_w[3], e_h[3], cur_h, cur_w, curXY[2];
PLAYERINFO* b_pinf;
ENEMYINFO b_einf;
HFONT b_hFont;
int bw, tX, tY, enemyLevel, adPower;

/*���b�Z�[�W�z��*/
LPCTSTR bWords[] = {
	TEXT("�G�����ꂽ�I"),					//0
	TEXT("�v���[���[�̍U��"),				//1
	TEXT("�̃_���[�W��^�����I"),			//2
	TEXT("�v���[���[�͉񕜎�����������"),	//3
	TEXT("�G�̍U��"),						//4
	TEXT("�̃_���[�W���󂯂��I"),			//5
	TEXT("�G��|����"),						//6
	TEXT("�v���[���[�͗͐s����"),			//7
	TEXT("�v���[���[�͓����o�����I"),		//8
	TEXT("�������A�G�ɉ�荞�܂ꂽ�I"),		//9
	TEXT("MP������Ȃ��I"),					//10
	TEXT("�v���[���[�͐��������I")			//11
};

/*�o�g��������*/
void BattleInit() {
	hBrsh_E = CreateSolidBrush(RGB(0, 0, 0));
	hBrsh_P = CreateSolidBrush(RGB(0, 0, 0));
	hBrsh_C = CreateSolidBrush(RGB(0, 0, 0));
	hBrsh_W = CreateSolidBrush(RGB(0, 0, 0));

	hBmp_e[0] = (HBITMAP)LoadImage(hInst_e, TEXT("resource\\enemy.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_e[1] = (HBITMAP)LoadImage(hInst_e, TEXT("resource\\enemy2.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_e[2] = (HBITMAP)LoadImage(hInst_e, TEXT("resource\\boss.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_cur = (HBITMAP)LoadImage(hInst_e, TEXT("resource\\cursor.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	for (int i = 0; i < 3; i++) {

		GetObject(hBmp_e[i], (int)sizeof(e_inf[i]), &e_inf[i]);
		e_w[i] = e_inf[i].bmWidth;
		e_h[i] = e_inf[i].bmHeight;
		hdc_e[i] = CreateCompatibleDC(NULL);
		SelectObject(hdc_e[i], hBmp_e[i]);

	}

	GetObject(hBmp_cur, (int)sizeof(cur_inf), &cur_inf);
	cur_w = cur_inf.bmWidth;
	cur_h = cur_inf.bmHeight;
	hdc_cur = CreateCompatibleDC(NULL);
	SelectObject(hdc_cur, hBmp_cur);

	curXY[0] = 38;
	curXY[1] = 170;
	bw = 0;
	tX = 50;
	tY = 340;

	b_pinf = GetPlayerInfo();
	//�G�̗̑͂ƃp���[��ݒ�
	enemyLevel = GetEnemyLevel(b_pinf->x, b_pinf->y);
	switch (enemyLevel)
	{
	case 1:
		b_einf.hp = 12;
		b_einf.pw = 2;
		break;
	case 2:
		b_einf.hp = 36;
		b_einf.pw = 6;
		break;
	case 3:
		b_einf.hp = 100;
		b_einf.pw = 10;
	default:
		break;
	}

	srand((unsigned int)time(NULL));

	return;
}

/*�o�g���J�n����*/
void BattleStart() {

	//�w�i�̃t�B�[���h�`��
	FieldDraw();

	//�e�p�l���`��
	hdc_b = GetHdc();

	SelectObject(hdc_b, hBrsh_E);
	Rectangle(hdc_b, 192, 32, 608, 320);

	SelectObject(hdc_b, hBrsh_P);
	Rectangle(hdc_b, 32, 32, 180, 128);

	SelectObject(hdc_b, hBrsh_C);
	Rectangle(hdc_b, 32, 140, 180, 320);

	SelectObject(hdc_b, hBrsh_W);
	Rectangle(hdc_b, 32, 332, 608, 480);

	//�G�`��
	BattleDraw();

	return;
}

/*�G�̕`�揈��*/
void BattleDraw() {
	
	if (bw == 100 || bw == 11) {
		//��ʐ؂�ւ����A���x���A�b�v���͓G���o���Ȃ�
	}else{
		if (enemyLevel == 1)
			TransparentBlt(hdc_b, 336, 48, e_w[0], e_h[0], hdc_e[0], 0, 0, e_w[0], e_h[0], RGB(255, 0, 255));
		else if (enemyLevel == 2)
			TransparentBlt(hdc_b, 323, 177, e_w[1], e_h[1], hdc_e[1], 0, 0, e_w[1], e_h[1], RGB(255, 0, 255));
		else
			TransparentBlt(hdc_b, 214, 68, e_w[2], e_h[2], hdc_e[2], 0, 0, e_w[2], e_h[2], RGB(255, 0, 255));
	}

	BattleWord(bw);		//���b�Z�[�W�\��
	BattleCommand();	//�R�}���h�\��
	BattleMeter();		//�v���[���[�̗̑́E���͕\��

	return;
}

/*�o�g���f�X�g���N�^*/
void BattleDelete() {

	DeleteDC(hdc_b);
	DeleteDC(eHdc);
	DeleteDC(hdc_cur);
	DeleteObject(hBrsh_E);
	DeleteObject(hBrsh_P);
	DeleteObject(hBrsh_C);
	DeleteObject(hBrsh_W);
	DeleteObject(b_hFont);
	DeleteObject(hBmp_cur);

	for (int i = 0; i < 3; i++) {
		DeleteObject(hBmp_e[i]);
		DeleteDC(hdc_e[i]);
	}

	return;
}

/*�R�}���h�L�[���͎�t*/
void BattleCommand(WPARAM wp) {

	switch (wp)
	{
	case VK_UP:

		if (curXY[1] > 170) curXY[1] -= 50;
		break;

	case VK_DOWN:

		if (curXY[1] < 270) curXY[1] += 50;
		break;

	case VK_RETURN:

		if (curXY[1] == 170) bw = 1;
		else if (curXY[1] == 220) bw = 3;
		else if (curXY[1] == 270) bw = 8;
		
		break;

	default:
		break;
	}

	return;
}

/*�G�̃��x���擾*/
int GetEnemyLevel(int x, int y) {
	if (x == 49 && y == 19) return 3;		//boss
    else if (x > 20 || y > 20) return 2;	//enemy2
	else return 1;							//enemy
}

/*���b�Z�[�W�\��*/
void BattleWord(int w) {

	b_hFont = CreateFont(32, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("�l�r�o�@�S�V�b�N"));
	SetBkMode(hdc_b, TRANSPARENT);
	SelectObject(hdc_b, b_hFont);
	SetTextColor(hdc_b, RGB(255, 255, 255));
	LPCTSTR word, lpszFormat;
	TCHAR szBuf[64];
	int ap;
	static int sc = 1;

	lpszFormat = TEXT("%d %s");

	//�v���[���[�̎��O�̗̓`�F�b�N
	if (w != 100 && b_pinf->hp <= 0) w = 7;

	switch (w) {
	case 1:
		//�v���[���[�̍U���J�n
		bw = 2;
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		SetRag(true);
		break;

	case 2:
		//�v���[���[�̍U��
		ap = GetAddPower();
		word = bWords[1];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		wsprintf(szBuf, lpszFormat, b_pinf->pw + ap, bWords[w]);
		TextOut(hdc_b, 50, 390, szBuf, lstrlen(szBuf));
		SetRag(true);
		ModPara(&(b_einf.hp), -(b_pinf->pw + ap));

		SetSound(SOUNDEFFECT::ATTACK);

		if (b_einf.hp <= 0) bw = 6;
		else bw = 4;
		break;

	case 3:
		//�v���[���[�̉񕜎���
		if (b_pinf->mp >= 2) {
			word = bWords[w];
			TextOut(hdc_b, 50, 340, word, lstrlen(word));
			SetRag(true);
			ModPara(&(b_pinf->hp), (b_pinf->maxhp - b_pinf->hp) > b_pinf->cure ?
				b_pinf->cure : (b_pinf->maxhp - b_pinf->hp));
			ModPara(&(b_pinf->mp), -2);
			bw = -1;
		}
		else {
			word = bWords[10];
			TextOut(hdc_b, 50, 340, word, lstrlen(word));
			SetRag(true);
			bw = -1;
		}

		SetSound(SOUNDEFFECT::CURE);

		break;

	case 4:
		//�G�̍U���J�n
		bw = 5;
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		SetRag(true);
		break;

	case 5:
		//�G�̍U��
		ap = GetAddPower();
		word = bWords[4];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		wsprintf(szBuf, lpszFormat, b_einf.pw + ap, bWords[w]);
		TextOut(hdc_b, 50, 390, szBuf, lstrlen(szBuf));
		SetRag(true);
		ModPara(&(b_pinf->hp), -(b_einf.pw + ap));

		SetSound(SOUNDEFFECT::DAMAGE);

		if (b_pinf->hp <= 0) bw = 7;
		else bw = -1;

		break;

	case 6:
		//�G��|����
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		b_pinf->exp += 2;
		if (enemyLevel == 3) {
			//�Q�[���N���A
			SetClearFlg(true);
			sc = 3;
			bw = 100;
		}
		else if (b_pinf->lv < 4 && b_pinf->exp % 10 == 0) {
			//���x���A�b�v
			bw = 11;
		}
		else {
			bw = 100;
		}
		break;

	case 7:
		//�v���[���[���͐s����
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		sc = 3;
		bw = 100;

		break;

	case 8:
		//�v���[���[�������o����
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));

		SetSound(SOUNDEFFECT::ESCAPE);

		if ((rand() % 50 + 1) > 45) bw = 9;
		else bw = 100;
		
		break;

	case 9:
		//�G�ɉ�荞�܂ꂽ
		word = bWords[8];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		word = bWords[w];
		TextOut(hdc_b, 50, 390, word, lstrlen(word));
		SetRag(true);
		bw = 4;
		break;

	case 11:
		//���x���A�b�v
		word = bWords[w];
		TextOut(hdc_b, 50, 340, word, lstrlen(word));
		bw = 100;
		LevelUp(b_pinf);

		SetSound(SOUNDEFFECT::LEVELUP);

		break;

	case 100:
		//�t�B�[���h��ʂɖ߂�
		Sleep(500);
		SetRag(false);
		b_pinf->e = 0;
		ChengeSceen(sc, false);
		break;

	default:
		SetRag(false);
		break;
	}

	return;
}

/*�R�}���h�\��*/
void BattleCommand() {

	b_hFont = CreateFont(24, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("�l�r�o�@�S�V�b�N"));

	SetBkMode(hdc_b, TRANSPARENT);
	SelectObject(hdc_b, b_hFont);
	SetTextColor(hdc_b, RGB(255, 255, 255));
	
	LPCTSTR word = TEXT("�̓�����");
	TextOut(hdc_b, 64, 170, word, lstrlen(word));
	word = TEXT("���@");
	TextOut(hdc_b, 64, 220, word, lstrlen(word));
	word = TEXT("������");
	TextOut(hdc_b, 64, 270, word, lstrlen(word));

	TransparentBlt(hdc_b, curXY[0], curXY[1], cur_w, cur_h, hdc_cur, 0, 0, cur_w, cur_h, RGB(255, 0, 255));

	return;
}

/*�v���[���[�̗̑́E���͕\��*/
void BattleMeter() {

	LPCTSTR lpszFormat;
	TCHAR szBuf[10];

	b_hFont = CreateFont(24, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("�l�r�o�@�S�V�b�N"));

	SetBkMode(hdc_b, TRANSPARENT);
	SelectObject(hdc_b, b_hFont);
	SetTextColor(hdc_b, RGB(255, 255, 255));
	
	lpszFormat = TEXT("%s %d");
	wsprintf(szBuf, lpszFormat, TEXT("HP�F"), b_pinf->hp < 0 ? 0 : b_pinf->hp);
	TextOut(hdc_b, 45, 55, szBuf, lstrlen(szBuf));
	wsprintf(szBuf, lpszFormat, TEXT("MP�F"), b_pinf->mp);
	TextOut(hdc_b, 45, 85, szBuf, lstrlen(szBuf));

	return;
}

/*�ǉ��U���͎擾*/
int GetAddPower() {
	//�U���͂̒ǉ���
	int a = rand() % 100 + 1;
	if (a > 95)
		return 3;
	else if (a > 90)
		return 2;
	else if (a > 80)
		return 1;
	else if (a > 10)
		return 0;
	else
		return -1;
}

/*�p�����[�^�X�V*/
void ModPara(int* hp, int pw) {
	*hp += pw;
	return;
}

/*���x���A�b�v����*/
void LevelUp(PLAYERINFO* pinf) {

	switch (pinf->lv)
	{
	case 1:
		pinf->maxhp = 25;
		pinf->maxmp = 6;
		pinf->pw = 5;
		pinf->cure = 15;
		break;
	case 2:
		pinf->maxhp = 35;
		pinf->maxmp = 8;
		pinf->pw = 8;
		pinf->cure = 20;
		break;
	case 3:
		pinf->maxhp = 45;
		pinf->maxmp = 10;
		pinf->pw = 12;
		pinf->cure = 25;
		break;
	default:
		return;
	}

	pinf->hp = pinf->maxhp;
	pinf->mp = pinf->maxmp;
	pinf->lv += 1;

	return;
}