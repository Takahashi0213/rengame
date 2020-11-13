#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"
#include "PointLight.h"

//IGameObjectを継承しているので開始時にNewGOしてください

/// <summary>
/// ライトを作成する
/// ・シングルトン
/// </summary>
class LightMaker final : public IGameObject
{
	static LightMaker* m_instance;
public:
	LightMaker();
	~LightMaker();
	void Update()override;
	void Render()override;

	/// <summary>
	/// ディレクションライトを設定する
	/// </summary>
	/// <param name="lightNo">ライトの番号</param>
	/// <param name="dir">ライトの方向</param>
	/// <param name="col">ライトの色</param>
	/// <param name="spec">スペキュラ</param>
	/// <returns>作成したライトのポインタ</returns>
	void LightMaker::D_LightMake(const int& lightNo, const CVector4& dir, const CVector4& col, const float& spec);

	/// <summary>
	/// ディレクションライトを消去する
	/// </summary>
	/// <param name="lightNo">削除するディレクションライトの番号</param>
	void LightMaker::D_LightDelete(const int& lightNo);

	/// <summary>
	/// ポイントライトを作成する
	/// </summary>
	/// <param name="lightNo">ライト番号</param>
	/// <param name="pos">座標</param>
	/// <param name="col">カラー</param>
	/// <param name="range">範囲</param>
	void LightMaker::P_LightMake(const int& lightNo, const CVector3& pos, const CVector3& col, const float& range);

	/// <summary>
	/// ポイントライトを全て削除
	/// </summary>
	void LightMaker::P_LightDeleteAll();

	/// <summary>
	/// ポイントライトを消去する
	/// </summary>
	/// <param name="lightNo">ライト番号</param>
	void LightMaker::P_LightDelete(const int& lightNo);

	/// <summary>
	/// 引数に設定したライトの方向を取得・変更する
	/// </summary>
	void LightMaker::D_Light_SetDirection(const int& lightNo, const CVector4& dir) {
		m_light.direction[lightNo] = dir;
	}
	CVector4 LightMaker::D_Light_GetDirection(const int& lightNo) {
		return m_light.direction[lightNo];
	}

	/// <summary>
	/// 引数に設定したライトの色を取得・変更する
	/// </summary>
	void LightMaker::D_Light_SetColer(const int& lightNo, const CVector4& col) {
		m_light.color[lightNo] = col;
	}
	CVector4 LightMaker::D_Light_GetColer(const int& lightNo) {
		return m_light.color[lightNo];
	}

	/// <summary>
	/// スペキュラの絞りを取得・変更する
	/// </summary>
	void LightMaker::D_Light_SetSpec(const int& lightNo, const float& spec) {
		m_light.color[lightNo].w = spec;
	}
	float LightMaker::D_Light_GetSpec(const int& lightNo) {
		return m_light.color[lightNo].w;
	}

	/// <summary>
	/// ポイントライトの座標を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetPos(const int& lightNo, const CVector3& pos) {
		m_pointLight.position[lightNo] = pos;
	}
	CVector3 LightMaker::P_Light_GetPos(const int& lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.position[lightNo]);
		return ret;
	}

	/// <summary>
	/// ポイントライトの色を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetColor(const int& lightNo, const CVector3& color) {
		m_pointLight.color[lightNo] = color;
	}
	CVector3 LightMaker::P_Light_GetColor(const int& lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.color[lightNo]);
		return ret;
	}

	/// <summary>
	/// ポイントライトの範囲を取得・変更
	/// </summary>
	void LightMaker::P_Light_SetRange(const int& lightNo, const float& range) {
		m_pointLight.color[lightNo].w = range;
	}
	float LightMaker::P_Light_GetRange(const int& lightNo) {
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
	void Set_D_LightFlag(const bool& flag) {
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
	void Set_P_LightFlag(const bool& flag) {
		m_lightFlag_P = flag;
	}

	/// <summary>
	/// 環境光をセットする
	/// </summary>
	/// <param name="color">環境光</param>
	void SetAmbientColor(const CVector3& color) {
		m_ambientColor = color;
	}

	/// <summary>
	/// 環境光をリセットする
	/// </summary>
	void ResetAmbientColor() {
		m_ambientColor = AmbientDefColor;
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
	void SetLightCameraPosition(const CVector3& pos) {
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
	void SetLightCameraTarget(const CVector3& pos) {
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
	/// ディレクションライトの空きNoを検索
	/// </summary>
	/// <returns>全て使用中なら-1を返す</returns>
	int GetDirectionLight_MakeNo() {
		for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
			if (m_directionLightSetFlag[i] == false) {
				return i;
			}
		}
		return - 1;		//どこも空いてなかった
	}
	/// <summary>
	/// ポイントライトの空きNoを検索
	/// </summary>
	/// <returns>全て使用中なら-1を返す</returns>
	int GetPointLight_MakeNo() {
		for (int i = 0; i < MAX_POINT_LIGHT; i++) {
			if (m_pointLightSetFlag[i] == false) {
				return i;
			}
		}
		return -1;		//どこも空いてなかった
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
	bool m_lightFlag_D = false;		//ディレクションライト有効フラグ
	bool m_lightFlag_P = false;		//ポイントライト有効フラグ

	const CVector3 AmbientDefColor = { 0.5f,0.5f,0.5f };	//環境光デフォルトカラー
	CVector3 m_ambientColor = AmbientDefColor;				//環境光の色

	CVector3 m_lightCameraPosition;				//ライトカメラの視点。
	CVector3 m_lightCameraTarget;				//ライトカメラの注視点。

	bool m_directionLightSetFlag[MAX_DIRECTION_LIGHT] = { false };		//ディレクションライトの設定フラグ
	bool m_pointLightSetFlag[MAX_POINT_LIGHT] = { false };				//ポイントライトの設定フラグ

	//定数
	const CVector4 DirectionLight_Direction_Def = { 0.0f, -1.0f, 0.0f, 0.0f };	//ディレクションライトの初期化で使う
	const CVector4 DirectionLight_Color_Def = { 0.5f,0.5f, 0.5f, 10.0f };		//ディレクションライトの初期化で使う

};

