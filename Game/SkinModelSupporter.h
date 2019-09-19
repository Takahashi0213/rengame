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

	void SkinModelSupporterUpdate();

private:
	//準備と片付け
	void SkinModelDataUpdate();
	void SkinModelDataReturn();
	//アップデート用
	void SkinModelMoveUpdate();

	//メンバ変数
	class SkinModelRender* m_skinModelRender;
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();					//拡大率
	//Move
	struct SkinModelMoveSet {
		CVector3 m_skinModelMovePos = CVector3().Zero();	//スプライトの移動先
		CVector3 m_skinModelMoveSpeed = CVector3().Zero();	//スプライトの移動量
		int m_skinModelMoveLimit = -1;	//スプライトの移動時間（-1は移動中ではない）
		int m_skinModelMoveDelay = -1;	//スプライトの移動ディレイ
		int m_skinModelMoveTimer = -1; //スプライトの移動タイマー
		bool m_skinModelMoveRelative = false;		//スプライトの相対移動フラグ（trueなら相対移動）
		bool m_skinModelMoveDeleteFlag = false;	//スプライトの削除フラグ（いじらないでね）
	};
	std::list<SkinModelMoveSet> m_skinModelMoveList; //移動のリスト
	//Rotation

};

