#pragma once

//=======================================
// ��C�N���X
//=======================================
class Cannon :public ObjectBase
{
public:

	Cannon() { m_ObjId = OBJECT_LIST::ID::CANNON; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moCannon;
};