#include "stdafx.h"
#include "SpriteSupporter.h"

SpriteSupporter::SpriteSupporter()
{
}

SpriteSupporter::~SpriteSupporter()
{
}

void SpriteSupporter::SpriteSupporter_Update() {

	//まずはデータ更新
	SpriteDataUpdate();

	//ここから画像更新
	SpriteMoveUpdate();
	SpriteRotationUpdate();
	SpriteScaleUpdate();
	SpriteColorUpdate();
	SpriteShakeUpdate();
	SpritePatternUpdate();

	//オートデスチェック
	if (m_autoDeathFlag == true) {
		//全く動作していない？？
		if (GetSpriteMoveListLen() == 0 &&
			GetSpriteScaleListLen() == 0) {
			//消滅する
			DeleteGO(m_spriteRender);
		}
	}

	//最後に更新したデータを返す
	SpriteDataReturn();
}

void SpriteSupporter::SpriteDataUpdate() {

	m_position = m_spriteRender->GetPosition(m_spriteNo);
	m_rotation = m_spriteRender->GetRotation(m_spriteNo);
	m_scale = m_spriteRender->GetScale(m_spriteNo);
	m_mulColor = m_spriteRender->GetMulColor(m_spriteNo);
	m_maxPattern = m_spriteRender->GetMaxPattern();
	m_nowPattern = m_spriteRender->GetNowPattern();

}

void SpriteSupporter::SpriteDataReturn() {

	m_spriteRender->SetPosition(m_position, m_spriteNo);
	m_spriteRender->SetRotation(m_rotation, m_spriteNo);
	m_spriteRender->SetScale(m_scale, m_spriteNo);
	m_spriteRender->SetMulColor(m_mulColor, m_spriteNo);
	if (m_maxPattern > -1) {
		m_spriteRender->ChangePattern(m_nowPattern);
	}

}

void SpriteSupporter::SpriteDelayReset() {

	//Move
	m_spriteMoveList.clear();
	//Rotation
	m_spriteRotation = CQuaternion().Identity();	//1フレームの回転量
	m_spriteRotationLimit = -1;	//スプライトの回転時間（-1は移動中ではない）
	m_spriteRotationDelay = -1;	//スプライトの回転ディレイ
	m_spriteRotationTimer = -1; //スプライトの回転タイマー
	m_spriteLoopRotationFlag = false;		//trueなら永遠に延々にフォーエバー回る回る回る
	//Scale
	m_spriteScaleList.clear();
	//MulColor
	m_spriteColor = CVector4().White();		//目標の色
	m_spriteColorMove = CVector4().White();	//1フレームの変化量
	m_spriteColorLimit = -1;	//スプライトの色変更時間（-1は変化中ではない）
	m_spriteColorDelay = -1;	//スプライトの変化ディレイ
	m_spriteColorTimer = -1;	//スプライトの変化タイマー
	//Shake
	m_spriteShakeList.clear();

}

void SpriteSupporter::SpriteMove(const CVector2& move, const int& moveTime,
	const int& moveDelay, const bool& relative) {

	//リストに追加や
	SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
	m_spriteMoveList.push_back(set);

}

void SpriteSupporter::SpriteRotation(const float& rot, const int& moveTime,
	const int& moveDelay, const bool& loopflag) {

	CQuaternion RotationZ;
	RotationZ.SetRotationDeg(CVector3().AxisZ(), rot);

	m_spriteRotation = RotationZ;
	m_spriteRotationLimit = moveTime;
	m_spriteRotationDelay = moveDelay;
	m_spriteLoopRotationFlag = loopflag;
	m_spriteRotationTimer = 0;
}

void SpriteSupporter::SpriteScale(const CVector3& scale, const int& moveTime, const int& moveDelay) {

	//リストに追加や
	SpriteScaleSet set = { scale ,CVector3::Zero(),moveTime,moveDelay , 0 ,false };
	m_spriteScaleList.push_back(set);

}
void SpriteSupporter::SpriteScale(const float& scale, const int& moveTime, const int& moveDelay) {
	CVector3 Scale = { scale ,scale ,1.0f };

	//リストに追加や
	SpriteScaleSet set = { Scale ,CVector3::Zero(),moveTime,moveDelay , 0 ,false };
	m_spriteScaleList.push_back(set);

}

void SpriteSupporter::SpriteColor(const CVector4& color, const int& moveTime, const int& moveDelay) {
	m_spriteColor = color;
	m_spriteColorLimit = moveTime;
	m_spriteColorDelay = moveDelay;
	m_spriteColorTimer = 0;
}

void SpriteSupporter::SpriteShake(const CVector2& move, const int& moveTime, const int& moveCount) {
	//m_spriteShakeMove.x = move.x;
	//m_spriteShakeMove.y = move.y;
	//m_spriteShakeLimit = moveTime;
	//m_spriteShakeCount = moveCount;
	//m_spriteShakeCounter = 0;
	//m_spriteShakeTimer = 0;
	////移動距離もここで計算
	//m_spriteShakeMove_OneFlame.x = (m_spriteShakeMove.x / (m_spriteShakeLimit * 2));
	//m_spriteShakeMove_OneFlame.y = (m_spriteShakeMove.y / (m_spriteShakeLimit * 2));

	//リストに追加や
	SpriteShakeSet set = { move ,{ (move.x / (moveTime * 2)),(move.y / (moveTime * 2)) },
		moveTime,moveCount , 0 ,0, false };
	m_spriteShakeList.push_back(set);

}

void SpriteSupporter::SpritePattern(const int& moveTime, const bool& loopflag, const int& overLimit, const bool& stopflag) {
	m_patternLimit = moveTime;
	m_patternTimer = 0;
	m_patternOverLimit = overLimit;
	m_patternLoopFlag = loopflag;
	m_patternStopFlag = stopflag;
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

	for (auto go = m_spriteScaleList.begin();
		go != m_spriteScaleList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_spriteScaleTimer >= 0) {

			if (go->m_spriteScaleTimer >= go->m_spriteScaleDelay) { //ディレイを考慮

				if (go->m_spriteScaleTimer == go->m_spriteScaleDelay) {
					//計算タイム
					go->m_spriteScaleMove = go->m_spriteScale - m_scale;
					go->m_spriteScaleMove /= (float)go->m_spriteScaleLimit;
				}

				m_scale += go->m_spriteScaleMove;

			}

			go->m_spriteScaleTimer++;

			if (go->m_spriteScaleTimer >= go->m_spriteScaleLimit + go->m_spriteScaleDelay) {
				//おしまひ
				go->m_spriteScaleDeleteFlag = true;
				go->m_spriteScaleTimer = -1;
			}
		}

	}
	
	//削除処理
	std::list<SpriteScaleSet>::iterator it;
	it = m_spriteScaleList.begin();
	while (it != m_spriteScaleList.end()) {
		if (it->m_spriteScaleDeleteFlag == true) {
			it = m_spriteScaleList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
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

	for (auto go = m_spriteShakeList.begin();
		go != m_spriteShakeList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_spriteShakeTimer >= 0) {

			//移動する
			m_position.x += go->m_spriteShakeMove_OneFlame.x;
			m_position.y += go->m_spriteShakeMove_OneFlame.y;

			go->m_spriteShakeTimer++;

			if (go->m_spriteShakeTimer == (go->m_spriteShakeLimit / 2)) {
				//折り返し
				go->m_spriteShakeMove_OneFlame.x *= -1.0f;
				go->m_spriteShakeMove_OneFlame.y *= -1.0f;

			}
			if (go->m_spriteShakeTimer >= go->m_spriteShakeLimit) {

				//1シェイク完了
				go->m_spriteShakeTimer = 0;
				go->m_spriteShakeMove_OneFlame.x *= -1.0f;
				go->m_spriteShakeMove_OneFlame.y *= -1.0f;

				//無限シェイクでないならシェイク回数を加算
				if (go->m_spriteShakeCount > 0) {
					go->m_spriteShakeCounter++;
					if (go->m_spriteShakeCount <= go->m_spriteShakeCounter) {
						//シェイク終了
						go->m_spriteShakeLimit = -1;
						go->m_spriteShakeDeleteFlag = true;
					}
				}
			}
		}

	}

	//削除処理
	std::list<SpriteShakeSet>::iterator it;
	it = m_spriteShakeList.begin();
	while (it != m_spriteShakeList.end()) {
		if (it->m_spriteShakeDeleteFlag == true) {
			it = m_spriteShakeList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

/// <summary>
/// パターン変更を実行
/// </summary>
void SpriteSupporter::SpritePatternUpdate() {

	if (m_patternLimit > -1) {
		m_patternTimer++;
		if (m_patternTimer >= m_patternLimit) {
			//パターン加算
			m_patternTimer = 0;
			m_nowPattern++;
		}
		//パターンがオーバー…
		if (m_nowPattern > m_maxPattern - 1) {
			//ループする？
			if (m_patternLoopFlag == false) {
				//アルファを0にして終了
				m_patternLimit = -1;
				m_nowPattern = m_maxPattern - 1;
				//停止しないならフェードアウト
				if (m_patternStopFlag == false) {
					SpriteColor({ m_mulColor.x,m_mulColor.y,m_mulColor.z, 0.0f }, 6, m_patternOverLimit);
					SpriteColorUpdate();
				}
			}
			else {
				//ループする
				m_nowPattern = 0;
			}
		}
	}

}