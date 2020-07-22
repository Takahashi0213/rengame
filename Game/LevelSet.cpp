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

	//���x���ǂݍ��݂܂��܂��܂���
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//�܂��̓I�u�W�F�N�gNo������
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//����
		NewObj(objData, ObjectTag);
		//�z��ɓo�^�i�����ɃL���X�g���Ă邯�Ǒ��v���͓�ł��j
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			(wchar_t)Level_Data.GetObjectName(m_levelNo, ObjNo),
			(wchar_t)Level_Data.GetObject_LinkObj(m_levelNo, ObjNo) };

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
		auto* pt = CGameObjectManager::GetInstance()->NewGO<Switch>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {	//�h�A
		auto* pt = CGameObjectManager::GetInstance()->NewGO<Door>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//�e�X�g�G�l�~�[
		auto* pt = CGameObjectManager::GetInstance()->NewGO<TestEnemy>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

}

void LevelSet::LinkObj(int levelNo, int i) {

	//�I�u�W�F�N�g�z��̗v�f�������[�v����
	for (int ii = 0; ii < i; ii++) {

		//���Ȃ܂���
		const wchar_t* linkObjName = m_Obj_Data[i].LinkObjName;

		//�����N�I�u�W�F�N�g���Ȃ��Ȃ�X�L�b�v
		if (linkObjName == L"") {
			break;
		}

		//�������N�I�u�W�F�N�g��T���Ēǉ�����
		int ObjNo = Level_Data.ObjName_Search(levelNo, linkObjName);
		int hoge=0;

	}

}