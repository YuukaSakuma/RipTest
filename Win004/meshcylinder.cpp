//========================================
//
//2D�A�N�V�����Q�[��(�J��������)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include"meshcylinder.h"

//�}�N����`
#define MAX_HEIGHT	(100.0f)		//�����̍ő�
#define MIN_HEIGHT	(0.0f)			//�����̍Œ�
#define WIDTH	(3000.0f)			//��


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureMeshCylinder = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshCylinder = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshCylinder g_MeshCylinder;

//========================================
//�|���S���̏���������
//========================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_apTextureMeshCylinder);

	g_MeshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 18,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f) * WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH);
	pVtx[1].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.75f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.75f)* WIDTH);
	pVtx[2].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.5f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.5f)* WIDTH);
	pVtx[3].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.25f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.25f)* WIDTH);
	pVtx[4].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.0f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.0f)* WIDTH);
	pVtx[5].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.25f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.25f)* WIDTH);
	pVtx[6].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.5f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.5f)* WIDTH);
	pVtx[7].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.75f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.75f)* WIDTH);
	pVtx[8].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH, MAX_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH);
	pVtx[9].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH);
	pVtx[10].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.75f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.75f)* WIDTH);
	pVtx[11].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.5f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.5f)* WIDTH);
	pVtx[12].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.25f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.25f)* WIDTH);
	pVtx[13].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 0.0f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 0.0f)* WIDTH);
	pVtx[14].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.25f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.25f)* WIDTH);
	pVtx[15].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.5f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.5f)* WIDTH);
	pVtx[16].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * -0.75f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * -0.75f)* WIDTH);
	pVtx[17].pos = D3DXVECTOR3(cosf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH, MIN_HEIGHT, sinf(g_MeshCylinder.rot.y + D3DX_PI * 1.0f)* WIDTH);
	 
	//�@��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[15].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	


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
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.375f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.625f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.875f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.125f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.375f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.625f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.75f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(0.875f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshCylinder,
		NULL);

	WORD *pIdx;			//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^���ւ̃|�C���^���擾
	g_pIndxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 9;
	pIdx[1] = 0;
	pIdx[2] = 10;
	pIdx[3] = 1;
	pIdx[4] = 11;
	pIdx[5] = 2;
	pIdx[6] = 12;
	pIdx[7] = 3;
	pIdx[8] = 13;
	pIdx[9] = 4;
	pIdx[10] =14;
	pIdx[11] = 5;
	pIdx[12] = 15;
	pIdx[13] = 6;
	pIdx[14] = 16;
	pIdx[15] = 7;
	pIdx[16] = 17;
	pIdx[17] = 8;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIndxBuffMeshCylinder->Unlock();
}

//========================================
//�|���S���̏I������
//========================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureMeshCylinder != NULL)
	{
		g_apTextureMeshCylinder->Release();
		g_apTextureMeshCylinder = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIndxBuffMeshCylinder != NULL)
	{
		g_pIndxBuffMeshCylinder->Release();
		g_pIndxBuffMeshCylinder = NULL;
	}
}

//========================================
//�|���S���̍X�V����
//========================================
void UpdateMeshCylinder(void)
{
	
}

//========================================
//�|���S���̕`�揈��
//========================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshCylinder.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshCylinder.rot.y, g_MeshCylinder.rot.x, g_MeshCylinder.rot.z);

	D3DXMatrixMultiply(&g_MeshCylinder.mtxWorld, &g_MeshCylinder.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshCylinder.pos.x, g_MeshCylinder.pos.y, g_MeshCylinder.pos.z);

	D3DXMatrixMultiply(&g_MeshCylinder.mtxWorld, &g_MeshCylinder.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�Ԃ��ӂ����f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIndxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureMeshCylinder);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		18,					//�p�ӂ������_�̐�
		0,
		18);				//�`�悷��v���~�e�B�u�̐�

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

