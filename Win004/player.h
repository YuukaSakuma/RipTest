//========================================
//
//2Dシューティングゲーム(アイテム取得処理)[getitem.h]
//Author:佐久間優香
//
//========================================
#ifndef _PLAYER_H_							//このマクロ定義がされていなかったら
#define _PLAYER_H_							//2重インクルード防止のマクロを定義するv

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 posOld;									//位置
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;									//移動量
	D3DXMATRIX mtxWorld;							//ワールドマトリックス
	int nldxShadow;
	bool bUse;											//使用しているかどうか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif