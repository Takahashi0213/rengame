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

	/// <summary>
	/// スプライトサポーターをまとめてアップデート
	/// （SpriteRenderが呼ぶ）
	/// </summary>
	void SpriteSupporter_Update();

	/// <summary>
	/// スプライトの演出を全てリセットする
	/// </summary>
	void SpriteDelayReset();

	//実行するコマンド

	/// <summary>
	/// 画像移動をセットする
	/// </summary>
	/// <param name="move">移動先の座標</param>
	/// <param name="moveTime">移動時間</param>
	/// <param name="moveDelay">移動ディレイ</param>
	/// <param name="relative">相対移動フラグ trueにするとmoveに設定した値を相対座標として扱うぞ</param>
	void SpriteMove(const CVector2& move, const int& moveTime,
		const int& moveDelay, const bool& relative = false);

	/// <summary>
	/// 回転移動をセットする
	/// </summary>
	/// <remarks>
	/// 
	/// 永久回転をセットしていて停止したい場合のサンプルコード
	/// SpriteRotation(0.0f, 0,0);
	/// 
	/// </remarks>
	/// <param name="rot">1フレームの回転量（float）</param>
	/// <param name="moveTime">回転時間（loopflagがtrueなら無効）</param>
	/// <param name="moveDelay">回転ディレイ</param>
	/// <param name="loopflag">trueにすると停止命令までずっと回転</param>
	void SpriteRotation(const float& rot, const int& moveTime,
		const int& moveDelay, const bool& loopflag = false);

	/// <summary>
	/// スムーズに拡大縮小するやつをセットする
	/// </summary>
	/// <param name="scale">目標の大きさ</param>
	/// <param name="moveTime">動作時間</param>
	/// <param name="moveDelay">動作ディレイ</param>
	void SpriteScale(const CVector3& scale, const int& moveTime, const int& moveDelay);
	void SpriteScale(const float& scale, const int& moveTime, const int& moveDelay);

	/// <summary>
	/// スプライトの乗算カラー変更をセットする
	/// </summary>
	/// <param name="color">目標のカラー</param>
	/// <param name="moveTime">動作時間</param>
	/// <param name="moveDelay">動作ディレイ</param>
	void SpriteColor(const CVector4& color, const int& moveTime, const int& moveDelay);

	/// <summary>
	/// スプライトのシェイクをセットする
	/// </summary>
	/// <param name="move">1回のシェイクにおける移動距離</param>
	/// <param name="moveTime">動作時間</param>
	/// <param name="moveCount">動作回数（0を指定するとループ）</param>
	void SpriteShake(const CVector2& move, const int& moveTime, const int& moveCount);

	/// <summary>
	/// スプライトのパラパラパターンを設定する
	/// </summary>
	/// <param name="moveTime">1枚の経過時間</param>
	/// <param name="loopflag">ループするかどうか（falseの場合終了時自動でアルファが0になるぞ）</param>
	/// <param name="overLimit">パターン終了後、消滅までの時間</param>
	/// <param name="stopflag">trueの場合、エフェクト終了後そのまま停止する</param>
	void SpritePattern(const int& moveTime, const bool& loopflag = false,
		const int& overLimit = 0 ,const bool& stopflag = false);

	/// <summary>
	/// このフラグがtrue かつ このスプライトが全く動いていない場合
	/// スプライトは自動でDeleteGOされる
	/// </summary>
	/// <param name="flag">フラグ</param>
	void SetAutoDeathFlag(const bool& flag) {
		m_autoDeathFlag = flag;
	}

	//状態取得用
	//スプライトの移動リスト要素数を取得
	//移動中のスプライトかどうかを判別する など
	int GetSpriteMoveListLen() {
		return static_cast<int>(m_spriteMoveList.size());
	}
	int GetSpriteScaleListLen() {
		return static_cast<int>(m_spriteScaleList.size());
	}

private:
	//準備と片付け

	//スプライトの情報を最初にアップデート！
	void SpriteDataUpdate();
	//スプライトの情報を返す 最後に実行しよう
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
		CVector2 m_spriteMovePos = { 0.0f,0.0f };			//スプライトの移動先
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };			//スプライトの移動量
		int m_spriteMoveLimit = -1;							//スプライトの移動時間（-1は移動中ではない）
		int m_spriteMoveDelay = -1;							//スプライトの移動ディレイ
		int m_spriteMoveTimer = -1;							//スプライトの移動タイマー
		bool m_spriteMoveRelative = false;					//スプライトの相対移動フラグ（trueなら相対移動）
		bool m_spriteMoveDeleteFlag = false;				//削除フラグ（いじらないでね）
	};
	std::list<SpriteMoveSet> m_spriteMoveList;				//移動のリスト
	//Rotation
	CQuaternion m_spriteRotation = CQuaternion().Identity();	//1フレームの回転量
	int m_spriteRotationLimit = -1;							//スプライトの回転時間（-1は移動中ではない）
	int m_spriteRotationDelay = -1;							//スプライトの回転ディレイ
	int m_spriteRotationTimer = -1;							//スプライトの回転タイマー
	bool m_spriteLoopRotationFlag = false;					//trueなら永遠に延々にフォーエバー回る回る回る
	//Scale
	struct SpriteScaleSet {
		CVector3 m_spriteScale = CVector3().Zero();			//目標の大きさ
		CVector3 m_spriteScaleMove = CVector3().Zero();		//1フレームの変化量
		int m_spriteScaleLimit = -1;						//スプライトの拡大時間（-1は移動中ではない）
		int m_spriteScaleDelay = -1;						//スプライトの拡大ディレイ
		int m_spriteScaleTimer = -1;						//スプライトの拡大タイマー
		bool m_spriteScaleDeleteFlag = false;				//削除フラグ（いじらないでね）
	};
	std::list<SpriteScaleSet> m_spriteScaleList;			//拡大縮小のリスト
	//MulColor
	CVector4 m_spriteColor = CVector4().White();			//目標の色
	CVector4 m_spriteColorMove = CVector4().White();		//1フレームの変化量
	int m_spriteColorLimit = -1;							//スプライトの色変更時間（-1は変化中ではない）
	int m_spriteColorDelay = -1;							//スプライトの変化ディレイ
	int m_spriteColorTimer = -1;							//スプライトの変化タイマー
	//Shake
	CVector2 m_spriteShakeMove = { 0.0f,0.0f };				//シェイクでの移動距離
	CVector2 m_spriteShakeMove_OneFlame = { 0.0f,0.0f };	//シェイクの1フレーム移動距離
	int m_spriteShakeLimit = -1;							//スプライトのシェイク間隔（-1は変化中ではない）
	int m_spriteShakeCount = -1;							//スプライトのシェイク回数（0の場合、止めるまでループする）
	int m_spriteShakeCounter = -1;							//スプライトのシェイク回数カウンター
	int m_spriteShakeTimer = -1;							//スプライトのシェイクタイマー
	//Pattern
	int m_patternLimit = -1;								//最終パターン
	int m_patternTimer = -1;								//パターン用タイマー
	int m_patternOverLimit = -1;							//パターン終了後の待ち時間（パターン終了時一瞬で消えたりするので）
	bool m_patternLoopFlag = false;							//falseならパターン終了時、アルファを自動で0にする trueならループする
	bool m_patternStopFlag = false;							//trueならパターン終了時に停止する
	//AutoDeath
	bool m_autoDeathFlag = false;							//何もしていない場合、親のスプライトレンダーを削除する


};

