//========================================
//
//2D�V���[�e�B���O�Q�[��(�G�t�F�N�g����)[effect.cpp]
//Author:���v�ԗD��
//
//========================================
#include"effect.h"

//�}�N����`
#define MAX_EFFECT			(4096)						//�G�t�F�N�g�̍ő吔
#define COL_R	 (0.0f)									//��
#define COL_G	 (0.0f)									//��
#define COL_B	 (0.0f)									//��
#define COL_A	 (1.0f)									//�����x


//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXCOLOR col;										//�F
	D3DXMATRIX g_mtxWorldEffect;
	float fRadius;										//���a(�傫��)
	float fAlpha;
	int nLife;											//����(�\������)
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�̃|�C���^
Effect g_aEffect[MAX_EFFECT];							//�G�t�F�N�g�̏��

//========================================
//�G�t�F�N�g�̏���������
//========================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;									//���_���ւ̃|�C���^
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fAlpha = 0.99f;
		g_aEffect[nCntEffect].nLife = 30;
		g_aEffect[nCntEffect].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���

	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[1].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[2].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);
		pVtx[3].col = D3DXCOLOR(COL_R, COL_G, COL_B, COL_A);

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;								//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//========================================
//�G�t�F�N�g�̏I������
//========================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//========================================
//�G�t�F�N�g�̍X�V����
//========================================
void  UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;
			g_aEffect[nCntEffect].fRadius *= 0.95f;
			g_aEffect[nCntEffect].col.a *= g_aEffect[nCntEffect].fAlpha;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);

			//�����̃J�E���g�_�E��
			g_aEffect[nCntEffect].nLife--;

			//�������s����
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}
		pVtx += 4;								//���_�f�[�^�̃|�C���^��4���i�߂� 
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//========================================
//�G�t�F�N�g�̕`�揈��
//========================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;								//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;									//�r���[�}�g���b�N�X�̎擾�p
	int nCntEffect;

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//a�u�����f�B���O�����Z���v�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].g_mtxWorldEffect);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aEffect[nCntEffect].g_mtxWorldEffect, NULL, &mtxView);	//�t�s������߂�
			g_aEffect[nCntEffect].g_mtxWorldEffect._41 = 0.0f;
			g_aEffect[nCntEffect].g_mtxWorldEffect._42 = 0.0f;
			g_aEffect[nCntEffect].g_mtxWorldEffect._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_aEffect[nCntEffect].g_mtxWorldEffect, &g_aEffect[nCntEffect].g_mtxWorldEffect, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].g_mtxWorldEffect);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//a�u�����f�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

}

//========================================
//�G�t�F�N�g�̐ݒ菈��
//========================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_3D *pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�G�t�F�N�g���g�p����ĂȂ�

			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].fAlpha = 1.0f;

			

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, COL_A);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, COL_A);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, COL_A);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, COL_A);

			g_aEffect[nCntEffect].bUse = true;				//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;								//���_�f�[�^�̃|�C���^��4���i�߂� 
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}