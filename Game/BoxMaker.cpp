#include "stdafx.h"
#include "BoxMaker.h"
#include "GameUI.h"

BoxMaker* BoxMaker::m_instance = nullptr;

BoxMaker::BoxMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�Q�[���̃|�C���^�ۑ�
	m_game = Game::GetInstance();
}

BoxMaker::~BoxMaker()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}	

void BoxMaker::Update() {

	//���N���b�N�̏�Ԃ𔻒�
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Center_Key);
	SceneManager::GameMode NowGameMode = SceneManager::GetInstance()->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��

	ModeChange();
	bool result = false;

	CVector3 boxPoint[4] = { CVector3::Zero() };
	CVector3 boxPoint_Stock[4] = { CVector3::Zero() };
	m_box_N_Now = CVector3::Zero();
	m_planeScaleNow = CVector3::Zero();

	//���̒ǉ�����
	key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	if (key == MouseSupporter::New_Push && NowGameMode == SceneManager::CreateMode
		&& m_boxMakerMode == NomalMode) {	//���N���b�N���ꂽ�u�Ԃ��N���G�C�g���[�h�����g�咆�łȂ�

		//�I�𒆂̔��������s����
		if (m_nowBox != nullptr) {

			//���Z�b�g
			bool surfaceFlag = false;

			for (auto go : m_nowBoxList) {

				//����
				m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();
				
				//�����`�F�b�N
				//CVector3 ray = g_camera3D.GetTarget() - g_camera3D.GetPosition();
				//ray.Normalize();
				//ray *= 10000.0f;
			
				result |= go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, boxPoint_Stock, m_boxN, m_planeScale);
				
				if (result == true) {
					if (surfaceFlag == false) {	//�܂����ݒ�

						//�ⓚ���p�Őݒ�
						m_box_N_Now = m_boxN;
						m_planeScaleNow = m_planeScale;
						surfaceFlag = true;
						for (int i = 0; i < 4; i++) {
							boxPoint[i] = boxPoint_Stock[i];
						}

					}
					else {	//�ݒ�ς�

						//���ɕۑ����Ă���ʂƔ�r���ĐV�����ʂ��J�����ɋ߂��Ȃ�㏑������
						CVector3 AveragePoint_Old = boxPoint[0] + boxPoint[1] + boxPoint[2] + boxPoint[3];
						AveragePoint_Old /= 4.0f;
						CVector3 AveragePoint_New = boxPoint_Stock[0] + boxPoint_Stock[1] + boxPoint_Stock[2] + boxPoint_Stock[3];
						AveragePoint_New /= 4.0f;
						CVector3 CameraPos = g_camera3D.GetPosition();

						//�������v�Z
						CVector3 Lange_Old_V = AveragePoint_Old - CameraPos;
						CVector3 Lange_New_V = AveragePoint_New - CameraPos;
						float Lange_Old = Lange_Old_V.Length();
						float Lange_New = Lange_New_V.Length();

						if (Lange_Old > Lange_New) {
							m_box_N_Now = m_boxN;
							m_planeScaleNow = m_planeScale;
							for (int i = 0; i < 4; i++) {
								boxPoint[i] = boxPoint_Stock[i];
							}
						}

					}
				}

			}

		}
		
		
		//�}�E�X�J�[�\�������̂����ꂩ�̃|���S���ɏՓ˂��Ă���Ȃ�c
		if (result) {
			//�em_boxPoint�̕��ς��v�Z
			CVector3 AveragePoint = boxPoint[0] + boxPoint[1] + boxPoint[2] + boxPoint[3];
			AveragePoint /= 4.0f;

			//���𐶐�
			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);
			m_box->SetOriginBox(m_originBox);

			//���㔠���猩�����[�J�����W���ۑ����Ă���
			CVector3 localPos = AveragePoint - m_originBox->GetPosition();
			m_box->SetLocalPos(localPos);

			//��]�ݒ�
			CVector3 boxUp = { 0.0f,1.0f,0.0f };
			m_box_N_Now.Cross(boxUp, m_box_N_Now);
			m_box_N = m_box_N_Now;		//�킩��ɂ������ǔ��̌�����ۑ�����
			CQuaternion rot = m_box->GetRotation();

			CQuaternion addRot = CQuaternion::Identity();

			if (m_box_N_Now.y < 0.098f) {
				//���̂����`���v�Z
				addRot.SetRotationDeg(m_box_N_Now, 90.0f);
				rot *= addRot;
			}
			m_box->SetRotation(rot);

			//�g�嗦�ݒ�
			CVector3 scl= m_box->GetScale();
			scl.y = 0.1f;
			//�ׂ��������m�F����
			if (m_planeScaleNow.x <= 0.01f) {
				m_boxDirection = X_Direction;
				scl.x = m_planeScaleNow.y;
				scl.z = m_planeScaleNow.z;
			}
			else if (m_planeScaleNow.y <= 0.01f) {
				m_boxDirection = Y_Direction;
				scl.x = m_planeScaleNow.x;
				scl.z = m_planeScaleNow.z;				
			}
			else if (m_planeScaleNow.z <= 0.01f) {
				m_boxDirection = Z_Direction;
				scl.x = m_planeScaleNow.x;				
				scl.z = m_planeScaleNow.y;
			}
			else {
				m_boxDirection = Z_Direction;
			}
			m_box->SetScale(scl);

			//���X�g�̏���
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);

			//���݌��Ă���{�b�N�X��ύX����
			m_originBox->SetBox(m_box);

			//�|�C���^��ύX
			m_nowBox_Stock = m_nowBox;
			m_nowBox = m_box;

			//�}�E�X�ړ��ʂ�������
			m_mouseMove.x = 0.0f;
			m_mouseMove.y = 0.0f;
			//���̃f�t�H���g�T�C�Y���ۑ�
			m_boxScaleDef = m_nowBox->GetScale();
			//���̐���ǉ�
			m_box_Nom++;
			//�g��k���p�}�i����
			m_downMana_Stock = m_downMana;
			m_manaHosei = 0;

			//���[�h���g�僂�[�h�ɕύX
			m_boxMakerMode = FocusMode;
		}
	}

	//�t�H�[�J�X���[�h�p�̏����`�`�`�`�`�`�`
	if (NowGameMode == SceneManager::CreateMode && m_boxMakerMode == FocusMode) {
		
		key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		
		if (key == MouseSupporter::Now_Pushing) {	//������Ă���

			//���̊g��k���`�`�`�`�`
			CVector2 mouseMove = MouseSupporter::GetInstance()->GetMouseMove();
			m_boxScale = m_nowBox->GetScale();

			//�ړ��ʂɕ␳��������
			mouseMove.x *= m_mouseMoveHosei;
			mouseMove.y *= m_mouseMoveHosei;

			//�}�i�v�Z
			CVector3 Scale = { m_boxScale.x - m_boxScaleDef.x ,
				m_boxScale.y - m_boxScaleDef.y ,
				m_boxScale.z - m_boxScaleDef.z };
			float ManaHosei = Scale.x + Scale.y + Scale.z;
			ManaHosei /= DefManaHosei;
			int ManaHosei2 = static_cast<int>( floor(ManaHosei));
			m_manaHosei = ManaHosei2;
			if (m_manaHosei < 0) {	//�o�O�h�~����
				m_manaHosei = 0;
			}
			m_downMana = m_downMana_Stock + m_manaHosei;

			//���̌����ɍ��킹�Ċg�嗦��F�X����
			switch (m_boxDirection)
			{
			case BoxMaker::X_Direction:
				if (m_downMana > m_startMana && mouseMove.y > 0.0f) {
					mouseMove.y = 0.0f;
				}
				m_boxScale.y += mouseMove.y;
				break;
			case BoxMaker::Y_Direction:
				if (m_downMana > m_startMana && mouseMove.y < 0.0f) {
					mouseMove.y = 0.0f;
				}
				m_boxScale.y += -mouseMove.y;
				break;
			case BoxMaker::Z_Direction:
				if (m_downMana > m_startMana && mouseMove.y > 0.0f) {
					mouseMove.y = 0.0f;
				}
				m_boxScale.y += mouseMove.y;
				break;
			}

			//�������Ȃ肷����ƃo�O��̂�
			if (m_boxScale.x < m_boxScaleDef.x) {
				m_boxScale.x = m_boxScaleDef.x;
			}
			if (m_boxScale.y < m_boxScaleDef.y) {
				m_boxScale.y = m_boxScaleDef.y;
			}
			if (m_boxScale.z < m_boxScaleDef.z) {
				m_boxScale.z = m_boxScaleDef.z;
			}

			m_nowBox->SetScale(m_boxScale);


		}else if (key == MouseSupporter::Release_Push) {	//�����ꂽ�I�I�I

			//�}�i����
			m_manaList.push_back(m_manaHosei);
			m_downMana = m_downMana_Stock + m_manaHosei;

			//�|�C���^��ύX
			m_nowBox = m_nowBox_Stock;

			//���[�h��ʏ탂�[�h�ɕύX
			m_boxMakerMode = NomalMode;

		}

	}

	//�A���h�D�����I�I�I�I
	if (NowGameMode == SceneManager::CreateMode && m_box_Nom > 1) {
		//CTRL+Z
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('Z') & 0x8000) {

			if (m_undoFlag == false) {
				//���O�̔�������
				auto p = m_boxList.back();
				delete(p);
				
				m_boxList.pop_back();
				m_nowBoxList.pop_back();
				m_originBox->SetBox_Delete();

				//�}�i������
				m_downMana -= m_manaList.back();
				m_manaList.pop_back();

				m_undoFlag = true;
				m_box_Nom--;
			}
		}
		else {
			m_undoFlag = false;
		}
	}

	//�}�i����
	if (NowGameMode == SceneManager::CreateMode) {
		GameData::GetInstance()->SetMagicPower(m_startMana - m_downMana);
	}

	BoxUpdate();

}

/// <summary>
/// �{�b�N�X��S���A�b�v�f�[�g����
/// </summary>
void BoxMaker::BoxUpdate() {
	SceneManager::GameMode NowGameMode = SceneManager::GetInstance()->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��

	for (auto go : m_boxList) {
	
		go->GameBox_Update();

		if (NowGameMode == SceneManager::ActionMode) {
			go->GameBoxUpdate_Colli();
		}
	}
	
	std::list<GameBox*>::iterator it;
	it = m_boxList.begin();
	while (it != m_boxList.end()) {
		bool flag = (*it)->DeathBox();
		if (flag == true) {
			it = BoxDelete_it(it);
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

/// <summary>
/// �{�b�N�X��S���`�悷��
/// </summary>
void BoxMaker::Render() {

	for (auto go : m_boxList) {

		go->GameBox_Render();

	}
}

void BoxMaker::ModeChange() {

	//���N���b�N�̏�Ԃ𔻒�
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Center_Key);
	SceneManager::GameMode NowGameMode = SceneManager::GetInstance()->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��
	int Mana = GameData::GetInstance()->GetMagicPower();

	//���N���b�N���ꂽ�u�Ԃ��A�N�V�������[�h���}�i��(CreateModeChangeBorder)�ȏ゠��
	if (key == MouseSupporter::New_Push && NowGameMode == SceneManager::ActionMode && Mana >= CreateModeChangeBorder) {

		m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();

		btDiscreteDynamicsWorld* dw = g_physics->GetDynamicWorld();
		btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_boxPos);
		dw->rayTest((btVector3)g_camera3D.GetPosition(), m_boxPos, CRR_Callback);
		if (CRR_Callback.hasHit()) {
			m_boxPos = CRR_Callback.m_hitPointWorld;
		}
		else {
			//�v���C���[�̂��傢��
			m_boxPos = m_player->GetPosition();
			m_boxPos.y += PosHoseiY;
			//CVector3 m_bp = MouseSupporter::GetInstance()->GetMousePos_3D();
			//m_bp.Normalize();
			//m_boxPos.x += m_bp.x;
			//m_boxPos.y += m_bp.y;
			//m_boxPos.z += m_bp.z;
		}
		
		const bool flag = BoxCreateCheck();

		if (flag == true) {

			//�N���G�C�g���[�h�֕ύX
			SceneManager::GetInstance()->SetGameMode(SceneManager::CreateMode);

			//���㔠����
			GameBox* m_box = new GameBox;		//���㔠���쐬
			m_box->GameBox_Set(m_boxPos);
			m_box->SetBoxTag(GameBox::Origin);	//���̃^�O���u�ŏ��̔��v�ɕύX����
			m_boxList.push_back(m_box);
			m_nowBoxList.clear();
			m_nowBoxList.push_back(m_box);
			m_nowBox = m_box;
			m_originBox = m_box;

			m_box_Nom = 1;				//���̐������Z�b�g

			//�}�i�ݒ�
			m_downMana = CreateModeChangeBorder;
			m_startMana = GameData::GetInstance()->GetMagicPower();

			//�Q�[���J�����ɓn��
			int a = Hash::MakeHash("GameCamera");
			GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
			GC->SetGameBox(m_box);

		}

	}
	//�N���G�C�g���[�h�Ɉڍs���������ǃ}�i��(CreateModeChangeBorder)�ɑ���Ȃ��ꍇ
	else if (key == MouseSupporter::New_Push && NowGameMode == SceneManager::ActionMode && Mana < CreateModeChangeBorder) {
		//�}�i������܂���I�̃V�F�C�N��������
		GameUI::GetInstance()->ManaShake();
	}
	//�N���G�C�g���[�h����A�N�V�������[�h�֖߂�}�X
	else if (key == MouseSupporter::New_Push && NowGameMode == SceneManager::CreateMode) {	//���N���b�N���ꂽ�u�Ԃ��A�N�V�������[�h

		//���͌���
		m_originBox->SetManaPower(m_downMana);
		GameData::GetInstance()->SetMagicPower(m_startMana - m_downMana);

		//�A�N�V�������[�h�֕ύX
		SceneManager::GetInstance()->SetGameMode(SceneManager::ActionMode);

		//�J�����ړ��𐧌䂷��
		int a = Hash::MakeHash("GameCamera");
		GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
		GC->PlayerCameraMove();

	}

}

bool BoxMaker::BoxCreateCheck() {

	bool ReturnFlag = false;

	CVector3 PlayerPos = m_player->GetPosition();
	CVector3 PlayerToBox_Diff = m_boxPos - PlayerPos;	//�v���C���[���甠�쐬�\��n�Ɍ������x�N�g�����쐬

	//�����𑪒�
	if (PlayerToBox_Diff.Length() < Player_Box_MaxRange) {
		ReturnFlag = true;
	}

	return ReturnFlag;

}

/// <summary>
/// �폜�n
/// </summary>

void BoxMaker::BoxDelete(GameBox* deleteBox) {

	//���̔����I���W������Ȃ�������G���[
	if (deleteBox->GetBoxTag() == GameBox::BoxTag::Another) {
		std::abort();
	}
	//�}�i���񕜂���
	GameData::GetInstance()->SetMagicPower(
		GameData::GetInstance()->GetMagicPower() + deleteBox->GetManaPower()
	);
	//�q�����������X�g����폜
	std::vector<GameBox*> AnotherBoxs = deleteBox->GetBoxList();
	for (int i = 0; i < AnotherBoxs.size(); i++) {
		m_boxList.remove(AnotherBoxs[i]);
	}
	//���̔��̎q����S�폜
	deleteBox->DeleteBox();
	//���̔����̂��폜
	delete deleteBox;
	//���X�g������폜
	m_boxList.remove(deleteBox);

}

std::list<GameBox*>::iterator BoxMaker::BoxDelete_it(std::list<GameBox*>::iterator deleteBox_it) {

	//���̔����I���W������Ȃ�������G���[
	if ((*deleteBox_it)->GetBoxTag() == GameBox::BoxTag::Another) {
		std::abort();
	}
	//�}�i���񕜂���
	GameData::GetInstance()->SetMagicPower(
		GameData::GetInstance()->GetMagicPower() + (*deleteBox_it)->GetManaPower()
	);
	//�q�����������X�g����폜
	std::vector<GameBox*> AnotherBoxs = (*deleteBox_it)->GetBoxList();
	for (int i = 0; i < AnotherBoxs.size(); i++) {
		m_boxList.remove(AnotherBoxs[i]);
	}
	//���̔��̎q����S�폜
	(*deleteBox_it)->DeleteBox();
	//���̔����̂��폜
	delete (*deleteBox_it);
	//���X�g������폜
	std::list<GameBox*>::iterator it;
	it = m_boxList.erase(deleteBox_it);

	return it;
}

void BoxMaker::BoxAllDelete() {

	//�폜
	for (auto go : m_boxList) {
		delete go;
	}
	//���X�g�̏�����
	m_boxList.clear();
	//�}�i��߂�
	GameData::GetInstance()->SetMagicPower(GameData::GetInstance()->GetMaxMagic());

}
