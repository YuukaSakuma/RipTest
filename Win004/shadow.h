//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _SHADOW_H_							//このマクロ定義がされていなかったら
#define _SHADOW_H_							//2重インクルード防止のマクロを定義する

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//移動量
	bool bUse;											//使用しているかどうか
}Shadow;


//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nldxShadow,D3DXVECTOR3 pos);
Shadow *GetShadow(void);
void NoShadow(int nldxShadow);

#endif