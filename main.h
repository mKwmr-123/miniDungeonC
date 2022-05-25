#pragma once

#include <Windows.h>
#include "field.h"
#include "player.h"
#include "sceen.h"

const int PX = 256;			//�v���[���[�\���ʒu(X���W)
const int PY = 192;			//�v���[���[�\���ʒu(Y���W)

/*�v���[���[���*/
typedef struct { int x,		//X���W
                     y,		//Y���W
	                 t,		//�A�j���[�V�����g�O��
	                 e,		//�G���J�E���g�l
	                 hp,	//�̗�
	                 mp,	//����
	                 maxhp, //�ő�̗�
	                 maxmp, //�ő喂��
	                 pw,	//�U����
	                 cure,	//���@����
	                 lv,	//���x��
	                 exp;	//�o���l
} PLAYERINFO;

/*���ʉ�*/
enum class SOUNDEFFECT {
	NONE,
	SPRING,
	ATTACK,
	DAMAGE,
	LEVELUP,
	ESCAPE,
	CURE,
	GAMEOVER,
	GAMECLEAR
};

HDC GetHdc();					//HDC�擾����
PLAYERINFO *GetPlayerInfo();	//�v���[���[���擾����
void SetWH(int, int);			//Window��BMP�̒����p��BMP�̏c���̃T�C�Y��ݒ肷��
void ChengeSceen(int, bool);	//�V�[���؂�ւ�
void SetRag(bool);				//�Ԋu���J����ׂ̃t���O�ݒ�
void SetSound(SOUNDEFFECT);		//���ʉ��̐ݒ�
void SetClearFlg(bool);			//�Q�[���N���A�t���O�̐ݒ�
bool GetClearFlg();				//�Q�[���N���A�t���O�̎擾