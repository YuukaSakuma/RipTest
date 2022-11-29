//========================================
//
//2Dシューティングゲーム(パーティクル処理)[particle.h]
//Author:佐久間優香
//
//========================================
#ifndef _PARTICLE_H_							//このマクロ定義がされていなかったら
#define _PARTICLE_H_							//2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType,int nLife);

#include "main.h"

#endif