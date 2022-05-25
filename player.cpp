/* プレイヤー処理 */
#include "player.h"
#include <time.h>

bool MoveCheck(int, int);

HINSTANCE hInst_p;
int p_w[2], p_h[2];
HDC hdc_p[2];
HBITMAP hBmp_p[2];
BITMAP p_inf[2];

/*プレーヤー初期化*/
void PlayerInit() {

	hBmp_p[0] = (HBITMAP)LoadImage(hInst_p, TEXT("resource\\player1.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_p[1] = (HBITMAP)LoadImage(hInst_p, TEXT("resource\\player2.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	for (int i = 0; i < 2; i++) {

		GetObject(hBmp_p[i], (int)sizeof(p_inf[i]), &p_inf[i]);
		p_w[i] = p_inf[i].bmWidth;
		p_h[i] = p_inf[i].bmHeight;
		hdc_p[i] = CreateCompatibleDC(NULL);
		SelectObject(hdc_p[i], hBmp_p[i]);

	}

	srand((unsigned int)time(NULL));
	return;
}

/*プレーヤー描画*/
void PlayerDraw(HDC hdc, int t) {
	TransparentBlt(hdc, PX, PY, p_w[t], p_h[t], hdc_p[t], 0, 0, p_w[t], p_h[t], RGB(255, 0, 255));
	return;
}

/*移動チェック*/
bool MoveCheck(int x, int y) {

	//マップデータ範囲外は移動不可
	if (x < 0 || y < 0 || x > 49 || y > 19) return false;

	bool ret = true;
	switch (GetMapData(x, y))
	{
	case 0:
		//木は移動不可
		ret = false;
		break;
	default:
		//それ以外は移動可
		break;
	}

	return ret;
}

/*プレーヤー移動*/
void PlayerMove(WPARAM wp) {

	PLAYERINFO *pInf = GetPlayerInfo();

	switch (wp)
	{
	case VK_UP:
		if (MoveCheck(pInf->x, pInf->y - 1)) pInf->y--;
		break;
	case VK_DOWN:
		if (MoveCheck(pInf->x, pInf->y + 1)) pInf->y++;
		break;
	case VK_LEFT:
		if (MoveCheck(pInf->x - 1, pInf->y)) pInf->x--;
		break;
	case VK_RIGHT:
		if (MoveCheck(pInf->x + 1, pInf->y)) pInf->x++;
		break;
	default:
		break;
	}

	if (GetMapData(pInf->x, pInf->y) == 2) {
		//回復の泉
		pInf->hp = pInf->maxhp;
		pInf->mp = pInf->maxmp;
		SetSound(SOUNDEFFECT::SPRING);
	}
	else if (GetMapData(pInf->x, pInf->y) == 4) {
		//ボス
		pInf->e = 100;
	}
	else {
		//敵のエンカウント率
		pInf->e = rand() % 99 + 1;
	}

	return;
}

/*プレーヤーデストラクタ*/
void PlayerDelete() {
	for (int i = 0; i < 2; i++) {
		DeleteObject(hBmp_p[i]);
		DeleteDC(hdc_p[i]);
	}
	return;
}