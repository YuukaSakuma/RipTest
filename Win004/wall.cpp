//========================================
//
//2Dアクションゲーム(カメラ処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "wall.h"

#define MAX_WALL	(128)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturewall = NULL;			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;		//頂点バッファへのポインタ
Wall g_Wall[MAX_WALL];

//========================================
//ポリゴンの初期化処理
//========================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	int nCntWall;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_apTexturewall);

	for (nCntWall = 0; nCntWall < 128; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].bUse = false;
	}
	

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffwall,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-200.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffwall->Unlock();
}

//========================================
//ポリゴンの終了処理
//========================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_apTexturewall != NULL)
	{
		g_apTexturewall->Release();
		g_apTexturewall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffwall != NULL)
	{
		g_pVtxBuffwall->Release();
		g_pVtxBuffwall = NULL;
	}
}

//========================================
//ポリゴンの更新処理
//========================================
void UpdateWall(void)
{
	
}

//========================================
//ポリゴンの描画処理
//========================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorldwall);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldwall, &g_Wall[nCntWall].mtxWorldwall, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldwall, &g_Wall[nCntWall].mtxWorldwall, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorldwall);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTexturewall);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);

		
		}
	}
}

//========================================
//壁の設定処理
//========================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	VERTEX_3D *pVtx;											//頂点情報へのポインタ

																//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < 128; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{

			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;

			g_Wall[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;												//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffwall->Unlock();
}

//========================================
//敵の取得
//========================================
Wall *GetWall(void)
{
	return &g_Wall[0];
}


