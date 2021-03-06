#pragma once
#include <vector>
#include "IGameObject.h"

#include "graphics/CGOM_Graphics.h"

/// <summary>
/// ゲームオブジェクトマネージャーです…
/// </summary>
	class CGameObjectManager {
		static CGameObjectManager* m_instance;
	public:

		CGameObjectManager();
		~CGameObjectManager();

		/// <summary>
		/// インスタンスを作成
		/// </summary>]
		/// <param name="obName">オブジェクト名</param>
		/// <returns>追加したオブジェクトのポインタ</returns>	
		template<class T>
		T* NewGO(const char* objName,const int priority = 0) {
			//インスタンスを生成する
			T* newObj = new T;
			//生成したインスタンスを可変長配列に追加する
			m_goList.push_back(newObj);
			//オブジェクト名を設定する
			newObj->SetObjectName(objName);
			//優先度を設定する
			newObj->SetPriority(priority);
			//追加したオブジェクトを戻す
			return newObj;
		}
		template<class T>
		T* NewGO(const wchar_t* objName, const int priority = 0) {
			//インスタンスを生成する
			T* newObj = new T;
			//生成したインスタンスを可変長配列に追加する
			m_goList.push_back(newObj);
			//オブジェクト名を設定する
			newObj->SetObjectName(objName);
			//優先度を設定する
			newObj->SetPriority(priority);
			//追加したオブジェクトを戻す
			return newObj;
		}

		/// <summary>
		/// オブジェクトの削除
		/// </summary>
		/// <param name="go">削除するオブジェクト</param>
		void DeleteGO(IGameObject* go) {

			//削除するオブジェクトを削除リストに追加しておく
			m_deleteList.push_back(go);

		}

		/// <summary>
		/// オブジェクトの名前で検索
		/// </summary>
		/// <param name="objName">探したいオブジェクトのネームキー</param>
		/// <param name="queryflag">trueにすると…
		/// ・発見したオブジェクトのクエリフラグがtrueならスルーするようになる
		/// ・返したオブジェクトのクエリフラグをtrueにする
		/// </param>
		/// <remarks>
		/// ネームキーはMakeHashで作ってね
		/// 
		/// ☆サンプルコード☆
		/// //プレイヤーを探す
		/// 
		/// Player* p = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"),false);
		/// 
		/// ※ハッシュ値を毎回生成するのが面倒なら前もってどっかで生成しとくといいんじゃないですかね
		/// </remarks>
		/// <returns>見つかったオブジェクトのアドレス</returns>
		template<class T>
		T* FindGO(const int objkey,bool queryflag = false) {
			
			bool m_findFlag = false; //発見したらtrueにする
			bool m_getFlag = false; //返すのがこのオブジェクトのアドレスで本当にOKならtrue
			T* ret;

			for (auto go : m_goList) {
				//名前検索
				if (go->GetObjectName() == objkey) {
					//名前が一致した

					m_getFlag = true; //フラグの初期化
					if (queryflag == true) { //クエリフラグの確認
						if (go->GetQueryFlag() == true) {
							m_getFlag = false; //このオブジェクトはクエリフラグオンなのでやめようね
						}
					}

					if (m_getFlag == true) { //trueならこいつで決定

					m_findFlag = true;

					if (queryflag == true) { //クエリフラグがtrueならオブジェクトのクエリフラグもtrueにする
						go->SetQueryFlag(true);
					}

#ifdef _DEBUG
					ret = dynamic_cast<T*>(go);
					if (ret == nullptr) {
						//型変換に失敗した。型間違ってない？？？
						std::abort();
					}
#else
						ret = (T*)go;
#endif
					}
				}
			}

			if (m_findFlag == true) {
				return ret;
			}
			else {
				return nullptr;
			}
		}

		/// <summary>
		/// 現在のオブジェクト数を返す
		/// </summary>
		/// <returns>オブジェクト数</returns>
		int AllObjects() {
			return (int)m_goList.size();
		}

		/// <summary>
		/// クエリフラグを全てfalseにする
		/// </summary>
		void QueryFlagReset() {
			for (auto go : m_goList) {
				go->SetQueryFlag(false);
			}
		}

		/// <summary>
		/// 検索した名前のオブジェクトがいくつあるかを返す
		/// </summary>
		/// <remarks>
		/// オブジェクトのクエリを行うときはこの関数を使って頑張ろう！
		/// �@この関数で検索対象となるオブジェクト数Xを取得
		/// �AX回ループする処理内でFindGOする
		/// 　必ずクエリフラグの引数をtrueにして実行すること
		/// �Bクエリ実行後QueryFlagResetを実行する
		/// 
		/// ☆サンプルコード☆
		/// //Enemyに対してクエリで攻撃を行う
		/// 
		/// int co = CGameObjectManager::GetInstance()->ObjCount<Enemy>(Enemyのネームキー);
		/// for( i = 0 ; i < co ; i++){ //発見したEnemyの数ループ
		/// 
		///		Enemy* enemy = CGameObjectManager::GetInstance()->FindGO<Enemy>(Enemyのネームキー,true);
		///		enemy->Attack();
		/// 
		/// }
		/// CGameObjectManager::GetInstance()->QueryFlagReset(); //クエリフラグをリセット（後片付け）
		/// 
		/// </remarks>
		/// <param name="objkey">オブジェクトキー</param>
		/// <returns>発見した数</returns>
		template<class T>
		int ObjCount(const int objkey) {
			int count = 0;
			//auto itr = m_goList.begin(); //先頭のイテレータ

			for (auto go : m_goList) {
				if (go->GetObjectName() == objkey) { //オブジェクトを発見！
					count++;
				}
				//itr++; //次の項目へ
			}
			return count;
		}

		/// <summary>
		/// 更新用関数
		/// </summary>
		void Execute();

		/// <summary>
		/// インスタンスを取得！
		/// </summary>
		/// <returns>インスタンスです</returns>
		static CGameObjectManager* CGameObjectManager::GetInstance() {

			if (m_instance == nullptr) { //オブジェクトが作られていなければ作る
				m_instance = new CGameObjectManager;
			}
			return m_instance;
		}

		/// <summary>
		/// メインレンダリングターゲットを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget* GetMainRenderTarget()
		{
			return m_cgom_Graphics->GetMainRenderTarget();
		}
		/// <summary>
		/// カメラ空間での深度値を書き込んでいるレンダリングターゲットを取得。
		/// </summary>
		/// <returns></returns>
		RenderTarget* GetDepthInViewRenderTarget()
		{
			return m_cgom_Graphics->GetDepthInViewRenderTarget();
		}

		/// <summary>
		/// フレームバッファのデプスステンシルビューを取得
		/// </summary>
		/// <returns></returns>
		ID3D11DepthStencilView* GetFrameBufferDepthStencilView() {
			return m_cgom_Graphics->GetFrameBufferDepthStencilView();
		}

		/// <summary>
		/// エフェクサーマネージャーを取得
		/// </summary>
		Effekseer::Manager* GetEffekseerManager() {
			return m_cgom_Graphics->GetEffekseerManager();
		}
		EffekseerRenderer::Renderer* GetEffekseerRender() {
			return m_cgom_Graphics->GetEffekseerRender();
		}

		ID3D11Texture2D* GetFrameBufferTexture() {
			return m_cgom_Graphics->GetFrameBufferTexture();
		}
		DXGI_FORMAT GetFormat() {
			return m_cgom_Graphics->GetFormat();
		}

	private:

		CGOM_Graphics * m_cgom_Graphics = nullptr;

		std::list<IGameObject*> m_goList;		//オブジェクトのリスト
		std::list<IGameObject*> m_deleteList;	//削除するオブジェクトのリスト

		/// <summary>
		/// 削除リストに積んだオブジェクトをまとめて削除する
		/// </summary>
		void CGameObjectManager::ExecuteDeleteGameObjects();

		/// <summary>
		/// プリレンダー
		/// </summary>
		void CGameObjectManager::PreRender();
		/// <summary>
		/// フォワードレンダー
		/// </summary>
		void CGameObjectManager::ForwordRender();
		/// <summary>
		/// ポストレンダー
		/// </summary>
		void CGameObjectManager::PostRender();

	};

	template<class T>
	/// <summary>
	/// インスタンスを作成
	/// </summary>
	/// <returns>追加したオブジェクトのポインタ</returns>
	static T* NewGO(const char* objName, const int priority = 0) {

		return CGameObjectManager::GetInstance()->NewGO<T>(objName);
	}

	/// <summary>
	/// オブジェクトの削除
	/// </summary>
	/// <param name="go">削除するオブジェクト</param>
	static void DeleteGO(IGameObject* go) {

		CGameObjectManager::GetInstance()->DeleteGO(go);

	}

	/// <summary>
	/// オブジェクトの名前で検索
	/// </summary>
	/// <param name="objName">探したいオブジェクト名</param>
	/// <returns>見つかったオブジェクトのアドレス</returns>
	template<class T>
	static T* FindGO(const char* objName) {
		CGameObjectManager::GetInstance()->FindGO(objName);
	}
