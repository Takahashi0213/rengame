#pragma once

/// <summary>
/// 操作方法を常時表示する
/// 一部の操作はここで行えるようにもする
/// メニュー中は非表示にする
/// </summary>
class UI_Supporter
{
public:
	UI_Supporter();
	~UI_Supporter();

	/// <summary>
	/// UIサポーターの更新（ゲームに呼んでもらう）
	/// </summary>
	void UI_Suppoter_Update();

	/// <summary>
	/// プレイヤーを設定
	/// </summary>
	void SetPlayer(Player* pl) {
		m_player = pl;
	}

	/// <summary>
	/// 何かしらUIにマウスオーバーしている？
	/// </summary>
	bool GetUI_MouseOver() {
		return m_mouseOver_Flag;
	}

private:
	/// <summary>
	/// 全部まとめてAlphaを設定
	/// </summary>
	void SetAllAlpha(const float& alpha);
	/// <summary>
	/// 描画状態が変わるたびに呼ぶ
	/// </summary>
	void UI_Suppoter_DrawUpdate();

	//比較（臨時）
	bool Vector4Hikaku(const CVector4& hoge, const CVector4& hoge2) {
		if (hoge.x != hoge2.x) {
			return false;
		}
		if (hoge.y != hoge2.y) {
			return false;
		}
		if (hoge.z != hoge2.z) {
			return false;
		}
		if (hoge.w != hoge2.w) {
			return false;
		}
		return true;
	}

	Player * m_player = nullptr;

	bool m_mouseOver_Flag = false;						//何かしらマウスオーバーしている？

	//スプライト
	const CVector2 UI_UnderSize = { 120.0f,120.0f };	//UIアンダーのサイズ
	const CVector2 UI_IconSize = { 80.0f,80.0f };		//UIアイコンのサイズ
	const CVector2 UI_MouseSize = { 25.0f,35.0f };		//マウスアイコンのサイズ

	const float UI_MouseOverScale = 1.05f;				//マウスオーバー中の大きさ

	const CVector4 UI_NullColor = { 0.1f,0.1f,0.1f,1.0f };	//空白の時の色

	SpriteRender* m_UI_Under1 = nullptr;				//動作アイコンの下（↑）
	const CVector3 UI_Under1_Hosei = { 0.0f,80.0f,0.0f };	//座標補正

	SpriteRender* m_UI_Under2 = nullptr;				//動作アイコンの下（←）
	const CVector3 UI_Under2_Hosei = { -80.0f,0.0f,0.0f };	//座標補正

	SpriteRender* m_UI_Under3 = nullptr;				//動作アイコンの下（→）
	const CVector3 UI_Under3_Hosei = { 80.0f,0.0f,0.0f };	//座標補正

	SpriteRender* m_UI_Under4 = nullptr;				//動作アイコンの下（↓）
	const CVector3 UI_Under4_Hosei = { 0.0f,-80.0f,0.0f };	//座標補正

	SpriteRender* m_UI_Icon1 = nullptr;					//動作アイコン（↑）
	SpriteRender* m_UI_Icon2 = nullptr;					//動作アイコン（←）
	SpriteRender* m_UI_Icon3 = nullptr;					//動作アイコン（→）
	SpriteRender* m_UI_Icon4 = nullptr;					//動作アイコン（↓）

	SpriteRender* m_UI_MouseCenter = nullptr;			//マウスアイコン（中クリック）
	const CVector3 UI_Mouse_Hosei = { 100.0f,-80.0f,0.0f };	//座標補正

	//テキスト
	const float UI_Font_Scale = 0.4f;					//フォントサイズ
	const float UI_Font_MouseScale = 0.3f;				//マウス説明フォントサイズ

	const CVector4 UI_Futi_Color = CVector4::White();	//フチの色
	const float FutiOffset = 2.0f;						//フチのオフセット

	FontRender* m_UI_Text1 = nullptr;					//操作名（↑）
	const CVector3 UI_Text1_Hosei = { -40.0f,90.0f,0.0f };	//座標補正
	const CVector4 UI_Text1_Color = { 0.8f,0.7f,0.2f,1.0f };	//フォントカラー

	FontRender* m_UI_Text2 = nullptr;					//操作名（←）
	const CVector3 UI_Text2_Hosei = { -10.0f,90.0f,0.0f };	//座標補正
	const CVector4 UI_Text2_Color = { 0.7f,0.1f,0.8f,1.0f };	//フォントカラー

	FontRender* m_UI_Text3 = nullptr;					//操作名（→）
	const CVector3 UI_Text3_Hosei = { -10.0f,90.0f,0.0f };	//座標補正
	const CVector4 UI_Text3_Color = { 0.1f,0.1f,0.8f,1.0f };	//フォントカラー

	FontRender* m_UI_Text4 = nullptr;					//操作名（↓）
	const CVector3 UI_Text4_Hosei = { -10.0f,90.0f,0.0f };	//座標補正
	const CVector4 UI_Text4_Color = { 0.8f,0.1f,0.1f,1.0f };	//フォントカラー

	FontRender* m_UI_Text_Center = nullptr;				//操作名（中クリック）
	const CVector3 UI_TextCenter_Hosei = { 70.0f,-110.0f,0.0f };	//座標補正
	const CVector4 UI_TextCenter_Color = { 1.0f,0.5f,0.2f,1.0f };	//フォントカラー
	const float UI_TextCenter_X_Hosei = -20.0f;						//補正

	//定数
	const CVector3 UI_Position = { 420.0f,-190.0f,0.0f };	//基礎座標
	const int SpritePriority = 8;							//優先度

	//マウス操作のテキスト
	//→左右はオミット（誰でもわかると思うので…）
	enum MouseUI_Text {
		MouseUI_Center_Action,	//中クリック、アクションモード		
		MouseUI_Center_Create,	//中クリック、クリエイトモード		
		MouseUI_Num,			//要素数
	};
	//内容
	const wchar_t* Mouse_Text[MouseUI_Num]{
		L"箱を作る",
		L"箱を完成させる",
	};

	//描画関連
	bool m_noDrawFlag = false;		//今は描画しません
	enum UI_DrawState {
		NULL_Mode,				//空白
		ActionMode_Normal,		//アクションモード、通常
		ActionMode_BoxCatch,	//箱持ち上げ体勢
		ActionMode_BoxUp,		//箱持ち上げ中
		CreateMode_Normal,		//クリエイトモード
	};
	UI_DrawState m_ui_DrawMode = NULL_Mode;		//描画状態

	//クイックアクション
	enum QuickAction {
		NULL_Action,		//空白
		Up_Action,			//上ボタン
		Left_Action,		//左ボタン
		Right_Action,		//右ボタン
		Down_Action,		//下ボタン
	};

};

