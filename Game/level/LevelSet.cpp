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

	//���x���ǂݍ��݂܂�
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//�܂��̓I�u�W�F�N�gNo������
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//����
		NewObj(objData, ObjectTag);
		//�ȍ~�̃I�u�W�F�N�g�����������ɂ��邽�߂ɖ��O�L�[���쐬���Ă����B
		const wchar_t* objName = Level_Data.GetObjectName(m_levelNo, ObjNo);
		int nameKey = Hash::MakeHash(objName);
		const wchar_t* linkObjeName = Level_Data.GetObject_LinkObj(m_levelNo, ObjNo);
		int linkObjNameKey = 0;// Hash::MakeHash(linkObjeName);
		//�z��ɓo�^
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			objName,
			nameKey,
			linkObjeName,
			linkObjNameKey
		};

		//����ʒu��1������
		i++;
		
		return true;
	});

	//�����N���܂�
	LinkObj(m_levelNo,i);

}
template<class T> 
T* LevelSet::NewObjCommon(const LevelObjectData& data)
{
	T* pt = CGameObjectManager::GetInstance()->NewGO<T>(data.name, 0);
	pt->SetPosition(data.position*10.0f);
	pt->SetRotation(data.rotation);
	pt->SetScale(data.scale*10.0f);
	return pt;
}
void LevelSet::NewObj(LevelObjectData& data, const LevelData::Obj_Tag tag) {


	//�|�C���^�̖��O��pt�œ���
	if (tag == LevelData::Obj_Tag::Tag_Switch) {		//�X�C�b�`
		NewObjCommon<Switch>(data);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {			//�h�A
		Door* pt = NewObjCommon<Door>(data);
		pt->GetSkinModelRender()->SetUp(pt->GetPosition(), pt->GetRotation(), pt->GetScale());
	}
	if (tag == LevelData::Obj_Tag::Tag_BigDoor1) {		//����h�A1
		BigDoor* pt = NewObjCommon<BigDoor>(data);
		pt->ModelChange(BigDoor::DoorModel::Model_BigDoor);
	}
	if (tag == LevelData::Obj_Tag::Tag_BigDoor2) {		//����h�A2
		BigDoor* pt = NewObjCommon<BigDoor>(data);
		pt->ModelChange(BigDoor::DoorModel::Model_BigDoor2);
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//�e�X�g�G�l�~�[
		NewObjCommon<TestEnemy>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Mannequin) {		//�}�l�L��
		NewObjCommon<Mannequin>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Benite) {		//�x�j�e�[
		NewObjCommon<Benite>(data);
	}

	if (tag == LevelData::Obj_Tag::Tag_Jewel) {			//�W���G��
		NewObjCommon<StarMoney>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Key1) {			//��
		Key* pt = NewObjCommon<Key>(data);
		pt->SetItemNo(SceneManager::GetInstance()->GetItemSave()->GetItemData()->ItemNoSearch(L"�����̌�"));
		pt->DataSet();
	}

	if (tag == LevelData::Obj_Tag::Tag_Board) {			//�Ŕ�
		Board* pt = NewObjCommon<Board>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetBoardMessage(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_Torch) {			//����
		Torch* pt = NewObjCommon<Torch>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetTorch(Level_Data.GetObject_BoolMemo(m_levelNo, ObjNo));
		pt->SetHosei(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {	//�S�[�X�g�{�b�N�X�c�ړ�
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetPlayerMoveTarget(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
		pt->SetYazirushiRot(Level_Data.GetObject_FloatMemo(m_levelNo, ObjNo));
		pt->SetYazirushiYHosei(Level_Data.GetObject_FloatMemo2(m_levelNo, ObjNo));
		pt->SetRotFlag(Level_Data.GetObject_BoolMemo(m_levelNo, ObjNo));
		pt->SetGhostBox_System(GhostBox::MapMove);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_GhostBox_Event) {	//�S�[�X�g�{�b�N�X�c�C�x���g
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetGhostBox_System(GhostBox::MapEvent);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_GhostBox_Damage) {	//�S�[�X�g�{�b�N�X�c�_���[�W
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		pt->SetGhostBox_System(GhostBox::DamageZone);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_StaticBox) {			//�X�^�e�B�b�N�{�b�N�X
		StaticBox* pt = NewObjCommon<StaticBox>(data);
		pt->CreateStaticBox();
	}
	if (tag == LevelData::Obj_Tag::Tag_EventObject) {	//�C�x���g�I�u�W�F�N�g
		EventObject* pt = NewObjCommon<EventObject>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetEventName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

}

void LevelSet::LinkObj(const int levelNo, const int i) {

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

			//�����Ă�I�u�W�F�N�g
			int now_hash = m_Obj_Data[ii].nameKey;
			ObjectClass* now_objClass;

			//�����Ŏ擾����I�u�W�F�N�g�͑��̃I�u�W�F�N�g�Ɂu�����鑤�v�ł�
			ObjectClass* NowObj = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(now_hash);
			now_objClass = NowObj->GetInstance();

			//�n�b�V���l���쐬
			int link_hash = Hash::MakeHash(linkObjName);

			//�I�u�W�F�N�g�^�O�ŕ���
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Door) {			//�h�A
				Door* obj = CGameObjectManager::GetInstance()->FindGO<Door>(link_hash);
				obj->SetLinkObj(now_objClass);
			}
			if (LinkObjTag == LevelData::Obj_Tag::Tag_EventObject) {	//�C�x���g�I�u�W�F�N�g
				EventObject* obj = CGameObjectManager::GetInstance()->FindGO<EventObject>(link_hash);
				obj->SetLinkObj(now_objClass);
			}
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Key1) {			//��
				Key* obj = CGameObjectManager::GetInstance()->FindGO<Key>(link_hash);
				obj->SetLinkObj(now_objClass);
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
			ObjectClass* go = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(m_Obj_Data[i].nameKey);
			if (go != nullptr) {
				go->DeleteObject();
			}
		}
	}

}