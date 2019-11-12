#include "stdafx.h"
#include "BoxMaker.h"

BoxMaker::BoxMaker()
{
}

BoxMaker::~BoxMaker()
{
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
	if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode) {	//���N���b�N���ꂽ�u�Ԃ��N���G�C�g���[�h

		//�I�𒆂̔��������s����
		if (m_nowBox != nullptr) {

			for (int i = 0; i < 4; i++) { //���Z�b�g
				m_boxPoint[i] = CVector3::Zero();
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

				go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, m_boxPoint);

			}

		}

		//�}�E�X�J�[�\�������̂����ꂩ�̃|���S���ɏՓ˂��Ă���Ȃ�c
		if (m_boxPoint[0].x != 0.0f && m_boxPoint[0].y != 0.0f && m_boxPoint[0].z != 0.0f) {
			//�em_boxPoint�̕��ς��v�Z
			CVector3 AveragePoint = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
			AveragePoint /= 4.0f;

			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);
			m_nowBox->SetBox(m_box);
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