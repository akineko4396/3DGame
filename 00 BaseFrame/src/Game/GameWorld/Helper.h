#pragma once

#include "Game\GameWorld\Base\ObjectBase.h"

class Helper {
public:

	/*�I�u�W�F�N�g���Ƃ̃Q�b�^�[-----------------------------------------

	���ꂼ��̃Q�b�^�[�̈�����
	�@���̃I�u�W�F�N�g��ID�Ɠo�^�ԍ������邱�Ƃ�
	 �@���̃I�u�W�F�N�g�̏�񂪕Ԃ�

	---------------------------------------------------------------------------*/
	//�v���C���[
	inline SPtr<ObjectBase> GetObject_Player() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::PLAYER); }

	//�G�l�~�[
	inline SPtr<ObjectBase> GetObject_Enemy(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::ENEMY); }

	//�}�b�v
	inline SPtr<ObjectBase> GetObject_Ground() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::GROUND); }

	//���_
	inline SPtr<ObjectBase> GetObject_Stronghold() { return ObjectBase::GetThisObject(0, OBJECT_LIST::ID::STRONGHOLD); }

	//��
	inline SPtr<ObjectBase> GetObject_Wall(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::WALL); }

	//���Ί�
	inline SPtr<ObjectBase> GetObject_SLING(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::SLING); }

	//��C
	inline SPtr<ObjectBase> GetObject_Cannon(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::CANNON); }

	//�Ή����ˊ�
	inline SPtr<ObjectBase> GetObject_Flamethrower(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::FLAMETHROWER); }

	//�v���X�@
	inline SPtr<ObjectBase> GetObject_Press(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::PRESS); }

	//�A�[��
	inline SPtr<ObjectBase> GetObject_Arm(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::ARM); }

	//�x���g�R���x�A
	inline SPtr<ObjectBase> GetObject_BeltConveyor(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::BELTCONVEYOR); }

	//�u���b�W
	inline SPtr<ObjectBase> GetObject_Bridge(int _num) { return ObjectBase::GetThisObject(_num, OBJECT_LIST::ID::BRIDGE); }

	//�S�ẴI�u�W�F�N�g
	inline SPtr<ObjectBase> GetObject_All(int _num) { return ObjectBase::GetThisObject(_num); }

	//------------------------------------------------------------------
	// �V���O���g��
private:
	Helper() {}
public:
	static Helper& GetInstance()
	{
		static Helper instance;
		return instance;
	}
	//------------------------------------------------------------------
};

#define HELP Helper::GetInstance()