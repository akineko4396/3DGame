#pragma once

//前方宣言
class BasePlayerAS;

//====================================
// プレイヤークラス
//====================================
class Player :public ObjectBase
{
public: 

	Player() { m_ObjId = OBJECT_LIST::ID::PLAYER;}

	//初期化設定
	void Init();

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() override;

	//行列更新
	void UpdateMatrix();

	//座標移動
	void MovePosition(YsVec3& _ToVec);

	//カメラ処理
	virtual void SetCamera() override;

	//カメラの情報をとってくる
	inline GameCamera GetCam() { return m_Cam; }
	

private:

	//モデルデータ
	YsModelObject	m_moPla;

	// アニメーター
	YsAnimator		m_aniPla;

	//ハンマー
	YsModelObject	m_moHammer;
	YsMatrix			m_mHammer;
	
	// 行動ごとに変化するアクションステート
	SPtr<BasePlayerAS> m_ActionState;

	//内積用の角度
	float				m_NormalAngleY;

	//----------------------------------
	// カメラ関係
	//----------------------------------
	int m_CameraEffectCnt = 0; // カメラ演出カウント
	GameCamera m_Cam; // カメラ 移動の基準にもなる

public:

	//移動量
	YsVec3			m_vMove;

	int m_SkyFlag = 0; // 0:地上 1:空中
};

//======================================
//Playerアクション基本クラス
//======================================
class BasePlayerAS
{
public:
	virtual ~BasePlayerAS(){}
	//毎回実行される
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state){}
};

//======================================
//「待機」状態
//======================================
class PlayerAS_Wait:public BasePlayerAS
{
public:
	//毎回実行される
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//「走る」状態
//======================================
class PlayerAS_Run:public BasePlayerAS
{
public:
	//毎回実行される
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//======================================
//「攻撃」状態
//======================================
class PlayerAS_Attack:public BasePlayerAS
{
public:
	//毎回実行される
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};

//=====================================

//=====================================================
// 汎用行動
// アニメーションが終了したら「立ち」に戻るだけ
//=====================================================
class PlayerAS_Generic : public BasePlayerAS 
{
public:
	// 毎回実行される
	virtual void Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state) override;
};