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
	/// 看板の内容を設定したり取得したり
	/// </summary>
	void SetBoardMessage(const wchar_t* message) {
		Message = message;
	}
	const wchar_t* GetBoardMessage() const {
		return Message;
	}

private:
	SkinModel m_model;					//モデル
	const wchar_t* Message = L"";		//看板の内容
	//定数
	const float BoardRange = 300.0f;	//調べられる範囲

};

