#include "main.h"
#include "../GameWorld.h"

std::vector<SPtr<CharacterBase>> CharacterBase::m_cList;

// �S�Ă̕`����s��
void CharacterBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		m_cList[ec]->Update();
	}
}

// �S�Ă̕`����s��
void CharacterBase::AllDraw()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		m_cList[ec]->Draw();
	}
}

// ���X�g�̑S����
void CharacterBase::FullClear()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		//delete m_cList[ec];
		m_cList[ec] = nullptr;
	}
	m_cList.clear();
}

// �L���t���O�𒲂ׂė����Ă����烊�X�g�������
void CharacterBase::CheckKillFlg()
{
	std::vector<SPtr<CharacterBase>>::iterator it = m_cList.begin();
	while (it != m_cList.end())
	{
		if ((*it)->GetId() == PLAYER)
		{
			it++;
			continue;
		}
		if ((*it)->GetKillFlg() == 1)
		{
			*it = NULL;
			it = m_cList.erase(it);
		}
		else{
			it++;
		}
	}
}

//�I�u�W�F�N�g����Ԃ�
SPtr<CharacterBase> CharacterBase::GetThisCharacter(int _id)
{

	for (UINT ec = 0; ec < m_cList.size(); ec++){

		if (m_cList[ec]->GetId() == _id)
		{
			return m_cList[ec];
		}

	}

	return nullptr;

}