#pragma once


//====================================
// スケルトンクラス
//====================================
class Skeleton : public CharacterBase
{
public:
	//初期化設定
	void Init(YsMatrix& _m, SPtr<YsGameModel>& _gm);

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:
	// アニメーター
	YsAnimator		m_aniSke;
};