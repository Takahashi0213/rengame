#pragma once

/// <summary>
/// マウスオーバーチェック
/// </summary>
class MouseOver
{
public:

	/// <summary>
	/// マウス座標をチェックしてこいつに被ってるかチェック！
	/// </summary>
	/// <param name="smr">スキンモデルレンダー</param>
	/// <returns>結果（trueならマウスカーソルは衝突している）</returns>
	bool MouseOverCheck(const SkinModelRender* smr, const CVector3 pos, const CQuaternion rot, const CVector3 scl);

private:

	//一時保存
	SkinModel* m_model = nullptr;
	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;

};

