#pragma once

//=======================================
// ベルトコンベアーメッシュクラス
//=======================================
class BeltConveyor :public ObjectBase
{
public:

	BeltConveyor() { m_ObjId = OBJECT_LIST::ID::BELT; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moBelt;
};