#pragma once



//====================================
// �{�X�N���X
//====================================
class Boss : public CharacterBase
{
public:

	//�������ݒ�
	void Init(YsMatrix& _m, SPtr<YsGameModel>& _gm);

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() override;

private:
	// �A�j���[�^�[
	YsAnimator		m_aniBoss;
};