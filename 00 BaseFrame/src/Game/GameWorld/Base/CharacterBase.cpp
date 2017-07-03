#include "main.h"
#include "../GameWorld.h"
#include "../Base/CollisionBase.h"

std::vector<SPtr<CharacterBase>> CharacterBase::m_cList;

// 全ての描画を行う
void CharacterBase::AllUpdate()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		m_cList[ec]->Update();
	}
}

// 全ての描画を行う
void CharacterBase::AllDraw()
{
	for (UINT ec = 0; ec < m_cList.size(); ec++)
	{
		//メッシュ数ぶんループ
		for (UINT i = 0; i < m_cList[ec]->GetModel().GetGameModel()->GetModelTbl().size(); i++) {
			//YsSingleModelからメッシュを取得
			SPtr<YsSingleModel> model = m_cList[ec]->GetModel().GetGameModel()->GetModelTbl()[i];
			SPtr<YsMesh> mesh = model->GetMesh();

			//視錘台で描画判定
			if (CheckViewFrustum(m_cList[ec], mesh)) {
				m_cList[ec]->Draw();
			}
		}
	}
}

void CharacterBase::FullClear()
{
	m_cList.clear();
}

// キルフラグを調べて立っていたらリストから消す
void CharacterBase::CheckKillFlg()
{
	std::vector<SPtr<CharacterBase>>::iterator it = m_cList.begin();
	while (it != m_cList.end())
	{
		if ((*it)->GetKillFlg() == 1)
		{
			*it = nullptr;
			it = m_cList.erase(it);
		}
		else{
			it++;
		}
	}
}