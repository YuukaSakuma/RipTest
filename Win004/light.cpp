//========================================
//
//2Dアクションゲーム(ライト処理)[item.cpp]
//Author:佐久間優香
//
//========================================
#include "main.h"
#include "light.h"


//グローバル変数宣言
D3DLIGHT9 g_light[3];				//ライトの情報

//========================================
//ライトの初期化処理
//========================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得
	D3DXVECTOR3 vecDir;									//設定用方向ベクトル
	int nCntLight;

	for (nCntLight = 0; nCntLight < 3;nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		if (nCntLight == 0)
		{
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			
		}
		else if (nCntLight == 1)
		{
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.8f, 0.55f, -0.55f);
			
		}
		else if (nCntLight == 2)
		{
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(-0.89f, -0.8f, 0.4f);
			
		}

		D3DXVec3Normalize(&vecDir, &vecDir);				//ベクトルを正規化する
		
		g_light[nCntLight].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(0, &g_light[nCntLight]);
	
		//ライトを有効にする
		pDevice->LightEnable(0, TRUE);
	}

}

//========================================
//ライトの終了処理
//========================================
void UninitLight(void)
{

}

//========================================
//ライトの更新処理
//========================================
void UpdateLight(void)
{

}

