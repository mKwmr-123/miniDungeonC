#pragma once
#include <Windows.h>
#include "main.h"

void BattleInit();							//�o�g��������
void BattleStart();							//�o�g���J�n
void BattleDelete();						//�o�g���f�X�g���N�^
void BattleCommand(WPARAM);					//�o�g���L�[���͎�t

typedef struct { int hp, pw; } ENEMYINFO;	//�G�̏��