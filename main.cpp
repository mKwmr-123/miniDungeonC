/* ウィンドウ処理 */
#include "main.h"

#define ID_MYTIMER 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
BOOL MyAdjustWindow(HWND, int, int);

LPCTSTR lpszClassName = TEXT("miniDungeon");

HWND hWnd;
HINSTANCE hInst;
HDC mHdc;
PAINTSTRUCT ps;
RECT rc;
PLAYERINFO inf,*p_inf;
int winx, winy;
int bg_w, bg_h;
int sc;
int cnt;
bool keyFlg, ragFlg, clFlg;
LPCTSTR pszSound;
SOUNDEFFECT sndeft;

//メイン関数
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst)) return FALSE;
	if (!InitInstance(hCurInst, nCmdShow)) return FALSE;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			break;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//ウィンドウクラスの登録
ATOM InitApp(HINSTANCE hCurInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hCurInst;
	wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpszClassName;
	wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//ウィンドウの生成
BOOL InitInstance(HINSTANCE hCurInst, int nCmdShow)
{
	hWnd = CreateWindowEx(WS_EX_COMPOSITED, lpszClassName, TEXT("ミニだんじょん２"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 640, 512, NULL, NULL, hCurInst, NULL);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	MINMAXINFO* lpminmax;

	switch (msg)
	{
	case WM_CREATE:
		//初期設定
		sc = 0;
		SceenInit(sc);
		
		cnt = 0;
		//プレーヤー情報
		inf = { 4		//マップX座標
			  , 2		//マップY座標
			  , 0		//アニメーショントグル
			  , -1		//敵とのエンカウント率
			  , 15		//体力
			  , 2		//魔力
			  , 15		//最大体力
			  , 2		//最大魔力
			  , 3		//攻撃力
			  , 10		//魔法効果
			  , 1		//レベル
			  , 0};		//経験値
		p_inf = &inf;
		keyFlg = false;
		ragFlg = false;
		clFlg = false;
		pszSound = TEXT("NONE");
		sndeft = SOUNDEFFECT::NONE;

		MyAdjustWindow(hWnd, bg_w, bg_h);

		SetTimer(hWnd, ID_MYTIMER, 100, NULL);

		break;

	case WM_GETMINMAXINFO:
		//ウィンドウ調整
		lpminmax = (LPMINMAXINFO)lp;
		lpminmax->ptMaxTrackSize.x = winx;
		lpminmax->ptMaxTrackSize.y = winy;
		lpminmax->ptMinTrackSize.x = winx;
		lpminmax->ptMinTrackSize.y = winy;
		break;

	case WM_PAINT:
		//描画
		GetClientRect(hWnd, &rc);

		mHdc = BeginPaint(hWnd, &ps);
		{
			SceenDraw(sc);
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		//キー入力受付
		if (keyFlg) {
			SceenKeyCheck(wp, sc);
			InvalidateRect(hWnd, NULL, TRUE);
			keyFlg = false;
		}
		
		break;

	case WM_TIMER:
		//タイマー
		if (wp != ID_MYTIMER) return DefWindowProc(hWnd, msg, 0, 0);

		switch (sc)
		{
		case 0:
			//スタート画面
			keyFlg = true;
			break;

		case 1:
			//フィールド画面
			if (inf.e == 100 || ++cnt > 4) {
				//アニメーション用カウンタ
				cnt = 0;
				if (inf.t) inf.t = 0;
				else inf.t = 1;

				keyFlg = true;
				InvalidateRect(hWnd, NULL, TRUE);

				//敵の出現判定
				if (inf.e > 85) ChengeSceen(2,true);
			}

			if (sndeft == SOUNDEFFECT::SPRING) {
				pszSound = TEXT("resource\\spring.wav");
			}

			break;
		case 2:
			//バトル画面
			if (++cnt > 3) {
				cnt = 0;
				keyFlg = true;
				if (ragFlg) Sleep(500);
				InvalidateRect(hWnd, NULL, TRUE);
			}

			switch (sndeft)
			{
			case SOUNDEFFECT::ATTACK:
				pszSound = TEXT("resource\\attack.wav");
				break;
			case SOUNDEFFECT::DAMAGE:
				pszSound = TEXT("resource\\damage.wav");
				break;
			case SOUNDEFFECT::LEVELUP:
				pszSound = TEXT("resource\\levelup.wav");
				break;
			case SOUNDEFFECT::CURE:
				pszSound = TEXT("resource\\cure.wav");
				break;
			case SOUNDEFFECT::ESCAPE:
				pszSound = TEXT("resource\\escape.wav");
				break;
			default:
				break;
			}

			break;

		case 3:
			//ゲーム終了画面
			if (sndeft == SOUNDEFFECT::GAMEOVER)
				pszSound = TEXT("resource\\gameover.wav");
			else if (sndeft == SOUNDEFFECT::GAMECLEAR)
				pszSound = TEXT("resource\\gameclear.wav");
			InvalidateRect(hWnd, NULL, TRUE);

			break;

		default:
			break;
		}

		if (sndeft != SOUNDEFFECT::NONE) {
			//効果音
			PlaySound(pszSound, NULL, SND_ASYNC | SND_FILENAME);
			sndeft = SOUNDEFFECT::NONE;
		}

		break;

	case WM_CLOSE:
		//画面が閉じられた場合の処理
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		//破棄処理
		KillTimer(hWnd, ID_MYTIMER);

		SceenDelete();

		PostQuitMessage(0);

		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}

	return 0;
}

/*Windowサイズの微調整*/
BOOL MyAdjustWindow(HWND hwnd, int bmpw, int bmph) {
	RECT rc;
	int x, y, w, h;

	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);

	rc.left = 0;
	rc.right = bmpw;
	rc.top = 0;
	rc.bottom = bmph;
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	winx = rc.right - rc.left;
	winy = rc.bottom - rc.top;
	x = (w - winx) / 2;
	y = (h - winy) / 2;
	MoveWindow(hwnd, x, y, winx, winy, FALSE);

	return TRUE;
}

/*HDC取得*/
HDC GetHdc() {
	return mHdc;
}

/*プレーヤー情報取得*/
PLAYERINFO *GetPlayerInfo() {
	return p_inf;
}

/*BMPの縦横サイズを取得*/
void SetWH(int w, int h) {
	bg_w = w;
	bg_h = h;
	return;
}

/*シーン切り替え*/
void ChengeSceen(int s, bool first) {
	sc = s;
	if(first) SceenInit(sc);
	return;
}

/*間隔を開ける為のフラグ設定*/
void SetRag(bool tf) {
	ragFlg = tf;
	return;
}

/*効果音フラグの設定*/
void SetSound(SOUNDEFFECT se){
	sndeft = se;
	return;
}

/*ゲームクリアフラグの設定*/
void SetClearFlg(bool cl) {
	clFlg = cl;
	return;
}

/*ゲームクリアフラグの取得*/
bool GetClearFlg() {
	return clFlg;
}