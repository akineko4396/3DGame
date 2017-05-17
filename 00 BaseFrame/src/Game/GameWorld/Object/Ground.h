#pragma once

//=======================================
// 仮の地形クラス
//=======================================
class Ground :public ObjectBase
{
public:

	Ground() { m_ObjId = OBJECT_LIST::ID::GROUND; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moMap;
};