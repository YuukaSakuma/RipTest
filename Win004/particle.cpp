//========================================
//
//2Dシューティングゲーム(パーティクル処理)[particle.cpp]
//Author:佐久間優香
//
//========================================
#include"particle.h"
#include"effect.h"
#include"model.h"

//マクロ定義
#define MAX_PARTICLE			(128)

//パーティクル構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置(開始時間)
	D3DXVECTOR3 move;
	D3DXCOLOR col;										//色
	int nLife;											//寿命(発生時間)
	int nType;											//種類
	bool bUse;											//使用しているかどうか
}Explosion;

//グローバル変数
Explosion g_aParticle[MAX_PARTICLE];						//爆発の情報

//========================================
//パーティクルの初期化処理
//========================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//パーティクルの情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].bUse = false;			//使用していない状態にする
	}
}

//========================================
//パーティクルの終了処理
//========================================
void UninitParticle(void)
{
	
}

//========================================
//パーティクルの更新処理
//========================================
void  UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos, move;
	D3DXCOLOR col;
	int nLife;
	float fRadius,  fMove;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//パーティクルが使用されている

			//パーティクルの生成
			for (nCntAppear = 0; nCntAppear < 10; nCntAppear++)
			{
				if (g_aParticle[nCntAppear].nType == 0)
				{
					//位置の設定
					pos = g_aParticle[nCntParticle].pos;

				

					//移動量を求める
					fMove = (float)((rand() % 20) / 10 + 0.2);

					//移動量の設定
					move.x = sinf((float)((rand() % 629 - 314) / 100.0f)) * fMove;
					move.y = cosf((float)((rand() % 629 - 314) / 100.0f)) * fMove;
					move.z = cosf((float)((rand() % 629 - 314) / 100.0f)) * fMove;

					//色の設定
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					//半径の設定
					fRadius = 5.0f;

					//寿命の設定
					nLife = 50;
				}

				//エフェクトの設定
				Model *pModel = GetModel();
				SetEffect(g_aParticle[nCntParticle].pos, move, col, fRadius, nLife);
			}

			//寿命のカウント
			g_aParticle[nCntParticle].nLife--;

			//寿命が尽きた
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//========================================
//パーティクルの描画処理
//========================================
void DrawParticle(void)
{

}

//========================================
//パーティクルの設定処理
//========================================
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//弾が使用されてない
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].bUse = true;				//使用している状態にする
			g_aParticle[nCntParticle].nLife = nLife;

			break;
		}
	}

}