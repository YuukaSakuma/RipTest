//========================================
//
//2D�V���[�e�B���O�Q�[��(�e�̏���)[bullet.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"



//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,					//�v���C���[�̒e
	BULLETTYPE_ENEMY,						//�G�̒e
	BULLETTYPE_MAX							
}BULLETTYPE;

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 posOld;									//�ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 rot;									//�ړ���
	int nLife;											//����
	int nShadow;
	BULLETTYPE nType;									//�e�̎��
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 rot,int nLife);
Bullet *GetBullet(void);

#endif
