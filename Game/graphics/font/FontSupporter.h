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
	void SetFontRender(class FontRender* fr) {
		m_fontRender = fr;
	}

	/// <summary>
	/// フォントレンダーの方で呼び出そう！
	/// </summary>
	void FontSupporter_Update();
	//動作リセット
	void FontDelayReset();

	//ここから演出セット用
	void FontMoveSet(const CVector2& move, const int& movespeed, const int& delay, const bool& relative = false);
	void FontColorSet(const CVector4& color, const int& moveTime, const int& moveDelay);

	//状態取得用
	//フォントの移動リスト要素数を取得
	//移動中のフォントかどうかを判別する など
	int GetFontMoveListLen() {
		return static_cast<int>(m_fontMoveList.size());
	}

private:
	class FontRender* m_fontRender;
	//準備と片付け
	void FontDataUpdate();
	void FontDataReturn();
	//移動関数
	void FontMoveUpdate();
	void FontColorUpdate();

	//フォントの情報
	CVector2 m_position;							//座標
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };	//乗算カラー

	//移動情報
	struct FontMoveData {
		CVector2 m_fontMovePos = { 0.0f,0.0f };		//フォントの移動先
		CVector2 m_fontMoveSpeed = { 0.0f,0.0f };	//フォントの移動量
		int m_fontMoveLimit = -1;					//フォントの移動時間（-1は移動中ではない）
		int m_fontMoveDelay = -1;					//フォントの移動ディレイ
		int m_fontMoveTimer = -1;					//フォントの移動タイマー
		bool m_fontMoveRelative = false;			//フォントの相対移動フラグ（trueなら相対移動）
		bool m_fontMoveDeleteFlag = false;			//削除フラグ（いじらないでね）
	};
	std::list<FontMoveData> m_fontMoveList;			//移動のリスト
	//MulColor
	CVector4 m_fontColor = CVector4().White();		//目標の色
	CVector4 m_fontColorMove = CVector4().White();	//1フレームの変化量
	int m_fontColorLimit = -1;						//フォントの色変更時間（-1は変化中ではない）
	int m_fontColorDelay = -1;						//フォントの変化ディレイ
	int m_fontColorTimer = -1;						//フォントの変化タイマー


};

