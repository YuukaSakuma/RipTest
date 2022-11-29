//========================================
//
//2D�A�N�V�����Q�[��(�J��������)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "meshwall.h"
#include"model.h"

void CollisionMeshWall(MeshWall *pMeshWall);

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshWall = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

MeshWall g_MeshWall[128];

//========================================
//�|���S���̏���������
//========================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	int nCntMeshWall;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_apTextureMeshWall);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		g_MeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntMeshWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * nCntMeshWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-2000.0f, 2000.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 2000.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(2000.0f, 2000.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-2000.0f, 0.0f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(2000.0f, 0.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-2000.0f, -2000.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, -2000.0f, 0.0f);
		pVtx[8].pos = D3DXVECTOR3(2000.0f, -2000.0f, 0.0f);

		//�@��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 9;												//���_�f�[�^�̃|�C���^��4���i�߂�

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshWall,
		NULL);

	WORD *pIdx;			//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^���ւ̃|�C���^���擾
	g_pIndxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
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

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIndxBuffMeshWall->Unlock();

}

//========================================
//�|���S���̏I������
//========================================
void UninitMeshWall(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIndxBuffMeshWall != NULL)
	{
		g_pIndxBuffMeshWall->Release();
		g_pIndxBuffMeshWall = NULL;
	}
}

//========================================
//�|���S���̍X�V����
//========================================
void UpdateMeshWall(void)
{
	
}

//========================================
//�|���S���̕`�揈��
//========================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	int nCntMeshWall;


	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntMeshWall = 0; nCntMeshWall < 128; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == true)
		{

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWall[nCntMeshWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntMeshWall].rot.y, g_MeshWall[nCntMeshWall].rot.x, g_MeshWall[nCntMeshWall].rot.z);

			D3DXMatrixMultiply(&g_MeshWall[nCntMeshWall].mtxWorld, &g_MeshWall[nCntMeshWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntMeshWall].pos.x, g_MeshWall[nCntMeshWall].pos.y, g_MeshWall[nCntMeshWall].pos.z);

			D3DXMatrixMultiply(&g_MeshWall[nCntMeshWall].mtxWorld, &g_MeshWall[nCntMeshWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntMeshWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�Ԃ��ӂ����f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIndxBuffMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureMeshWall);
			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				9,					//�p�ӂ������_�̐�
				0,
				12);				//�`�悷��v���~�e�B�u�̐�
		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//========================================
//�ǂ̐ݒ菈��
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
//�G�ƒe�̓����蔻��(�A���[�ɒ���! �|�C���^)
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
//�e�̎擾
//========================================
MeshWall *GetMeshWall(void)
{
	return &g_MeshWall[0];
}

