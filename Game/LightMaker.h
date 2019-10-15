#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"

//IGameObject���p�����Ă���̂ŊJ�n����NewGO���Ă��������ˁ`

/// <summary>
/// ���C�g��邭��
/// </summary>
class LightMaker : public IGameObject
{
	static LightMaker* m_instance;
public:
	LightMaker();
	~LightMaker();
	void Update()override;
	void Render()override;

	void LightMaker::D_LightMake(int lightNo, CVector4 dir, CVector4 col);

	void LightMaker::D_LightDelete(int lightNo);

	/// <summary>
	/// �����ɐݒ肵�����C�g�̕�����ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̏ꏊ</param>
	/// <param name="dir">���C�g�̕���</param>
	void LightMaker::D_Light_SetDirection(int lightNo, CVector4 dir) {
		m_light.direction[lightNo] = dir;
	}

	/// <summary>
	/// �����ɐݒ肵�����C�g�̐F��ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̏ꏊ</param>
	/// <param name="col">���C�g�̐F</param>
	void LightMaker::D_Light_SetColer(int lightNo, CVector4 col) {
		m_light.color[lightNo] = col;
	}

	/// <summary>
	/// �f�B���N�V�������C�g�L���t���O��Ԃ�
	/// </summary>
	/// <returns>�t���O</returns>
	bool Get_D_LightFlag() {
		return m_lightFlag_D;
	}

	/// <summary>
	/// �f�B���N�V�������C�g�L���t���O���Z�b�g
	/// </summary>
	/// <param name="flag">�t���O</param>
	void Set_D_LightFlag(bool flag) {
		m_lightFlag_D = flag;
	}

	/// <summary>
	/// �������Z�b�g����
	/// </summary>
	/// <param name="color">����</param>
	void SetAmbientColor(CVector3 color) {
		m_ambientColor = color;
	}

	/// <summary>
	/// ������Ԃ�
	/// </summary>
	/// <returns>����</returns>
	CVector3 GetAmbientColor() {
		return m_ambientColor;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static LightMaker* LightMaker::GetInstance() {
		return m_instance;
	}

private:
	SDirectionLight m_light;
	bool m_lightFlag_D = false;

	CVector3 m_ambientColor = { 0.4f,0.4f,0.4f };	//�����̐F

};
