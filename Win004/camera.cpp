//========================================
//
//2Dアクションゲーム(カメラ処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "camera.h"
#include"input.h"
#include"model.h"
#include"player.h"

//マクロ定義
#define LENGTH	(300.0f)			//長さ
#define POSVX	(0.0f)				//視点X
#define POSVY	(0.0f)			//視点Y
#define POSVZ	(0.0f)			//視点Z
#define POSVDX	(0.0f)				//目的の視点X
#define POSVDY	(0.0f)				//目的の視点Y
#define POSVDZ	(0.0f)				//目的の視点Z
#define POSRX	(0.0f)				//注視点X
#define POSRY	(0.0f)				//注視点Y
#define POSRZ	(0.0f)				//注視点Z
#define POSRDX	(0.0f)				//目的の注視点X
#define POSRDY	(0.0f)				//目的の注視点Y
#define POSRDZ	(0.0f)				//目的の注視点Z
#define VECUX	(0.0f)				//上方向ベクトルX
#define VECUY	(1.0f)				//上方向ベクトルY
#define VECUZ	(0.0f)				//上方向ベクトルZ
#define ROTX	(1.2f)				//向きX
#define ROTY	(0.0f)				//向きY
#define ROTZ	(0.0f)				//向きZ
#define MOVE	(1.0f)				//移動量
#define MOVE1	(0.05f)				//移動量
#define CURVE	(0.0f)				//角度
#define CURVE1	(1.0f)				//角度
#define CURVE2	(0.25f)				//角度
#define CURVE3	(0.5f)				//角度
#define CURVE4	(0.75f)				//角度
#define UPROT_MAX	(D3DX_PI * 0.95f)	//上の方向の角度の上限
#define DOWNROT_MIN	(D3DX_PI * 0.05f)	//下の方向の角度の上限

//プロトタイプ宣言



//グローバル変数宣言
Camera g_camera;				//カメラの情報

//========================================
//カメラの初期化処理
//========================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(POSVX, POSVY, POSVZ);		//視点の初期化
	g_camera.posR = D3DXVECTOR3(POSRX, POSRY, POSRZ);		//注視点の初期化
	g_camera.vecU = D3DXVECTOR3(VECUX, VECUY, VECUZ);		//上方向ベクトルの初期化
	g_camera.rot = D3DXVECTOR3(ROTX, ROTY, atan2f(g_camera.posR.x - g_camera.posV.x, g_camera.posR.z - g_camera.posV.z));			//向きの初期化
	g_camera.posVDest = D3DXVECTOR3(POSVDX, POSVDY, POSVDZ);		//目的の視点の初期化
	g_camera.posRDest = D3DXVECTOR3(POSRDX, POSRDY, POSRDZ);		//目的の注視点の初期化

	g_camera.posV.x = g_camera.posR.x + (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * LENGTH;
	g_camera.posV.z = g_camera.posR.z + (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

}

//========================================
//カメラの終了処理
//========================================
void UninitCamera(void)
{
	
}

//========================================
//カメラの更新処理
//========================================
void UpdateCamera(void)
{
	
	//目的の注視点を設定(移動)
	Move();

	
	////キーが押されたとき
	//if (GetKeyboardPress(DIK_A) == true)
	//{//Aキーが押された
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//左上移動
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//左下移動
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//左移動			
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//	}													
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{//Dキーが押された

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//右上移動
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//右下移動
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//右移動
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{//Wキーが押された
	//	g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;

	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{//Sキーが押された
	//	g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//}

	//視点
	if (GetKeyboardPress(DIK_Z) == true)
	{//Zキーが押された
		g_camera.rot.y += MOVE1;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//Cキーが押された
		g_camera.rot.y -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_Y) == true)
	{//Yキーが押された
		g_camera.rot.x -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{//Nキーが押された
		g_camera.rot.x += MOVE1;
	}

	//視点
	g_camera.posV.x = g_camera.posR.x + (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * LENGTH;
	g_camera.posV.z = g_camera.posR.z + (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//注視点
	if (GetKeyboardPress(DIK_Q) == true)
	{//Qキーが押された
		g_camera.rot.y += MOVE1;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//Eキーが押された
		g_camera.rot.y -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_T) == true)
	{//Tキーが押された
		g_camera.rot.x += MOVE1;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{//Bキーが押された
		g_camera.rot.x -= MOVE1;
	}

	//注視点
	g_camera.posR.x = g_camera.posV.x - (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posR.y = g_camera.posV.y - cosf(g_camera.rot.x) * LENGTH;
	g_camera.posR.z = g_camera.posV.z - (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//回転の制限
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}

	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI;
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI;
	}

	//カメラの上下回転の上限
	if (g_camera.rot.x > UPROT_MAX)
	{//上
		g_camera.rot.x = UPROT_MAX;
	}
	else if (g_camera.rot.x < DOWNROT_MIN)
	{//下
		g_camera.rot.x = DOWNROT_MIN;
	}
}

//========================================
//カメラの描画処理
//========================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	//プロジェクトマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

}

//========================================
//カメラの取得処理
//========================================
Camera *GetCamera(void)
{
	return &g_camera;
}

//========================================
//目的の注視点を設定(移動) 
//========================================
void Move(void)
{
	D3DXVECTOR3 VDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 RDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player *pPlayer = GetPlayer();

	g_camera.posRDest = D3DXVECTOR3
	(pPlayer->pos.x + sinf(pPlayer->rot.y) * -20.0f,
		pPlayer->pos.y,
		pPlayer->pos.z + cosf(pPlayer->rot.y) * -20.0f);

	//目的の視点を設定
	g_camera.posVDest.x = g_camera.posRDest.x - (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posVDest.z = g_camera.posRDest.z - (cosf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//注視点の補正
	RDiff = g_camera.posRDest - g_camera.posR;

	//視点の補正
	VDiff = g_camera.posVDest - g_camera.posV;

	//慣性
	g_camera.posR += RDiff * 0.4f;
	g_camera.posV += RDiff * 0.4f;
}

//========================================
//目的の注視点を設定(回転) 
//========================================
void Rot(void)
{
	D3DXVECTOR3 RotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player *pPlayer = GetPlayer();
	
	RotDest.y = -pPlayer->rot.y + D3DX_PI * 0.5f;

	RotDiff.y = RotDest.y - g_camera.rot.y;

	//一周したときに戻す処理
	if (RotDiff.y > D3DX_PI)
	{
		RotDiff.y += -D3DX_PI * 2;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		RotDiff.y += D3DX_PI * 2;
	}

	g_camera.rot.y += RotDiff.y * 0.05f;

	if (pPlayer->rot.y > D3DX_PI)
	{
		pPlayer->rot.y += -D3DX_PI * 2;
	}
	else if (pPlayer->rot.y < -D3DX_PI)
	{
		pPlayer->rot.y += D3DX_PI * 2;
	}

}