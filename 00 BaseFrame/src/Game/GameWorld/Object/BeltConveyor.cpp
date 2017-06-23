#include "main.h"
#include "../GameWorld.h"


void BeltConveyor::Init(YsMatrix& _m, SPtr<YsGameModel>& _gm)
{
	//���b�V���ǂݍ���
	//m_gmChara = YsDx.GetResStg()->LoadMesh("data/model/Belt/belt.x");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moChara.SetModel(_gm);

	//�@�����̍s��ݒ�
	m_mChara = _m;

	//ID�ݒ�
	m_CharaId = OBJECT_LIST::ID::BELTCONVEYOR;
}

void BeltConveyor::Update()
{

}

void BeltConveyor::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moChara, &m_mChara);
}
