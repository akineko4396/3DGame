#include "main.h"
#include "../GameWorld.h"

void Player::Init()
{
	//　モデル読み込み
	m_gmObj=APP.m_ResStg.LoadMesh("data/model/Hackadoll_1/model.xed");
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
	m_aniPla.ChangeAnime_FromName("立ち", true);
}

void Player::Update()
{

	// 作業用変数
	/*static float		JUMP_POWER;			//ジャンプ力
	const static float	GRAVITY = 0.1f;			//重力
	static YsVec3		Pos;				//プレイヤーY座標一時保存用
	static float		prev;				//ジャンプしたときの座標保存用
	static bool			JFlg = false;		//ジャンプしているかのフラグ*/

	//===========================================================
	// 移動処理
	//===========================================================
	if (INPUT.KeyCheck('W'))m_mObj.Move_Local(0.0f, 0.0f, 0.1f);
	if (INPUT.KeyCheck('S'))m_mObj.Move_Local(0.0f, 0.0f, -0.1f);
	if (INPUT.KeyCheck('A'))m_mObj.Move_Local(-0.1f, 0.0f, 0.0f);
	if (INPUT.KeyCheck('D'))m_mObj.Move_Local(0.1f, 0.0f, 0.0f);

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
}

void Player::Draw()
{
	// SampleShaderクラスで描画する
	ShMgr.m_Samp.DrawModel(m_moPla, &m_mObj);

	////=======================================
	//// 武器描画
	////=======================================
	//auto bone = m_moPla.SearchBone("RHandPoint");		//ボーン検索
	//if (bone){		//ボーン発見
	//	// ボーン	の行列を使って、武器を描画
	//	ShMgr.m_Samp.DrawModel(m_moKatana, &bone->WorldMat);
	//}

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