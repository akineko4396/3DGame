#pragma once

//=======================================
// ���Ί�N���X
//=======================================
class Sling :public ObjectBase
{
public:

	Sling() { m_ObjId = OBJECT_LIST::ID::SLING; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moSling;
};