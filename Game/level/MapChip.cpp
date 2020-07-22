#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"

MapChip::MapChip(const LevelObjectData& objData)
{
	wchar_t filePath[256];
	wchar_t filePath_Dummy[256];	//�؂�o�����߂̂���
	wchar_t nomChar[11] = L"0123456789";	//������؂�o�����߁A�����������ɂ܂Ƃ߂Ă���

	swprintf_s(filePath_Dummy, L"Assets/modelData/%s.cmo", objData.name);

	//���������؂�o�� ���ǉ�
	//const wchar_t* text = nullptr;
	//text = filePath_Dummy.c_str();

	int len = (int)wcslen(filePath_Dummy);	//���������擾
	int t = 0;		//�������R�s�[����ۂ̑����ԍ�
	for (int i=0; i < len; i++) {

		//�����ȊO�Ȃ�R�s�y
		bool HitFlag = false;
		for (int s = 0; s < 10; s++) {
			if (filePath_Dummy[i] == nomChar[s]) {
				//�ꏏ�Ȃ�t���O�������
				HitFlag = true;
			}
		}

		//�����q�b�g���Ă���Ȃ�΃R�s�[�͎��s���Ȃ�
		if (HitFlag == false) {
			filePath[t] = filePath_Dummy[i];
			t++;
		}
		
	}
	filePath[t] = L'\0';

	m_model.Init(filePath);
	m_model.UpdateWorldMatrix(objData.position, objData.rotation, CVector3::One());
	//�ÓI�����I�u�W�F�N�g�����b�V���R���C�_�[����쐬����B
	m_physicsStaticObject.CreateMeshObject(m_model, objData.position, objData.rotation);
}

void MapChip::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}