//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _MODEL_H_							//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

#include"main.h"

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;									//�ړ���
	D3DXMATRIX g_mtxWorldModel;							//���[���h�}�g���b�N�X
	int nldxShadow;
	int nType;
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Model;

//�e�\���̂̒�`
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[10];		//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh;						//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;							//�}�e���A���̐�				//�g�p���Ă��邩�ǂ���
}MODEL;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);

#endif