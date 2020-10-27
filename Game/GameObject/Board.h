#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

class Board : public ObjectClass
{
public:
	Board();
	~Board();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �Ŕ̓��e��ݒ肵����擾������
	/// </summary>
	void SetBoardMessage(const wchar_t* message) {
		Message = message;
	}
	const wchar_t* GetBoardMessage() const {
		return Message;
	}

private:
	SkinModel m_model;					//���f��
	const wchar_t* Message = L"";		//�Ŕ̓��e
	//�萔
	const float BoardRange = 300.0f;	//���ׂ���͈�

};
