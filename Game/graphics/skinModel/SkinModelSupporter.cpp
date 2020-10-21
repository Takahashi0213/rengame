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
	SkinModelRotationUpdate();

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
/// <param name="relative">相対移動フラグ trueにするとmoveに設定した値を相対座標として扱う</param>
void SkinModelSupporter::SkinModelMove(CVector3 move, int moveTime, int moveDelay, bool relative) {
	//リストに追加や
	SkinModelMoveSet set = { move,CVector3().Zero(),moveTime,moveDelay,0,relative,false };
	m_skinModelMoveList.push_back(set);
}

/// <summary>
/// 回転移動をセットする
/// </summary>
/// <remarks>
/// 
/// 永久回転をセットしていて停止したい場合のサンプルコード
/// SkinModelRotation(0.0f, 0,0);
/// 
/// </remarks>
/// <param name="rot">1フレームの回転量（float）</param>
/// <param name="axis">回転軸（CVector3::AxisY()など）</param>
/// <param name="moveTime">回転時間（loopflagがtrueなら無効）</param>
/// <param name="moveDelay">回転ディレイ</param>
/// <param name="loopflag">trueにすると停止命令までずっと回転</param>
void SkinModelSupporter::SkinModelRotation(const float rot, CVector3 axis, 
	const int moveTime, const int moveDelay, const bool loopflag) {

	//現在の回転に合わせる
	CQuaternion rotation = m_skinModelRender->GetRotation();
	rotation.Multiply(axis);
	rotation.SetRotationDeg(axis, rot);

	m_skinModelRotation = rotation;
	m_skinModelRotationLimit = moveTime;
	m_skinModelRotationDelay = moveDelay;
	m_skinModelLoopRotationFlag = loopflag;
	m_skinModelRotationTimer = 0;
}

/// <summary>
/// モデル移動のアップデート
/// </summary>
void SkinModelSupporter::SkinModelMoveUpdate() {

	//リスト分ループ
	for (auto go = m_skinModelMoveList.begin();
		go != m_skinModelMoveList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_skinModelMoveTimer >= 0) {

			if (go->m_skinModelMoveTimer >= go->m_skinModelMoveDelay) { //ディレイを考慮

				//移動距離を計算
				if (go->m_skinModelMoveTimer == go->m_skinModelMoveDelay) {
					if (go->m_skinModelMoveRelative == false) { //指定された座標へ移動
						go->m_skinModelMoveSpeed.x = go->m_skinModelMovePos.x - m_position.x;
						go->m_skinModelMoveSpeed.y = go->m_skinModelMovePos.y - m_position.y;
						go->m_skinModelMoveSpeed.z = go->m_skinModelMovePos.z - m_position.z;
					}
					else { //相対移動
						go->m_skinModelMoveSpeed.x = go->m_skinModelMovePos.x;
						go->m_skinModelMoveSpeed.y = go->m_skinModelMovePos.y;
						go->m_skinModelMoveSpeed.z = go->m_skinModelMovePos.z;
					}
					go->m_skinModelMoveSpeed.x /= (float)go->m_skinModelMoveLimit;
					go->m_skinModelMoveSpeed.y /= (float)go->m_skinModelMoveLimit;
					go->m_skinModelMoveSpeed.z /= (float)go->m_skinModelMoveLimit;
				}

				m_position.x += go->m_skinModelMoveSpeed.x;
				m_position.y += go->m_skinModelMoveSpeed.y;
				m_position.z += go->m_skinModelMoveSpeed.z;

			}

			go->m_skinModelMoveTimer++;

			if (go->m_skinModelMoveTimer >= go->m_skinModelMoveLimit + go->m_skinModelMoveDelay) {
				//おしまひ
				go->m_skinModelMoveDeleteFlag = true;
				go->m_skinModelMoveTimer = -1;
				//go = m_spriteMoveList.erase(go);
			}
		}
	}

	//削除処理
	std::list<SkinModelMoveSet>::iterator it;
	it = m_skinModelMoveList.begin();
	while (it != m_skinModelMoveList.end()) {
		if (it->m_skinModelMoveDeleteFlag == true) {
			it = m_skinModelMoveList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

/// <summary>
/// モデルの回転を実行
/// </summary>
void SkinModelSupporter::SkinModelRotationUpdate() {

	//タイマーが0以上なら実行中
	if (m_skinModelRotationTimer >= 0) {

		if (m_skinModelRotationTimer >= m_skinModelRotationDelay) { //ディレイを考慮

															  //回転を計算
			m_rotation *= m_skinModelRotation;

		}

		m_skinModelRotationTimer++;

		if (m_skinModelRotationTimer >= m_skinModelRotationLimit + m_skinModelRotationDelay && m_skinModelLoopRotationFlag == false) {
			//おしまい
			m_skinModelRotationTimer = -1;
		}
	}

}
