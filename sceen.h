#ifndef _SCEENS_DEF_
#define _SCEENS_DEF_
#include "field.h"
#include "player.h"
#include "start.h"
#include "battle.h"
#include "end.h"
#endif // _SCEENS_DEF_

void SceenInit(int);				//�e�V�[���̏�����
void SceenDraw(int);				//�e�V�[���̕`��
void SceenDelete();					//�e�V�[���̃f�X�g���N�^
void SceenKeyCheck(WPARAM, int);	//�e�V�[���̃L�[���͎�t