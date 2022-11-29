//========================================
//
//2Dシューティングゲーム(カメラ取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _CAMERA_H_							//このマクロ定義がされていなかったら
#define _CAMERA_H_							//2重インクルード防止のマクロを定義する

#include "main.h"

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;						//視点
	D3DXVECTOR3 posR;						//注視点
	D3DXVECTOR3 vecU;						//上方向ベクトル
	D3DXMATRIX mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX mtxView;						//ビューマトリックス
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 posVDest;					//目的の視点
	D3DXVECTOR3 posRDest;					//目的の注視点

}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);
void Move(void);			//目的の注視点を設定(移動)
void Rot(void);				//目的の注視点を設定(回転) 

#endif
