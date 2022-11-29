//========================================
//
//2Dアクションゲーム(影の処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "shadow.h"

#define MAX_SHADOW	(256)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureShadow = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファへのポインタ
Shadow g_Shadow[MAX_SHADOW];
D3DXMATRIX g_mtxWorldShadow[MAX_SHADOW];							//ワールドマトリック

//========================================
//影の初期化処理
//========================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	int nCntShadow;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_apTextureShadow);

	//変数の初期化
	for (nCntShadow = 0;nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx; 

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;												//頂点データのポインタを4つ分進める

	}
	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//========================================
//影の終了処理
//========================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_apTextureShadow != NULL)
	{
		g_apTextureShadow->Release();
		g_apTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//========================================
//影の更新処理
//========================================
void UpdateShadow(void)
{
	
}

//========================================
//影の描画処理
//========================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	int nCntShadow;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldShadow[nCntShadow]);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow[nCntShadow], &g_mtxWorldShadow[nCntShadow], &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow[nCntShadow], &g_mtxWorldShadow[nCntShadow], &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow[nCntShadow]);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}
	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);

}

//========================================
//影の設定処理
//========================================
int SetShadow(void)
{
	int nCntShadow = -1;
	int nCount;

	for (nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (g_Shadow[nCount].bUse == false)
		{//弾が使用されてない
			nCntShadow = nCount;
			g_Shadow[nCount].bUse = true;

			break;
		}
	}
	return nCntShadow;
}

//========================================
//影の位置設定処理
//========================================
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos)
{
	g_Shadow[nldxShadow].pos.x = pos.x;
	g_Shadow[nldxShadow].pos.z = pos.z;
}

//========================================
//影の取得
//========================================
Shadow *GetShadow(void)
{
	return &g_Shadow[0];
}

//========================================
//影を消す
//========================================
void NoShadow(int nldxShadow)
{
	g_Shadow[nldxShadow].bUse = false;
}

