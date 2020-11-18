#include "stdafx.h"
#include "SystemBox.h"

#include "GameSystem/StageSet/StageSet.h"

GhostBox::GhostBox()
{
	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GhostBox::~GhostBox()
{
	//���̍폜
	if (m_Yazirushi != nullptr) {
		DeleteGO(m_Yazirushi);
	}

	if (m_boxSystem == MapMove && m_mapMoveFlag == true) {
		//�g�����W�V��������
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true , true);
	}
}

void GhostBox::Update() {

	//�v���C���[�Ƃ̏Փ˔���
	CharacterController* charaCon = m_player->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			GhostAction();
		}
		});

	//���
	if (m_boxSystem == MapMove) {

		if (m_Yazirushi == nullptr) {
			//����
			m_Yazirushi = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>(L"Yazirushi", 0);

			//���W�␳
			CVector3 pos = m_position;
			pos.y += m_yazirushiYHosei;
			CQuaternion RotationY;
			RotationY.SetRotationDeg(CVector3().AxisY(), m_yazirushiRotAngle);
			CQuaternion rot = m_rotation * RotationY;
			//�ǂ�������H
			EnFbxUpAxis axis;
			if (YazirushiRotFlag == false) {
				axis = EnFbxUpAxis::enFbxUpAxisY;
			}
			else {
				axis = EnFbxUpAxis::enFbxUpAxisZ;
			}

			m_Yazirushi->Model_Init(
				L"Assets/modelData/Yazirushi.cmo",
				pos,
				rot,
				{5.0f,5.0f,5.0f},
				axis
			);
		}
		else {
			//���m�N����
			if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
				m_Yazirushi->GetModel()->SetRenderMode(RenderMode::Monochrome);
				m_Yazirushi->SetIsUpdateSkinModelSupporter(false);	//���̈ړ����ꎞ��~
				m_monochromeFlag = true;
			}
			else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
				m_Yazirushi->GetModel()->SetRenderMode(RenderMode::Default);
				m_Yazirushi->SetIsUpdateSkinModelSupporter(true);	//���̈ړ����ĊJ
				m_monochromeFlag = false;
			}

			//�ړ�
			if (m_Yazirushi->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
				CVector3 front;
				if (YazirushiRotFlag == false) {
					front.Set(0.0f, 1.0f, 0.0f);
				}
				else {
					front.Set(0.0f, 0.0f, 1.0f);
				}

				CQuaternion y_rot = m_Yazirushi->GetRotation();
				y_rot.Multiply(front);
				CVector3 moveVec = front * YazirushiMoveHosei;
				m_Yazirushi->m_skinModelSupporter.SkinModelMove(moveVec, YazirushiMoveTime, 0, true);
				m_Yazirushi->m_skinModelSupporter.SkinModelMove(-moveVec, YazirushiMoveTime, YazirushiMoveTime, true);
			}
		}
	}

	//�}�b�v�ړ��҂�
	if (m_mapMoveFlag == true) {
		m_mapMoveTimer++;
		if (m_mapMoveTimer == SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime) {
			//���݂̏ꏊ�ƈړ���̏ꏊ���Ⴄ�Ȃ�BGM���Đ�����
			GameData::Place_Data NextPlace = StageSet::GetInstance()->GetStagePlace(m_LoadName);
			GameData::Place_Data NowPlace = GameData::GetInstance()->GetPlace();
			if (NowPlace != NextPlace) {
				wchar_t* bgmName = StageSet::GetInstance()->GetStageBGM_Name(NextPlace);
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(bgmName);
			}
			m_player->SetPosition(m_playerMoveTarget);				//�v���C���[�ړ�
			StageSet::GetInstance()->InitStage(m_LoadName);			//�X�e�[�W�ǂݍ���
			m_player->MapMove();									//�����グ��Ԃ̃��Z�b�g
		}
	}

}

void GhostBox::Render() {

}

void GhostBox::CreateGhost() {

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject.CreateBox(
		m_position,		//�������͍��W�B
		m_rotation,		//�������͉�]�N�H�[�^�j�I���B
		m_scale			//��O�����̓{�b�N�X�̃T�C�Y�B
	);

}

void GhostBox::GhostAction() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//�}�b�v�ړ�
	if (m_boxSystem == MapMove && m_mapMoveFlag == false) {
		//�g�����W�V����
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false, true);
		//�}�b�v�ړ�SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/MapMove.wav");
		//���݂̏ꏊ�ƈړ���̏ꏊ���Ⴄ�Ȃ�BGM���t�F�[�h�A�E�g������
		GameData::Place_Data NowPlace = GameData::GetInstance()->GetPlace();
		GameData::Place_Data NextPlace = StageSet::GetInstance()->GetStagePlace(m_LoadName);
		if (NowPlace != NextPlace) {
			//BGM�̃t�F�[�h�A�E�g
			SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(0.0f,
				SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime);
		}
		//�}�b�v�ړ��t���O��true�ɂ���
		m_mapMoveFlag = true;
	}
	//�C�x���g
	if (m_boxSystem == MapEvent) {
	
		//�C�x���g�̎��s
		SceneManager::GetInstance()->GetGameEvent()->EvemtStart(m_LoadName);

		//���̔��͍폜�����
		DeleteGO(this);
	}
	//�����_���[�W
	if (m_boxSystem == DamageZone) {
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/PlayerDamage.wav");
		Game::GetInstance()->GetDamageSystem()->Damage(-FallDamage);	//�_���[�W���󂯂�
		CVector3 pos = m_player->GetPositionBackup();
		pos.y += PlayerMiss_Y_Hosei;
		m_player->SetPosition(pos);			//���W��߂�
	}
}

/// <summary>
/// ��������X�^�e�B�b�N�{�b�N�X
/// </summary>

StaticBox::StaticBox()
{

}

StaticBox::~StaticBox()
{
}

void StaticBox::Update() {
	//�����X�V
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void StaticBox::Render() {

}

void StaticBox::CreateStaticBox() {
	//�����쐬
	m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);
}