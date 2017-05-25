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
	m_mObj.Scale(m_vScale);
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
	m_aniPla.AnimationAndScript(1.0, scriptProc, &m_Mat);
	// 全身のWorldMatを算出
	m_moPla.CalcBoneMatrix_SkipRoot(&m_mObj);

	// 作業用変数
	/*static float		JUMP_POWER;			//ジャンプ力
	const static float	GRAVITY = 0.1f;			//重力
	static YsVec3		Pos;				//プレイヤーY座標一時保存用
	static float		prev;				//ジャンプしたときの座標保存用
	static bool			JFlg = false;		//ジャンプしているかのフラグ*/

	//入力コンポーネント処理
	if (m_Controller) {
		m_Keys = m_Controller->Update();
	}

	if (m_Keys&GK_LLEFT) {
		m_mObj.Move_Local(-0.3f, 0.0f, 0.0f);
	}
	if (m_Keys&GK_LUP) {
		m_mObj.Move_Local(0.0f, 0.0f, 0.3f);
	}
	if (m_Keys&GK_LRIGHT) {
		m_mObj.Move_Local(0.3f, 0.0f, 0.0f);
	}
	if (m_Keys&GK_LDOWN) {
		m_mObj.Move_Local(0.0f, 0.0f, -0.3f);
	}

	if (m_ActionState) {
		auto p = m_ActionState;
		m_ActionState->Update(*this, m_aniPla, m_ActionState);
	}

	//===========================================================
	// ジャンプ処理
	//===========================================================
	/*if (INPUT.KeyCheck(VK_SPACE) && !JFlg){
		JFlg = true;
		JUMP_POWER = 1;
		Pos = m_mObj.GetPos();
		prev = Pos.y;
	}
	if (JFlg){
		if (Pos.y >= prev){
			JUMP_POWER -= GRAVITY;
			Pos.y += JUMP_POWER;
		}
		else {
			JFlg = false;
			Pos.y = prev;
		}
		m_mObj.Move_Local(0.0f, Pos.y, 0.0f);
	}*/

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

//=====================================================
// 「待機」状態
//=====================================================
void PlayerAS_Wait::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// 方向キー
	if (Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("走り", 0, 10, true);
		// 行動切り替え
		SPtr<PlayerAS_Run> p = std::make_shared<PlayerAS_Run>();
		state=p;
		return;
	}
	// マウス左クリック
	if (INPUT.MouseCheck_Enter(INPUT.MOUSE_L)) {
		//アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("攻撃", 0, 10, false);
		// 行動切り替え
		SPtr<PlayerAS_Attack> p = std::make_shared<PlayerAS_Attack>();
		state=p;
		return;
	}
}
//=====================================================
// 「走り」状態
//=====================================================
void PlayerAS_Run::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	// 移動キーを押してる？
	if (!(Player.GetKeys() & GK_LUP || Player.GetKeys() & GK_LLEFT || Player.GetKeys() & GK_LRIGHT || Player.GetKeys() & GK_LDOWN)) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
	// アニメ速度を移動速度にする
	//float RunSpeed = (float)Player.GetAnim().GetAnimeSpeed() * 0.05f;
	//Player.m_Mat.Move_Local(0, 0, RunSpeed);

}
//=====================================================
//	「攻撃」状態
//=====================================================
void PlayerAS_Attack::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (!INPUT.MouseCheck_Enter(INPUT.MOUSE_L) && anime.IsAnimationEnd()) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
}
//=====================================================
// 汎用行動
//=====================================================
void PlayerAS_Generic::Update(Player& Player, YsAnimator& anime, SPtr<BasePlayerAS>& state)
{
	if (anime.IsAnimationEnd()) {
		// アニメ切り替え
		anime.ChangeAnimeSmooth_FromName("待機", 0, 10, true);
		// 行動切り替え
		SPtr<PlayerAS_Wait> p = std::make_shared<PlayerAS_Wait>();
		state=p;
		return;
	}
}