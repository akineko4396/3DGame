#pragma once

//===================================
// �A�[���N���X
//===================================
class Arm :public ObjectBase {
public:

	Arm() { m_ObjId = OBJECT_LIST::ID::ARM; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

	//�J��������
	virtual void SetCamera() override {};

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moArm;
};