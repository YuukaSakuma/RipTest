//========================================
//
//2D�A�N�V�����Q�[��(���C�g����)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "light.h"


//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[3];				//���C�g�̏��

//========================================
//���C�g�̏���������
//========================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;									//�ݒ�p�����x�N�g��
	int nCntLight;

	for (nCntLight = 0; nCntLight < 3;nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		if (nCntLight == 0)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			
		}
		else if (nCntLight == 1)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.8f, 0.55f, -0.55f);
			
		}
		else if (nCntLight == 2)
		{
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.89f, -0.8f, 0.4f);
			
		}

		D3DXVec3Normalize(&vecDir, &vecDir);				//�x�N�g���𐳋K������
		
		g_light[nCntLight].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(0, &g_light[nCntLight]);
	
		//���C�g��L���ɂ���
		pDevice->LightEnable(0, TRUE);
	}

}

//========================================
//���C�g�̏I������
//========================================
void UninitLight(void)
{

}

//========================================
//���C�g�̍X�V����
//========================================
void UpdateLight(void)
{

}

