//========================================
//
//2Dシューティングゲーム(メッシュフィールド処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _MESHFIELD_H_							//このマクロ定義がされていなかったら
#define _MESHFIELD_H_							//2重インクルード防止のマクロを定義する

//プロトタイプ宣言
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif