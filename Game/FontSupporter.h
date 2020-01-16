#pragma once

/// <summary>
/// フォントを楽に動かしマスィーン
/// </summary>
class FontSupporter
{
public:
	FontSupporter();
	~FontSupporter();

	/// <summary>
	/// アドレスを設定
	/// </summary>
	/// <param name="fr">フォントレンダー</param>
	void SetFontRender(class FontRender* fr) {
		m_fontRender = fr;
	}

	/// <summary>
	/// フォントレンダーの方で呼び出そう！
	/// </summary>
	void FontSupporter_Update();

	//ここから演出セット用
	void FontMoveSet(CVector2 move, int movespeed, int delay, bool relative = false);

private:
	class FontRender* m_fontRender;
	//準備と片付け
	void FontDataUpdate();
	void FontDataReturn();
	//移動関数
	void FontMoveUpdate();

	//フォントの情報
	CVector2 m_position;

	//移動情報
	CVector2 m_moveSpeed = { 0.0f,0.0f };			//1フレームの移動量
	int m_moveLimit = 0;							//移動フレーム
	int m_moveDelay = 0;							//移動ディレイ
	int m_moveTimer = 0;							//移動タイマー
	bool m_moveRelative = false;					//相対移動
	bool m_moveFlag = false;						//移動中


};

