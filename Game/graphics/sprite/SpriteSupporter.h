#pragma once

/// <summary>
/// スプライトの移動や演出をワンコマンドでやってくれる
/// </summary>
class SpriteSupporter
{
public:
	SpriteSupporter();
	~SpriteSupporter();

	/// <summary>
	/// SpriteRenderのアドレスを代入する
	/// 最初に実行してね！
	/// </summary>
	/// <param name="sp">ポインタ</param>
	void SpriteRenderSetting(class SpriteRender* sp ,int No = -1) {
		m_spriteRender = sp;
		m_spriteNo = No;
	}

	void SpriteSupporter_Update();

	/// <summary>
	/// スプライトの演出を全てリセットする
	/// </summary>
	void SpriteDelayReset();

	//実行するコマンド
	void SpriteMove(const CVector2& move, const int& moveTime,
		const int& moveDelay, const bool& relative = false);
	void SpriteRotation(const float& rot, const int& moveTime,
		const int& moveDelay, const bool& loopflag = false);
	void SpriteScale(const CVector3& scale, const int& moveTime, const int& moveDelay);
	void SpriteScale(const float& scale, const int& moveTime, const int& moveDelay);
	void SpriteColor(const CVector4& color, const int& moveTime, const int& moveDelay);
	void SpriteShake(const CVector2& move, const int& moveTime, const int& moveCount);
	void SpritePattern(const int& moveTime, const bool& loopflag = false,
		const int& overLimit = 0);

	//状態取得用
	//スプライトの移動リスト要素数を取得
	//移動中のスプライトかどうかを判別する など
	int GetSpriteMoveListLen() {
		return static_cast<int>(m_spriteMoveList.size());
	}

private:
	//準備と片付け
	void SpriteDataUpdate();
	void SpriteDataReturn();
	//アップデート用
	void SpriteMoveUpdate();
	void SpriteRotationUpdate();
	void SpriteScaleUpdate();
	void SpriteColorUpdate();
	void SpriteShakeUpdate();
	void SpritePatternUpdate();

	//メンバ変数
	class SpriteRender* m_spriteRender;
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();					//拡大率
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//乗算カラー
	int m_maxPattern = -1;									//最大パターン
	int m_nowPattern = -1;									//現在パターン
	int m_spriteNo = -1;									//スプライト番号（サブスプライト関連）
	//Move
	struct SpriteMoveSet {
		CVector2 m_spriteMovePos = { 0.0f,0.0f };	//スプライトの移動先
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };	//スプライトの移動量
		int m_spriteMoveLimit = -1;					//スプライトの移動時間（-1は移動中ではない）
		int m_spriteMoveDelay = -1;					//スプライトの移動ディレイ
		int m_spriteMoveTimer = -1;					//スプライトの移動タイマー
		bool m_spriteMoveRelative = false;			//スプライトの相対移動フラグ（trueなら相対移動）
		bool m_spriteMoveDeleteFlag = false;		//削除フラグ（いじらないでね）
	};
	std::list<SpriteMoveSet> m_spriteMoveList;		 //移動のリスト
	//Rotation
	CQuaternion m_spriteRotation = CQuaternion().Identity();	//1フレームの回転量
	int m_spriteRotationLimit = -1;					//スプライトの回転時間（-1は移動中ではない）
	int m_spriteRotationDelay = -1;					//スプライトの回転ディレイ
	int m_spriteRotationTimer = -1;					//スプライトの回転タイマー
	bool m_spriteLoopRotationFlag = false;			//trueなら永遠に延々にフォーエバー回る回る回る
	//Scale
	struct SpriteScaleSet {
		CVector3 m_spriteScale = CVector3().Zero();			//目標の大きさ
		CVector3 m_spriteScaleMove = CVector3().Zero();		//1フレームの変化量
		int m_spriteScaleLimit = -1;				//スプライトの拡大時間（-1は移動中ではない）
		int m_spriteScaleDelay = -1;				//スプライトの拡大ディレイ
		int m_spriteScaleTimer = -1;				//スプライトの拡大タイマー
		bool m_spriteScaleDeleteFlag = false;		//削除フラグ（いじらないでね）
	};
	std::list<SpriteScaleSet> m_spriteScaleList;	 //拡大縮小のリスト
	//MulColor
	CVector4 m_spriteColor = CVector4().White();		//目標の色
	CVector4 m_spriteColorMove = CVector4().White();	//1フレームの変化量
	int m_spriteColorLimit = -1;						//スプライトの色変更時間（-1は変化中ではない）
	int m_spriteColorDelay = -1;						//スプライトの変化ディレイ
	int m_spriteColorTimer = -1;						//スプライトの変化タイマー
	//Shake
	CVector2 m_spriteShakeMove = { 0.0f,0.0f };				//シェイクでの移動距離
	CVector2 m_spriteShakeMove_OneFlame = { 0.0f,0.0f };	//シェイクの1フレーム移動距離
	int m_spriteShakeLimit = -1;							//スプライトのシェイク間隔（-1は変化中ではない）
	int m_spriteShakeCount = -1;							//スプライトのシェイク回数（0の場合、止めるまでループする）
	int m_spriteShakeCounter = -1;							//スプライトのシェイク回数カウンター
	int m_spriteShakeTimer = -1;							//スプライトのシェイクタイマー
	//Pattern
	int m_patternLimit = -1;							//最終パターン
	int m_patternTimer = -1;							//パターン用タイマー
	int m_patternOverLimit = -1;						//パターン終了後の待ち時間（パターン終了時一瞬で消えたりするので）
	bool m_patternLoopFlag = false;						//falseならパターン終了時、アルファを自動で0にする trueならループする

};

