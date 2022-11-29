//========================================
//
//2Dアクションゲーム(カメラ処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "meshwall.h"
#include"model.h"

void CollisionMeshWall(MeshWall *pMeshWall);

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshWall = NULL;		//インデックスバッファへのポインタ

MeshWall g_MeshWall[128];

//========================================
//ポリゴンの初期化処理
//========================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	int nCntMeshWall;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_apTextureMeshWall);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		g_MeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntMeshWall].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * nCntMeshWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-2000.0f, 2000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 2000.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(2000.0f, 2000.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-2000.0f, -2000.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, -2000.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(2000.0f, -2000.0f, 0.0f);

		//法線
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;												//頂点データのポインタを4つ分進める

	}
	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshWall,
		NULL);

	WORD *pIdx;			//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号データをへのポインタを取得
	g_pIndxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//頂点番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロックする
	g_pIndxBuffMeshWall->Unlock();

}

//========================================
//ポリゴンの終了処理
//========================================
void UninitMeshWall(void)
{
	//テクスチャの破棄
	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIndxBuffMeshWall != NULL)
	{
		g_pIndxBuffMeshWall->Release();
		g_pIndxBuffMeshWall = NULL;
	}
}

//========================================
//ポリゴンの更新処理
//========================================
void UpdateMeshWall(void)
{
	
}

//========================================
//ポリゴンの描画処理
//========================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス

	int nCntMeshWall;


	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == true)
		{

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshWall[nCntMeshWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntMeshWall].rot.y, g_MeshWall[nCntMeshWall].rot.x, g_MeshWall[nCntMeshWall].rot.z);

			D3DXMatrixMultiply(&g_MeshWall[nCntMeshWall].mtxWorld, &g_MeshWall[nCntMeshWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntMeshWall].pos.x, g_MeshWall[nCntMeshWall].pos.y, g_MeshWall[nCntMeshWall].pos.z);

			D3DXMatrixMultiply(&g_MeshWall[nCntMeshWall].mtxWorld, &g_MeshWall[nCntMeshWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntMeshWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//インデックスぶっふぁをデータストリームに設定
			pDevice->SetIndices(g_pIndxBuffMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureMeshWall);
			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				9,					//用意した頂点の数
				0,
				12);				//描画するプリミティブの数
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//========================================
//壁の設定処理
//========================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntMeshWall;
	
	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == false)
		{
			g_MeshWall[nCntMeshWall].pos = pos;
			g_MeshWall[nCntMeshWall].rot = rot;

			g_MeshWall[nCntMeshWall].bUse = true;
			break;
		}
	}
	
}

//========================================
//敵と弾の当たり判定(アローに直す! ポインタ)
//========================================
void CollisionMeshWall(MeshWall *pMeshWall)
{
	/*Model *pModel = GetModel();

	if (pMeshWall->pos.x > 200.0f)
	{
		pModel->move.x = 0.0f;
		pModel->move.z = 0.0f;
	}
	else if (pMeshWall->pos.x < -200.0f)
	{
		pModel->move.x = 0.0f;
		pModel->move.z = 0.0f;
	}

	if (pMeshWall->pos.z > 200.0f)
	{
		pModel->move.x = 0.0f;
		pModel->move.z = 0.0f;
	}
	else if (pMeshWall->pos.z < -200.0f)
	{
		pModel->move.x = 0.0f;
		pModel->move.z = 0.0f;
	}*/
}

//========================================
//弾の取得
//========================================
MeshWall *GetMeshWall(void)
{
	return &g_MeshWall[0];
}

