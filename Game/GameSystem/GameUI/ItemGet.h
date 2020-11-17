#pragma once

/// <summary>
/// �A�C�e���Q�b�g���o
/// </summary>
class ItemGet
{
public:
	ItemGet();
	~ItemGet();

	/// <summary>
	/// Game�ɌĂ�ł��炤�A�b�v�f�[�g
	/// </summary>
	void ItemGetUpdate();

	/// <summary>
	/// �A�C�e�����擾����
	/// 
	/// ���o������������S�čs�����߁A
	/// �A�C�e�����擾����Ƃ��͂��ꂳ���ǂ�ł�����OK
	/// </summary>
	/// <param name="itemNo">�A�C�e���ԍ�</param>
	void ItemGetEffect(const int& itemNo);

	/// <summary>
	/// �A�C�e�����T�C�����g�擾����
	/// </summary>
	/// <param name="itemNo">�A�C�e���ԍ�</param>
	void ItemGet_NoEffect(const int& itemNo);

private:
	int m_nowItemNo = -1;											//���݉��o���̃A�C�e��No
	Player* m_player = nullptr;										//�v���C���[�i���o�p�j

	float m_effectTimer = 0.0f;										//�G�t�F�N�g�^�C�}�[
	const float EffectLimit = 0.6f;									//�G�t�F�N�g���ԁi�����t�܂ł̎��ԁj

	SpriteRender* m_itemGetEffect = nullptr;						//�A�C�e���Q�b�g�G�t�F�N�g
	const CVector3 ItemGetEffectDefPos = { 0.0f,400.0f,0.0f };		//�A�C�e���Q�b�g�G�t�F�N�g�̍��W

	SpriteRender* m_itemGetEffect_Light = nullptr;					//�A�C�e���Q�b�g�G�t�F�N�g�̌�
	const CVector3 ItemGetEffectLightDefPos = { 0.0f,300.0f,0.0f };	//�A�C�e���Q�b�g�G�t�F�N�g�i���j�̍��W

	SpriteRender* m_itemSprite = nullptr;							//�A�C�e���A�C�R��
	const CVector3 ItemSpriteDefPos = { 0.0f,100.0f,0.0f };			//�A�C�e���̍��W

	SpriteRender* m_itemWindow= nullptr;							//�A�C�e���E�B���h�E
	const CVector3 ItemWindowDefPos = { 0.0f,-200.0f,0.0f };		//�A�C�e���E�B���h�E�̊�b���W
	const CVector3 ItemWindowDefScale = { 500.0f,80.0f,0.0f };		//�A�C�e���E�B���h�E�̑傫��

	FontRender* m_itemName = nullptr;								//�A�C�e����
	const CVector3 ItemNameDefPos = { -70.0f,-175.0f,0.0f };		//�A�C�e�����̊�b���W
	const float ItemNameScale = 0.6f;								//�A�C�e�����̃t�H���g�T�C�Y
	const CVector4 ItemNameColor = { 0.1f,0.1f,1.0f,1.0f };			//�A�C�e�����̐F

	FontRender* m_itemSetumei = nullptr;							//�A�C�e������
	const CVector3 ItemSetumeiDefPos = { -150.0f,-250.0f,0.0f };	//�A�C�e�������̊�b���W
	const float ItemSetumeiScale = 0.5f;							//�A�C�e�������̃t�H���g�T�C�Y
	const CVector4 ItemSetumeiColor = CVector4::White();			//�A�C�e�������̐F
	const CVector4 ItemSetumeiOutLineColor = { 0.1f,0.1f,1.0f,1.0f };//�A�C�e�������t�`�̐F
	const float ItemSetumeiOutLineOffset = 1.0f;					//�A�C�e�������t�`�̃I�t�Z�b�g

	bool m_effectCameraFlag = false;
	bool m_effectLightFlag = false;
	bool m_effectEndFlag = false;

	const int SpritePriority = 6;									//�D��x
	const int FadeSpeed = 10;										//�t�F�[�h���x

};

