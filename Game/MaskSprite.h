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
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3 pos, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Position = pos;
		}
		else {
			m_subSpriteData.Position = pos;
		}
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3 GetPosition(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Position;
		}
		else {
			return m_subSpriteData.Position;
		}
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Rotation = rot;
		}
		else {
			m_subSpriteData.Rotation = rot;
		}
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	const CQuaternion GetRotation(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Rotation;
		}
		else {
			return m_subSpriteData.Rotation;
		}
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scr">拡大率</param>
	void SetScale(const CVector3 scl, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Scale = scl;
		}
		else {
			m_subSpriteData.Scale = scl;
		}
	}
	void SetScale(const float scl, bool subFlag = false) { //便利Ver
		if (subFlag == false) {
			m_mainSpriteData.Scale.x = scl;
			m_mainSpriteData.Scale.y = scl;
		}
		else {
			m_subSpriteData.Scale.x = scl;
			m_subSpriteData.Scale.y = scl;
		}
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	/// <returns>拡大率</returns>
	const CVector3 GetScale(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Scale;
		}
		else {
			return m_subSpriteData.Scale;
		}
	}
	/// <summary>
	/// ピボットを設定
	/// </summary>
	/// <param name="pivot">ピボット</param>
	void SetPivot(const CVector2 pivot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Pivot.x = pivot.x;
			m_mainSpriteData.Pivot.y = pivot.y;
		}
		else {
			m_subSpriteData.Pivot.x = pivot.x;
			m_subSpriteData.Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// ピボットを取得
	/// </summary>
	/// <returns>ピボット</returns>
	CVector2 GetPivot(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSpriteData.Pivot;
		}
		else {
			return m_subSpriteData.Pivot;
		}
	}

	/// <summary>
	/// サイズを設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(CVector2 size, bool subFlag = false) {
		if (subFlag == false) {
			m_mainSpriteData.Wide = size.x;
			m_mainSpriteData.High = size.y;
		}
		else {
			m_subSpriteData.Wide = size.x;
			m_subSpriteData.High = size.y;
		}

	}

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.MulColor = mulColor;
			m_mainSprite.SetMulColor(m_mainSpriteData.MulColor);
		}
		else {
			m_subSpriteData.MulColor = mulColor;
			m_subSprite.SetMulColor(m_subSpriteData.MulColor);
		}
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSpriteData.MulColor;
		}
		else {
			return m_subSpriteData.MulColor;
		}
	}
	
	Sprite* GetMainSprite() {
		return &m_mainSprite;
	}
	Sprite* GetSubSprite() {
		return &m_subSprite;
	}

private:
	void MaskSprite::CreateDepthStencilState();

	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilState* m_depthStencilState2 = nullptr;

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

	SpriteData m_mainSpriteData;	//メインスプライト
	SpriteData m_subSpriteData;		//サブスプライト（マスクを作るときに使います！）

	Sprite m_mainSprite;
	Sprite m_subSprite;

};

