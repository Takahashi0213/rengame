#include "stdafx.h"
#include "SkinModelSupporter.h"


SkinModelSupporter::SkinModelSupporter()
{
}

SkinModelSupporter::~SkinModelSupporter()
{
}

/// <summary>
/// まとめてアップデート
/// </summary>
void SkinModelSupporter::SkinModelSupporterUpdate() {

	//まずはデータ更新
	SkinModelDataUpdate();

	//ここからモデル更新
	SkinModelMoveUpdate();

	//最後に更新したデータを返す
	SkinModelDataReturn();
}

/// <summary>
/// モデルの情報を最初にアップデート！
/// </summary>
void SkinModelSupporter::SkinModelDataUpdate() {

	m_position = m_skinModelRender->GetPosition();
	m_rotation = m_skinModelRender->GetRotation();
	m_scale = m_skinModelRender->GetScale();

}

/// <summary>
/// モデルの情報を返す 最後に実行しよう
/// </summary>
void SkinModelSupporter::SkinModelDataReturn() {
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

/// <summary>
/// 移動をセットする
/// </summary>
/// <param name="move">移動先の座標</param>
/// <param name="moveTime">移動時間</param>
/// <param name="moveDelay">移動ディレイ</param>
/// <param name="relative">相対移動フラグ trueにするとmoveに設定した値を相対座標として扱うぞ</param>
void SkinModelSupporter::SkinModelMove(CVector3 move, int moveTime, int moveDelay, bool relative) {
	//リストに追加や
	SkinModelMoveSet set = { move,CVector3().Zero(),moveTime,moveDelay,0,relative,false };
	m_skinModelMoveList.push_back(set);
}

/// <summary>
/// モデル移動のアップデート
/// </summary>
void SkinModelSupporter::SkinModelMoveUpdate() {

}