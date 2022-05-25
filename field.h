#pragma once

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void FieldInit();				//フィールド初期化
void FieldDraw();				//フィールド描画
int GetMapData(int, int);		//マップ情報取得
void FieldDelete();				//フィールドデストラクタ