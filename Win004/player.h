//========================================
//
//2D�V���[�e�B���O�Q�[��(�A�C�e���擾����)[getitem.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _PLAYER_H_							//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 posOld;									//�ʒu
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;									//�ړ���
	D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	int nldxShadow;
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif