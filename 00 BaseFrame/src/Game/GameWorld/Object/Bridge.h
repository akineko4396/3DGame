#pragma once

//===================================
// �u���b�W�N���X
//===================================
class Bridge :public ObjectBase {
public:

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
	YsModelObject		m_moBridge;
};