#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"
#include "PointLight.h"

//IGameObjectを継承しているので開始時にNewGOしてくださいね～

/// <summary>
/// ライト作るくん
/// ・シングルトン
/// </summary>
class LightMaker : public IGameObject
{
	static LightMaker* m_instance;
public:
	LightMaker();
	~LightMaker();
	void Update()override;
	void Render()override;

	void LightMaker::D_LightMake(int lightNo, CVector4 dir, CVector4 col,float spec);
	void LightMaker::D_LightDelete(int lightNo);

	void LightMaker::P_LightMake(int lightNo, CVector3 pos, CVector3 col, float range);
	void LightMaker::P_LightDeleteAll();
	void LightMaker::P_LightDelete(int lightNo);

	/// <summary>
	/// 引数に設定したライトの方向を変更する
	/// </summary>
	void LightMaker::D_Light_SetDirection(int lightNo, CVector4 dir) {
		m_light.direction[lightNo] = dir;
	}
	CVector4 LightMaker::D_Light_GetDirection(int lightNo) {
		return m_light.direction[lightNo];
	}

	/// <summary>
	/// 引数に設定したライトの色を変更する
	/// </summary>
	void LightMaker::D_Light_SetColer(int lightNo, CVector4 col) {
		m_light.color[lightNo] = col;
	}
	CVector4 LightMaker::D_Light_GetColer(int lightNo) {
		return m_light.color[lightNo];
	}

	/// <summary>
	/// スペキュラの絞りを変更する
	/// </summary>
	void LightMaker::D_Light_SetSpec(int lightNo, float spec) {
		m_light.color[lightNo].w = spec;
	}
	float LightMaker::D_Light_GetSpec(int lightNo) {
		return m_light.color[lightNo].w;
	}

	/// <summary>
	/// ポイントライトの座標を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetPos(int lightNo, CVector3 pos) {
		m_pointLight.position[lightNo] = pos;
	}
	CVector3 LightMaker::P_Light_GetPos(int lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.position[lightNo]);
		return ret;
	}

	/// <summary>
	/// ポイントライトの色を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetColor(int lightNo, CVector3 color) {
		m_pointLight.color[lightNo] = color;
	}
	CVector3 LightMaker::P_Light_GetColor(int lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.color[lightNo]);
		return ret;
	}

	/// <summary>
	/// ポイントライトの範囲を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetRange(int lightNo, float range) {
		m_pointLight.color[lightNo].w = range;
	}
	float LightMaker::P_Light_GetRange(int lightNo) {
		return m_pointLight.color[lightNo].w;
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
	/// ポイントライト有効フラグを返す
	/// </summary>
	/// <returns>フラグ</returns>
	bool Get_P_LightFlag() {
		return m_lightFlag_P;
	}
	/// <summary>
	/// ポイントライト有効フラグをセット
	/// </summary>
	/// <param name="flag">フラグ</param>
	void Set_P_LightFlag(bool flag) {
		m_lightFlag_P = flag;
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
	//ライトたち！
	SDirectionLight m_light;
	SPointLight m_pointLight;

	//有効フラグ
	bool m_lightFlag_D = false;	//ディレクションライト有効フラグ
	bool m_lightFlag_P = false;	//ポイントライト有効フラグ

	CVector3 m_ambientColor = { 0.1f,0.1f,0.2f };	//環境光の色

	CVector3 m_lightCameraPosition;				//ライトカメラの視点。
	CVector3 m_lightCameraTarget;				//ライトカメラの注視点。

	//定数
	const CVector4 DirectionLight_Direction_Def = { 0.0f, -1.0f, 0.0f, 0.0f };	//ディレクションライトの初期化で使う
	const CVector4 DirectionLight_Color_Def = { 0.5f,0.5f, 0.5f, 10.0f };		//ディレクションライトの初期化で使う

};

