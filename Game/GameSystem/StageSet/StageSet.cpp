#include "stdafx.h"
#include "StageSet.h"
#include "GameSystem/Box/BoxMaker.h"

StageSet* StageSet::m_instance = nullptr;

StageSet::StageSet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

StageSet::~StageSet()
{
}

void StageSet::InitStage(const wchar_t* stage_name) {
	
	//最初にステージとレベルを削除
	DeleteStage();

	int Size = m_stageData.GetStageListSize();
	
	//どのレベルかチェックするためのループ
	for (int i = 0; i < Size; i++) {
		//一致する場合そいつに決定する
		if (wcscmp(m_stageData.GetStageName(i), stage_name) == 0) {
			m_stageNo = i;	//お前しか…いない！
			break;
		}
	}

	//エラーチェック
	if (m_stageNo == -1) {
		//どれにも引っかかっていないためエラー
		std::abort();
	}

	//ここから生成処理

	//ステージ番号をセット
	GameData::GetInstance()->SetNowStageNo(m_stageNo);
	//ステージ場所をセット
	GameData::GetInstance()->SetPlace(m_stageData.GetStagePlace(m_stageNo));
	//環境光を設定
	LightMaker::GetInstance()->SetAmbientColor(m_stageData.GetStageAmbientColor(m_stageNo));
	//箱の全削除
	BoxMaker::GetInstance()->BoxAllDelete();

	//生成タイム
	CreateStage(m_stageData.GetStageModel(m_stageNo),
		m_stageData.GetStageLevel(m_stageNo));
}

void StageSet::InitStage(const int& stage_nom) {

	//最初にステージとレベルを削除
	DeleteStage();

	//エラーチェック
	if (stage_nom == -1) {
		//どれにも引っかかっていないためエラー
		std::abort();
	}

	//ここから生成処理

	//ステージ番号をセット
	GameData::GetInstance()->SetNowStageNo(stage_nom);
	//ステージ場所をセット
	GameData::GetInstance()->SetPlace(m_stageData.GetStagePlace(stage_nom));
	//環境光を設定
	LightMaker::GetInstance()->SetAmbientColor(m_stageData.GetStageAmbientColor(stage_nom));
	//箱の全削除
	BoxMaker::GetInstance()->BoxAllDelete();

	//生成タイム
	CreateStage(m_stageData.GetStageModel(stage_nom),
		m_stageData.GetStageLevel(stage_nom));
}

void StageSet::CreateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath) {

	//ステージの生成
	m_bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	m_bg->Init(stage_filePath);

	//レベルの生成
	m_levelSet.Init(level_filePath);

}

void StageSet::DeleteStage() {

	//メンバステージ番号をリセット
	m_stageNo = -1;
	//ステージ番号をリセット
	GameData::GetInstance()->SetNowStageNo(-1);
	//レベル番号をリセット
	GameData::GetInstance()->SetNowMapLevel(-1);

	//背景の削除
	if (m_bg != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_bg);
		m_bg = nullptr;
	}

	//レベルの削除
	m_levelSet.LevelDelete();

}

const GameData::Place_Data StageSet::GetStagePlace(const wchar_t* stage_name) {

	int Size = m_stageData.GetStageListSize();
	int stageNo = -1;

	//どのレベルかチェックするためのループ
	for (int i = 0; i < Size; i++) {
		//一致する場合そいつに決定する
		if (wcscmp(m_stageData.GetStageName(i), stage_name) == 0) {
			stageNo = i;	//お前しか…いない！
			break;
		}
	}

	//エラーチェック
	if (stageNo == -1) {
		//どれにも引っかかっていないためエラー
		std::abort();
	}

	return m_stageData.GetStagePlace(stageNo);
}