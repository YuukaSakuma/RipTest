//========================================
//
//2D�A�N�V�����Q�[��(�r���{�[�h����)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "billboard.h"

#define MAX_BILLBOARD	(1)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureBillboard = NULL;			//�e�N�X�`��(3����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBillboard[MAX_BILLBOARD];								//�ʒu
D3DXMATRIX g_mtxWorldBillboard[MAX_BILLBOARD];							//���[���h�}�g���b�N�X

//========================================
//�r���{�[�h�̏���������
//========================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	VERTEX_3D *pVtx;
	int nCntBillboard;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_apTextureBillboard);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_posBillboard[nCntBillboard] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
		g_pVtxBuffBillboard->Unlock();
}

//========================================
//�r���{�[�h�̏I������
//========================================
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureBillboard != NULL)
	{
		g_apTextureBillboard->Release();
		g_apTextureBillboard = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//========================================
//�r���{�[�h�̍X�V����
//========================================
void UpdateBillboard(void)
{
	
}

//========================================
//�r���{�[�h�̕`�揈��
//========================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;								//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;									//�r���[�}�g���b�N�X�̎擾�p

	

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldBillboard[nCntBillboard]);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_mtxWorldBillboard[nCntBillboard], NULL, &mtxView);	//�t�s������߂�
		g_mtxWorldBillboard[nCntBillboard]._41 = 0.0f;
		g_mtxWorldBillboard[nCntBillboard]._42 = 0.0f;
		g_mtxWorldBillboard[nCntBillboard]._43 = 0.0f;
		
		
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_posBillboard[nCntBillboard].x, g_posBillboard[nCntBillboard].y, g_posBillboard[nCntBillboard].z);

		D3DXMatrixMultiply(&g_mtxWorldBillboard[nCntBillboard], &g_mtxWorldBillboard[nCntBillboard], &mtxTrans);

		////Z�e�X�g�𖳌��ɂ���
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//�A���t�@�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard[nCntBillboard]);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBillboard);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);

		//�A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		////Z�e�X�g��L���ɂ���
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

}

//========================================
//�r���{�[�h�̐ݒ菈��
//========================================
void SetBillboard(D3DXVECTOR3 pos)
{

}

