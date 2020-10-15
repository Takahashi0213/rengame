#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

class Board : public IGameObject, public ObjectClass
{
public:
	Board();
	~Board();
	void Update()override;
	void Render()override;

	/// <summary>
	/// 看板の内容を設定したり取得したり
	/// </summary>
	void SetBoardMessage(wchar_t* message) {
		Message = message;
	}
	const wchar_t* GetBoardMessage() const {
		return Message;
	}

private:
	SkinModelRender * m_model;	//もで〜〜る

	wchar_t* Message = L"";		//看板の内容

};

