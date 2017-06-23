#pragma once

//=======================================
// 大砲クラス
//=======================================
class Cannon :public CharacterBase
{
public:

	//初期設定
	void Init(YsMatrix& _m, SPtr<YsGameModel>& _gm);

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

	//カメラ処理
	virtual void SetCamera() override {};
};