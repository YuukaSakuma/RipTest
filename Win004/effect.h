//========================================
//
//2D�V���[�e�B���O�Q�[��(�G�t�F�N�g����)[effect.h]
//Author:���v�ԗD��
//
//========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius,int nLife);

#endif
