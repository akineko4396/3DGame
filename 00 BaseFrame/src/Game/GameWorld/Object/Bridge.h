#pragma once

//===================================
// �u���b�W�N���X
//===================================
class Bridge :public ObjectBase {
public:

	Bridge() { m_ObjId = OBJECT_LIST::ID::BRIDGE; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moBridge;
};