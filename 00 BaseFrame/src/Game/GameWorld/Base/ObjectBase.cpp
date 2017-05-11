#include "main.h"
#include "../GameWorld.h"

std::vector<SPtr<ObjectBase>> ObjectBase::m_oList;

// 全ての描画を行う
void ObjectBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		m_oList[ec]->Update();
	}
}

// 全ての描画を行う
void ObjectBase::AllDraw()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		m_oList[ec]->Draw();
	}
}

// リストの全消去
void ObjectBase::FullClear()
{
	for (UINT ec = 0; ec < m_oList.size(); ec++)
	{
		//delete m_oList[ec];
		m_oList[ec] = nullptr;
	}
	m_oList.clear();
}

// キルフラグを調べて立っていたらリストから消す
void ObjectBase::CheckKillFlg()
{
	std::vector<SPtr<ObjectBase>>::iterator it = m_oList.begin();
	while (it != m_oList.end())
	{
		//例外設定
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

//オブジェクト情報を返す
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