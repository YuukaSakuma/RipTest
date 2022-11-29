//========================================
//
//2D�A�N�V�����Q�[��(���f������)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "model.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"meshwall.h"

//�}�N����`
#define NUM_MODEL	(10)							//���f���̐�
#define POSX		(0.0f)							//�ʒuX
#define POSY		(20.0f)							//�ʒuY
#define POSZ		(0.0f)							//�ʒuZ
#define ROTX		(0.0f)							//����X
#define ROTY		(0.0f)							//����Y
#define ROTZ		(0.0f)							//����Z
#define SET_SHADOW	(-1)							//�e�̐ݒ�




//�v���g�^�C�v�錾
void CollisionModel(Model *pModel);
void ModelMove(void);				//���f���̓���
void PressBullet(void);				//�e�𔭎˂�����

//�O���[�o���ϐ��錾
Model g_Model[2];
MODEL g_MODEL[NUM_MODEL];

//========================================
//���f���̏���������
//========================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^
	int nCntModel;

	//�e��ϐ��̏�����
	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		g_Model[nCntModel].pos = D3DXVECTOR3(POSX, POSY, POSZ);		//�ʒu�̏�����
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ�������
		g_Model[nCntModel].rot = D3DXVECTOR3(ROTX, ROTY, ROTZ);		//�����̏�����
		g_Model[nCntModel].nldxShadow = SET_SHADOW;					//�e�̐ݒu
		g_Model[nCntModel].nType = 1;
		g_Model[nCntModel].bUse = true;	//�g�p���Ă��邩�ǂ�

	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\flower000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MODEL[0].pBuffMat,
		NULL,
		&g_MODEL[0].dwNumMat,
		&g_MODEL[0].pMesh);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_MODEL[0].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_MODEL[0].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_MODEL[0].apTexture[nCntMat]);
		}
	}


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\flower000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MODEL[1].pBuffMat,
		NULL,
		&g_MODEL[1].dwNumMat,
		&g_MODEL[1].pMesh);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_MODEL[1].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_MODEL[1].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_MODEL[1].apTexture[nCntMat]);
		}
	}


	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		//�e�̐ݒ菈��
		g_Model[nCntModel].nldxShadow = SetShadow();
	}
} 

//========================================
//���f���̏I������
//========================================
void UninitModel(void)
{
	//���b�V���̔j��
	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{

		if (g_MODEL[nCntModel].pMesh != NULL)
		{
			g_MODEL[nCntModel].pMesh->Release();
			g_MODEL[nCntModel].pMesh = NULL;
		}


		//�}�e���A���̔j��
		if (g_MODEL[nCntModel].pBuffMat != NULL)
		{
			g_MODEL[nCntModel].pBuffMat->Release();
			g_MODEL[nCntModel].pBuffMat = NULL;
		}


		//�e�N�X�`���̔j��
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
//���f���̍X�V����
//========================================
void UpdateModel(void)
{
	////���f���̓���
	//ModelMove();

	////�e�𔭎˂�����
	//PressBullet();

	////�e�̈ʒu�ݒ菈��
	//SetPositionShadow(g_Model.nldxShadow, g_Model.pos);
}

//========================================
//���f���̕`�揈��
//========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model[nCntModel].g_mtxWorldModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_Model[nCntModel].g_mtxWorldModel, &g_Model[nCntModel].g_mtxWorldModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].pos.x, g_Model[nCntModel].pos.y, g_Model[nCntModel].pos.z);

			D3DXMatrixMultiply(&g_Model[nCntModel].g_mtxWorldModel, &g_Model[nCntModel].g_mtxWorldModel, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].g_mtxWorldModel);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_MODEL[g_Model[nCntModel].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_MODEL[g_Model[nCntModel].nType].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);



				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_MODEL[g_Model[nCntModel].nType].apTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_MODEL[g_Model[nCntModel].nType].pMesh->DrawSubset(nCntMat);
			}
			

			//�ۑ����Ă����}�e���A����߂� 
			pDevice->SetMaterial(&matDef);
		}
	}
}

//========================================
//�e�̐ݒ菈��
//========================================
void SetModel(D3DXVECTOR3 pos, int nType)
{
	int nCntModel;

	for (nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == false)
		{//�e���g�p����ĂȂ�
			g_Model[nCntModel].pos = pos;
			g_Model[nCntModel].nType = nType;
			g_Model[nCntModel].bUse = true;						//�g�p���Ă����Ԃɂ���

			break;
		}
	
	}
}


//========================================
//���f���̎擾
//========================================
Model *GetModel(void)
{
	return &g_Model[0];
}

//========================================
//���f���̓���
//========================================
void ModelMove(void)
{
	//Camera *pCamera = GetCamera();
	//float fRotMove = g_Model.rot.y;
	//float fRotDest = g_Model.rot.y;
	//float fRotDiff;

	////�L�[�������ꂽ�Ƃ�
	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{//A�L�[�������ꂽ
	//	if (GetKeyboardPress(DIK_UP) == true)
	//	{//����ړ�
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.75f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + D3DX_PI * 0.25f;

	//	}
	//	else if (GetKeyboardPress(DIK_DOWN) == true)
	//	{//�����ړ�
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.25f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.25f;
	//	}
	//	else
	//	{//���ړ�
	//		g_Model.move.x += cosf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;
	//		g_Model.move.z += sinf(pCamera->rot.y + -D3DX_PI * 0.5f) * 0.5f;

	//		fRotDest = -pCamera->rot.y + -D3DX_PI * 0.0f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	//{//D�L�[�������ꂽ

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
	//{//W�L�[�������ꂽ
	//	g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;
	//	g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 1.0f) * 0.5f;

	//	fRotDest = -pCamera->rot.y + D3DX_PI * 0.5f;
	//}
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	//{//S�L�[�������ꂽ
	//	g_Model.move.x += cosf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;
	//	g_Model.move.z += sinf(pCamera->rot.y + D3DX_PI * 0.0f) * 0.5f;

	//	fRotDest = -pCamera->rot.y + -D3DX_PI * 0.5f;

	//}

	////�ړI�̈ړ������܂ł̍���
	//fRotDiff = fRotDest - fRotMove;

	//CollisionModel(&g_Model);

	////
	//g_Model.pos.x += g_Model.move.x;
	//g_Model.pos.z += g_Model.move.z;


	////�ړ��ʂ��X�V
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

	////��������Ƃ��ɖ߂�����
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
//�e�𔭎˂�����
//========================================
void PressBullet(void)
{
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	//�e�̐ݒ�
	//	if (g_Model.bUse == true)
	//	{
	//		SetBullet(g_Model.pos, D3DXVECTOR3(sinf(g_Model.rot.y) * -1.0f, 0.0f, cosf(g_Model.rot.y)  * -1.0f), g_Model.rot, 2000);
	//	}
	//}
}

//========================================
//�v���C���[�ƕǂ̓����蔻��(�A���[�ɒ���! �|�C���^)
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
