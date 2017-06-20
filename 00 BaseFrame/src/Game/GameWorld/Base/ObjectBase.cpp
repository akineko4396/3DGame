#include "main.h"
#include "../GameWorld.h"
#include "../Base/CollisionBase.h"

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
		//メッシュ数ぶんループ
		for (UINT i = 0; i < m_oList[ec]->GetModel()->GetModelTbl().size(); i++) {
			//YsSingleModelからメッシュを取得
			SPtr<YsSingleModel> model = m_oList[ec]->GetModel()->GetModelTbl()[i];
			SPtr<YsMesh> mesh = model->GetMesh();

			//視錘台で描画判定
			if (CheckViewFrustum(m_oList[ec], mesh)) {
				m_oList[ec]->Draw();
			}
		}
	}
}

void ObjectBase::FullClear()
{
	m_oList.clear();
}

// キルフラグを調べて立っていたらリストから消す
void ObjectBase::CheckKillFlg()
{
	std::vector<SPtr<ObjectBase>>::iterator it = m_oList.begin();
	while (it != m_oList.end())
	{
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
SPtr<ObjectBase> ObjectBase::GetThisObject(int _Num, int _id)
{
	//オブジェクトの個数分回す
	for (UINT ec = 0; ec < m_oList.size(); ec++){

		//指定されてない場合
		if (_id == OBJECT_LIST::ID::FREE) {
			//指定のオブジェクト登録番号
			if (m_oList[ec]->GetNum() == _Num)
			{
				return m_oList[ec];
			}
		}
		//指定がある場合
		else {
			//指定のオブジェクトID
			if (m_oList[ec]->GetObjId() == _id) {
				//指定のオブジェクト登録番号
				if (m_oList[ec]->GetNum() == _Num)
				{
					return m_oList[ec];
				}

			}
		}

	}

	return nullptr;

}