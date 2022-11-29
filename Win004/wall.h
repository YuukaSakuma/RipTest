//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _WALL_H_							//���̃}�N����`������Ă��Ȃ�������
#define _WALL_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//�ړ���
	D3DXMATRIX mtxWorldwall;
	bool bUse;
}Wall;


//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
Wall *GetWall(void);

#endif