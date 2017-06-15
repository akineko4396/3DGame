#include "main.h"
#include "../GameWorld.h"


void BeltConveyor::Init()
{
	//���b�V���ǂݍ���
	//m_gmObj = YsDx.GetResStg()->LoadMesh("data/model/Belt/belt.x");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moBelt.SetModel(m_gmObj);

	//�@�����̍s��ݒ�
	m_mObj.CreateMove(m_vPos);
	//�@�����̃T�C�Y
	m_mObj.Scale_Local(m_vScale);
	//�@�����̉�]��
	m_mObj.RotateY_Local(m_vAngle.y);
	m_mObj.RotateX_Local(m_vAngle.x);
	m_mObj.RotateZ_Local(m_vAngle.z);
	//m_mObj.Scale_Normal(5.0f, 5.0f, 5.0f);
}

void BeltConveyor::Update()
{

}

void BeltConveyor::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moBelt, &m_mObj);
}
