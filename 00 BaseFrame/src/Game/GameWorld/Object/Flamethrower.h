#pragma once

//=======================================
// �Ή����ˊ�N���X
//=======================================
class Flamethrower :public ObjectBase
{
public:

	Flamethrower() { m_ObjId = OBJECT_LIST::ID::FLAMETHROWER; }

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
	YsModelObject		m_moFlame;
};