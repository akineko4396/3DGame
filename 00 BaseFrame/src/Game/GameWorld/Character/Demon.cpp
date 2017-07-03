#include "main.h"
#include "../GameWorld.h"

void Demon::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//　モデルデータをセット
	m_moChara.SetModel(_gm);
	//　初期の行列設定
	m_mChara = _m;

	//　アニメータを初期化
	m_moChara.InitAnimator(m_aniDe);
	//　初期アニメ
	m_aniDe.ChangeAnime_FromName("歩き", true);

	//ID設定
	m_CharaId = OBJECT_LIST::ID::DEMON;
}

void Demon::Update()
{
	// 全身のWorldMatを算出
	m_moChara.CalcBoneMatrix_SkipRoot(&m_mChara);

	static int cnt = 0;

	switch (cnt) {
	case 200:
		m_aniDe.ChangeAnimeSmooth_FromName("攻撃1", 0, 10, true);
		break;
	case 400:
		m_aniDe.ChangeAnimeSmooth_FromName("攻撃2", 0, 10, true);
		break;
	case 600:
		m_aniDe.ChangeAnimeSmooth_FromName("歩き", 0, 10, true);
		cnt = 0;
		break;
	}
	cnt++;

	//アニメーションを進める
	// 正確には、アニメーション情報をもとに、全ボーンの「TransMat」を更新する
	m_aniDe.Animation(1.0);

	//全ボーンの「WorldMat」を「TransMat」をもとに算出する
	// 実際に描画などで必要なのがこのWorldMatです
	m_moChara.CalcBoneMatrix(&m_mChara);
}

void Demon::Draw()
{
	// SampleShaderクラスで描画する
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}