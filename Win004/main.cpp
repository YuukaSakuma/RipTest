//========================================
//
//2Dシューティングゲーム[main.cpp]
//Author:佐久間優香
//
//========================================
#include<stdio.h>
#include "main.h"
#include "input.h"
#include"polygon.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"billboard.h"
#include"wall.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"meshfield.h"
#include"meshwall.h"
#include"meshcylinder.h"
#include"player.h"

//マクロ定義
#define CLASS_NAME				"WindowClass"					//ウインドウクラスの名前
#define WINDOW_NAME				"2Dアクションゲーム"		//ウインドウの名前(キャプションに表示)
#define ID_BUTTON_FINISH		(101)							//終了ボタンのID
#define ID_TIMER				(131)							//タイマーのID
#define TIMER_INTERVAL			(1000/60)						//タイマーの発生間隔(ミリ秒)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstsnce, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawMove(void);
void DrawRot(void);
void DrawPos(void);
void DrawModelPos(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;										//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;							//Direc3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;										//フォントへのポインタ
int g_nCountFPS = 0;											//FPSカウント
bool g_bDispDebug = false;										//デバッグ表示のON/OFF
MODE g_mode = MODE_TITLE;										//現在のモード

//========================================
//メイン関数
//========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,													//ウインドウのスタイル
		WindowProc,													//ウインドウのプロシージャ
		0,															//0にする(通常は使用しない)
		0,															//0にする(通常は使用しない)
		hInstance,													//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),								//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),									//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),									//クライアント領域の背景色
		NULL,														//メニューバー
		CLASS_NAME,													//ウインドクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),								//ファイルのアイコン
	};

	HWND hWnd;														//ウインドウハンドル(識別子)
	MSG msg;														//メッセージを格納する変数
	DWORD dwCurrentTime;											//現在時刻
	DWORD dwExecLastTime;											//最後に処理した時刻
	DWORD dwFrameCount;												//フレームカウント
	DWORD dwFPSLastTime;											//最後にを計測した時刻

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };				//画面サイズの構造体

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,										//拡張ウインドウスタイル
		CLASS_NAME,													//ウインドウクラスの名前
		WINDOW_NAME,												//ウインドウの名前
		WS_OVERLAPPEDWINDOW,										//ウインドウのスタイル
		CW_USEDEFAULT,												//ウインドウの左上X座標
		CW_USEDEFAULT,												//ウインドウの左上Y座標
		(rect.right - rect.left),									//ウインドウの幅
		(rect.bottom - rect.top),									//ウインドウの高さ
		NULL,														//親ウインドウのハンドル
		NULL,														//メニューハンドルまたは子ウインドウID
		hInstance,													//インスタンスハンドル
		NULL);														//ウインドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;												//初期化
	dwExecLastTime = timeGetTime();									//現在時刻を取得(保存)

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);										//ウインドウの表示状態を設定
	UpdateWindow(hWnd);												//クライアント領域を更新
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	srand((unsigned int)time(0));//乱数の初期化

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);								//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);								//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();							//現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;						//FPSを計測したときの時刻を保存
				dwFrameCount = 0;									//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60文の1秒経過
				dwExecLastTime = dwCurrentTime;						//処理開始の時刻[現在時刻]を保存

			//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;										//フレームカウントを加算
			}
		}
	}
	//終了処理
	Uninit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;

}

//========================================
//ウインドウプロシージャ
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;														//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:												//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:												//[ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{

				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_COMMAND:												//コマンド発行のメッセージ
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{
			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{

				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:

		nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウインドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;												//0を返さないと終了してしまう
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//既定の処理を返す
}

//========================================
//初期化処理
//========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;									//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,

				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバッグ表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKyeboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ポリゴンの初期化処理
	InitPolygon();

	//メッシュフィールドの初期化
	InitMeshField();

	//弾の初期化処理
	InitBullet();

	//エフェクトの初期化
	InitEffect();

	//パーティクルの初期化
	InitParticle();

	//爆発の初期化
	InitExplosion();

	//壁の初期化処理
	InitWall();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	
	//
	InitMeshWall();

	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	//
	InitMeshCylinder();

	//ビルボードの初期化処理
	InitBillboard();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	InitPlayer();

	//モデルの初期化処理
	InitModel();

	SetModel(D3DXVECTOR3(0.0f, 0.0f, 100.0f), 0);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, -100.0f), 1);

	return S_OK;
}

//========================================
//終了処理
//========================================
void Uninit(void)
{
	//分解能を戻す
	timeEndPeriod(1);

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//ポリゴンの終了処理
	UninitPolygon();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//弾の終了処理
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//爆発の終了処理
	UninitExplosion();

	//壁の終了処理
	UninitWall();

	//
	UninitMeshWall();

	//
	UninitMeshCylinder();

	//ビルボードの終了処理
	UninitBillboard();

	//影の終了処理
	UninitShadow();

	//モデルの終了処理
	UninitPlayer();

	//モデルの終了処理
	UninitModel();

	//キーボードの終了処理
	UninitKeyboard();

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================================
//更新処理
//========================================
void Update(void)
{
	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//ポリゴンの更新処理
	UpdatePolygon();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//モデルの更新処理
	UpdatePlayer();

	//モデルの更新処理
	UpdateModel();

	//弾の更新処理
	UpdateBullet();

	//エフェクトの更新処理
	UpdateEffect();

	//パーティクルの更新処理
	UpdateParticle();

	//爆発の更新処理
	UpdateExplosion();

	//影の更新処理
	UpdateShadow();

	//壁の更新処理
	UpdateWall();

	//
	UpdateMeshWall();

	//
	UpdateMeshCylinder();

	//ビルボードの更新処理
	UpdateBillboard();

	//キーボードの更新処理
	UpdateKeyboard();
}

//========================================
//描画処理
//========================================
void Draw(void)
{
	//画面クリア(バックバッファとZバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//カメラの設定処理
		SetCamera();
	
		//ポリゴンの描画処理
	//	DrawPolygon();

		//メッシュフィールドの描画処理
		DrawMeshField();

		//ビルボードの描画処理
		DrawBillboard();

		//モデルの描画処理
		DrawPlayer();

		//モデルの描画処理
		DrawModel();

		//弾の描画処理
		DrawBullet();

		//影の描画処理
		DrawShadow();

		//壁の描画処理
		//DrawWall();

		//
		DrawMeshWall();

		//
		DrawMeshCylinder();

		//爆発の描画処理
		DrawExplosion();

		//エフェクトの描画処理
		DrawEffect();

		//パーティクルの描画処理
		DrawParticle();

#ifdef _DEBUG
		//移動量
		DrawMove();

		//FPSの表示
		DrawFPS();

		//向き
		DrawRot();

		//位置
		DrawPos();

		//モデルの位置
		DrawModelPos();

#endif

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
//デバイスの取得
//========================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//========================================
//FPSの表示
//========================================
void DrawFPS(void)
{
	RECT rect = { 0,160,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//操作説明
//========================================
void DrawMove(void)
{
	RECT rect1 = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rect2 = { 0,80,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[2][256];

	//文字列に代入
	wsprintf(&aStr[0][0], "左移動:[A]\n右移動:[D]\n奥移動:[W]\n手前移動:[S]\n");
	wsprintf(&aStr[1][0], "左移動:[←]\n右移動:[→]\n奥移動:[↑]\n手前移動:[↓]\n");
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0][0], -1, &rect1, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStr[1][0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//操作説明
//========================================
void DrawRot(void)
{
	Camera *pCamera = GetCamera();
	RECT rect3 = { 0,200,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "カメラの角度;%0.3f %0.3f %0.3f", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect3, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//操作説明
//========================================
void DrawPos(void)
{
	Camera *pCamera = GetCamera();
	RECT rect4 = { 0,180,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "カメラの位置;%0.3f %0.3f %0.3f", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//操作説明
//========================================
void DrawModelPos(void)
{
	Model *pModel = GetModel();
	RECT rect4 = { 0,220,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "モデルの位置;%0.3f %0.3f %0.3f", pModel->pos.x, pModel->pos.y, pModel->pos.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//モードの設定
//========================================
void SetMode(MODE mode)
{
	
}

//========================================
//モードの取得
//========================================
MODE GetMode(void)
{
	return g_mode;
}

