#pragma once

//=======================================
// �ǃN���X
//=======================================
class Wall :public ObjectBase
{
public:

	Wall() { m_ObjId = OBJECT_LIST::ID::WALL; }

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
	YsModelObject		m_moWall;
};