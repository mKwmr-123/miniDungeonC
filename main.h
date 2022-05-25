#pragma once

#include <Windows.h>
#include "field.h"
#include "player.h"
#include "sceen.h"

const int PX = 256;			//プレーヤー表示位置(X座標)
const int PY = 192;			//プレーヤー表示位置(Y座標)

/*プレーヤー情報*/
typedef struct { int x,		//X座標
                     y,		//Y座標
	                 t,		//アニメーショントグル
	                 e,		//エンカウント値
	                 hp,	//体力
	                 mp,	//魔力
	                 maxhp, //最大体力
	                 maxmp, //最大魔力
	                 pw,	//攻撃力
	                 cure,	//魔法効果
	                 lv,	//レベル
	                 exp;	//経験値
} PLAYERINFO;

/*効果音*/
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

HDC GetHdc();					//HDC取得処理
PLAYERINFO *GetPlayerInfo();	//プレーヤー情報取得処理
void SetWH(int, int);			//WindowとBMPの調整用にBMPの縦横のサイズを設定する
void ChengeSceen(int, bool);	//シーン切り替え
void SetRag(bool);				//間隔を開ける為のフラグ設定
void SetSound(SOUNDEFFECT);		//効果音の設定
void SetClearFlg(bool);			//ゲームクリアフラグの設定
bool GetClearFlg();				//ゲームクリアフラグの取得