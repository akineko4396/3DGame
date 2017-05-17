#pragma once

//=======================================
// 投石器クラス
//=======================================
class Sling :public ObjectBase
{
public:

	Sling() { m_ObjId = OBJECT_LIST::ID::SLING; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moSling;
};