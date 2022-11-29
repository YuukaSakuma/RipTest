//========================================
//
//2Dシューティングゲーム(入力処理)[input.h]
//Author:佐久間優香
//
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//プロトタイプ宣言
HRESULT InitKyeboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

#endif