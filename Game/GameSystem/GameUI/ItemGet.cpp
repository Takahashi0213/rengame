#include "stdafx.h"
#include "ItemGet.h"
#include "GameScene/SceneManager.h"

ItemGet::ItemGet()
{
	//準備
	m_itemWindow = NewGO<SpriteRender>("ItemWindow", SpritePriority);
	m_itemWindow->ChangeSliceSprite({ 300.0f,105.0f });
	m_itemWindow->Set3Slice(300.0f);
	m_itemWindow->Init(L"Assets/sprite/window9.dds",
		ItemWindowDefScale.x,
		ItemWindowDefScale.y,
		SpritePriority);
	m_itemWindow->SetPosition(ItemWindowDefPos);
	m_itemWindow->SetAlpha(0.0f);
	//アイテム名
	m_itemName = NewGO<FontRender>("ItemName", SpritePriority);
	m_itemName->SetPivot({ 0.5f,0.5f });
	m_itemName->SetText(L"テスト名");
	m_itemName->SetColor(ItemNameColor);
	m_itemName->SetScale(ItemNameScale);
	m_itemName->SetPosition({ ItemNameDefPos.x,ItemNameDefPos.y });
	m_itemName->SetAlpha(0.0f);
	//説明
	m_itemSetumei = NewGO<FontRender>("ItemSetumei", SpritePriority);
	m_itemSetumei->SetPivot({ 0.5f,0.5f });
	m_itemSetumei->SetText(L"アイテム説明文です");
	m_itemSetumei->SetColor(ItemSetumeiColor);
	m_itemSetumei->SetScale(ItemSetumeiScale);
	m_itemSetumei->SetPosition({ ItemSetumeiDefPos.x,ItemSetumeiDefPos.y });
	m_itemSetumei->SetAlpha(0.0f);

	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));
}

ItemGet::~ItemGet()
{
}

void ItemGet::ItemGetUpdate() {

	if (m_nowItemNo != -1) {
		//準備
		if (m_effectTimer == 0.0f) {
			//エフェクト表示
			m_itemGetEffect = GameEffect::GetInstance()->GetInstance_SpriteAnime()->
				NewAnimationSprite_pt(GameEffect_AnimationSprite::Anime_Name::Anime_ItemGet,
					ItemGetEffectDefPos, CVector3::One(), SpritePriority);
			//プレイヤーをカメラに向ける
			CVector3 front = { 0.0f, 0.0f,-1.0f };
			CVector3 playerPos = m_player->GetPosition();
			CVector3 diff = playerPos - g_camera3D.GetPosition();
			diff.Normalize();
			diff.y = 0.0f;
			CQuaternion qRot;
			qRot.SetRotation(front, diff);
			m_player->SetRotation(qRot);
			m_player->SetClearAnimationFlag(true);
			CameraSupporter::GetInstance()->CameraMove_Zoom(160.0f, 20, 0);
		}

		if (m_effectTimer >= 0.3f && m_effectCameraFlag == false) {
			CameraSupporter::GetInstance()->CameraMove_Zoom(60.0f, 10, 0, true);
			m_effectCameraFlag = true;
		}

		if (m_effectTimer >= 0.4f && m_effectLightFlag == false) {
			//エフェクト表示
			m_itemGetEffect_Light = GameEffect::GetInstance()->GetInstance_SpriteAnime()->
				NewAnimationSprite_pt(GameEffect_AnimationSprite::Anime_Name::Anime_ItemLoop,
					ItemGetEffectLightDefPos, CVector3::One(), SpritePriority);
			//アイテム画像表示
			if (m_itemSprite != nullptr) {
				DeleteGO(m_itemSprite);
			}
			m_itemSprite = NewGO<SpriteRender>("ItemGet_ItemSprite", SpritePriority);
			m_itemSprite->SetAlpha(0.0f);
			m_itemSprite->SetPosition(ItemSpriteDefPos);
			m_itemSprite->Init(SceneManager::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_nowItemNo].Item_FilaPath_Sprite,
				100.0f, 100.0f, 0);
			m_itemSprite->SetAlpha(1.0f);
			//ウィンドウ表示
			m_itemWindow->m_spriteSupporter.SpriteColor({ 1.0f, 1.0f, 1.0f, 1.0f }, FadeSpeed, 0);
			//アイテム名表示
			m_itemName->SetText(SceneManager::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_nowItemNo].Item_Name);
			m_itemName->m_fontSupporter.FontColorSet(ItemNameColor, FadeSpeed, 0);
			//説明文表示
			m_itemSetumei->SetText(SceneManager::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_nowItemNo].Item_Explanation);
			m_itemSetumei->m_fontSupporter.FontColorSet(ItemSetumeiColor, FadeSpeed, 0);

			m_effectLightFlag = true;
		}

		int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		if (m_effectTimer >= EffectLimit && Left_Key == MouseSupporter::Release_Push) {
			//片付け
			m_itemGetEffect->m_spriteSupporter.SpriteColor({ 1.0f, 1.0f, 1.0f, 0.0f }, FadeSpeed, 0);
			m_itemGetEffect_Light->m_spriteSupporter.SpriteColor({ 1.0f, 1.0f, 1.0f, 0.0f }, FadeSpeed, 0);
			m_itemSprite->m_spriteSupporter.SpriteColor({ 1.0f, 1.0f, 1.0f, 0.0f }, FadeSpeed, 0);
			m_itemWindow->m_spriteSupporter.SpriteColor({ 1.0f, 1.0f, 1.0f, 0.0f }, FadeSpeed, 0);
			m_itemName->m_fontSupporter.FontColorSet({ ItemNameColor.x,ItemNameColor.y,ItemNameColor.z,0.0f }, FadeSpeed, 0);
			m_itemSetumei->m_fontSupporter.FontColorSet({ ItemNameColor.x,ItemNameColor.y,ItemNameColor.z,0.0f }, FadeSpeed, 0);
			//終了フラグ
			m_effectTimer = 0.0f;
			m_effectEndFlag = true;
		}

		if (m_effectEndFlag == true && m_effectTimer >= 0.2f) {
			//終了
			m_nowItemNo = -1;
			SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = false;
			SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = false;	//イベントムーヴ
			m_player->SetRotFlag(true);
			m_player->SetClearAnimationFlag(false);
			ItemGet_NoEffect(m_nowItemNo);		//アイテムを取得
		}

		//時間加算
		m_effectTimer += CGameTime::GetFrameDeltaTime();
		//フチ色更新
		m_itemSetumei->SetShadowParam(true, ItemSetumeiOutLineOffset,
			{ ItemSetumeiOutLineColor.x,ItemSetumeiOutLineColor.y,ItemSetumeiOutLineColor.z ,m_itemSetumei->GetColor().w });
	}

}

void ItemGet::ItemGetEffect(const int& itemNo) {
	//エフェクト中でなければ準備する
	if (m_nowItemNo == -1) {
		m_nowItemNo = itemNo;
		m_effectTimer = 0.0f;
		m_effectCameraFlag = false;
		m_effectLightFlag = false;
		m_effectEndFlag = false;
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = true;
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = true;	//イベントムーヴ
		m_player->SetMoveTarget(m_player->GetPosition());
		m_player->SetRotFlag(false);
	}
}

void ItemGet::ItemGet_NoEffect(const int& itemNo) {
	SceneManager::GetInstance()->GetItemSave()->SetItemSave(itemNo);
}