#pragma once

//=======================================
// �x���g�R���x�A�[�N���X
//=======================================
class BeltConveyor :public CharacterBase
{
public:

	//�����ݒ�
	void Init(YsMatrix& _m, SPtr<YsGameModel>& _gm);

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

	//�J��������
	virtual void SetCamera() override {};
};