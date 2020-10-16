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
	void SkinModelMove(CVector3 move, int moveTime, int moveDelay, bool relative = false);
	void SkinModelRotation(const float rot, CVector3 axis , const int moveTime, const int moveDelay, const bool loopflag = false);
	//初期化
	void SkinModelMoveClear() {
		m_skinModelMoveList.clear();
	}

	void SkinModelSupporterUpdate();

private:
	//準備と片付け
	void SkinModelDataUpdate();
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

