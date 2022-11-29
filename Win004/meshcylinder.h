//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _MESHCYLINDER_H_							//このマクロ定義がされていなかったら
#define _MESHCYLINDER_H_							//2重インクルード防止のマクロを定義する


//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//移動量
	D3DXMATRIX mtxWorld;								//ワールドマトリックス
}MeshCylinder;

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif