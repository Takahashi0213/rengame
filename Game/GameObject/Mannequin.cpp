#include "stdafx.h"
#include "Mannequin.h"

Mannequin::Mannequin()
{
	//モデル準備
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_wait].Load(L"Assets/animData/MannequinStay.tka");
	m_animClips[enAnimationClip_wait].SetLoopFlag(true);

	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Mannequin", 1);
	m_modelRender->Model_Init_Anim(L"Assets/modelData/Mannequin.cmo",
		m_animClips, enAnimationClip_Num);
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetRotation(m_rotation);
	m_modelRender->SetScale(Scale);
	m_modelRender->PlayAnimation(enAnimationClip_wait);

	//シャドウレシーバーにする。
	m_modelRender->SetShadowReciever(true);

	//シャドウキャスターにも登録
	m_modelRender->SetShadowCasterFlag(true);

	//キャラコン！！
	m_charaCon.Init(
		60.0f,  //キャラクターの半径。
		150.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::EnemyObj;
}


Mannequin::~Mannequin()
{
	//片付ける
	if (m_modelRender != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	}
	m_charaCon.RemoveRigidBoby();
}

void Mannequin::Update() {

	//モノクロ化
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//クリエイトモード中は一切の更新をしない
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	//箱との衝突判定
	bool DeathFlag = BoxAttackSearch(m_position);
	if (DeathFlag == true && m_deathEffectFlag == false) {
		//死んじゃった
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//経験値を獲得
		EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::EnemyDeath,
			false, m_position.x, m_position.y, m_position.z);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Enemy_Death.wav");	//SE
		CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
		m_modelRender = nullptr;
		CGameObjectManager::GetInstance()->DeleteGO(this);
		m_deathEffectFlag = true;
	}

	//キャラコン実行
	m_position = m_charaCon.Execute(1.0f, CVector3::Zero());
	//ModelRender更新
	if (m_modelRender != nullptr) {
		m_modelRender->SetPosition(m_position);
	}
}
void Mannequin::Render() {

}
