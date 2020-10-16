#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //すでに出ているためクラッシュ
		}

		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;

		m_cgom_Graphics = new CGOM_Graphics;
		m_cgom_Graphics->Init();
	}

	CGameObjectManager::~CGameObjectManager() {

		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;

	}

	/// <summary>
	/// 更新関数
	/// </summary>
	void CGameObjectManager::Execute() {

		//！アクティブフラグがtrueだと更新されないよ！

		///////////////////////////////////////////////
		//ここから更新処理
		///////////////////////////////////////////////

		//登録されている背景スプライトの更新関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//登録されているゲームオブジェクトの更新関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//登録されているスプライトの更新関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

		///////////////////////////////////////////////
		//ここから描画処理
		///////////////////////////////////////////////

		//準備する
		m_cgom_Graphics->Standby();

		{
			//プリレンダリング
			PreRender();

			//フォワードレンダリング
			ForwordRender();

			//デバッグ
			m_cgom_Graphics->DebugDraw();

			//エフェクサー
			m_cgom_Graphics->EffectRender(false);

			//ポストレンダリング
			PostRender();

		}

		///////////////////////////////////////////////
		//ここから通常レンダリング。
		///////////////////////////////////////////////

		m_cgom_Graphics->EndSet();

		//登録されているスプライトの描画関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//エフェクサー
		m_cgom_Graphics->EffectRender(true);

		//エフェクトデータの削除
		EffekseerSupporter::GetInstance()->EffectClear();
		//削除リストに積まれたオブジェクトをまとめて消去する
		ExecuteDeleteGameObjects();

	}

	/// <summary>
	/// 削除する予定のオブジェクトをまとめて消去する
	/// </summary>
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		//削除リストの要素数分ループする
		for (auto go = m_deleteList.begin();
			go != m_deleteList.end();
			go++) {

			//引数で指定されたゲームオブジェクトを検索
			for (auto it = m_goList.begin();
				it != m_goList.end();
				it++) {

				if (*it == *go) {
					//見つかったので削除
					delete *it; //メモリ解放
					m_goList.erase(it); //可変長配列から除去
					return;
				}
			}
		}

		//削除リストをリセット
		m_deleteList.clear();

	}

	void CGameObjectManager::PreRender() {

		m_cgom_Graphics->PreRender();

	}

	void CGameObjectManager::ForwordRender(){

		m_cgom_Graphics->ForwordRender();

		//登録されているスプライトの描画関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//登録されているゲームオブジェクトの描画関数を呼び出す
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

	}

	void CGameObjectManager::PostRender() {

		m_cgom_Graphics->PostRender();

	}

