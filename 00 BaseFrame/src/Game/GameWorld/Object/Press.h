#pragma once

//=======================================
// �v���X�@�N���X
//=======================================
class Press :public ObjectBase
{
public:

	Press() { m_ObjId = OBJECT_LIST::ID::PRESS; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moPress;
};