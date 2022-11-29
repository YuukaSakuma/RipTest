//========================================
//
//2Dシューティングゲーム(弾の処理)[bullet.h]
//Author:佐久間優香
//
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"



//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER = 0,					//プレイヤーの弾
	BULLETTYPE_ENEMY,						//敵の弾
	BULLETTYPE_MAX							
}BULLETTYPE;

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 posOld;									//位置
	D3DXVECTOR3 move;									//移動量
	D3DXVECTOR3 rot;									//移動量
	int nLife;											//寿命
	int nShadow;
	BULLETTYPE nType;									//弾の種類
	bool bUse;											//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 rot,int nLife);
Bullet *GetBullet(void);

#endif
