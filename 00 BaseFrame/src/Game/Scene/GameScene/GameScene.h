#ifndef __GameScene_h__
#define __GameScene_h__

#include "Game/GameCamera.h"

//=========================================================
// ゲームシーンクラス
//=========================================================
class GameScene : public BaseScene{
public:

	// 初期設定関数
	void Init();
	// 解放関数
	void Release();
	// 更新処理
	virtual int Update() override;
	// 描画処理
	virtual void Draw() override;

	// 
	GameScene() {
	}
	// 
	virtual ~GameScene() {
		Release();
	}

public:
	//=========================================================
	// その他データ
	//=========================================================

	// 平行光源
	SPtr<DirLight>	m_DirLight;

	// 平行光源の明るさ
	float			m_LightPower;


};

#endif