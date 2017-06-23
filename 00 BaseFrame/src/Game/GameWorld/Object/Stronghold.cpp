#include "main.h"
#include "../GameWorld.h"


void Stronghold::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//���b�V���ǂݍ���
	//m_gmChara = YsDx.GetResStg()->LoadMesh("");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moChara.SetModel(_gm);

	//�@�����̍s��ݒ�
	m_mChara = _m;

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::STRONGHOLD;
}

void Stronghold::Update()
{

}

void Stronghold::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
