#include "main.h"
#include "../GameWorld.h"

void Player::Init()
{
	//　モデル読み込み
	m_gmObj=APP.m_ResStg.LoadMesh("data/model/Player/Player.xed");
	m_moHammer.LoadMesh("data/model/Hammer/hammer.xed");
	//　モデルデータをセット
	m_moPla.SetModel(m_gmObj);
	//　初期の行列設定
	m_mObj.CreateMove(m_vPos);
	//　初期のサイズ
	m_mObj.Scale_Local(m_vScale);
	//　初期の回転量
	m_mObj.RotateY_Local(m_vAngle.y);
	m_mObj.RotateX_Local(m_vAngle.x);
	m_mObj.RotateZ_Local(m_vAngle.z);

	//　アニメータを初期化
	m_moPla.InitAnimator(m_aniPla);
	//　初期アニメ
	m_aniPla.ChangeAnime_FromName("待機", true);

	// キー入力コンポーネント生成
	SetInput(std::make_shared<KeyInputComponent>()); 

	// アクションステート
	m_ActionState = std::make_shared<PlayerAS_Wait>();

	m_SkyFlag = 0;
	m_CameraEffectCnt = 0;

	// カメラ設定
	m_Cam.Init(0, 0, -3, false); // 少し後ろに引いた位置
	m_Cam.m_BaseMat.CreateMove(0, 1.7f, 0);
	m_Cam.m_BaseMat.SetPos(0, 1.7f, 0); // ベースの位置は、頭くらいの位置
	m_Cam.m_LocalMat.RotateX(15); // 見やすいように少し見下ろす
}

void Player::Update()
{

	// スクリプト関数
	auto scriptProc = [this](YsAnimeKey_Script* scr)
	{
		//ここでアニメーション中に発生するスクリプトを処理する
	};
	// アニメ進行・スクリプト実行
	// スクリプトがある場合は、funcが実行される
	m_aniPla.AnimationAndScript(1.0, scriptProc, &m_mObj);
	// 全身のWorldMatを算出
	m_moPla.CalcBoneMatrix_SkipRoot(&m_mObj);

	//入力コンポーネント処理
	if (m_Controller) {
		m_Keys = m_Controller->Update();
	}

	// カメラ演出カウント
	m_CameraEffectCnt--;
	if (m_CameraEffectCnt < 0)m_CameraEffectCnt = 0;

	POINT* pt = INPUT.GetMouseMoveValue();
	pt->x = pt->x % 360;
	m_Cam.m_BaseMat.RotateY_Local(pt->x*0.5f);

	if (m_ActionState) {
		auto p = m_ActionState;
		m_ActionState->Update(*this, m_aniPla, m_ActionState);
	}

	//アニメーションを進める
	// 正確には、アニメーション情報をもとに、全ボーンの「TransMat」を更新する
	m_aniPla.Animation(1.0);

	/*auto bone = m_moPla.SearchBone("首");
	if (bone){
	bone->TransMat.RotateY_Local(45);
	}*/

	//全ボーンの「WorldMat」を「TransMat」をもとに算出する
	// 実際に描画などで必要なのがこのWorldMatです
	m_moPla.CalcBoneMatrix(&m_mObj);

	//Spaceで次のアニメへ
	/*if (INPUT.KeyCheck_Enter(VK_SPACE)){
	//キャラ１
	int aniNo = m_aniPla.GetAnimeNo();
	aniNo++;
	if (aniNo >= m_aniPla.GetMaxAnimeNum()){
	aniNo = 0;
	}
	m_aniPla.ChangeAnimeSmooth(aniNo, 0, 20, true);
	}*/

	//武器
	{
		auto bone = m_moPla.SearchBone("右手ダミー");
		if (bone) {
			m_mHammer = bone->WorldMat;
		}
	}
	m_moHammer.CalcBoneMatrix(&m_mHammer);
}

void Player::Draw()
{
	// SampleShaderクラスで描画する
	ShMgr.m_Samp.DrawModel(m_moPla, &m_mObj);

	////=======================================
	//// 武器描画
	////=======================================
	ShMgr.m_Samp.DrawModel(m_moHammer, &m_mHammer);

	////=======================================
	//// キャラ１ ボーン名表示
	////=======================================
	//YsDx.GetSprite().Begin(true);
	//for (auto& bn : m_moPla.GetBoneTree()){
	//	// ボーン行列を2D座標へ変換
	//	YsVec3 v2D;
	//	m_Cam.Convert3Dto2D(v2D, bn->WorldMat.GetPos());
	//	if (v2D.z > 0){
	//		YsDx.GetSprite().DrawFont(bn->pSrcBoneNode->BoneName, v2D.x + 1, v2D.y + 1, &YsVec4(0, 0, 0, 1));
	//		YsDx.GetSprite().DrawFont(bn->pSrcBoneNode->BoneName, v2D.x, v2D.y, &YsVec4(1, 1, 1, 1));
	//	}
	//}
	//YsDx.GetSprite().End();
}

//======================
//カメラ処理
//======================
void Player::SetCamera()
{
	//=============================================================
	// 射影行列
	//=============================================================
	m_Cam.SetPerspectiveFovLH(60, (float)YsDx.GetRezoW() / YsDx.GetRezoH(), 0.01f, 1000);
	//=============================================================
	// ビュー行列
	//=============================================================
	// カメラ演出中
	if (m_CameraEffectCnt > 0) {
		auto camBone = m_moPla.SearchBone("Camera");
		if (camBone) {
			m_Cam.mCam = camBone->WorldMat;
		}
	}
	// 通常時
	else {
		// カメラのベース行列に、キャラの座標を加算する
		YsMatrix mChara;
		mChara = m_Cam.m_BaseMat;
		mChara.GetPos() += m_mObj.GetPos();
		// 最終的なカメラ行列を求める
		m_Cam.mCam = m_Cam.m_LocalMat * mChara;
	}
	// カメラ行列からビュー行列作成
	m_Cam.CameraToView();
}

//=====================================================
// 「待機」状態
//=====================================================
void PlayerAS_Wait::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// 方向キー
	if (Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("走り", 0, 10, true, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Run> p = std::make_shared<PlayerAS_Run>();
		state=p;
		return;
	}
	// マウス左クリック
	if (Player.GetKeys() & GK_X) {
		//アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("攻撃", 0, 10, false, 1);
		// 行動切り替え
		SPtr<PlayerAS_Attack> p = std::make_shared<PlayerAS_Attack>();
		state=p;
		return;
	}

	// スペースキー
	if (Player.GetKeys() & GK_A) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("ジャンプ", 0, 10, false, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Jump> p = std::make_shared<PlayerAS_Jump>();
		state = p;
		return;
	}

	//一時計算用行列
	YsMatrix mMat;
	//プレイヤー行列保存
	mMat = Player.GetMatrix();

	// 摩擦
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}*/
	// 力移動
	mMat.Move(Player.m_vMove);

	//プレイヤー行列にセット
	Player.SetMatrix(mMat);
}
//=====================================================
// 「走り」状態
//=====================================================
void PlayerAS_Run::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// 移動キーを押してる？
	if (!(Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN)) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

	//一時計算用行列
	YsMatrix mMat;
	//プレイヤー行列保存
	mMat = Player.GetMatrix();

	// 移動による視点補正
	float rotaAng = 0;
	/*if (Player.GetKeys() & GK_LEFT) {
	rotaAng = -1.0f;
	}
	if (Player.GetKeys() & GK_RIGHT) {
	rotaAng = 1.0f;
	}*/
	if (Player.GetKeys() & GK_LUP) {
		rotaAng *= 0.5f;
	}
	// カメラ回転
	Player.GetCam().m_BaseMat.RotateY_Local(rotaAng);
	// キーによりキャラの向きを回転
	YsVec3 vTar;
	if (Player.GetKeys() & GK_LRIGHT) {
		vTar += Player.GetCam().m_BaseMat.GetXAxis();
	}
	else if (Player.GetKeys() & GK_LLEFT) {
		vTar -= Player.GetCam().m_BaseMat.GetXAxis();
	}
	if (Player.GetKeys() & GK_LUP) {
		vTar += Player.GetCam().m_BaseMat.GetZAxis();
	}
	else if (Player.GetKeys() & GK_LDOWN) {
		vTar -= Player.GetCam().m_BaseMat.GetZAxis();
	}
	vTar.y = 0;
	vTar.Normalize();
	YsVec3 vZ = Player.GetMatrix().GetZAxis();
	vZ.Homing(vTar, 10);
	mMat.SetLookAt(vZ, YsVec3::Up);
	// アニメ速度を移動速度にする
	float walkSpeed = (float)anime.GetAnimeSpeed() * 0.5f;
	mMat.Move_Local(0, 0, walkSpeed);
	// 重力
	//Player.m_vMove.y -= 0.01f;
	// 摩擦
	/*if (Player.m_SkyFlag == 0) {
		Player.m_vMove *= 0.9f;
	}*/
	// 力移動
	mMat.Move(Player.m_vMove);

	//プレイヤー行列にセット
	Player.SetMatrix(mMat);
}
//=====================================================
//	「攻撃」状態
//=====================================================
void PlayerAS_Attack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!(Player.GetKeys() & GK_X) && anime.IsAnimationEnd()) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
		return;
	}
}
//=====================================================
//	「ジャンプ」状態
//=====================================================
void PlayerAS_Jump::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!(Player.GetKeys() & GK_A) && anime.IsAnimationEnd()) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state = p;
		return;
	}

	//一時計算用行列
	YsMatrix mMat;
	//プレイヤー行列保存
	mMat = Player.GetMatrix();

	// 力移動
	mMat.Move(Player.m_vMove);

	//プレイヤー行列にセット
	Player.SetMatrix(mMat);
}
//=====================================================
// 汎用行動
//=====================================================
void PlayerAS_Generic::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true, 0.5);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}

	//一時計算用行列
	YsMatrix mMat;
	//プレイヤー行列保存
	mMat = Player.GetMatrix();

	// 摩擦
	/*if (Player.m_SkyFlag == 0) {
	Player.m_vMove *= 0.9f;
	}*/
	// 力移動
	mMat.Move(Player.m_vMove);

	//プレイヤー行列にセット
	Player.SetMatrix(mMat);
}