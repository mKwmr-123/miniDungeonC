#pragma once
#include <Windows.h>
#include "main.h"

void BattleInit();							//バトル初期化
void BattleStart();							//バトル開始
void BattleDelete();						//バトルデストラクタ
void BattleCommand(WPARAM);					//バトルキー入力受付

typedef struct { int hp, pw; } ENEMYINFO;	//敵の情報