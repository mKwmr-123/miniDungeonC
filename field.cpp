/* マップ描画処理 */
#include "field.h"

void MapInit();
bool MapRead();
void MapDraw(HDC, int, int);
void MapDelete();
int ctoi(char);

HINSTANCE hInst_f;

int tr_w, tr_h, gr_w, gr_h, sp_w, sp_h, mt_w, mt_h, cv_w, cv_h;
HDC hdc_tr, hdc_gr, hdc_sp, fHdc, hdc_mt, hdc_cv;
HBITMAP hBmp_tr, hBmp_gr, hBmp_sp, hBmp_mt, hBmp_cv;
BITMAP tr_inf, gr_inf, sp_inf, mt_inf, cv_inf;
PLAYERINFO* fInf;

int mdata[20][50];

/*フィールド初期化*/
void FieldInit() {
	PlayerInit();
	MapInit();
	MapRead();
	return;
}

/*マップ初期化*/
void MapInit() {

	hBmp_tr = (HBITMAP)LoadImage(hInst_f, TEXT("resource\\tree.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_gr = (HBITMAP)LoadImage(hInst_f, TEXT("resource\\grass.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_sp = (HBITMAP)LoadImage(hInst_f, TEXT("resource\\spring.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_mt = (HBITMAP)LoadImage(hInst_f, TEXT("resource\\mountain.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	hBmp_cv = (HBITMAP)LoadImage(hInst_f, TEXT("resource\\cave.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);

	GetObject(hBmp_tr, (int)sizeof(tr_inf), &tr_inf);
	tr_w = tr_inf.bmWidth;
	tr_h = tr_inf.bmHeight;
	hdc_tr = CreateCompatibleDC(NULL);
	SelectObject(hdc_tr, hBmp_tr);

	GetObject(hBmp_gr, (int)sizeof(gr_inf), &gr_inf);
	gr_w = gr_inf.bmWidth;
	gr_h = gr_inf.bmHeight;
	hdc_gr = CreateCompatibleDC(NULL);
	SelectObject(hdc_gr, hBmp_gr);

	GetObject(hBmp_sp, (int)sizeof(sp_inf), &sp_inf);
	sp_w = sp_inf.bmWidth;
	sp_h = sp_inf.bmHeight;
	hdc_sp = CreateCompatibleDC(NULL);
	SelectObject(hdc_sp, hBmp_sp);

	GetObject(hBmp_mt, (int)sizeof(mt_inf), &mt_inf);
	mt_w = mt_inf.bmWidth;
	mt_h = mt_inf.bmHeight;
	hdc_mt = CreateCompatibleDC(NULL);
	SelectObject(hdc_mt, hBmp_mt);

	GetObject(hBmp_cv, (int)sizeof(cv_inf), &cv_inf);
	cv_w = cv_inf.bmWidth;
	cv_h = cv_inf.bmHeight;
	hdc_cv = CreateCompatibleDC(NULL);
	SelectObject(hdc_cv, hBmp_cv);

	return;
}

/*マップデータ読み込み*/
bool MapRead() {

	FILE *fp;
	char fname[] = "resource\\map.txt";
	errno_t err;
	int d, i, j;

	err = fopen_s(&fp, fname, "r");
	if (err != 0) return false;
 
	i = 0;
	j = 0;
	while ((d = fgetc(fp)) != EOF) {

		if (d == '\n') continue;

		if (j > 49) {
			j = 0;
			++i;
		}

		if (i > 19) break;

		mdata[i][j] = ctoi(d);
		
		++j;

	}

	fclose(fp);

	return true;
}

/*CHAR型→数値変換*/
int ctoi(char c) {
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return 0;
	}
}

/*フィールド描画*/
void FieldDraw() {
	fHdc = GetHdc();
	fInf = GetPlayerInfo();

	MapDraw(fHdc, fInf->x, fInf->y);
	PlayerDraw(fHdc, fInf->t);
	return;
}

/*マップ描画*/
void MapDraw(HDC hdc, int x, int y) {

	int mX = 0, mY = 0;
	int wkX, wkY;
	for (int i = -3; i < 5; i++) {
		for (int j = -4; j < 6; j++) {
			wkX = x + j;
			wkY = y + i;

			if (wkX < 0 || wkY < 0 || wkX > 49 || wkY > 19) {
				//山
				BitBlt(hdc, mX, mY, gr_w, gr_h, hdc_gr, 0, 0, SRCCOPY);
				TransparentBlt(hdc, mX, mY, mt_w, mt_h, hdc_mt, 0, 0, mt_w, mt_h, RGB(255, 0, 255));
				mX += 64;
				continue;
			}

			switch (mdata[wkY][wkX])
			{
			case 0:
				//草原
				BitBlt(hdc, mX, mY, gr_w, gr_h, hdc_gr, 0, 0, SRCCOPY);
				TransparentBlt(hdc, mX, mY, tr_w, tr_h, hdc_tr, 0, 0, tr_w, tr_h, RGB(255, 0, 255));
				break;
			case 1:
				//木
				BitBlt(hdc, mX, mY, gr_w, gr_h, hdc_gr, 0, 0, SRCCOPY);
				break;
			case 2:
				//泉
				BitBlt(hdc, mX, mY, gr_w, gr_h, hdc_gr, 0, 0, SRCCOPY);
				TransparentBlt(hdc, mX, mY, sp_w, sp_h, hdc_sp, 0, 0, sp_w, sp_h, RGB(255, 0, 255));
				break;
			case 4:
				//洞窟
				BitBlt(hdc, mX, mY, gr_w, gr_h, hdc_gr, 0, 0, SRCCOPY);
				TransparentBlt(hdc, mX, mY, cv_w, cv_h, hdc_cv, 0, 0, cv_w, cv_h, RGB(255, 0, 255));
				break;
			default:
				break;
			}

			mX += 64;
		}

		mX = 0;
		mY += 64;
	}

	return;
}

/*マップ情報取得*/
int GetMapData(int x, int y) {
	return mdata[y][x];
}

/*フィールドデストラクタ*/
void FieldDelete() {
	PlayerDelete();
	MapDelete();
	return;
}

/*マップデストラクタ*/
void MapDelete() {
	
	DeleteObject(hBmp_tr);
	DeleteObject(hBmp_gr);
	DeleteObject(hBmp_sp);
	DeleteObject(hBmp_mt);
	DeleteObject(hBmp_cv);
	DeleteDC(hdc_tr);
	DeleteDC(hdc_gr);
	DeleteDC(hdc_sp);
	DeleteDC(hdc_mt);
	DeleteDC(hdc_cv);
	DeleteDC(fHdc);

	return;
}