#pragma once

/// <summary>
/// マウスオーバーチェックくん
/// </summary>
class MouseOver
{
public:

	/// <summary>
	/// マウス座標をチェックしてこいつに被ってるかチェーーーック！
	/// </summary>
	/// <param name="smr">スキンモデルレンダー</param>
	/// <returns>結果（trueならマウスカーソルは衝突しているゾイ）</returns>
	bool MouseOverCheck(SkinModelRender* smr, CVector3 pos, CQuaternion rot, CVector3 scl);

private:

	//一時保存
	SkinModel* m_model = nullptr;
	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;

};

