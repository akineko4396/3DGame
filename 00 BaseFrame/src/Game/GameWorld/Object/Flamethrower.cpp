#include "main.h"
#include "../GameWorld.h"


void Flamethrower::Init()
{
	//メッシュ読み込み
	//m_gmObj = YsDx.GetResStg()->LoadMesh("");

	// ステージマップをセット
	m_moFlame.SetModel(m_gmObj);

	//　初期の行列設定
	m_mObj.CreateMove(m_vPos);
	//　初期のサイズ
	m_mObj.Scale_Local(m_vScale);
	//　初期の回転量
	m_mObj.RotateY_Local(m_vAngle.y);
	m_mObj.RotateX_Local(m_vAngle.x);
	m_mObj.RotateZ_Local(m_vAngle.z);
	//m_mObj.Scale_Normal(5.0f, 5.0f, 5.0f);
}

void Flamethrower::Update()
{

}

void Flamethrower::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moFlame, &m_mObj);
}
