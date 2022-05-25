/* �E�B���h�E���� */
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

//���C���֐�
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

//�E�B���h�E�N���X�̓o�^
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

//�E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hCurInst, int nCmdShow)
{
	hWnd = CreateWindowEx(WS_EX_COMPOSITED, lpszClassName, TEXT("�~�j���񂶂��Q"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 640, 512, NULL, NULL, hCurInst, NULL);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	MINMAXINFO* lpminmax;

	switch (msg)
	{
	case WM_CREATE:
		//�����ݒ�
		sc = 0;
		SceenInit(sc);
		
		cnt = 0;
		//�v���[���[���
		inf = { 4		//�}�b�vX���W
			  , 2		//�}�b�vY���W
			  , 0		//�A�j���[�V�����g�O��
			  , -1		//�G�Ƃ̃G���J�E���g��
			  , 15		//�̗�
			  , 2		//����
			  , 15		//�ő�̗�
			  , 2		//�ő喂��
			  , 3		//�U����
			  , 10		//���@����
			  , 1		//���x��
			  , 0};		//�o���l
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
		//�E�B���h�E����
		lpminmax = (LPMINMAXINFO)lp;
		lpminmax->ptMaxTrackSize.x = winx;
		lpminmax->ptMaxTrackSize.y = winy;
		lpminmax->ptMinTrackSize.x = winx;
		lpminmax->ptMinTrackSize.y = winy;
		break;

	case WM_PAINT:
		//�`��
		GetClientRect(hWnd, &rc);

		mHdc = BeginPaint(hWnd, &ps);
		{
			SceenDraw(sc);
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		//�L�[���͎�t
		if (keyFlg) {
			SceenKeyCheck(wp, sc);
			InvalidateRect(hWnd, NULL, TRUE);
			keyFlg = false;
		}
		
		break;

	case WM_TIMER:
		//�^�C�}�[
		if (wp != ID_MYTIMER) return DefWindowProc(hWnd, msg, 0, 0);

		switch (sc)
		{
		case 0:
			//�X�^�[�g���
			keyFlg = true;
			break;

		case 1:
			//�t�B�[���h���
			if (inf.e == 100 || ++cnt > 4) {
				//�A�j���[�V�����p�J�E���^
				cnt = 0;
				if (inf.t) inf.t = 0;
				else inf.t = 1;

				keyFlg = true;
				InvalidateRect(hWnd, NULL, TRUE);

				//�G�̏o������
				if (inf.e > 85) ChengeSceen(2,true);
			}

			if (sndeft == SOUNDEFFECT::SPRING) {
				pszSound = TEXT("resource\\spring.wav");
			}

			break;
		case 2:
			//�o�g�����
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
			//�Q�[���I�����
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
			//���ʉ�
			PlaySound(pszSound, NULL, SND_ASYNC | SND_FILENAME);
			sndeft = SOUNDEFFECT::NONE;
		}

		break;

	case WM_CLOSE:
		//��ʂ�����ꂽ�ꍇ�̏���
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		//�j������
		KillTimer(hWnd, ID_MYTIMER);

		SceenDelete();

		PostQuitMessage(0);

		break;

	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}

	return 0;
}

/*Window�T�C�Y�̔�����*/
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

/*HDC�擾*/
HDC GetHdc() {
	return mHdc;
}

/*�v���[���[���擾*/
PLAYERINFO *GetPlayerInfo() {
	return p_inf;
}

/*BMP�̏c���T�C�Y���擾*/
void SetWH(int w, int h) {
	bg_w = w;
	bg_h = h;
	return;
}

/*�V�[���؂�ւ�*/
void ChengeSceen(int s, bool first) {
	sc = s;
	if(first) SceenInit(sc);
	return;
}

/*�Ԋu���J����ׂ̃t���O�ݒ�*/
void SetRag(bool tf) {
	ragFlg = tf;
	return;
}

/*���ʉ��t���O�̐ݒ�*/
void SetSound(SOUNDEFFECT se){
	sndeft = se;
	return;
}

/*�Q�[���N���A�t���O�̐ݒ�*/
void SetClearFlg(bool cl) {
	clFlg = cl;
	return;
}

/*�Q�[���N���A�t���O�̎擾*/
bool GetClearFlg() {
	return clFlg;
}