#include "main.h"
#include "../GameWorld.h"

std::vector<SPtr<ObjectBase>> ObjectBase::m_oList;

// �S�Ă̕`����s��
void ObjectBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		m_oList[ec]->Update();
	}
}

// �S�Ă̕`����s��
void ObjectBase::AllDraw()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		m_oList[ec]->Draw();
	}
}

// ���X�g�̑S����
void ObjectBase::FullClear()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		//delete m_oList[ec];
		m_oList[ec] = nullptr;
	}
	m_oList.clear();
}

// �L���t���O�𒲂ׂė����Ă����烊�X�g�������
void ObjectBase::CheckKillFlg()
{
	std::vector<SPtr<ObjectBase>>::iterator it = m_oList.begin();
	while (it != m_oList.end())
	{
		//��O�ݒ�
		/*if ((*it)->GetId() == PLAYER)
		{
			it++;
			continue;
		}*/
		if ((*it)->GetKillFlg() == 1)
		{
			*it = NULL;
			it = m_oList.erase(it);
		}
		else{
			it++;
		}
	}
}

//�I�u�W�F�N�g����Ԃ�
SPtr<ObjectBase> ObjectBase::GetThisObject(int _id)
{

	for (UINT ec = 0; ec < m_oList.size(); ec++){

		if (m_oList[ec]->GetId() == _id)
		{
			return m_oList[ec];
		}

	}

	return nullptr;

}