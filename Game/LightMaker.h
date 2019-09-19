#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"

//IGameObjectを継承しているので開始時にNewGOしてくださいね～

/// <summary>
/// ライト作るくん
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
	/// 引数に設定したライトの方向を変更する
	/// </summary>
	/// <param name="light">変更するライトのポインタ</param>
	/// <param name="dir">ライトの方向</param>
	void LightMaker::D_Light_SetDirection(SDirectionLight* light, CVector4 dir) {
		light->direction = dir;
	}	

	/// <summary>
	/// 引数に設定したライトの色を変更する
	/// </summary>
	/// <param name="light">変更するライトのポインタ</param>
	/// <param name="col">ライトの色</param>
	void LightMaker::D_Light_SetColer(SDirectionLight* light, CVector4 col) {
		light->color = col;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static LightMaker* LightMaker::GetInstance() {
		return m_instance;
	}

private:
	std::list<SDirectionLight*> m_dLightList; //ディレクションライトのリスト


};

