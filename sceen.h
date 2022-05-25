#ifndef _SCEENS_DEF_
#define _SCEENS_DEF_
#include "field.h"
#include "player.h"
#include "start.h"
#include "battle.h"
#include "end.h"
#endif // _SCEENS_DEF_

void SceenInit(int);				//各シーンの初期化
void SceenDraw(int);				//各シーンの描画
void SceenDelete();					//各シーンのデストラクタ
void SceenKeyCheck(WPARAM, int);	//各シーンのキー入力受付