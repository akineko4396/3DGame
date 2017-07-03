#include "main.h"
#include "../GameWorld.h"

void Boss::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//　モデルデータをセット
	m_moChara.SetModel(_gm);
	//　初期の行列設定
	m_mChara = _m;

	//　アニメータを初期化
	m_moChara.InitAnimator(m_aniBoss);
	//　初期アニメ
	m_aniBoss.ChangeAnime_FromName("待機", true);

	//ID設定
	m_CharaId = OBJECT_LIST::ID::BOSS;
}

void Boss::Update()
{
	// 全身のWorldMatを算出
	m_moChara.CalcBoneMatrix_SkipRoot(&m_mChara);

	//アニメーションを進める
	// 正確には、アニメーション情報をもとに、全ボーンの「TransMat」を更新する
	m_aniBoss.Animation(1.0);

	//全ボーンの「WorldMat」を「TransMat」をもとに算出する
	// 実際に描画などで必要なのがこのWorldMatです
	m_moChara.CalcBoneMatrix(&m_mChara);
}

void Boss::Draw()
{
	// SampleShaderクラスで描画する
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}