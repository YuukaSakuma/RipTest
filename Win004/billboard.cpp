//========================================
//
//2Dアクションゲーム(ビルボード処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "billboard.h"

#define MAX_BILLBOARD	(1)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBillboard = NULL;			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posBillboard[MAX_BILLBOARD];								//位置
D3DXMATRIX g_mtxWorldBillboard[MAX_BILLBOARD];							//ワールドマトリックス

//========================================
//ビルボードの初期化処理
//========================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	VERTEX_3D *pVtx;
	int nCntBillboard;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_apTextureBillboard);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_posBillboard[nCntBillboard] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
		g_pVtxBuffBillboard->Unlock();
}

//========================================
//ビルボードの終了処理
//========================================
void UninitBillboard(void)
{
	//テクスチャの破棄
	if (g_apTextureBillboard != NULL)
	{
		g_apTextureBillboard->Release();
		g_apTextureBillboard = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//========================================
//ビルボードの更新処理
//========================================
void UpdateBillboard(void)
{
	
}

//========================================
//ビルボードの描画処理
//========================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxTrans;								//計算用マトリックス
	D3DXMATRIX mtxView;									//ビューマトリックスの取得用

	

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldBillboard[nCntBillboard]);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_mtxWorldBillboard[nCntBillboard], NULL, &mtxView);	//逆行列を求める
		g_mtxWorldBillboard[nCntBillboard]._41 = 0.0f;
		g_mtxWorldBillboard[nCntBillboard]._42 = 0.0f;
		g_mtxWorldBillboard[nCntBillboard]._43 = 0.0f;
		
		
		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_posBillboard[nCntBillboard].x, g_posBillboard[nCntBillboard].y, g_posBillboard[nCntBillboard].z);

		D3DXMatrixMultiply(&g_mtxWorldBillboard[nCntBillboard], &g_mtxWorldBillboard[nCntBillboard], &mtxTrans);

		////Zテストを無効にする
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//アルファテストを有効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard[nCntBillboard]);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBillboard);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);

		//アルファテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		////Zテストを有効にする
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

}

//========================================
//ビルボードの設定処理
//========================================
void SetBillboard(D3DXVECTOR3 pos)
{

}

