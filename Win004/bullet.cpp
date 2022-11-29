//========================================
//
//2D�V���[�e�B���O�Q�[��(�e�̏���)[bullet.cpp]
//Author:���v�ԗD��
//
//========================================
#include"bullet.h"
#include"shadow.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"

//�}�N����`
#define MAX_BULLET			(128)
#define NUM_BULLET			(2)
#define NUM_BULLET_LIFE		(2000)
#define COL_R	 (1.0f)									//��
#define COL_G	 (1.0f)									//��
#define COL_B	 (1.0f)									//��
#define COL_A	 (1.0f)									//�����x

//�v���g�^�C�v�錾
void CollisionWall(Bullet *pBullet);					//�G�ƒe�̓����蔻��
void CollisionPlayer(Bullet *pBullet);					//�v���C���[�ƒe�̓����蔻��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�̃|�C���^
D3DXMATRIX g_mtxWorldBullet[MAX_BULLET];				//���[���h�}�g���b�N�X
Bullet g_aBullet[MAX_BULLET];							//�e�̏��

//========================================
//�e�̏���������
//========================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;									//���_���ւ̃|�C���^
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nShadow = -1;
		g_aBullet[nCntBullet].nLife = NUM_BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���

	}

	//���_�o�b�t�@�̐���
 	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);

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

		pVtx += 4;										//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();	
}

//========================================
//�e�̏I������
//========================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//========================================
//�e�̍X�V����
//========================================
void  UpdateBullet(void)
{
	
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

			//�ʒu���X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//�e�̏ꏊ
			SetPositionShadow(g_aBullet[nCntBullet].nShadow, g_aBullet[nCntBullet].pos);

			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 30);

			CollisionWall(&g_aBullet[nCntBullet]);
			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--;

			//�������s����
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
				g_aBullet[nCntBullet].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
				NoShadow(g_aBullet[nCntBullet].nShadow);
			}
		}

	}


}

//========================================
//�e�̕`�揈��
//========================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;								//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;									//�r���[�}�g���b�N�X�̎擾�p
	int nCntBullet;

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
 	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet[nCntBullet]);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBullet[nCntBullet], NULL, &mtxView);	//�t�s������߂�
			g_mtxWorldBullet[nCntBullet]._41 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._42 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldBullet[nCntBullet], &g_mtxWorldBullet[nCntBullet], &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet[nCntBullet]);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	
}

//========================================
//�e�̐ݒ菈��
//========================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife)
{
	int nCntBullet;
	VERTEX_3D *pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����ĂȂ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].nShadow = SetShadow();
			g_aBullet[nCntBullet].bUse = true;						//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;												//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//========================================
//�G�ƒe�̓����蔻��(�A���[�ɒ���! �|�C���^)
//========================================
void CollisionWall(Bullet *pBullet)
{	
	D3DXVECTOR3 vecLine1 = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	D3DXVECTOR3 vecLine2 = D3DXVECTOR3(2000.0f, 0.0f, -2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecLine3 = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecLine4 = D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f) - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);

	D3DXVECTOR3 vecToPos1 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f);
	D3DXVECTOR3 vecToPos2 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecToPos3 = pBullet->pos - D3DXVECTOR3(2000.0f, 0.0f, -2000.0f);
	D3DXVECTOR3 vecToPos4 = pBullet->pos - D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f);

	//if (pBullet->pos.x > 200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}
	//else if(pBullet->pos.x < -200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}

	//if (pBullet->pos.z > 200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}
	//else if (pBullet->pos.z < -200.0f)
	//{
	//	pBullet->bUse = false;
	//	NoShadow(pBullet->nShadow);
	//	SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	//	SetParticle(pBullet->pos, 0, 20);
	//}

	//�O�ς̓����蔻��
	if ( (vecLine1.z * vecToPos1.x) - (vecLine1.x * vecToPos1.z) <= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine2.z * vecToPos2.x) - (vecLine2.x * vecToPos2.z) >= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine3.z * vecToPos3.x) - (vecLine3.x * vecToPos3.z) >= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}

	if ((vecLine4.z * vecToPos4.x) - (vecLine4.x * vecToPos4.z) <= 0.0f)
	{
		pBullet->bUse = false;
		NoShadow(pBullet->nShadow);
		SetExplosion(pBullet->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
		SetParticle(pBullet->pos, 0, 20);
	}


}

//========================================
//�v���C���[�ƒe�̓����蔻��(�A���[�ɒ���! �|�C���^)
//========================================
void CollisionPlayer(Bullet *pBullet)
{
	
}

//========================================
//�e�̎擾
//========================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}


