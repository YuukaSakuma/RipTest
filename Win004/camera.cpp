//========================================
//
//2D�A�N�V�����Q�[��(�J��������)[item.cpp]
//Author:���v�ԗD��
//
//========================================
#include "main.h"
#include "camera.h"
#include"input.h"
#include"model.h"
#include"player.h"

//�}�N����`
#define LENGTH	(300.0f)			//����
#define POSVX	(0.0f)				//���_X
#define POSVY	(0.0f)			//���_Y
#define POSVZ	(0.0f)			//���_Z
#define POSVDX	(0.0f)				//�ړI�̎��_X
#define POSVDY	(0.0f)				//�ړI�̎��_Y
#define POSVDZ	(0.0f)				//�ړI�̎��_Z
#define POSRX	(0.0f)				//�����_X
#define POSRY	(0.0f)				//�����_Y
#define POSRZ	(0.0f)				//�����_Z
#define POSRDX	(0.0f)				//�ړI�̒����_X
#define POSRDY	(0.0f)				//�ړI�̒����_Y
#define POSRDZ	(0.0f)				//�ړI�̒����_Z
#define VECUX	(0.0f)				//������x�N�g��X
#define VECUY	(1.0f)				//������x�N�g��Y
#define VECUZ	(0.0f)				//������x�N�g��Z
#define ROTX	(1.2f)				//����X
#define ROTY	(0.0f)				//����Y
#define ROTZ	(0.0f)				//����Z
#define MOVE	(1.0f)				//�ړ���
#define MOVE1	(0.05f)				//�ړ���
#define CURVE	(0.0f)				//�p�x
#define CURVE1	(1.0f)				//�p�x
#define CURVE2	(0.25f)				//�p�x
#define CURVE3	(0.5f)				//�p�x
#define CURVE4	(0.75f)				//�p�x
#define UPROT_MAX	(D3DX_PI * 0.95f)	//��̕����̊p�x�̏��
#define DOWNROT_MIN	(D3DX_PI * 0.05f)	//���̕����̊p�x�̏��

//�v���g�^�C�v�錾



//�O���[�o���ϐ��錾
Camera g_camera;				//�J�����̏��

//========================================
//�J�����̏���������
//========================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(POSVX, POSVY, POSVZ);		//���_�̏�����
	g_camera.posR = D3DXVECTOR3(POSRX, POSRY, POSRZ);		//�����_�̏�����
	g_camera.vecU = D3DXVECTOR3(VECUX, VECUY, VECUZ);		//������x�N�g���̏�����
	g_camera.rot = D3DXVECTOR3(ROTX, ROTY, atan2f(g_camera.posR.x - g_camera.posV.x, g_camera.posR.z - g_camera.posV.z));			//�����̏�����
	g_camera.posVDest = D3DXVECTOR3(POSVDX, POSVDY, POSVDZ);		//�ړI�̎��_�̏�����
	g_camera.posRDest = D3DXVECTOR3(POSRDX, POSRDY, POSRDZ);		//�ړI�̒����_�̏�����

	g_camera.posV.x = g_camera.posR.x + (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * LENGTH;
	g_camera.posV.z = g_camera.posR.z + (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

}

//========================================
//�J�����̏I������
//========================================
void UninitCamera(void)
{
	
}

//========================================
//�J�����̍X�V����
//========================================
void UpdateCamera(void)
{
	
	//�ړI�̒����_��ݒ�(�ړ�)
	Move();

	
	////�L�[�������ꂽ�Ƃ�
	//if (GetKeyboardPress(DIK_A) == true)
	//{//A�L�[�������ꂽ
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//����ړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//�����ړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//���ړ�			
	//		g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE3) * MOVE;
	//	}													
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{//D�L�[�������ꂽ

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//�E��ړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{//�E���ړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//�E�ړ�
	//		g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//		g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{//W�L�[�������ꂽ
	//	g_camera.posV.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posV.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posR.x += cosf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	g_camera.posR.z += sinf(g_camera.rot.y + -D3DX_PI * CURVE1) * MOVE;

	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{//S�L�[�������ꂽ
	//	g_camera.posV.x += cosf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posV.z += sinf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posR.x += cosf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//	g_camera.posR.z += sinf(g_camera.rot.y + D3DX_PI * CURVE) * MOVE;
	//}

	//���_
	if (GetKeyboardPress(DIK_Z) == true)
	{//Z�L�[�������ꂽ
		g_camera.rot.y += MOVE1;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//C�L�[�������ꂽ
		g_camera.rot.y -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_Y) == true)
	{//Y�L�[�������ꂽ
		g_camera.rot.x -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_N) == true)
	{//N�L�[�������ꂽ
		g_camera.rot.x += MOVE1;
	}

	//���_
	g_camera.posV.x = g_camera.posR.x + (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * LENGTH;
	g_camera.posV.z = g_camera.posR.z + (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//�����_
	if (GetKeyboardPress(DIK_Q) == true)
	{//Q�L�[�������ꂽ
		g_camera.rot.y += MOVE1;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//E�L�[�������ꂽ
		g_camera.rot.y -= MOVE1;
	}
	else if (GetKeyboardPress(DIK_T) == true)
	{//T�L�[�������ꂽ
		g_camera.rot.x += MOVE1;
	}
	else if (GetKeyboardPress(DIK_B) == true)
	{//B�L�[�������ꂽ
		g_camera.rot.x -= MOVE1;
	}

	//�����_
	g_camera.posR.x = g_camera.posV.x - (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posR.y = g_camera.posV.y - cosf(g_camera.rot.x) * LENGTH;
	g_camera.posR.z = g_camera.posV.z - (sinf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//��]�̐���
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}

	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI;
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI;
	}

	//�J�����̏㉺��]�̏��
	if (g_camera.rot.x > UPROT_MAX)
	{//��
		g_camera.rot.x = UPROT_MAX;
	}
	else if (g_camera.rot.x < DOWNROT_MIN)
	{//��
		g_camera.rot.x = DOWNROT_MIN;
	}
}

//========================================
//�J�����̕`�揈��
//========================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�̎擾
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	//�v���W�F�N�g�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

}

//========================================
//�J�����̎擾����
//========================================
Camera *GetCamera(void)
{
	return &g_camera;
}

//========================================
//�ړI�̒����_��ݒ�(�ړ�) 
//========================================
void Move(void)
{
	D3DXVECTOR3 VDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 RDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player *pPlayer = GetPlayer();

	g_camera.posRDest = D3DXVECTOR3
	(pPlayer->pos.x + sinf(pPlayer->rot.y) * -20.0f,
		pPlayer->pos.y,
		pPlayer->pos.z + cosf(pPlayer->rot.y) * -20.0f);

	//�ړI�̎��_��ݒ�
	g_camera.posVDest.x = g_camera.posRDest.x - (sinf(g_camera.rot.x) * cosf(g_camera.rot.y))* LENGTH;
	g_camera.posVDest.z = g_camera.posRDest.z - (cosf(g_camera.rot.x) * sinf(g_camera.rot.y))* LENGTH;

	//�����_�̕␳
	RDiff = g_camera.posRDest - g_camera.posR;

	//���_�̕␳
	VDiff = g_camera.posVDest - g_camera.posV;

	//����
	g_camera.posR += RDiff * 0.4f;
	g_camera.posV += RDiff * 0.4f;
}

//========================================
//�ړI�̒����_��ݒ�(��]) 
//========================================
void Rot(void)
{
	D3DXVECTOR3 RotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player *pPlayer = GetPlayer();
	
	RotDest.y = -pPlayer->rot.y + D3DX_PI * 0.5f;

	RotDiff.y = RotDest.y - g_camera.rot.y;

	//��������Ƃ��ɖ߂�����
	if (RotDiff.y > D3DX_PI)
	{
		RotDiff.y += -D3DX_PI * 2;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		RotDiff.y += D3DX_PI * 2;
	}

	g_camera.rot.y += RotDiff.y * 0.05f;

	if (pPlayer->rot.y > D3DX_PI)
	{
		pPlayer->rot.y += -D3DX_PI * 2;
	}
	else if (pPlayer->rot.y < -D3DX_PI)
	{
		pPlayer->rot.y += D3DX_PI * 2;
	}

}