#pragma once

//=======================================
// プレス機クラス
//=======================================
class Press :public ObjectBase
{
public:

	Press() { m_ObjId = OBJECT_LIST::ID::PRESS; }

	//初期設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

private:

	// ステージマップオブジェクタ
	YsModelObject		m_moPress;
};