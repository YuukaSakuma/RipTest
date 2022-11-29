//========================================
//
//2Dシューティングゲーム(弾の処理)[bullet.cpp]
//Author:佐久間優香
//
//========================================
#include"bullet.h"
#include"shadow.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"

//マクロ定義
#define MAX_BULLET			(128)
#define NUM_BULLET			(2)
#define NUM_BULLET_LIFE		(2000)
#define COL_R	 (1.0f)									//赤
#define COL_G	 (1.0f)									//緑
#define COL_B	 (1.0f)									//青
#define COL_A	 (1.0f)									//透明度

//プロトタイプ宣言
void CollisionWall(Bullet *pBullet);					//敵と弾の当たり判定
void CollisionPlayer(Bullet *pBullet);					//プレイヤーと弾の当たり判定

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファのポインタ
D3DXMATRIX g_mtxWorldBullet[MAX_BULLET];				//ワールドマトリックス
Bullet g_aBullet[MAX_BULLET];							//弾の情報

//========================================
//弾の初期化処理
//========================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;									//頂点情報へのポインタ
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nShadow = -1;
		g_aBullet[nCntBullet].nLife = NUM_BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;				//使用していない状態にする

	}

	//頂点バッファの生成
 	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;										//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();	
}

//========================================
//弾の終了処理
//========================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//========================================
//弾の更新処理
//========================================
void  UpdateBullet(void)
{
	
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている

			//位置を更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//影の場所
			SetPositionShadow(g_aBullet[nCntBullet].nShadow, g_aBullet[nCntBullet].pos);

			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 30);

			CollisionWall(&g_aBullet[nCntBullet]);
			//寿命のカウントダウン
			g_aBullet[nCntBullet].nLife--;

			//寿命が尽きた
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
				g_aBullet[nCntBullet].bUse = false;				//使用していない状態にする
				NoShadow(g_aBullet[nCntBullet].nShadow);
			}
		}

	}


}

//========================================
//弾の描画処理
//========================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxTrans;								//計算用マトリックス
	D3DXMATRIX mtxView;									//ビューマトリックスの取得用
	int nCntBullet;

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
 	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet[nCntBullet]);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldBullet[nCntBullet], NULL, &mtxView);	//逆行列を求める
			g_mtxWorldBullet[nCntBullet]._41 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._42 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldBullet[nCntBullet], &g_mtxWorldBullet[nCntBullet], &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet[nCntBullet]);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	
}

//========================================
//弾の設定処理
//========================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife)
{
	int nCntBullet;
	VERTEX_3D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されてない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].nShadow = SetShadow();
			g_aBullet[nCntBullet].bUse = true;						//使用している状態にする

			break;
		}
		pVtx += 4;												//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//========================================
//敵と弾の当たり判定(アローに直す! ポインタ)
//========================================
void CollisionWall(Bullet *pBullet)
{	
	D3DXVECTOR3 vecLine1 = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	D3DXVECTOR3 vecLine2 = D3DXVECTOR3(2000.0f, 0.0f, -2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecLine3 = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecLine4 = D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);

	D3DXVECTOR3 vecToPos1 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	D3DXVECTOR3 vecToPos2 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecToPos3 = pBullet->pos - D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecToPos4 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);

	//if (pBullet->pos.x > 200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}
	//else if(pBullet->pos.x < -200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}

	//if (pBullet->pos.z > 200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}
	//else if (pBullet->pos.z < -200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}

	//外積の当たり判定
	if ( (vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) <= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine2.z * vecToPos2.x) - (vecLine2.x * vecToPos2.z) >= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine3.z * vecToPos3.x) - (vecLine3.x * vecToPos3.z) >= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine4.z * vecToPos4.x) - (vecLine4.x * vecToPos4.z) <= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}


}

//========================================
//プレイヤーと弾の当たり判定(アローに直す! ポインタ)
//========================================
void CollisionPlayer(Bullet *pBullet)
{
	
}

//========================================
//弾の取得
//========================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}


