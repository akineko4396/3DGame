#pragma once

//=======================================
// ���̒n�`�N���X
//=======================================
class Ground :public ObjectBase
{
public:

	Ground() { m_ObjId = OBJECT_LIST::ID::GROUND; }

	//�����ݒ�
	void Init();

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:

	// �X�e�[�W�}�b�v�I�u�W�F�N�^
	YsModelObject		m_moMap;
};