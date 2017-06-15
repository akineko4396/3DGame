#include "main.h"
#include "../GameWorld.h"

void Ground::Init()
{
	//���b�V���ǂݍ���
	//m_gmObj = YsDx.GetResStg()->LoadMesh("data/model/map/map.x");

	// �X�e�[�W�}�b�v���Z�b�g
	m_moMap.SetModel(m_gmObj);

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

void Ground::Update()
{

}

void Ground::Draw()
{
	ShMgr.m_Samp.DrawModel(m_moMap, &m_mObj);
}
