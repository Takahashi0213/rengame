#include "stdafx.h"
#include "SpriteSupporter.h"

SpriteSupporter::SpriteSupporter()
{
}

SpriteSupporter::~SpriteSupporter()
{
}

/// <summary>
/// スプライトサポーターをまとめてアップデート
/// </summary>
void SpriteSupporter::SpriteSupporter_Update() {

	//まずはデータ更新
	SpriteDataUpdate();

	//ここから画像更新
	SpriteMoveUpdate();
	SpriteRotationUpdate();
	SpriteScaleUpdate();
	SpriteColorUpdate();
	SpriteShakeUpdate();

	//最後に更新したデータを返す
	SpriteDataReturn();
}

/// <summary>
/// スプライトの情報を最初にアップデート！
/// </summary>
void SpriteSupporter::SpriteDataUpdate() {

	m_position = m_spriteRender->GetPosition();
	m_rotation = m_spriteRender->GetRotation();
	m_scale = m_spriteRender->GetScale();
	m_mulColor = m_spriteRender->GetMulColor();

}

/// <summary>
/// スプライトの情報を返す 最後に実行しよう
/// </summary>
void SpriteSupporter::SpriteDataReturn() {

	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetRotation(m_rotation);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetMulColor(m_mulColor);

}

void SpriteSupporter::SpriteDelayReset() {

	//
	m_spriteMoveList.clear();
	//
	m_spriteRotation = CQuaternion().Identity();	//1フレームの回転量
	m_spriteRotationLimit = -1;	//スプライトの回転時間（-1は移動中ではない）
	m_spriteRotationDelay = -1;	//スプライトの回転ディレイ
	m_spriteRotationTimer = -1; //スプライトの回転タイマー
	m_spriteLoopRotationFlag = false;		//trueなら永遠に延々にフォーエバー回る回る回る
	//Scale
	m_spriteScale = CVector3().Zero();			//目標の大きさ
	m_spriteScaleMove = CVector3().Zero();		//1フレームの変化量
	m_spriteScaleLimit = -1;	//スプライトの拡大時間（-1は移動中ではない）
	m_spriteScaleDelay = -1;	//スプライトの拡大ディレイ
	m_spriteScaleTimer = -1;	//スプライトの拡大タイマー
	//MulColor
	m_spriteColor = CVector4().White();		//目標の色
	m_spriteColorMove = CVector4().White();	//1フレームの変化量
	m_spriteColorLimit = -1;	//スプライトの色変更時間（-1は変化中ではない）
	m_spriteColorDelay = -1;	//スプライトの変化ディレイ
	m_spriteColorTimer = -1;	//スプライトの変化タイマー
	//Shake
	m_spriteShakeMove.x = 0.0f;
	m_spriteShakeMove.y = 0.0f;
	m_spriteShakeMove_OneFlame.x = 0.0f;
	m_spriteShakeMove_OneFlame.y = 0.0f;
	m_spriteShakeLimit = -1;	//スプライトのシェイク間隔（-1は変化中ではない）
	m_spriteShakeCount = -1;	//スプライトのシェイク回数（0の場合、止めるまでループする）
	m_spriteShakeCounter = -1;	//スプライトのシェイク回数カウンター
	m_spriteShakeTimer = -1;	//スプライトのシェイクタイマー

}

/// <summary>
/// 画像移動をセットする
/// </summary>
/// <param name="move">移動先の座標</param>
/// <param name="moveTime">移動時間</param>
/// <param name="moveDelay">移動ディレイ</param>
/// <param name="relative">相対移動フラグ trueにするとmoveに設定した値を相対座標として扱うぞ</param>
void SpriteSupporter::SpriteMove(CVector2 move, int moveTime, int moveDelay, bool relative) {

	//リストに追加や
	SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
	m_spriteMoveList.push_back(set);

}

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
void SpriteSupporter::SpriteRotation(float rot, int moveTime, int moveDelay, bool loopflag) {

	CQuaternion RotationZ;
	RotationZ.SetRotationDeg(CVector3().AxisZ(), rot);

	m_spriteRotation = RotationZ;
	m_spriteRotationLimit = moveTime;
	m_spriteRotationDelay = moveDelay;
	m_spriteLoopRotationFlag = loopflag;
	m_spriteRotationTimer = 0;
}

/// <summary>
/// スムーズに拡大縮小するやつをセットする
/// </summary>
/// <param name="scale">目標の大きさ</param>
/// <param name="moveTime">動作時間</param>
/// <param name="moveDelay">動作ディレイ</param>
void SpriteSupporter::SpriteScale(CVector3 scale, int moveTime, int moveDelay) {

	m_spriteScale = scale;
	m_spriteScaleLimit = moveTime;
	m_spriteScaleDelay = moveDelay;
	m_spriteScaleTimer = 0;
}

/// <summary>
/// スプライトの乗算カラー変更をセットする
/// </summary>
/// <param name="color">目標のカラー</param>
/// <param name="moveTime">動作時間</param>
/// <param name="moveDelay">動作ディレイ</param>
void SpriteSupporter::SpriteColor(CVector4 color, int moveTime, int moveDelay) {
	m_spriteColor = color;
	m_spriteColorLimit = moveTime;
	m_spriteColorDelay = moveDelay;
	m_spriteColorTimer = 0;
}

/// <summary>
/// スプライトのシェイクをセットする
/// </summary>
/// <param name="move">1回のシェイクにおける移動距離</param>
/// <param name="moveTime">動作時間</param>
/// <param name="moveCount">動作回数（0を指定するとループ）</param>
void SpriteSupporter::SpriteShake(CVector2 move, int moveTime, int moveCount) {
	m_spriteShakeMove.x = move.x;
	m_spriteShakeMove.y = move.y;
	m_spriteShakeLimit = moveTime;
	m_spriteShakeCount = moveCount;
	m_spriteShakeCounter = 0;
	m_spriteShakeTimer = 0;
	//移動距離もこ↑こ↓で計算
	m_spriteShakeMove_OneFlame.x = (m_spriteShakeMove.x / (m_spriteShakeLimit * 2));
	m_spriteShakeMove_OneFlame.y = (m_spriteShakeMove.y / (m_spriteShakeLimit * 2));

}

//////////////////////////////////////
///////ここからアップデート関数///////
//////////////////////////////////////

/// <summary>
/// スプライトの移動を実行
/// </summary>
void SpriteSupporter::SpriteMoveUpdate() {

	//リスト分ループ
	for (auto go = m_spriteMoveList.begin();
		go != m_spriteMoveList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_spriteMoveTimer >= 0) {

			if (go->m_spriteMoveTimer >= go->m_spriteMoveDelay) { //ディレイを考慮

				//移動距離を計算
				if (go->m_spriteMoveTimer == go->m_spriteMoveDelay) {
					if (go->m_spriteMoveRelative == false) { //指定された座標へ移動
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x - m_position.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y - m_position.y;
					}
					else { //相対移動
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y;
					}
					go->m_spriteMoveSpeed.x /= (float)go->m_spriteMoveLimit;
					go->m_spriteMoveSpeed.y /= (float)go->m_spriteMoveLimit;
				}

				m_position.x += go->m_spriteMoveSpeed.x;
				m_position.y += go->m_spriteMoveSpeed.y;

			}

			go->m_spriteMoveTimer++;

			if (go->m_spriteMoveTimer >= go->m_spriteMoveLimit + go->m_spriteMoveDelay) {
				//おしまひ
				go->m_spriteMoveDeleteFlag = true;
				go->m_spriteMoveTimer = -1;
				//go = m_spriteMoveList.erase(go);
			}
		}
	}

	//削除処理
	std::list<SpriteMoveSet>::iterator it;
	it = m_spriteMoveList.begin();
	while (it != m_spriteMoveList.end()) {
		if (it->m_spriteMoveDeleteFlag == true) {
			it = m_spriteMoveList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

/// <summary>
/// スプライトの回転を実行
/// </summary>
void SpriteSupporter::SpriteRotationUpdate() {

	//タイマーが0以上なら実行中
	if (m_spriteRotationTimer >= 0) {

		if (m_spriteRotationTimer >= m_spriteRotationDelay) { //ディレイを考慮

			//回転を計算
			m_rotation *= m_spriteRotation;

		}

		m_spriteRotationTimer++;

		if (m_spriteRotationTimer >= m_spriteRotationLimit + m_spriteRotationDelay && m_spriteLoopRotationFlag == false) {
			//おしまひ
			m_spriteRotationTimer = -1;
		}
	}

}

/// <summary>
/// スプライトの拡大縮小を実行
/// </summary>
void SpriteSupporter::SpriteScaleUpdate() {

	//タイマーが0以上なら実行中
	if (m_spriteScaleTimer >= 0) {

		if (m_spriteScaleTimer >= m_spriteScaleDelay) { //ディレイを考慮

			if (m_spriteScaleTimer == m_spriteScaleDelay) {
				//計算タイム
				m_spriteScaleMove = m_spriteScale - m_scale;
				m_spriteScaleMove /= (float)m_spriteScaleLimit;
			}

			m_scale += m_spriteScaleMove;

		}

		m_spriteScaleTimer++;

		if (m_spriteScaleTimer >= m_spriteScaleLimit + m_spriteScaleDelay) {
			//おしまひ
			m_spriteScaleTimer = -1;
		}
	}

}

/// <summary>
/// スプライトの色変更を実行
/// </summary>
void SpriteSupporter::SpriteColorUpdate() {

	//タイマーが0以上なら実行中
	if (m_spriteColorTimer >= 0) {

		if (m_spriteColorTimer >= m_spriteColorDelay) { //ディレイを考慮

			if (m_spriteColorTimer == m_spriteColorDelay) {
				//計算タイム
				m_spriteColorMove = m_spriteColor - m_mulColor;
				m_spriteColorMove.x /= (float)m_spriteColorLimit;
				m_spriteColorMove.y /= (float)m_spriteColorLimit;
				m_spriteColorMove.z /= (float)m_spriteColorLimit;
				m_spriteColorMove.w /= (float)m_spriteColorLimit;
			}

			m_mulColor.x += m_spriteColorMove.x;
			m_mulColor.y += m_spriteColorMove.y;
			m_mulColor.z += m_spriteColorMove.z;
			m_mulColor.w += m_spriteColorMove.w;

			//最小計算
			if (m_mulColor.x < 0.0f) {
				m_mulColor.x = 0.0f;
			}			
			if (m_mulColor.y < 0.0f) {
				m_mulColor.y = 0.0f;
			}			
			if (m_mulColor.z < 0.0f) {
				m_mulColor.z = 0.0f;
			}		
			if (m_mulColor.w < 0.0f) {
				m_mulColor.w = 0.0f;
			}

		}

		m_spriteColorTimer++;

		if (m_spriteColorTimer >= m_spriteColorLimit + m_spriteColorDelay) {
			//おしまひ
			m_spriteColorTimer = -1;
		}
	}

}

/// <summary>
/// スプライトのシェイクを実行
/// </summary>
void SpriteSupporter::SpriteShakeUpdate() {

	if (m_spriteShakeLimit == -1) {
		//実行中でない
		return;
	}

	//移動する
	m_position.x += m_spriteShakeMove_OneFlame.x;
	m_position.y += m_spriteShakeMove_OneFlame.y;

	//タイマーの処理
	m_spriteShakeTimer++;
	if (m_spriteShakeTimer == (m_spriteShakeLimit / 2)) {
		//折り返し
		m_spriteShakeMove_OneFlame.x *= -1.0f;
		m_spriteShakeMove_OneFlame.y *= -1.0f;

	}
	if (m_spriteShakeTimer >= m_spriteShakeLimit) {

		//1シェイク完了
		m_spriteShakeTimer = 0;
		m_spriteShakeMove_OneFlame.x *= -1.0f;
		m_spriteShakeMove_OneFlame.y *= -1.0f;

		//無限シェイクでないならシェイク回数を加算
		if (m_spriteShakeCount > 0) {
			m_spriteShakeCounter++;
			if (m_spriteShakeCount <= m_spriteShakeCounter) {
				//シェイク終了
				m_spriteShakeLimit = -1;
			}
		}
	}

}