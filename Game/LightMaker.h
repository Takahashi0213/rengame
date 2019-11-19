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

	void LightMaker::D_LightMake(int lightNo, CVector4 dir, CVector4 col);

	void LightMaker::D_LightDelete(int lightNo);

	/// <summary>
	/// 引数に設定したライトの方向を変更する
	/// </summary>
	/// <param name="light">変更するライトの場所</param>
	/// <param name="dir">ライトの方向</param>
	void LightMaker::D_Light_SetDirection(int lightNo, CVector4 dir) {
		m_light.direction[lightNo] = dir;
	}

	/// <summary>
	/// 引数に設定したライトの色を変更する
	/// </summary>
	/// <param name="light">変更するライトの場所</param>
	/// <param name="col">ライトの色</param>
	void LightMaker::D_Light_SetColer(int lightNo, CVector4 col) {
		m_light.color[lightNo] = col;
	}

	/// <summary>
	/// ディレクションライト有効フラグを返す
	/// </summary>
	/// <returns>フラグ</returns>
	bool Get_D_LightFlag() {
		return m_lightFlag_D;
	}

	/// <summary>
	/// ディレクションライト有効フラグをセット
	/// </summary>
	/// <param name="flag">フラグ</param>
	void Set_D_LightFlag(bool flag) {
		m_lightFlag_D = flag;
	}

	/// <summary>
	/// 環境光をセットする
	/// </summary>
	/// <param name="color">環境光</param>
	void SetAmbientColor(CVector3 color) {
		m_ambientColor = color;
	}

	/// <summary>
	/// 環境光を返す
	/// </summary>
	/// <returns>環境光</returns>
	CVector3 GetAmbientColor() {
		return m_ambientColor;
	}

	/// <summary>
	/// ライトカメラの座標を指定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetLightCameraPosition(CVector3 pos) {
		m_lightCameraPosition = pos;
	}

	/// <summary>
	/// ライトカメラの座標を返す
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetLightCameraPosition() {
		return m_lightCameraPosition;
	}

	/// <summary>
	/// ライトカメラの注視点を指定
	/// </summary>
	/// <param name="pos">注視点</param>
	void SetLightCameraTarget(CVector3 pos) {
		m_lightCameraTarget = pos;
	}

	/// <summary>
	/// ライトカメラの注視点を返す
	/// </summary>
	/// <returns>注視点</returns>
	CVector3 GetLightCameraTarget() {
		return m_lightCameraTarget;
	}

	/// <summary>
	/// ライトカメラの取得
	/// （参照Ver)
	/// </summary>
	/// <param name="m_pos">座標</param>
	/// <param name="m_tgt">注視点</param>
	void GetLightCamera(CVector3& m_pos, CVector3& m_tgt) {
		m_pos = m_lightCameraPosition;
		m_tgt = m_lightCameraTarget;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static LightMaker* LightMaker::GetInstance() {
		return m_instance;
	}

private:
	SDirectionLight m_light;
	bool m_lightFlag_D = false;

	CVector3 m_ambientColor = { 0.4f,0.4f,0.4f };	//環境光の色

	CVector3 m_lightCameraPosition;				//ライトカメラの視点。
	CVector3 m_lightCameraTarget;				//ライトカメラの注視点。

};

