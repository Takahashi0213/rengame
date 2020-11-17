#pragma once

/// <summary>
/// モデルの移動や演出をワンコマンドでやってくれる
/// </summary>
class SkinModelSupporter
{
public:
	SkinModelSupporter();
	~SkinModelSupporter();

	/// <summary>
	/// SkinModelRenderのアドレスを代入する
	/// 最初に実行してね！
	/// </summary>
	/// <param name="sp">ポインタ</param>
	void SkinModelRenderSetting(class SkinModelRender* smr) {
		m_skinModelRender = smr;
	}

	//実行するコマンド

	/// <summary>
	/// 移動をセットする
	/// </summary>
	/// <param name="move">移動先の座標</param>
	/// <param name="moveTime">移動時間</param>
	/// <param name="moveDelay">移動ディレイ</param>
	/// <param name="relative">相対移動フラグ trueにするとmoveに設定した値を相対座標として扱う</param>
	void SkinModelMove(const CVector3& move, const int& moveTime,
		const int& moveDelay, const bool& relative = false);

	/// <summary>
	/// 回転移動をセットする
	/// </summary>
	/// <remarks>
	/// 
	/// 永久回転をセットしていて停止したい場合のサンプルコード
	/// SkinModelRotation(0.0f, CVector3::Zero(), 0, 0);
	/// 
	/// </remarks>
	/// <param name="rot">1フレームの回転量（float）</param>
	/// <param name="axis">回転軸（CVector3::AxisY()など）</param>
	/// <param name="moveTime">回転時間（loopflagがtrueなら無効）</param>
	/// <param name="moveDelay">回転ディレイ</param>
	/// <param name="loopflag">trueにすると停止命令までずっと回転</param>
	void SkinModelRotation(const float& rot, CVector3 axis , const int& moveTime, 
		const int& moveDelay, const bool& loopflag = false);

	//初期化
	void SkinModelMoveClear() {
		m_skinModelMoveList.clear();
	}

	/// <summary>
	/// まとめてアップデート
	/// </summary>
	void SkinModelSupporterUpdate();

	//状態取得用
	//モデルの移動リスト要素数を取得
	//移動中のモデルかどうかを判別する など
	int GetSkinModelMoveListLen() {
		return static_cast<int>(m_skinModelMoveList.size());
	}

private:
	/// <summary>
	/// モデルの情報を最初にアップデート！
	/// </summary>
	void SkinModelDataUpdate();
	/// <summary>
	/// モデルの情報を返す 最後に実行しよう
	/// </summary>
	void SkinModelDataReturn();
	//アップデート用
	void SkinModelMoveUpdate();
	void SkinModelRotationUpdate();

	//メンバ変数
	class SkinModelRender* m_skinModelRender;
	CVector3 m_position = CVector3::Zero();						//座標
	CQuaternion m_rotation = CQuaternion().Identity();			//回転
	CVector3 m_scale = CVector3().One();						//拡大率
	//Move
	struct SkinModelMoveSet {
		CVector3 m_skinModelMovePos = CVector3().Zero();		//モデルの移動先
		CVector3 m_skinModelMoveSpeed = CVector3().Zero();		//モデルの移動量
		int m_skinModelMoveLimit = -1;							//モデルの移動時間（-1は移動中ではない）
		int m_skinModelMoveDelay = -1;							//モデルの移動ディレイ
		int m_skinModelMoveTimer = -1;							//モデルの移動タイマー
		bool m_skinModelMoveRelative = false;					//モデルの相対移動フラグ（trueなら相対移動）
		bool m_skinModelMoveDeleteFlag = false;					//削除フラグ（いじらないでね）
	};
	std::list<SkinModelMoveSet> m_skinModelMoveList;			//移動のリスト
	//Rotation
	CQuaternion m_skinModelRotation = CQuaternion().Identity();	//1フレームの回転量
	int m_skinModelRotationLimit = -1;							//モデルの回転時間（-1は移動中ではない）
	int m_skinModelRotationDelay = -1;							//モデルの回転ディレイ
	int m_skinModelRotationTimer = -1;							//モデルの回転タイマー
	bool m_skinModelLoopRotationFlag = false;					//trueなら永遠に延々にフォーエバー回る回る回る

};

