#pragma once

//====================================
// プレイヤークラス
//====================================
class Player :public CharacterBase
{
public: 

	Player(){
		m_Id = PLAYER;
	}

	//初期化設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// モデルオブジェクタ（キャラクタ）
	YsModelObject	m_moPla;

	// アニメーター
	YsAnimator		m_aniPla;

};