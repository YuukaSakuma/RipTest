//========================================
//
//2D�A�N�V�����Q�[��(�e�̏���)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "shadow.h"

#define MAX_SHADOW	(256)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureShadow = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Shadow g_Shadow[MAX_SHADOW];
D3DXMATRIX g_mtxWorldShadow[MAX_SHADOW];							//���[���h�}�g���b�N

//========================================
//�e�̏���������
//========================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	int nCntShadow;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_apTextureShadow);

	//�ϐ��̏�����
	for (nCntShadow = 0;nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx; 

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;												//���_�f�[�^�̃|�C���^��4���i�߂�

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//========================================
//�e�̏I������
//========================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureShadow != NULL)
	{
		g_apTextureShadow->Release();
		g_apTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//========================================
//�e�̍X�V����
//========================================
void UpdateShadow(void)
{
	
}

//========================================
//�e�̕`�揈��
//========================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	int nCntShadow;

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow[nCntShadow]);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow[nCntShadow], &g_mtxWorldShadow[nCntShadow], &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow[nCntShadow], &g_mtxWorldShadow[nCntShadow], &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow[nCntShadow]);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}
	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);

}

//========================================
//�e�̐ݒ菈��
//========================================
int SetShadow(void)
{
	int nCntShadow = -1;
	int nCount;

	for (nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (g_Shadow[nCount].bUse == false)
		{//�e���g�p����ĂȂ�
			nCntShadow = nCount;
			g_Shadow[nCount].bUse = true;

			break;
		}
	}
	return nCntShadow;
}

//========================================
//�e�̈ʒu�ݒ菈��
//========================================
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos)
{
	g_Shadow[nldxShadow].pos.x = pos.x;
	g_Shadow[nldxShadow].pos.z = pos.z;
}

//========================================
//�e�̎擾
//========================================
Shadow *GetShadow(void)
{
	return &g_Shadow[0];
}

//========================================
//�e������
//========================================
void NoShadow(int nldxShadow)
{
	g_Shadow[nldxShadow].bUse = false;
}

