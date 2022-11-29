//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _MESHWALL_H_							//���̃}�N����`������Ă��Ȃ�������
#define _MESHWALL_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//�ړ���
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
	bool bUse;
}MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
MeshWall *GetMeshWall(void);

#endif