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
	m_levelNo = -1;		//������
	//�S��������
	for (int j = 0; j < MAX_LEVEL_OBJ; j++) {
		m_Obj_Data[j] = {};
	}

	//�ǂ̃��x�����`�F�b�N���邽�߂̃��[�v
	for (int j = 0; j < Size; j++) {
		//��v����ꍇ�����Ɍ��肷��
		if ( wcscmp(Level_Data.GetLevelName(j), LEVEL_Name) == 0) {
			m_levelNo = j;	//���O�����c���Ȃ��I
			break;
		}
	}
	//�G���[�`�F�b�N
	if (m_levelNo == -1) {
		//�ǂ�ɂ������������Ă��Ȃ����߃G���[
		std::abort();
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
		
		return true;
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

	if (tag == LevelData::Obj_Tag::Tag_Board) {	//�Ŕ�
		Board* pt = CGameObjectManager::GetInstance()->NewGO<Board>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetBoardMessage(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {	//�S�[�X�g�{�b�N�X�c�ړ�
		//const wchar_t* hoge = Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo);	//�e�X�g���b�Z�[�W
		GhostBox* pt = CGameObjectManager::GetInstance()->NewGO<GhostBox>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->CreateGhost();
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetPlayerMoveTarget(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
	}
	if (tag == LevelData::Obj_Tag::Tag_StaticBox) {	//�X�^�e�B�b�N�{�b�N�X
		StaticBox* pt = CGameObjectManager::GetInstance()->NewGO<StaticBox>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->CreateStaticBox();
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

				//�����ɒǉ�����I�u�W�F�N�g�͑��̃I�u�W�F�N�g�Ɂu�����鑤�v�ł�
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

void LevelSet::LevelDelete() {

	//�S�������A���h�폜�ł���I
	for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
		if (wcscmp(m_Obj_Data[i].ObjName, L"") == 0) {
			//���O���Ȃ��I�����I��
			break;
		}
		else {
			//�������ď���
			LevelData::Obj_Tag tag = m_Obj_Data[i].ObjTag;
			//�폜���
			if (tag == LevelData::Obj_Tag::Tag_Switch) {
				Switch* pt = CGameObjectManager::GetInstance()->FindGO<Switch>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Door) {
				Door* pt = CGameObjectManager::GetInstance()->FindGO<Door>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {
				TestEnemy* pt = CGameObjectManager::GetInstance()->FindGO<TestEnemy>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Jewel) {
				StarMoney* pt = CGameObjectManager::GetInstance()->FindGO<StarMoney>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Board) {
				Board* pt = CGameObjectManager::GetInstance()->FindGO<Board>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {
				GhostBox* pt = CGameObjectManager::GetInstance()->FindGO<GhostBox>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_StaticBox) {
				StaticBox* pt = CGameObjectManager::GetInstance()->FindGO<StaticBox>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}


		}
	}

}