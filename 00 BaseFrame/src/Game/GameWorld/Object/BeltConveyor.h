#pragma once

//=======================================
// �x���g�R���x�A�[���b�V���N���X
//=======================================
class BeltConveyor :public ObjectBase
{
public:

	BeltConveyor() { m_ObjId = OBJECT_LIST::ID::ARM; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moBelt;
};