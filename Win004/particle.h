//========================================
//
//2D�V���[�e�B���O�Q�[��(�p�[�e�B�N������)[particle.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _PARTICLE_H_							//���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType,int nLife);

#include "main.h"

#endif