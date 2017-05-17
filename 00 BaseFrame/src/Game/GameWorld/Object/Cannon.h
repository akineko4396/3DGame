#pragma once

//=======================================
// 大砲クラス
//=======================================
class Cannon :public ObjectBase
{
public:

	Cannon() { m_ObjId = OBJECT_LIST::ID::CANNON; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moCannon;
};