//========================================
//
//2D�V���[�e�B���O�Q�[��(�p�[�e�B�N������)[particle.cpp]
//Author:���v�ԗD��
//
//========================================
#include"particle.h"
#include"effect.h"
#include"model.h"

//�}�N����`
#define MAX_PARTICLE			(128)

//�p�[�e�B�N���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu(�J�n����)
	D3DXVECTOR3 move;
	D3DXCOLOR col;										//�F
	int nLife;											//����(��������)
	int nType;											//���
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Explosion;

//�O���[�o���ϐ�
Explosion g_aParticle[MAX_PARTICLE];						//�����̏��

//========================================
//�p�[�e�B�N���̏���������
//========================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�p�[�e�B�N���̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���
	}
}

//========================================
//�p�[�e�B�N���̏I������
//========================================
void UninitParticle(void)
{
	
}

//========================================
//�p�[�e�B�N���̍X�V����
//========================================
void  UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos, move;
	D3DXCOLOR col;
	int nLife;
	float fRadius,  fMove;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//�p�[�e�B�N�����g�p����Ă���

			//�p�[�e�B�N���̐���
			for (nCntAppear = 0; nCntAppear < 10; nCntAppear++)
			{
				if (g_aParticle[nCntAppear].nType == 0)
				{
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

				

					//�ړ��ʂ����߂�
					fMove = (float)((rand() % 20) / 10 + 0.2);

					//�ړ��ʂ̐ݒ�
					move.x = sinf((float)((rand() % 629 - 314) / 100.0f)) * fMove;
					move.y = cosf((float)((rand() % 629 - 314) / 100.0f)) * fMove;
					move.z = cosf((float)((rand() % 629 - 314) / 100.0f)) * fMove;

					//�F�̐ݒ�
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					//���a�̐ݒ�
					fRadius = 5.0f;

					//�����̐ݒ�
					nLife = 50;
				}

				//�G�t�F�N�g�̐ݒ�
				Model *pModel = GetModel();
				SetEffect(g_aParticle[nCntParticle].pos, move, col, fRadius, nLife);
			}

			//�����̃J�E���g
			g_aParticle[nCntParticle].nLife--;

			//�������s����
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}

//========================================
//�p�[�e�B�N���̕`�揈��
//========================================
void DrawParticle(void)
{

}

//========================================
//�p�[�e�B�N���̐ݒ菈��
//========================================
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�e���g�p����ĂȂ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].bUse = true;				//�g�p���Ă����Ԃɂ���
			g_aParticle[nCntParticle].nLife = nLife;

			break;
		}
	}

}