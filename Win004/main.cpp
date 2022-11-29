//========================================
//
//2D�V���[�e�B���O�Q�[��[main.cpp]
//Author:���v�ԗD��
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

//�}�N����`
#define CLASS_NAME				"WindowClass"					//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME				"2D�A�N�V�����Q�[��"		//�E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define ID_BUTTON_FINISH		(101)							//�I���{�^����ID
#define ID_TIMER				(131)							//�^�C�}�[��ID
#define TIMER_INTERVAL			(1000/60)						//�^�C�}�[�̔����Ԋu(�~���b)

//�v���g�^�C�v�錾
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

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;										//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;							//Direc3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;										//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;											//FPS�J�E���g
bool g_bDispDebug = false;										//�f�o�b�O�\����ON/OFF
MODE g_mode = MODE_TITLE;										//���݂̃��[�h

//========================================
//���C���֐�
//========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,													//�E�C���h�E�̃X�^�C��
		WindowProc,													//�E�C���h�E�̃v���V�[�W��
		0,															//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,															//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,													//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),								//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),									//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),									//�N���C�A���g�̈�̔w�i�F
		NULL,														//���j���[�o�[
		CLASS_NAME,													//�E�C���h�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),								//�t�@�C���̃A�C�R��
	};

	HWND hWnd;														//�E�C���h�E�n���h��(���ʎq)
	MSG msg;														//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;											//���ݎ���
	DWORD dwExecLastTime;											//�Ō�ɏ�����������
	DWORD dwFrameCount;												//�t���[���J�E���g
	DWORD dwFPSLastTime;											//�Ō�ɂ��v����������

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };				//��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,										//�g���E�C���h�E�X�^�C��
		CLASS_NAME,													//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,												//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,										//�E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,												//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,												//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),									//�E�C���h�E�̕�
		(rect.bottom - rect.top),									//�E�C���h�E�̍���
		NULL,														//�e�E�C���h�E�̃n���h��
		NULL,														//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,													//�C���X�^���X�n���h��
		NULL);														//�E�C���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;												//������
	dwExecLastTime = timeGetTime();									//���ݎ������擾(�ۑ�)

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);										//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);												//�N���C�A���g�̈���X�V
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	srand((unsigned int)time(0));//�����̏�����

	//���b�Z�[�W���[�v
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
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);								//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);								//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();							//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;						//FPS���v�������Ƃ��̎�����ۑ�
				dwFrameCount = 0;									//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;						//�����J�n�̎���[���ݎ���]��ۑ�

			//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;										//�t���[���J�E���g�����Z
			}
		}
	}
	//�I������
	Uninit();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;

}

//========================================
//�E�C���h�E�v���V�[�W��
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;														//�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:												//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:												//[ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{

				//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_COMMAND:												//�R�}���h���s�̃��b�Z�[�W
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{

				//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:

		nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;												//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//����̏�����Ԃ�
}

//========================================
//����������
//========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;									//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@�𐶐�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKyeboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�|���S���̏���������
	InitPolygon();

	//���b�V���t�B�[���h�̏�����
	InitMeshField();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�����̏�����
	InitExplosion();

	//�ǂ̏���������
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

	//�r���{�[�h�̏���������
	InitBillboard();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	InitPlayer();

	//���f���̏���������
	InitModel();

	SetModel(D3DXVECTOR3(0.0f, 0.0f, 100.0f), 0);
	SetModel(D3DXVECTOR3(0.0f, 0.0f, -100.0f), 1);

	return S_OK;
}

//========================================
//�I������
//========================================
void Uninit(void)
{
	//����\��߂�
	timeEndPeriod(1);

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�|���S���̏I������
	UninitPolygon();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�����̏I������
	UninitExplosion();

	//�ǂ̏I������
	UninitWall();

	//
	UninitMeshWall();

	//
	UninitMeshCylinder();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�e�̏I������
	UninitShadow();

	//���f���̏I������
	UninitPlayer();

	//���f���̏I������
	UninitModel();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================================
//�X�V����
//========================================
void Update(void)
{
	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//�|���S���̍X�V����
	UpdatePolygon();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//���f���̍X�V����
	UpdatePlayer();

	//���f���̍X�V����
	UpdateModel();

	//�e�̍X�V����
	UpdateBullet();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();

	//�����̍X�V����
	UpdateExplosion();

	//�e�̍X�V����
	UpdateShadow();

	//�ǂ̍X�V����
	UpdateWall();

	//
	UpdateMeshWall();

	//
	UpdateMeshCylinder();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();
}

//========================================
//�`�揈��
//========================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�J�����̐ݒ菈��
		SetCamera();
	
		//�|���S���̕`�揈��
	//	DrawPolygon();

		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshField();

		//�r���{�[�h�̕`�揈��
		DrawBillboard();

		//���f���̕`�揈��
		DrawPlayer();

		//���f���̕`�揈��
		DrawModel();

		//�e�̕`�揈��
		DrawBullet();

		//�e�̕`�揈��
		DrawShadow();

		//�ǂ̕`�揈��
		//DrawWall();

		//
		DrawMeshWall();

		//
		DrawMeshCylinder();

		//�����̕`�揈��
		DrawExplosion();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�p�[�e�B�N���̕`�揈��
		DrawParticle();

#ifdef _DEBUG
		//�ړ���
		DrawMove();

		//FPS�̕\��
		DrawFPS();

		//����
		DrawRot();

		//�ʒu
		DrawPos();

		//���f���̈ʒu
		DrawModelPos();

#endif

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
//�f�o�C�X�̎擾
//========================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//========================================
//FPS�̕\��
//========================================
void DrawFPS(void)
{
	RECT rect = { 0,160,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//�������
//========================================
void DrawMove(void)
{
	RECT rect1 = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rect2 = { 0,80,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[2][256];

	//������ɑ��
	wsprintf(&aStr[0][0], "���ړ�:[A]\n�E�ړ�:[D]\n���ړ�:[W]\n��O�ړ�:[S]\n");
	wsprintf(&aStr[1][0], "���ړ�:[��]\n�E�ړ�:[��]\n���ړ�:[��]\n��O�ړ�:[��]\n");
	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0][0], -1, &rect1, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStr[1][0], -1, &rect2, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//�������
//========================================
void DrawRot(void)
{
	Camera *pCamera = GetCamera();
	RECT rect3 = { 0,200,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "�J�����̊p�x;%0.3f %0.3f %0.3f", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect3, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//�������
//========================================
void DrawPos(void)
{
	Camera *pCamera = GetCamera();
	RECT rect4 = { 0,180,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "�J�����̈ʒu;%0.3f %0.3f %0.3f", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//�������
//========================================
void DrawModelPos(void)
{
	Model *pModel = GetModel();
	RECT rect4 = { 0,220,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "���f���̈ʒu;%0.3f %0.3f %0.3f", pModel->pos.x, pModel->pos.y, pModel->pos.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect4, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
//���[�h�̐ݒ�
//========================================
void SetMode(MODE mode)
{
	
}

//========================================
//���[�h�̎擾
//========================================
MODE GetMode(void)
{
	return g_mode;
}

