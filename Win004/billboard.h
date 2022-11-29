//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _BILLBOARD_H_							//このマクロ定義がされていなかったら
#define _BILLBOARD_H_							//2重インクルード防止のマクロを定義する

//プロトタイプ宣言
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos);

#endif