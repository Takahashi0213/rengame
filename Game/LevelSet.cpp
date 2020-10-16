#include "stdafx.h"
#include "LevelSet.h"

//�܂Ƃ߂�
#include "IncludeHeader.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

LevelSet::~LevelSet()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

void LevelSet::Init(const wchar_t* LEVEL_Name) {

	//���x���̗v�f�����擾�i���x�����̂��������݂��邩�j
	int Size = Level_Data.GetLevelDataSize();
	int i = 0;	//�z��Z�b�g�p

	//�ǂ̃��x�����`�F�b�N���邽�߂̃��[�v
	for (int i = 0; i < Size; i++) {
		//��v����ꍇ�����Ɍ��肷��
		if ( wcscmp(Level_Data.GetLevelName(i), LEVEL_Name) == 0) {
			m_levelNo = i;	//���O�����c���Ȃ��I
			break;
		}
	}

	//���x��No��n��
	GameData::GetInstance()->SetNowMapLevel(m_levelNo);

	//���x���ǂݍ��݂܂��܂��܂���
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//�܂��̓I�u�W�F�N�gNo������
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//����
		NewObj(objData, ObjectTag);
		//�z��ɓo�^
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			Level_Data.GetObjectName(m_levelNo, ObjNo),
			Level_Data.GetObject_LinkObj(m_levelNo, ObjNo) };

		//����ʒu��1������
		i++;

		return false;
	});

	//�����N���܂�
	LinkObj(m_levelNo,i);

}

void LevelSet::NewObj(LevelObjectData& data, LevelData::Obj_Tag tag) {

	//�|�C���^�̖��O��pt�œ���
	if (tag == LevelData::Obj_Tag::Tag_Switch) {	//�X�C�b�`
		Switch* pt = CGameObjectManager::GetInstance()->NewGO<Switch>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {	//�h�A
		Door* pt = CGameObjectManager::GetInstance()->NewGO<Door>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->GetSkinModelRender()->SetUp(pt->GetPosition(), pt->GetRotation(), pt->GetScale());
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//�e�X�g�G�l�~�[
		TestEnemy* pt = CGameObjectManager::GetInstance()->NewGO<TestEnemy>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}

	if (tag == LevelData::Obj_Tag::Tag_Jewel) {	//�W���G��
		StarMoney* pt = CGameObjectManager::GetInstance()->NewGO<StarMoney>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}
}

void LevelSet::LinkObj(int levelNo, int i) {

	//�I�u�W�F�N�g�z��̗v�f�������[�v����
	for (int ii = 0; ii < i; ii++) {

		//���Ȃ܂���
		const wchar_t* nowObjName = m_Obj_Data[ii].ObjName;
		const wchar_t* linkObjName = m_Obj_Data[ii].LinkObjName;
		LevelData::Obj_Tag NowObjTag = m_Obj_Data[ii].ObjTag;

		//�����N�I�u�W�F�N�g���Ȃ��Ȃ�X�L�b�v
		if (wcscmp(linkObjName, L"") != 0) {

			//�������N�I�u�W�F�N�g��T���Ēǉ�����
			int ObjNo = Level_Data.ObjName_Search(levelNo, linkObjName);
			LevelData::Obj_Tag LinkObjTag = Level_Data.GetObjectTag(levelNo, ObjNo);

			//�I�u�W�F�N�g�^�O�ŕ���
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Door) {	//�h�A

				//�����Ă�I�u�W�F�N�g
				int now_hash = Hash::MakeHash(nowObjName);
				ObjectClass* now_objClass;
				if (NowObjTag == LevelData::Obj_Tag::Tag_Switch) {
					Switch* NowObj = CGameObjectManager::GetInstance()->FindGO<Switch>(now_hash);
					now_objClass = NowObj->GetInstance();
				}
				if (NowObjTag == LevelData::Obj_Tag::Tag_Test_Enemy) {
					TestEnemy* NowObj = CGameObjectManager::GetInstance()->FindGO<TestEnemy>(now_hash);
					now_objClass = NowObj->GetInstance();
				}

				//�����N�I�u�W�F�N�g
				int link_hash = Hash::MakeHash(linkObjName);
				Door* door = CGameObjectManager::GetInstance()->FindGO<Door>(link_hash);
				//ObjectClass* link_objClass = door->GetInstance();
				door->SetLinkObj(now_objClass);
			}

		}

	}

}