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

	SDirectionLight* LightMaker::D_LightMake(CVector4 dir, CVector4 col);

	void LightMaker::D_LightDelete(SDirectionLight* light);

	/// <summary>
	/// �����ɐݒ肵�����C�g�̕�����ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̃|�C���^</param>
	/// <param name="dir">���C�g�̕���</param>
	void LightMaker::D_Light_SetDirection(SDirectionLight* light, CVector4 dir) {
		light->direction = dir;
	}	

	/// <summary>
	/// �����ɐݒ肵�����C�g�̐F��ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̃|�C���^</param>
	/// <param name="col">���C�g�̐F</param>
	void LightMaker::D_Light_SetColer(SDirectionLight* light, CVector4 col) {
		light->color = col;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static LightMaker* LightMaker::GetInstance() {
		return m_instance;
	}

private:
	std::list<SDirectionLight*> m_dLightList; //�f�B���N�V�������C�g�̃��X�g


};

