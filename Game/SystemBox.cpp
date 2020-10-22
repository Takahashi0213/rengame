#include "stdafx.h"
#include "SystemBox.h"

#include "StageSet.h"

GhostBox::GhostBox()
{
	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GhostBox::~GhostBox()
{
	if (m_Yazirushi != nullptr) {
		DeleteGO(m_Yazirushi);
	}

	if (m_LoadStageName != nullptr && m_mapMoveFlag == true) {
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
			if (m_LoadStageName != nullptr && m_mapMoveFlag == false) {
				//�}�b�v�ړ�
				//�g�����W�V����
				TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
					SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false, true);
				//�}�b�v�ړ��t���O��true�ɂ���
				m_mapMoveFlag = true;
			}
			else {
				//�����_���[�W

			}
		}
		});

	//���
	if (m_LoadStageName != nullptr) {
		if (m_Yazirushi == nullptr) {
			//����
			m_Yazirushi = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>(L"Yazirushi", 0);

			//���W�␳
			CVector3 pos = m_position;
			pos.y += m_yazirushiYHosei;
			CQuaternion RotationY;
			RotationY.SetRotationDeg(CVector3().AxisY(), m_yazirushiRotAngle);
			CQuaternion rot = m_rotation * RotationY;

			m_Yazirushi->Model_Init(
				L"Assets/modelData/Yazirushi.cmo",
				pos,
				rot,
				{5.0f,5.0f,5.0f},
				EnFbxUpAxis::enFbxUpAxisY
			);
		}
		else {
			//�ړ�
			if (m_Yazirushi->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
				CVector3 front = { 0.0f, 1.0f,0.0f };
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
			m_player->SetPosition(m_playerMoveTarget);				//�v���C���[�ړ�
			StageSet::GetInstance()->InitStage(m_LoadStageName);	//�X�e�[�W�ǂݍ���
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
		m_scale				//��O�����̓{�b�N�X�̃T�C�Y�B
	);

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