#pragma once

/// <summary>
/// アイテムゲット演出
/// </summary>
class ItemGet
{
public:
	ItemGet();
	~ItemGet();

	/// <summary>
	/// Gameに呼んでもらうアップデート
	/// </summary>
	void ItemGetUpdate();

	/// <summary>
	/// アイテムを取得する
	/// 
	/// 演出兼内部処理を全て行うため、
	/// アイテムを取得するときはこれさえ読んでおけばOK
	/// </summary>
	/// <param name="itemNo">アイテム番号</param>
	void ItemGetEffect(const int& itemNo);

	/// <summary>
	/// アイテムをサイレント取得する
	/// </summary>
	/// <param name="itemNo">アイテム番号</param>
	void ItemGet_NoEffect(const int& itemNo);

private:
	int m_nowItemNo = -1;											//現在演出中のアイテムNo
	Player* m_player = nullptr;										//プレイヤー（演出用）

	float m_effectTimer = 0.0f;										//エフェクトタイマー
	const float EffectLimit = 0.6f;									//エフェクト時間（決定受付までの時間）

	SpriteRender* m_itemGetEffect = nullptr;						//アイテムゲットエフェクト
	const CVector3 ItemGetEffectDefPos = { 0.0f,400.0f,0.0f };		//アイテムゲットエフェクトの座標

	SpriteRender* m_itemGetEffect_Light = nullptr;					//アイテムゲットエフェクトの光
	const CVector3 ItemGetEffectLightDefPos = { 0.0f,300.0f,0.0f };	//アイテムゲットエフェクト（光）の座標

	SpriteRender* m_itemSprite = nullptr;							//アイテムアイコン
	const CVector3 ItemSpriteDefPos = { 0.0f,100.0f,0.0f };			//アイテムの座標

	SpriteRender* m_itemWindow= nullptr;							//アイテムウィンドウ
	const CVector3 ItemWindowDefPos = { 0.0f,-200.0f,0.0f };		//アイテムウィンドウの基礎座標
	const CVector3 ItemWindowDefScale = { 500.0f,80.0f,0.0f };		//アイテムウィンドウの大きさ

	FontRender* m_itemName = nullptr;								//アイテム名
	const CVector3 ItemNameDefPos = { -70.0f,-175.0f,0.0f };		//アイテム名の基礎座標
	const float ItemNameScale = 0.6f;								//アイテム名のフォントサイズ
	const CVector4 ItemNameColor = { 0.1f,0.1f,1.0f,1.0f };			//アイテム名の色

	FontRender* m_itemSetumei = nullptr;							//アイテム説明
	const CVector3 ItemSetumeiDefPos = { -150.0f,-250.0f,0.0f };	//アイテム説明の基礎座標
	const float ItemSetumeiScale = 0.5f;							//アイテム説明のフォントサイズ
	const CVector4 ItemSetumeiColor = CVector4::White();			//アイテム説明の色
	const CVector4 ItemSetumeiOutLineColor = { 0.1f,0.1f,1.0f,1.0f };//アイテム説明フチの色
	const float ItemSetumeiOutLineOffset = 1.0f;					//アイテム説明フチのオフセット

	bool m_effectCameraFlag = false;
	bool m_effectLightFlag = false;
	bool m_effectEndFlag = false;

	const int SpritePriority = 6;									//優先度
	const int FadeSpeed = 10;										//フェード速度

};

