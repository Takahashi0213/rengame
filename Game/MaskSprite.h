#pragma once
class MaskSprite
{
public:
	MaskSprite();
	~MaskSprite();

	void Draw();

	//設定色々
	//全てのsubFlagはfalseならメインスプライト、trueならサブスプライトを変更します

	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition(const CVector3& pos, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Position = pos;
		}
		else {
			m_subSpriteList[list].subData.Position = pos;
		}
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	const CVector3 GetPosition(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Position;
		}
		else {
			return m_subSpriteList[list].subData.Position;		//サブ
		}
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	void SetRotation(const CQuaternion& rot, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Rotation = rot;
		}
		else {
			m_subSpriteList[list].subData.Rotation = rot;		//サブ
		}
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	const CQuaternion GetRotation(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Rotation;
		}
		else {
			return m_subSpriteList[list].subData.Rotation;		//サブ
		}
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	void SetScale(const CVector3& scl, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Scale = scl;
		}
		else {
			m_subSpriteList[list].subData.Scale = scl;		//サブ
		}
	}
	void SetScale(const float& scl, const int& list = -1) { //便利Ver
		if (list == -1) {
			m_mainSpriteData.Scale.x = scl;
			m_mainSpriteData.Scale.y = scl;
		}
		else {
			m_subSpriteList[list].subData.Scale.x = scl;
			m_subSpriteList[list].subData.Scale.y = scl;
		}
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	const CVector3 GetScale(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Scale;
		}
		else {
			return m_subSpriteList[list].subData.Scale;
		}
	}
	/// <summary>
	/// ピボットを設定
	/// </summary>
	void SetPivot(const CVector2& pivot, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Pivot = pivot;
		}
		else {
			m_subSpriteList[list].subData.Pivot = pivot;
		}
	}
	/// <summary>
	/// ピボットを取得
	/// </summary>
	CVector2 GetPivot(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSpriteData.Pivot;
		}
		else {
			return m_subSpriteList[list].subData.Pivot;
		}
	}

	/// <summary>
	/// サイズを設定
	/// </summary>
	void SetSize(const CVector2& size, const int& list = -1) {
		
		if (list == -1) {
			m_mainSpriteData.Wide = size.x;
			m_mainSpriteData.High = size.y;
		}
		else {
			m_subSpriteList[list].subData.Wide = size.x;
			m_subSpriteList[list].subData.High = size.y;
		}
	}

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	void SetMulColor(const CVector4& mulColor, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.MulColor = mulColor;
			m_mainSprite.SetMulColor(m_mainSpriteData.MulColor);
		}
		else {
			m_subSpriteList[list].subData.MulColor = mulColor;
			m_subSpriteList[list].sprite->SetMulColor(m_subSpriteList[list].subData.MulColor);
		}
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	CVector4 GetMulColor(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSpriteData.MulColor;
		}
		else {
			return m_subSpriteList[list].subData.MulColor;
		}
	}
	
	/// <summary>
	/// レンダーモードの変更
	/// </summary>
	void ChangeRenderMode(const Sprite_RenderMode srm, const int& list) {
		if (list >= 0) {
			m_subSpriteList[list].sprite->m_renderMode = srm;
		}
		else {
			std::abort(); //異常な値です！！！
		}
	}

	/// <summary>
	/// サブスプライトの追加
	/// </summary>
	Sprite* AddSubSprite(const wchar_t* texFilePath, float w, float h);

	//取得
	Sprite* GetMainSprite() {
		return &m_mainSprite;
	}
	Sprite* GetSubList_Sprite(int i) {
		return m_subSpriteList[i].sprite;
	}


private:
	//ステートを作成
	void MaskSprite::CreateDepthStencilState();

	//深度ステンシル
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilState* m_depthStencilState_Def = nullptr;
	ID3D11DepthStencilState* m_depthStencilState_Z = nullptr;

	//スプライトのデータ
	struct SpriteData
	{
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		float Wide = 0.0f;	//幅！
		float High = 0.0f;	//高さ！
		CVector4 MulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<乗算カラー。
	};

	//メインスプライト
	SpriteData m_mainSpriteData;
	Sprite m_mainSprite;

	//サブスプライト！！
	struct SubSpriteData {
		Sprite* sprite;
		SpriteData subData;
	};
	std::vector<SubSpriteData> m_subSpriteList;		//追加分

};

