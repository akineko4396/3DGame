#pragma once

//===================================
// ブリッジクラス
//===================================
class Bridge :public ObjectBase {
public:

	Bridge() { m_ObjId = OBJECT_LIST::ID::BRIDGE; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moBridge;
};