#include "main.h"
#include "../GameWorld.h"


void Press::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//���b�V���ǂݍ���
	//m_gmChara = YsDx.GetResStg()->LoadMesh("data/model/box/box.x");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moChara.SetModel(_gm);

	//�@�����̍s��ݒ�
	m_mChara = _m;

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::PRESS;
}

void Press::Update()
{

}

void Press::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
