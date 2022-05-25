#pragma once

#include "field.h"

void PlayerInit();				//プレーヤー初期化
void PlayerDraw(HDC, int);		//プレーヤー描画
void PlayerDelete();			//プレーヤーデストラクタ
void PlayerMove(WPARAM);		//プレーヤー移動