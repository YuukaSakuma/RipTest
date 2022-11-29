//========================================
//
//2Dアクションゲーム(モデル処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "model.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"meshwall.h"

//マクロ定義
#define NUM_MODEL	(10)							//モデルの数
#define POSX		(0.0f)							//位置X
#define POSY		(20.0f)							//位置Y
#define POSZ		(0.0f)							//位置Z
#define ROTX		(0.0f)							//向きX
#define ROTY		(0.0f)							//向きY
#define ROTZ		(0.0f)							//向きZ
#define SET_SHADOW	(-1)							//影の設定




//プロトタイプ宣言
void CollisionModel(Model *pModel);
void ModelMove(void);				//モデルの動き
void PressBullet(void);				//弾を発射させる

//グローバル変数宣言
Model g_Model[2];
MODEL g_MODEL[NUM_MODEL];

//========================================
//モデルの初期化処理
//========================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ
	int nCntModel;

	//各種変数の初期化
	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		g_Model[nCntModel].pos = D3DXVECTOR3(POSX, POSY, POSZ);		//位置の初期化
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量を初期化
		g_Model[nCntModel].rot = D3DXVECTOR3(ROTX, ROTY, ROTZ);		//向きの初期化
		g_Model[nCntModel].nldxShadow = SET_SHADOW;					//影の設置
		g_Model[nCntModel].nType = 1;
		g_Model[nCntModel].bUse = true;	//使用しているかどう

	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\flower000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MODEL[0].pBuffMat,
		NULL,
		&g_MODEL[0].dwNumMat,
		&g_MODEL[0].pMesh);

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_MODEL[0].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_MODEL[0].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_MODEL[0].apTexture[nCntMat]);
		}
	}


	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\flower000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MODEL[1].pBuffMat,
		NULL,
		&g_MODEL[1].dwNumMat,
		&g_MODEL[1].pMesh);

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_MODEL[1].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_MODEL[1].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_MODEL[1].apTexture[nCntMat]);
		}
	}


	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		//影の設定処理
		g_Model[nCntModel].nldxShadow = SetShadow();
	}
} 

//========================================
//モデルの終了処理
//========================================
void UninitModel(void)
{
	//メッシュの破棄
	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{

		if (g_MODEL[nCntModel].pMesh != NULL)
		{
			g_MODEL[nCntModel].pMesh->Release();
			g_MODEL[nCntModel].pMesh = NULL;
		}


		//マテリアルの破棄
		if (g_MODEL[nCntModel].pBuffMat != NULL)
		{
			g_MODEL[nCntModel].pBuffMat->Release();
			g_MODEL[nCntModel].pBuffMat = NULL;
		}


		//テクスチャの破棄
		for (int nCntMat = 0; nCntMat < (int)g_MODEL[nCntModel].dwNumMat; nCntMat++)
		{
			if (g_MODEL[nCntModel].apTexture[nCntMat] != NULL)
			{
				g_MODEL[nCntModel].apTexture[nCntMat]->Release();
				g_MODEL[nCntModel].apTexture[nCntMat] = NULL;
			}
		}
	}
	
}

//========================================
//モデルの更新処理
//========================================
void UpdateModel(void)
{
	////モデルの動き
	//ModelMove();

	////弾を発射させる
	//PressBullet();

	////影の位置設定処理
	//SetPositionShadow(g_Model.nldxShadow, g_Model.pos);
}

//========================================
//モデルの描画処理
//========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	D3DMATERIAL9 matDef;								//現在のマテリアル保存用
	D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ

	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model[nCntModel].g_mtxWorldModel);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_Model[nCntModel].g_mtxWorldModel, &g_Model[nCntModel].g_mtxWorldModel, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].pos.x, g_Model[nCntModel].pos.y, g_Model[nCntModel].pos.z);

			D3DXMatrixMultiply(&g_Model[nCntModel].g_mtxWorldModel, &g_Model[nCntModel].g_mtxWorldModel, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].g_mtxWorldModel);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_MODEL[g_Model[nCntModel].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_MODEL[g_Model[nCntModel].nType].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);



				//テクスチャの設定
				pDevice->SetTexture(0, g_MODEL[g_Model[nCntModel].nType].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_MODEL[g_Model[nCntModel].nType].pMesh->DrawSubset(nCntMat);
			}
			

			//保存していたマテリアルを戻す 
			pDevice->SetMaterial(&matDef);
		}
	}
}

//========================================
//弾の設定処理
//========================================
void SetModel(D3DXVECTOR3 pos, int nType)
{
	int nCntModel;

	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == false)
		{//弾が使用されてない
			g_Model[nCntModel].pos = pos;
			g_Model[nCntModel].nType = nType;
			g_Model[nCntModel].bUse = true;						//使用している状態にする

			break;
		}
	
	}
}


//========================================
//モデルの取得
//========================================
Model *GetModel(void)
{
	return &g_Model[0];
}

//========================================
//モデルの動き
//========================================
void ModelMove(void)
{
	//Camera *pCamera = GetCamera();
	//float fRotMove = g_Model.rot.y;
	//float fRotDest = g_Model.rot.y;
	//float fRotDiff;

	////キーが押されたとき
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{//Aキーが押された
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//左上移動
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + D3DX_PI * 0.25f;

	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//左下移動
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.25f;
	//	}
	//	else
	//	{//左移動
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.0f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	//{//Dキーが押された

	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//
	//		g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + D3DX_PI * 0.75f;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//
	//		g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.75f;
	//	}
	//	else
	//	{//
	//		g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 1.0f;

	//	}
	//}
	//else if (GetKeyboardPress(DIK_UP) == true)
	//{//Wキーが押された
	//	g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;
	//	g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;

	//	fRotDest = -pCamera->rot.y + D3DX_PI * 0.5f;
	//}
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	//{//Sキーが押された
	//	g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;
	//	g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;

	//	fRotDest = -pCamera->rot.y + -D3DX_PI * 0.5f;

	//}

	////目的の移動方向までの差分
	//fRotDiff = fRotDest - fRotMove;

	//CollisionModel(&g_Model);

	////
	//g_Model.pos.x += g_Model.move.x;
	//g_Model.pos.z += g_Model.move.z;


	////移動量を更新
	//g_Model.move.x += (0.0f - g_Model.move.x) * 0.1f;
	//g_Model.move.z += (0.0f - g_Model.move.z) * 0.1f;

	//

	//if (g_Model.move.x <= 0.0f && g_Model.move.x >= -0.1f || g_Model.move.x >= 0.0f && g_Model.move.x <= 0.1f)
	//{
	//	if (g_Model.move.z <= 0.0f && g_Model.move.z >= -0.1f || g_Model.move.z >= 0.0f && g_Model.move.z <= 0.1f)
	//	{
	//		Rot();
	//	}
	//}

	////一周したときに戻す処理
	//if (fRotDiff > D3DX_PI)
	//{
	//	fRotDiff += -D3DX_PI * 2;
	//}
	//else if (fRotDiff < -D3DX_PI)
	//{
	//	fRotDiff += D3DX_PI * 2;
	//}

	//g_Model.rot.y += fRotDiff * 0.2f;


	//if (g_Model.rot.y > D3DX_PI)
	//{
	//	g_Model.rot.y += -D3DX_PI * 2;
	//}
	//else if (g_Model.rot.y < -D3DX_PI)
	//{
	//	g_Model.rot.y += D3DX_PI * 2;
	//}
}

//========================================
//弾を発射させる
//========================================
void PressBullet(void)
{
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	//弾の設定
	//	if (g_Model.bUse == true)
	//	{
	//		SetBullet(g_Model.pos, D3DXVECTOR3(sinf(g_Model.rot.y) * -1.0f, 0.0f, cosf(g_Model.rot.y)  * -1.0f), g_Model.rot, 2000);
	//	}
	//}
}

//========================================
//プレイヤーと壁の当たり判定(アローに直す! ポインタ)
//========================================
void CollisionModel(Model *pModel)
{

	//if (pModel->pos.x > 2000.0f + 10.0f)
	//{
	//	pModel->pos.x = 2000.0f + 10.0f;
	//	 

	//	pModel->move.x = 0.0f;
	//	pModel->move.z = 0.0f;
	//}
	//else if (pModel->pos.x < -2000.0f + 10.0f)
	//{
	//	pModel->pos.x = -2000.0f + 10.0f;
	//	
	//	pModel->move.x = 0.0f;
	//	pModel->move.z = 0.0f;
	//}

	//if (pModel->pos.z > 2000.0f + 10.0f)
	//{
	//	
	//	pModel->pos.z = 2000.0f + 10.0f;

	//	pModel->move.x = 0.0f;
	//	pModel->move.z = 0.0f;
	//}
	//else if (pModel->pos.z < -2000.0f + 10.0f)
	//{
	//	
	//	pModel->pos.z = -2000.0f + 10.0f;

	//	pModel->move.x = 0.0f;
	//	pModel->move.z = 0.0f;
	//}

	//////外積の判定
	////D3DXVECTOR3 vecLine1 = D3DXVECTOR3(200.0f, 0.0f, 200.0f) - D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	////D3DXVECTOR3 vecLine2 = D3DXVECTOR3(200.0f, 0.0f, -200.0f) - D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	////D3DXVECTOR3 vecLine3 = D3DXVECTOR3(200.0f, 0.0f, 200.0f) - D3DXVECTOR3(200.0f, 0.0f, -200.0f);
	////D3DXVECTOR3 vecLine4 = D3DXVECTOR3(-200.0f, 0.0f, 200.0f) - D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	////D3DXVECTOR3 vecToPos1 = pModel->pos - D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	////D3DXVECTOR3 vecToPos2 = pModel->pos - D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	////D3DXVECTOR3 vecToPos3 = pModel->pos - D3DXVECTOR3(200.0f, 0.0f, -200.0f);
	////D3DXVECTOR3 vecToPos4 = pModel->pos - D3DXVECTOR3(-200.0f, 0.0f, -200.0f);

	////if (pModel->bUse == true)
	////{
	////	if ((vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) <= 0.0f)
	////	{
	////		pModel->move.x = 0.0f;
	////		pModel->move.z = 0.0f;
	////	}
	////	if ((vecLine2.z * vecToPos2.x) - (vecLine2.x * vecToPos2.z) >= 0.0f)
	////	{
	////		pModel->move.x = 0.0f;
	////		pModel->move.z = 0.0f;
	////	}

	////	if ((vecLine3.z * vecToPos3.x) - (vecLine3.x * vecToPos3.z) >= 0.0f)
	////	{
	////		pModel->move.x = 0.0f;
	////		pModel->move.z = 0.0f;
	////	}
	////	if ((vecLine4.z * vecToPos4.x) - (vecLine4.x * vecToPos4.z) <= 0.0f)
	////	{
	////		pModel->move.x = 0.0f;
	////		pModel->move.z = 0.0f;
	////	}
	////}
}
