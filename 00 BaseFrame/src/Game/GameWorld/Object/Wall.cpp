#include "main.h"
#include "../GameWorld.h"


void Wall::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//メッシュ読み込み
	//m_gmChara = YsDx.GetResStg()->LoadMesh("");

	// ステージマップをセット
	m_moChara.SetModel(_gm);

	//　初期の行列設定
	m_mChara = _m;

	//ID設定
	m_CharaId = OBJECT_LIST::ID::WALL;
}

void Wall::Update()
{

}

void Wall::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
