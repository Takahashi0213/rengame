#include "stdafx.h"
#include "BoxMaker.h"

BoxMaker* BoxMaker::m_instance = nullptr;

BoxMaker::BoxMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

BoxMaker::~BoxMaker()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}	

void BoxMaker::Update() {

	//���N���b�N�̏�Ԃ𔻒�
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Center_Key);
	Game::GameMode NowGameMode = m_game->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��

	if (key == MouseSupporter::New_Push && NowGameMode == Game::ActionMode) {	//���N���b�N���ꂽ�u�Ԃ��A�N�V�������[�h

		//�N���G�C�g���[�h�֕ύX
		m_game->SetGameMode(Game::CreateMode);

		m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();

		btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
		btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_boxPos);
		dw->rayTest((btVector3)g_camera3D.GetPosition(), m_boxPos, CRR_Callback);
		if (CRR_Callback.hasHit()) {
			m_boxPos = CRR_Callback.m_hitPointWorld;
		}
		else {
			//�v���C���[�̂��傢��
			m_boxPos = m_player->Getm_Position();
			m_boxPos.y += PosHoseiY;
			//CVector3 m_bp = MouseSupporter::GetInstance()->GetMousePos_3D();
			//m_bp.Normalize();
			//m_boxPos.x += m_bp.x;
			//m_boxPos.y += m_bp.y;
			//m_boxPos.z += m_bp.z;
		}

		GameBox* m_box = new GameBox;
		m_box->GameBox_Set(m_boxPos);
		m_boxList.push_back(m_box);
		m_nowBoxList.push_back(m_box);
		m_nowBox = m_box;

		//�Q�[���J�����ɓn��
		int a = Hash::MakeHash("GameCamera");
		GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
		GC->SetGameBox(m_box);

	}

	//���̒ǉ�����
	key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode 
		&& m_boxMakerMode == NomalMode) {	//���N���b�N���ꂽ�u�Ԃ��N���G�C�g���[�h�����g�咆�łȂ�

		//�I�𒆂̔��������s����
		if (m_nowBox != nullptr) {

			//���Z�b�g
			m_surfaceFlag = false;
			for (int i = 0; i < 4; i++) { //���̍��W�����Z�b�g
				m_boxPoint[i] = CVector3::Zero();
				m_boxPoint_Stock[i] = CVector3::Zero();
			}

			for (auto go : m_nowBoxList) {

				//����
				m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();

				btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
				btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_boxPos);
				dw->rayTest((btVector3)g_camera3D.GetPosition(), m_boxPos, CRR_Callback);

				//�����`�F�b�N
				//CVector3 ray = g_camera3D.GetTarget() - g_camera3D.GetPosition();
				//ray.Normalize();
				//ray *= 10000.0f;

				go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, m_boxPoint_Stock, m_boxN);

				if (m_surfaceFlag == false) {	//�܂����ݒ�

					//�ⓚ���p�Őݒ�
					m_surfaceFlag = true;
					for (int i = 0; i < 4; i++) {
						m_boxPoint[i] = m_boxPoint_Stock[i];
					}

				}
				else {	//�ݒ�ς�

					//���ɕۑ����Ă���ʂƔ�r���ĐV�����ʂ��J�����ɋ߂��Ȃ�㏑������
					CVector3 AveragePoint_Old = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
					AveragePoint_Old /= 4.0f;
					CVector3 AveragePoint_New = m_boxPoint_Stock[0] + m_boxPoint_Stock[1] + m_boxPoint_Stock[2] + m_boxPoint_Stock[3];
					AveragePoint_New /= 4.0f;
					CVector3 CameraPos = g_camera3D.GetPosition();

					//�������v�Z
					CVector3 Lange_Old_V = AveragePoint_Old - CameraPos;
					CVector3 Lange_New_V = AveragePoint_New - CameraPos;
					float Lange_Old = Lange_Old_V.Length();
					float Lange_New = Lange_New_V.Length();

					if (Lange_Old > Lange_New) {
						for (int i = 0; i < 4; i++) {
							m_boxPoint[i] = m_boxPoint_Stock[i];
						}
					}

				}

			}

		}

		//�}�E�X�J�[�\�������̂����ꂩ�̃|���S���ɏՓ˂��Ă���Ȃ�c
		if (m_boxPoint[0].x != m_boxPoint[1].x || 
			m_boxPoint[0].y != m_boxPoint[1].y || 
			m_boxPoint[0].z != m_boxPoint[1].z) {
			//�em_boxPoint�̕��ς��v�Z
			CVector3 AveragePoint = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
			AveragePoint /= 4.0f;

			//���𐶐�
			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);

			//��]�ݒ�
			CVector3 boxUp = { 0.0f,1.0f,0.0f };
			m_boxN.Cross(boxUp);
			m_box_N = m_boxN;		//�킩��ɂ������ǔ��̌�����ۑ�����
			CQuaternion rot = m_box->GetRotation();

			CQuaternion addRot;

			if (m_boxN.y < 0.098f) {
				//���̂����`���v�Z
				addRot.SetRotationDeg(m_boxN, 90.0f);
				rot *= addRot;
			}
			m_box->SetRotation(rot);

			//���X�g�̏���
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);

			//���݌��Ă���{�b�N�X��ύX����
			m_nowBox->SetBox(m_box);

			//�|�C���^��ύX
			m_nowBox_Stock = m_nowBox;
			m_nowBox = m_box;

			//�}�E�X�ړ��ʂ�������
			m_mouseMove.x = 0.0f;
			m_mouseMove.y = 0.0f;
			//���̃f�t�H���g�T�C�Y���ۑ�
			m_boxScaleDef = m_nowBox->GetScale();

			//���[�h���g�僂�[�h�ɕύX
			m_boxMakerMode = FocusMode;
		}
	}

	//�t�H�[�J�X���[�h�p�̏����`�`�`�`�`�`�`
	if (NowGameMode == Game::CreateMode && m_boxMakerMode == FocusMode) {
		
		key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		
		if (key == MouseSupporter::Now_Pushing) {	//������Ă���

			CVector2 mouseMove = MouseSupporter::GetInstance()->GetMouseMove();
			m_boxScale = m_nowBox->GetScale();

			mouseMove.x /= 2.0f;
			mouseMove.y /= 2.0f;

			m_boxScale.x += mouseMove.x;
			m_boxScale.y += mouseMove.y;

			//�������Ȃ肷����ƃo�O��̂�
			if (m_boxScale.x < m_boxScaleDef.x) {
				m_boxScale.x = m_boxScaleDef.x;
			}
			if (m_boxScale.y < m_boxScaleDef.y) {
				m_boxScale.y = m_boxScaleDef.y;
			}

			m_nowBox->SetScale(m_boxScale);


		}else if (key == MouseSupporter::Release_Push) {	//�����ꂽ�I�I�I

			//�|�C���^��ύX
			m_nowBox = m_nowBox_Stock;

			//���[�h��ʏ탂�[�h�ɕύX
			m_boxMakerMode = NomalMode;

		}

	}

	BoxUpdate();

}

/// <summary>
/// �{�b�N�X��S���A�b�v�f�[�g����
/// </summary>
void BoxMaker::BoxUpdate() {

	for (auto go : m_boxList) {
	
		go->GameBox_Update();
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