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
	/// ŠÅ”Â‚Ì“à—e‚ğİ’è‚µ‚½‚èæ“¾‚µ‚½‚è
	/// </summary>
	void SetBoardMessage(const wchar_t* message) {
		Message = message;
	}
	const wchar_t* GetBoardMessage() const {
		return Message;
	}

private:
	SkinModel m_model;			//‚à‚Å``‚é

	const wchar_t* Message = L"";				//ŠÅ”Â‚Ì“à—e

	const float BoardRange = 300.0f;	//’²‚×‚ç‚ê‚é”ÍˆÍ

};

