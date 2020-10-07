#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

class Board : public IGameObject, public ObjectClass
{
public:
	Board();
	~Board();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �Ŕ̓��e��ݒ肵����擾������
	/// </summary>
	void SetBoardMessage(wchar_t* message) {
		Message = message;
	}
	const wchar_t* GetBoardMessage() const {
		return Message;
	}

private:
	SkinModelRender * m_model;	//���Ł`�`��

	wchar_t* Message = L"";		//�Ŕ̓��e

};

