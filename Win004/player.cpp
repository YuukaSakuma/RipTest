//========================================
//
//2D�A�N�V�����Q�[��(���f������)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "player.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"

//�}�N����`
#define NUM_PLAYER	(10)							//���f���̐�
#define POSX		(0.0f)							//�ʒuX
#define POSY		(20.0f)							//�ʒuY
#define POSZ		(0.0f)							//�ʒuZ
#define ROTX		(0.0f)							//����X
#define ROTY		(0.0f)							//����Y
#define ROTZ		(0.0f)							//����Z
#define SET_SHADOW	(-1)							//�e�̐ݒ�

//�v���g�^�C�v�錾
void CollisionPlayer(Player *pPlayer);
void PlayerMove(void);				//���f���̓���
void PressB(void);				//�e�𔭎˂�����


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTexturePlayer[NUM_PLAYER] = {};		//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshPlayer = NULL;						//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;							//�}�e���A���̐�
Player g_Player;

//========================================
//���f���̏���������
//========================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�e��ϐ��̏�����
	g_Player.pos = D3DXVECTOR3(POSX, POSY, POSZ);		//�ʒu�̏�����
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ�������
	g_Player.rot = D3DXVECTOR3(ROTX, ROTY, ROTZ);		//�����̏�����
	g_Player.nldxShadow = SET_SHADOW;					//�e�̐ݒu
	g_Player.bUse = true;								//�g�p���Ă��邩�ǂ���

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\airplane000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat  = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	//�e�̐ݒ菈��
	g_Player.nldxShadow = SetShadow();
} 

//========================================
//���f���̏I������
//========================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//�e�N�X�`���̔j��
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
//���f���̍X�V����
//========================================
void UpdatePlayer(void)
{
	//���f���̓���
	PlayerMove();

	//�e�𔭎˂�����
	PressB();

	//�e�̈ʒu�ݒ菈��
	SetPositionShadow(g_Player.nldxShadow, g_Player.pos);
}

//========================================
//���f���̕`�揈��
//========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂� 
	pDevice->SetMaterial(&matDef);
}

//========================================
//���f���̎擾
//========================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//========================================
//���f���̓���
//========================================
void PlayerMove(void)
{
	Camera *pCamera = GetCamera();
	float fRotMove = g_Player.rot.y;
	float fRotDest = g_Player.rot.y;
	float fRotDiff;

	//�L�[�������ꂽ�Ƃ�
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{//����ړ�
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;

			fRotDest = -pCamera->rot.y + D3DX_PI * 0.25f;

		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//�����ړ�
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 0.25f;
		}
		else
		{//���ړ�
			g_Player.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;
			g_Player.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;

			fRotDest = -pCamera->rot.y + -D3DX_PI * 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//D�L�[�������ꂽ

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
	{//W�L�[�������ꂽ
		g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;
		g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;

		fRotDest = -pCamera->rot.y + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//S�L�[�������ꂽ
		g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;
		g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;

		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.5f;

	}

	//�ړI�̈ړ������܂ł̍���
	fRotDiff = fRotDest - fRotMove;

	CollisionPlayer(&g_Player);

	//
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.z += g_Player.move.z;

	//�ړ��ʂ��X�V
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.1f;

	if (g_Player.move.x <= 0.0f && g_Player.move.x >= -0.1f || g_Player.move.x >= 0.0f && g_Player.move.x <= 0.1f)
	{
		if (g_Player.move.z <= 0.0f && g_Player.move.z >= -0.1f || g_Player.move.z >= 0.0f && g_Player.move.z <= 0.1f)
		{
			Rot();
		}
	}

	//��������Ƃ��ɖ߂�����
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
//�e�𔭎˂�����
//========================================
void PressB(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		//�e�̐ݒ�
		if (g_Player.bUse == true)
		{
			SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y) * -1.0f, 0.0f, cosf(g_Player.rot.y)  * -1.0f), g_Player.rot, 2000);
		}
	}
}

//========================================
//�v���C���[�ƕǂ̓����蔻��(�A���[�ɒ���! �|�C���^)
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

	//////�O�ς̔���
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


