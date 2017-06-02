#pragma once

//===================================
// アームクラス
//===================================
class Arm :public ObjectBase {
public:

	Arm() { m_ObjId = OBJECT_LIST::ID::ARM; }

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
	YsModelObject		m_moArm;
};