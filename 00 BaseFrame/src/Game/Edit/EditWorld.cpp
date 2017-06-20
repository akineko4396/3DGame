#include "main.h"
#include "Data/DataManager.h"
#include "Game\GameWorld\GameWorld.h"
#include "EditWorld.h"

//static�����o�ϐ��̖{��
EditWorld* EditWorld::s_pInst = nullptr;

void EditWorld::Init(int _ObjNum)
{
	//���݂̃I�u�W�F�N�g������
	Obj_Num_Max = _ObjNum;

	//���ڏ�̃��b�V���ǂݍ���
	SPtr<YsGameModel> m_gmEdit = YsDx.GetResStg()->LoadMesh("data/model/StageForEdit/stage.x");
	m_moEdit.SetModel(m_gmEdit);
	m_mEdit.CreateMove(YsVec3(0, 0, 0));
	m_mEdit.Scale_Local(YsVec3(0.01f, 0.01f, 0.01f));
}

void EditWorld::Release()
{

}

void EditWorld::Update()
{
	if (INPUT.KeyCheck_Enter('S')) {
		//�O���̃e�L�X�g�t�@�C���֕ۑ�
		UPtr<DataManager> uDM(new DataManager);
		uDM->CsvDataSave("data/txt/Object.csv", Obj_Num_Max);
	}

}

void EditWorld::Draw()
{
	YsVec3 Vec;
	Vec.Transform(m_Cam.mCam);
	YsVec3 MousePos = YsVec3(INPUT.GetMousePos()->x, INPUT.GetMousePos()->y, 0);
	m_Cam.Convert2Dto3D(MousePos, MousePos);
	ShMgr.m_Samp.DrawLine(MousePos, YsVec3(0,0,0), &YsVec4(1, 1, 1, 1));

	Dw_Static(11, "Pos(%.2f, %.2f, %.2f)", (float)MousePos.x, (float)MousePos.y, Vec.z);
	Dw_Static(12, "CamPos(%.2f, %.2f, %.2f)", Vec.x, Vec.y, Vec.z);

	// �Ƃ肠����XYZ�������`�悵�Ƃ�
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(1, 0, 0), &YsVec4(1, 0, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 1, 0), &YsVec4(0, 1, 0, 1));
	ShMgr.m_Samp.DrawLine(YsVec3(0, 0, 0), YsVec3(0, 0, 1), &YsVec4(0, 0, 1, 1));

	// ��������
	std::string text;
	text = "[�G�f�B�b�g���[�h]\n";
	text += "M:�Q�[���V�[����\n";
	text += "S:�Z�[�u\n";

	// 2D�`��(����)
	YsDx.GetSprite().Begin(true);
	{
		YsDx.GetSprite().DrawFont(text, 1, 1, &YsVec4(0, 0, 0, 1));
		YsDx.GetSprite().DrawFont(text, 0, 0, &YsVec4(1, 1, 1, 1));
	}
	YsDx.GetSprite().End();
}