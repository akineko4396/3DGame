#pragma once

//=======================================
// 火炎放射器クラス
//=======================================
class Flamethrower :public ObjectBase
{
public:

	Flamethrower() { m_ObjId = OBJECT_LIST::ID::FLAMETHROWER; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

	//カメラ処理
	virtual void SetCamera() override {};

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moFlame;
};