//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _WALL_H_							//このマクロ定義がされていなかったら
#define _WALL_H_							//2重インクルード防止のマクロを定義する

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//移動量
	D3DXMATRIX mtxWorldwall;
	bool bUse;
}Wall;


//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
Wall *GetWall(void);

#endif