#pragma once

/// <summary>
/// �}�E�X�I�[�o�[�`�F�b�N����
/// </summary>
class MouseOver
{
public:

	/// <summary>
	/// �}�E�X���W���`�F�b�N���Ă����ɔ���Ă邩�`�F�[�[�[�b�N�I
	/// </summary>
	/// <param name="smr">�X�L�����f�������_�[</param>
	/// <returns>���ʁitrue�Ȃ�}�E�X�J�[�\���͏Փ˂��Ă���]�C�j</returns>
	bool MouseOverCheck(SkinModelRender* smr, CVector3 pos, CQuaternion rot, CVector3 scl);

private:

	//�ꎞ�ۑ�
	SkinModel* m_model = nullptr;
	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;

};

