//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _MESHCYLINDER_H_							//���̃}�N����`������Ă��Ȃ�������
#define _MESHCYLINDER_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����


//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//�ړ���
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
}MeshCylinder;

//�v���g�^�C�v�錾
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif