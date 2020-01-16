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
	void SpriteRenderSetting(class SpriteRender* sp) {
		m_spriteRender = sp;
	}

	void SpriteSupporter_Update();

	/// <summary>
	/// スプライトの演出を全てリセットする
	/// </summary>
	void SpriteDelayReset();

	//実行するコマンド
	void SpriteMove(CVector2 move, int moveTime, int moveDelay, bool relative = false);
	void SpriteRotation(float rot, int moveTime, int moveDelay, bool loopflag = false);
	void SpriteScale(CVector3 scale, int moveTime, int moveDelay);
	void SpriteColor(CVector4 color, int moveTime, int moveDelay);
	void SpriteShake(CVector2 move, int moveTime, int moveCount);

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

	//メンバ変数
	class SpriteRender* m_spriteRender;
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();					//拡大率
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//乗算カラー
	//Move
	struct SpriteMoveSet {
		CVector2 m_spriteMovePos = { 0.0f,0.0f };	//スプライトの移動先
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };	//スプライトの移動量
		int m_spriteMoveLimit = -1;	//スプライトの移動時間（-1は移動中ではない）
		int m_spriteMoveDelay = -1;	//スプライトの移動ディレイ
		int m_spriteMoveTimer = -1; //スプライトの移動タイマー
		bool m_spriteMoveRelative = false;		//スプライトの相対移動フラグ（trueなら相対移動）
		bool m_spriteMoveDeleteFlag = false;	//スプライトの削除フラグ（いじらないでね）
	};
	std::list<SpriteMoveSet> m_spriteMoveList; //移動のリスト
	//Rotation
	CQuaternion m_spriteRotation = CQuaternion().Identity();	//1フレームの回転量
	int m_spriteRotationLimit = -1;	//スプライトの回転時間（-1は移動中ではない）
	int m_spriteRotationDelay = -1;	//スプライトの回転ディレイ
	int m_spriteRotationTimer = -1; //スプライトの回転タイマー
	bool m_spriteLoopRotationFlag = false;		//trueなら永遠に延々にフォーエバー回る回る回る
	//Scale
	CVector3 m_spriteScale = CVector3().Zero();			//目標の大きさ
	CVector3 m_spriteScaleMove = CVector3().Zero();		//1フレームの変化量
	int m_spriteScaleLimit = -1;	//スプライトの拡大時間（-1は移動中ではない）
	int m_spriteScaleDelay = -1;	//スプライトの拡大ディレイ
	int m_spriteScaleTimer = -1;	//スプライトの拡大タイマー
	//MulColor
	CVector4 m_spriteColor = CVector4().White();		//目標の色
	CVector4 m_spriteColorMove = CVector4().White();	//1フレームの変化量
	int m_spriteColorLimit = -1;	//スプライトの色変更時間（-1は変化中ではない）
	int m_spriteColorDelay = -1;	//スプライトの変化ディレイ
	int m_spriteColorTimer = -1;	//スプライトの変化タイマー
	//Shake
	CVector2 m_spriteShakeMove = { 0.0f,0.0f }; //シェイクでの移動距離
	CVector2 m_spriteShakeMove_OneFlame = { 0.0f,0.0f }; //シェイクの1フレーム移動距離
	int m_spriteShakeLimit = -1;	//スプライトのシェイク間隔（-1は変化中ではない）
	int m_spriteShakeCount = -1;	//スプライトのシェイク回数（0の場合、止めるまでループする）
	int m_spriteShakeCounter = -1;	//スプライトのシェイク回数カウンター
	int m_spriteShakeTimer = -1;	//スプライトのシェイクタイマー



};

