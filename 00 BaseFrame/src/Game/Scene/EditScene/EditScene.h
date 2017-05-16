#pragma once

#include "Game/GameCamera.h"

//=========================================================
// ゲームシーンクラス
//=========================================================
class EditScene : public BaseScene {
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
	EditScene() {
	}
	// 
	virtual ~EditScene() {
		Release();
	}

public:
	//=========================================================
	// その他データ
	//=========================================================

	//=================
	//　カメラ
	//=================
	GameCamera		m_Cam;

	// 平行光源
	SPtr<DirLight>	m_DirLight;

	// 平行光源の明るさ
	float			m_LightPower;


};