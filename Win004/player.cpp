//========================================
//
//2Dアクションゲーム(モデル処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "player.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"

//マクロ定義
#define NUM_PLAYER	(10)							//モデルの数
#define POSX		(0.0f)							//位置X
#define POSY		(20.0f)							//位置Y
#define POSZ		(0.0f)							//位置Z
#define ROTX		(0.0f)							//向きX
#define ROTY		(0.0f)							//向きY
#define ROTZ		(0.0f)							//向きZ
#define SET_SHADOW	(-1)							//影の設定

//プロトタイプ宣言
void CollisionPlayer(Player *pPlayer);
void PlayerMove(void);				//モデルの動き
void PressB(void);				//弾を発射させる


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTexturePlayer[NUM_PLAYER] = {};		//テクスチャへのポインタ
LPD3DXMESH g_pMeshPlayer = NULL;						//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;				//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;							//マテリアルの数
Player g_Player;

//========================================
//モデルの初期化処理
//========================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	//各種変数の初期化
	g_Player.pos = D3DXVECTOR3(POSX, POSY, POSZ);		//位置の初期化
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量を初期化
	g_Player.rot = D3DXVECTOR3(ROTX, ROTY, ROTZ);		//向きの初期化
	g_Player.nldxShadow = SET_SHADOW;					//影の設置
	g_Player.bUse = true;								//使用しているかどうか

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\airplane000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat  = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	//影の設定処理
	g_Player.nldxShadow = SetShadow();
} 

//========================================
//モデルの終了処理
//========================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//テクスチャの破棄
	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (g_apTexturePlayer[nCntMat] != NULL)
		{
			g_apTexturePlayer[nCntMat]->Release();
			g_apTexturePlayer[nCntMat] = NULL;
		}
	}
	
}

//========================================
//モデルの更新処理
//========================================
void UpdatePlayer(void)
{
	//モデルの動き
	PlayerMove();

	//弾を発射させる
	PressB();

	//影の位置設定処理
	SetPositionShadow(g_Player.nldxShadow, g_Player.pos);
}

//========================================
//モデルの描画処理
//========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス
	D3DMATERIAL9 matDef;								//現在のマテリアル保存用
	D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す 
	pDevice->SetMaterial(&matDef);
}

//========================================
//モデルの取得
//========================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//========================================
//モデルの動き
//========================================
void PlayerMove(void)
{
	Camera *pCamera = GetCamera();
	float fRotMove = g_Player.rot.y;
	float fRotDest = g_Player.rot.y;
	float fRotDiff;

	//キーが押されたとき
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{//左上移動
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;

			fRotDest = -pCamera->rot.y + D3DX_PI * 0.25f;

		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//左下移動
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 0.25f;
		}
		else
		{//左移動
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//Dキーが押された

		if (GetKeyboardPress(DIK_UP) == true)
		{//
			g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 0.5f;

			fRotDest = -pCamera->rot.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//
			g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 0.75f;
		}
		else
		{//
			g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 1.0f;

		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//Wキーが押された
		g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;
		g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;

		fRotDest = -pCamera->rot.y + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//Sキーが押された
		g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;
		g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;

		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.5f;

	}

	//目的の移動方向までの差分
	fRotDiff = fRotDest - fRotMove;

	CollisionPlayer(&g_Player);

	//
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.z += g_Player.move.z;

	//移動量を更新
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.1f;

	if (g_Player.move.x <= 0.0f && g_Player.move.x >= -0.1f || g_Player.move.x >= 0.0f && g_Player.move.x <= 0.1f)
	{
		if (g_Player.move.z <= 0.0f && g_Player.move.z >= -0.1f || g_Player.move.z >= 0.0f && g_Player.move.z <= 0.1f)
		{
			Rot();
		}
	}

	//一周したときに戻す処理
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += -D3DX_PI * 2;
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2;
	}

	g_Player.rot.y += fRotDiff * 0.2f;


	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y += -D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}
}

//========================================
//弾を発射させる
//========================================
void PressB(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		//弾の設定
		if (g_Player.bUse == true)
		{
			SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y) * -1.0f, 0.0f, cosf(g_Player.rot.y)  * -1.0f), g_Player.rot, 2000);
		}
	}
}

//========================================
//プレイヤーと壁の当たり判定(アローに直す! ポインタ)
//========================================
void CollisionPlayer(Player *pPlayer)
{

	if (pPlayer->pos.x > 2000.0f - 10.0f)
	{
		pPlayer->pos.x = 2000.0f - 10.0f;
		 

		pPlayer->move.x = 0.0f;
		pPlayer->move.z = 0.0f;
	}
	else if (pPlayer->pos.x < -2000.0f + 10.0f)
	{
		pPlayer->pos.x = -2000.0f + 10.0f;
		
		pPlayer->move.x = 0.0f;
		pPlayer->move.z = 0.0f;
	}

	if (pPlayer->pos.z > 2000.0f - 10.0f)
	{
		
		pPlayer->pos.z = 2000.0f - 10.0f;

		pPlayer->move.x = 0.0f;
		pPlayer->move.z = 0.0f;
	}
	else if (pPlayer->pos.z < -2000.0f + 10.0f)
	{
		
		pPlayer->pos.z = -2000.0f + 10.0f;

		pPlayer->move.x = 0.0f;
		pPlayer->move.z = 0.0f;
	}

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


