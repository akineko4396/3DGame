#include "main.h"
#include "../GameWorld.h"

void Ground::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//���b�V���ǂݍ���
	//m_gmChara = YsDx.GetResStg()->LoadMesh("data/model/map/map.x");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moChara.SetModel(_gm);

	//�@�����̍s��ݒ�
	m_mChara = _m;

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::GROUND;
}

void Ground::Update()
{

}

void Ground::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
