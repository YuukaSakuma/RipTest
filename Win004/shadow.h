//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _SHADOW_H_							//���̃}�N����`������Ă��Ȃ�������
#define _SHADOW_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//�ړ���
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Shadow;


//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nldxShadow,D3DXVECTOR3 pos);
Shadow *GetShadow(void);
void NoShadow(int nldxShadow);

#endif