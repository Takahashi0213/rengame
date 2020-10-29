#include "stdafx.h"
#include "FontSupporter.h"


FontSupporter::FontSupporter()
{
}


FontSupporter::~FontSupporter()
{
}

void FontSupporter::FontSupporter_Update() {

	//情報を取得
	FontDataUpdate();

	//更新
	FontMoveUpdate();
	FontColorUpdate();

	//情報を返す
	FontDataReturn();

}

void FontSupporter::FontDataUpdate() {

	m_position.x = m_fontRender->GetPosition().x;
	m_position.y = m_fontRender->GetPosition().y;
	m_mulColor = m_fontRender->GetColor();
}

void FontSupporter::FontDataReturn() {

	m_fontRender->SetPosition(m_position);
	m_fontRender->SetColor(m_mulColor);

}

void FontSupporter::FontDelayReset() {

	m_fontMoveList.clear();
	m_fontColorLimit = -1;
	m_fontColorDelay = -1;
	m_fontColorTimer = -1;

}

//ここから設定

void FontSupporter::FontMoveSet(const CVector2& move, const int& movespeed, const int& delay, const bool& relative) {

	//ねんのため
	//FontDataUpdate();

	//リストに追加
	FontMoveData set = { move,{ 0.0f,0.0f },movespeed,delay,0,relative,false };
	m_fontMoveList.push_back(set);

}

void FontSupporter::FontColorSet(const CVector4& color, const int& moveTime, const int& moveDelay) {
	m_fontColor = color;
	m_fontColorLimit = moveTime;
	m_fontColorDelay = moveDelay;
	m_fontColorTimer = 0;
}

//ここから更新

void FontSupporter::FontMoveUpdate() {

	//リスト分ループ
	for (auto go = m_fontMoveList.begin();
		go != m_fontMoveList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_fontMoveTimer >= 0) {

			if (go->m_fontMoveTimer >= go->m_fontMoveDelay) { //ディレイを考慮

				 //移動距離を計算
				if (go->m_fontMoveTimer == go->m_fontMoveDelay) {
					if (go->m_fontMoveRelative == false) { //指定された座標へ移動
						go->m_fontMoveSpeed.x = go->m_fontMovePos.x - m_position.x;
						go->m_fontMoveSpeed.y = go->m_fontMovePos.y - m_position.y;
					}
					else { //相対移動
						go->m_fontMoveSpeed.x = go->m_fontMovePos.x;
						go->m_fontMoveSpeed.y = go->m_fontMovePos.y;
					}
					go->m_fontMoveSpeed.x /= (float)go->m_fontMoveLimit;
					go->m_fontMoveSpeed.y /= (float)go->m_fontMoveLimit;
				}

				m_position.x += go->m_fontMoveSpeed.x;
				m_position.y += go->m_fontMoveSpeed.y;

			}

			go->m_fontMoveTimer++;

			if (go->m_fontMoveTimer >= go->m_fontMoveLimit + go->m_fontMoveDelay) {
				//おしまい
				go->m_fontMoveDeleteFlag = true;
				go->m_fontMoveTimer = -1;
			}
		}
	}

	//削除処理
	std::list<FontMoveData>::iterator it;
	it = m_fontMoveList.begin();
	while (it != m_fontMoveList.end()) {
		if (it->m_fontMoveDeleteFlag == true) {
			it = m_fontMoveList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

void FontSupporter::FontColorUpdate() {

	//タイマーが0以上なら実行中
	if (m_fontColorTimer >= 0) {

		if (m_fontColorTimer >= m_fontColorDelay) { //ディレイを考慮

			if (m_fontColorTimer == m_fontColorDelay) {
				//計算タイム
				m_fontColorMove = m_fontColor - m_mulColor;
				m_fontColorMove.x /= (float)m_fontColorLimit;
				m_fontColorMove.y /= (float)m_fontColorLimit;
				m_fontColorMove.z /= (float)m_fontColorLimit;
				m_fontColorMove.w /= (float)m_fontColorLimit;
			}

			m_mulColor.x += m_fontColorMove.x;
			m_mulColor.y += m_fontColorMove.y;
			m_mulColor.z += m_fontColorMove.z;
			m_mulColor.w += m_fontColorMove.w;

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

		m_fontColorTimer++;

		if (m_fontColorTimer >= m_fontColorLimit + m_fontColorDelay) {
			//おしまい
			m_fontColorTimer = -1;
		}
	}

}