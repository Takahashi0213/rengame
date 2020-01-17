#pragma once

	class IGameObject
	{
	public:
		/// <summary>
		/// オブジェクトタグ
		/// 上から順番に実行される
		/// </summary>
		enum objectTag {
			t_BackSprite, //背景スプライト
			t_Other,
			t_Sprite,	//スプライトじゃなくてもポストエフェクト後にレンダリングしたいものはここに分類するといいと思いますよ 知らんけど
		};

		IGameObject();
		~IGameObject();
		virtual void Update() = 0;
		virtual void Render() = 0;

		/// <summary>
		/// オブジェクト名からネームキーを設定
		/// </summary>
		/// <param name="name">設定するオブジェクト名</param>
		void SetObjectName(const char* name) {
			int m_name = Hash::MakeHash(name);
			m_nameKey = m_name;
		}

		/// <summary>
		/// ネームキーを返す
		/// </summary>
		/// <returns>ネームキー</returns>
		int GetObjectName() {
			return m_nameKey;
		}

		/// <summary>
		/// アクティブフラグをセットする
		/// </summary>
		/// <param name="flag">設定するフラグ</param>
		void SetActiveFlag(bool flag) {
			m_activeFlag = flag;
		}

		/// <summary>
		/// アクティブフラグを取得する
		/// </summary>
		/// <returns>このオブジェクトのアクティブフラグ</returns>
		bool GetActiveFlag() {
			return m_activeFlag;
		}

		/// <summary>
		/// クエリフラグをセットする
		/// </summary>
		/// <param name="flag">設定するフラグ</param>
		void SetQueryFlag(bool flag) {
			m_queryFlag = flag;
		}

		/// <summary>
		/// クエリフラグを取得する
		/// </summary>
		/// <returns>このオブジェクトのクエリフラグ</returns>
		bool GetQueryFlag() {
			return m_queryFlag;
		}

		/// <summary>
		/// オブジェクトタグを設定する
		/// </summary>
		/// <param name="tag">タグ</param>
		void SetObjectTag(objectTag tag) {
			m_tag = tag;
		}

		/// <summary>
		/// オブジェクトタグを取得する
		/// </summary>
		/// <returns>タグ</returns>
		objectTag GetObjectTag() {
			return m_tag;
		}

		/// <summary>
		/// 優先度を設定
		/// </summary>
		/// <param name="priority">優先度（最小は0、最大はMAX_PRIORITY）</param>
		void SetPriority(int priority) {
			if (priority > MAX_PRIORITY) {
				priority = MAX_PRIORITY;
			}
			if (priority < 0) {
				priority = 0;
			}
			m_priority = priority;
		}

		/// <summary>
		/// 優先度を取得
		/// </summary>
		/// <returns>優先度（最小は0、最大はMAX_PRIORITY）</returns>
		int GetPriority() {
			return m_priority;
		}

	private:
		int m_nameKey = 0;						//ネームキー
		int m_priority = 0;						//優先度
		bool m_activeFlag = true;				//アクティブフラグ
		bool m_queryFlag = false;				//クエリ用フラグ

		objectTag m_tag = t_Other;				//オブジェクトタグ
	};

