//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _MODEL_H_							//このマクロ定義がされていなかったら
#define _MODEL_H_							//2重インクルード防止のマクロを定義するv

#include"main.h"

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;									//移動量
	D3DXMATRIX g_mtxWorldModel;							//ワールドマトリックス
	int nldxShadow;
	int nType;
	bool bUse;											//使用しているかどうか
}Model;

//弾構造体の定義
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[10];		//テクスチャへのポインタ
	LPD3DXMESH pMesh;						//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
	DWORD dwNumMat;							//マテリアルの数				//使用しているかどうか
}MODEL;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);

#endif