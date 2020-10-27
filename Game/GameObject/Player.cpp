#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "GameSystem/GameUI/GameUI.h"
#include "BoxMaker.h"

int Game_UI = Hash::MakeHash("GameUI");

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_model_Sl.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	//m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model_Sl.SetRenderMode(RenderMode::Silhouette);

	//�A�j���[�V����
	m_playerAnimationClips[enAnimationClip_Idle].Load(L"Assets/animData/idle.tka");
	m_playerAnimationClips[enAnimationClip_Idle].SetLoopFlag(true);

	m_playerAnimationClips[enAnimationClip_Run].Load(L"Assets/animData/run.tka");
	m_playerAnimationClips[enAnimationClip_Run].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_playerAnimation.Init(
		m_model,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_playerAnimationClips,		//�A�j���[�V�����N���b�v�̔z��B
		enAnimationClip_Num			//�A�j���[�V�����N���b�v�̐��B
	);
	m_playerAnimationSL.Init(
		m_model_Sl,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_playerAnimationClips,		//�A�j���[�V�����N���b�v�̔z��B
		enAnimationClip_Num			//�A�j���[�V�����N���b�v�̐��B
	);

	//���[���h�s��̍X�V�B
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_nextPos = m_position;		//�ړ����������

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(Radius, Height, m_position);

	//���C�g���[�J�[�̎擾
	m_lightMaker = LightMaker::GetInstance();

	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	//�Q�[���̃|�C���^
	m_gameObj = Game::GetInstance();

	//�X�v���C�g�}�X�N�̃e�X�g

	//SpriteRender* MainSprite = NewGO<SpriteRender>("TEST", 0);
	//MainSprite->ChangeMaskSprite();
	//MainSprite->Init(L"Assets/sprite/keis.dds", 588.0f, 1240.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-250.0f ,0.0f });
	//MainSprite->InitSub(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-50.0f ,0.0f }, 0);
	//MainSprite->GetSubSpriteSupporter(0)->SpriteRotation(10.0f, 600, 0, true);

}

Player::~Player()
{

}

void Player::Update()
{
	//���m�N���ɂȂ�
	if (m_gameObj != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}
	//�A�j���[�V����
	if (m_gameObj != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode) {
			//�A�j���[�V�����Đ�
			float MovePower = m_moveSpeed.Length();
			if (MovePower > 2.0f) {
				m_playerAnimation.Play(enAnimationClip_Run);
				m_playerAnimationSL.Play(enAnimationClip_Run);
			}
			else {
				m_playerAnimation.Play(enAnimationClip_Idle);
				m_playerAnimationSL.Play(enAnimationClip_Idle);
			}
			m_playerAnimation.Update(1.0f / 20.0f);
			m_playerAnimationSL.Update(1.0f / 20.0f);
		}
	}

	//����

	//�����グ���̔��̍��W���v���C���[�ɍ��킹��
	BoxUp();
	//�ړ�
	Move();
	//�n��ɂ�����W�����v
	Jump();
	//�����グ�锠��T��
	BoxSearch();
	//�L�[�������ꂽ�玝���グ���艺�낵���肷��
	BoxCatch();
	//�L�[�������ꂽ�玝���グ�Ă��锠���폜����
	BoxDelete();
	//�グ�������̕⊮�ړ�������
	BoxMove();

	//���[���h�s��̍X�V�B
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode){ //�A�N�V�������[�h�łȂ���΍X�V���Ȃ��I

		//�d��
		m_moveSpeed.y -= m_gravity;
		//�L�����R���ړ�
		m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	}

	//�V���h�E�L���X�^�[��o�^�B
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());

	//���C�g�J�������X�V
	CVector3 LC_Pos = LightMaker::GetInstance()->GetLightCameraPosition();
	LC_Pos = m_position;
	LC_Pos.y += 1000.0f;
	LightMaker::GetInstance()->SetLightCameraPosition(LC_Pos);
	//�^�[�Q�b�g��
	LC_Pos = LightMaker::GetInstance()->GetLightCameraTarget();
	LC_Pos = m_position;
	LightMaker::GetInstance()->SetLightCameraTarget(LC_Pos);
}

void Player::Render()
{
	m_model_Sl.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//���̏グ���낵���͋����I��
	if (m_boxMoveFlag == true) {
		return;
	}

	//���N���b�N�̏�Ԃ𔻒�
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	bool OnG_Flag = m_charaCon.IsOnGround();
	GameUI* ui = CGameObjectManager::GetInstance()->FindGO<GameUI>(Game_UI);

	//���L�[�������ꂽ�����݃A�N�V�������[�h�����j���[�{�^���ɔ���Ă��Ȃ����m�b�N�o�b�N���łȂ�
	if (key == MouseSupporter::Release_Push &&
		SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode &&
		ui->GetGemeMenu()->GetSelectFlag() == false &&
		m_damage_Flag == false)
	{
		if (MouseSupporter::GetInstance()->GetMouseTimer(MouseSupporter::Left_Key) < 12) {

			m_nextPos = MouseSupporter::GetInstance()->GetMousePos_3D();

			//btCollisionWorld::ClosestRayResultCallback ResultCallback();
			btDiscreteDynamicsWorld* dw = g_physics->GetDynamicWorld();
			btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_nextPos);
			dw->rayTest((btVector3)g_camera3D.GetPosition(), m_nextPos, CRR_Callback);
			if (CRR_Callback.hasHit()) {
				m_nextPos = CRR_Callback.m_hitPointWorld;
			}
			else {
				m_nextPos = m_position + (m_moveSpeed / 1000.0f);
			}

		}
	}

	//�ړ�
	m_nextPos.y = m_position.y;

	m_moveSpeed.x = m_nextPos.x - m_position.x;
	m_moveSpeed.z = m_nextPos.z - m_position.z;
	m_moveSpeed.x /= 20.0f;
	m_moveSpeed.z /= 20.0f;

	//���
	if (m_moveSpeed.x > m_moveMax) {
		m_moveSpeed.x = m_moveMax;
	}
	if (m_moveSpeed.x < -m_moveMax) {
		m_moveSpeed.x = -m_moveMax;
	}
	if (m_moveSpeed.z > m_moveMax) {
		m_moveSpeed.z = m_moveMax;
	}
	if (m_moveSpeed.z < -m_moveMax) {
		m_moveSpeed.z = -m_moveMax;
	}

	//�ړ������ɉ�]������i�m�b�N�o�b�N���͉�]���Ȃ��j
	if (m_damage_Flag == false) {
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3().AxisY(), angle);
	}

	//���݈ʒu�̃o�b�N�A�b�v
	if (m_jumpNow == false) {
		m_posBackup = m_position;
	}

}

void Player::Jump() {
	
	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//���̏グ���낵���͋����I��
	if (m_boxMoveFlag == true) {
		return;
	}

	bool OnG_Flag = m_charaCon.IsOnGround();

	//�W�����v����
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (m_jumpNow == false && OnG_Flag == true) {
			m_moveSpeed.y = m_jumpPower;

			//EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::TestData, false, 100.0f, 100.0f, 0.0f);
			//EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::TestData, true,
			//	300.0f, 100.0f, 0.0f,
			//	180.0f, 180.0f, 180.0f);
		}
		m_jumpNow = true;

	}
	else {
		m_jumpNow = false;
	}

	//�󒆃t���O���Z�b�g
	if (OnG_Flag == false) {
		if (m_damage_JumpFlag == false && m_damage_Flag == true) {
			m_damage_JumpFlag = true;
		}
	}
	else {
		if (m_damage_JumpFlag == true && m_damage_Flag == true) {
			//�m�b�N�o�b�N�I��
			m_damage_Flag = false;
			m_damage_JumpFlag = false;
			m_nextPos = m_position;
		}
	}

}

void Player::BoxCatch() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}

	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//���̏グ���낵���͋����I��
	if (m_boxMoveFlag == true) {
		return;
	}

	//�Ή�����{�^����������ĂȂ��Ȃ狭���I��
	if (HIWORD(GetAsyncKeyState(GameData::GetInstance()->GetBoxCatchKey()))) {
		if (m_boxButtonFlag == false) {
			m_boxButtonFlag = true;
		}
		else {
			return;
		}
	}
	else {
		m_boxButtonFlag = false;
		return;
	}

	//���������グ�Ă��邩�ǂ����ŕ���
	if (m_boxUpFlag == false) {

		//��������������

		if (m_upKouho_Box != nullptr) { //�����グ���锠������H
			m_upBox = m_upKouho_Box;
			m_boxUpFlag = true;
			m_boxMoveFlag = true;
			m_upOrDown = false;	//�����グ�Ă�t���O
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
			
			//���̕�������
			{
				CVector3 playerForward = { 0.0f, 0.0f, 1.0f };
				//�@���������������̃x�N�g�����v�Z����B
				CVector3 targetVector = m_upBox->GetPosition() - m_position;
				//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
				targetVector.y = 0.0f;
				targetVector.Normalize();
				CQuaternion qRot;
				qRot.SetRotation(playerForward, targetVector);
				m_rotation = qRot;
			}
			//���W�v�Z
			{
				m_point_2 = m_upBox->GetPosition();	//�n�_
				CVector3 Pos = m_position;
				Pos.y += m_boxPos_Y_Hosei;
				m_point_3 = Pos;	//�I�_
				CVector3 Vec = Pos - m_upBox->GetPosition();	//�n�_����I�_�ɐL�т�x�N�g��
				Vec /= 4.0f;
				CVector3 Pos2 = m_upBox->GetPosition() + Vec;
				Pos2.y += m_boxMove_Y_Hosei;
				m_point_4 = Pos2;	//�n�_���
				Pos2 = Pos - Vec;
				Pos2.y = m_point_4.y;
				m_point_1 = Pos2;	//�I�_���
			}

		}

	}
	else {

		//�ړ��ʂɉ����Ĕ���u���������邩�ύX
		CVector3 Move = m_moveSpeed / m_boxPutHosei;
		Move.y = 0.0f;
		float MovePower = Move.Length();
		if (MovePower >= 0.0f) {

			//������
			CVector3 MoveSpeed = BoxThrowSearch();
			m_upBox->SetMoveSpeed(MoveSpeed);

			//���Z�b�g
			m_boxUpFlag = false;
			m_upBox = nullptr;

		}
		else {
			//�������낷

			//���W�͑O����
			{
				//���W�v�Z
				m_point_2 = m_upBox->GetPosition();	//�n�_
				CVector3 Pos = m_position;
				CVector3 Move_ = m_moveSpeed;
				Move_.Normalize();
				Pos += Move_ * m_boxPut_Hosei;
				m_point_3 = Pos;	//�I�_
				CVector3 Vec = Pos - m_upBox->GetPosition();	//�n�_����I�_�ɐL�т�x�N�g��
				Vec /= 4.0f;
				CVector3 Pos2 = m_upBox->GetPosition() + Vec;
				Pos2.y += m_boxMove_Y_Hosei_Put;
				m_point_4 = Pos2;	//�n�_���
				Pos2 = Pos - Vec;
				Pos2.y = m_point_4.y;
				m_point_1 = Pos2;	//�I�_���
			}

			//���Z�b�g
			m_boxUpFlag = false;
			m_boxMoveFlag = true;
			m_upOrDown = true;	//�������낵�Ă�t���O
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

		}

	}

}

void Player::BoxSearch() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//���������グ�Ă���Ȃ狭���I��
	if (m_boxUpFlag == true) {
		return;
	}

	//�{�b�N�X���[�J�[
	BoxMaker* BoxMaker_p = BoxMaker::GetInstance();

	//�߂��ɔ������邩����
	const std::list<GameBox*>& boxList = BoxMaker_p->GetBoxList();
	float FinalRange = 0.0f;		//�����ۑ��p
	GameBox* UpBox = nullptr;		//�����グ�锠�̃|�C���^
	CVector3 P_B_Range;				//�����v�Z�p
	float P_B_Range_Final;			//����
	GameBox* UpBox_Origin= nullptr;	//�����グ�锠�̐e�inull�Ȃ�I���W���j
	CVector3 Hosei;					//Another�p���W�␳
	float Range_Hosei;				//�����␳

	for (auto go : boxList) {

		//Origin���ȁH
		if (go->GetBoxTag() == GameBox::Origin) {

			UpBox_Origin = nullptr;	//�������I���W���Ȃ̂ŏ��������Ă���
			Hosei = CVector3::Zero();
			Range_Hosei = 0.0f;

			go->SetAllColor({ 0.0f,0.0f,0.0f });	//�F�����������Ă���

		}
		else if (go->GetBoxTag() == GameBox::Another) {
			//�A�i�U�[��
			UpBox_Origin = go->GetOriginBox();
			Hosei = go->GetAnotherHosei();
			Range_Hosei = go->GetAnotherRangeHosei();
		}

		//�ړ��ʌv�Z
		P_B_Range = m_position - (go->GetPosition() + Hosei);
		P_B_Range_Final = P_B_Range.Length();

		//���ʃ^�C��
		bool Flag = false;

		//�߂��ɂ��邩�H
		if (P_B_Range_Final > m_boxUpRange + Range_Hosei) {
			Flag = true;	//�������I�A�E�g�I
		}
		//�������������H
		if (fabsf(P_B_Range.y) > m_boxUp_Y_Max) {
			Flag = true;	//�����Ⴂ�����I�A�E�g�I
		}
		//�p�x���������H
		CVector3 playerForward = CVector3::AxisZ();
		m_rotation.Multiply(playerForward);
		//������v���C���[�ɐL�т�x�N�g�������߂�B
		CVector3 toPlayerDir = m_position - (go->GetPosition() + Hosei);
		toPlayerDir.Normalize();
		//���ς��v�Z����B
		float d = playerForward.Dot(toPlayerDir);
		//�Ȃ��p�����߂�B
		float angle = acos(d);
		//����p����
		if (fabsf(angle) < CMath::DegToRad(m_boxUp_Angle)) {
			Flag = true;	//�p�x�Ⴂ�����I�A�E�g�I
		}

		if (Flag == false) {	//�R���ɒʂ������݂̂������܂ŗ����

			if (UpBox == nullptr) {
				if (UpBox_Origin == nullptr) {
					UpBox = go;
				}
				else {
					UpBox = UpBox_Origin;
				}
				FinalRange = P_B_Range_Final;
			}
			else {
				//�������߂����ȁH
				if (FinalRange > P_B_Range_Final) {
					if (UpBox_Origin == nullptr) {
						UpBox = go;
					}
					else {
						UpBox = UpBox_Origin;
					}
					FinalRange = P_B_Range_Final;
				}
			}

		}

	}

	//����I
	m_upKouho_Box = UpBox;

	//�F�ύX
	if (m_upKouho_Box != nullptr) {
		m_upKouho_Box->SetAllColor({ 1.0f,0.0f,0.0f });
	}

}

void Player::BoxUp() {

	//���������グ�ĂȂ��Ȃ�I��
	if (m_upBox == nullptr) {
		return;
	}
	//���̏グ���낵���Ȃ狭���I��
	if (m_boxMoveFlag == true) {
		return;
	}

	//���ړ�
	CVector3 BoxPos = m_upBox->GetPosition();
	BoxPos = m_position;
	BoxPos.y += m_boxPos_Y_Hosei;	//��������ׂ��ꏊ�ɓ�����
	m_upBox->GameBox_Set(BoxPos, m_rotation);
	
}

void Player::BoxMove() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//���̏グ���낵���łȂ��Ȃ狭���I��
	if (m_boxMoveFlag == false) {
		return;
	}

	//�x�W�F�Ȑ����g�����v�Z
	m_catmull_U += 0.1f;
	CVector3 output_point = m_point_2 * (1 - m_catmull_U)*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 * 
							m_point_4 * m_catmull_U*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 * 
							m_point_1 * m_catmull_U*m_catmull_U*(1 - m_catmull_U) + 
							m_point_3 * m_catmull_U*m_catmull_U*m_catmull_U;
	m_upBox->GameBox_Set(output_point, m_upBox->GetRotation());

	//�ړ��I��
	if (m_catmull_U >= 1.0f) {
		m_boxMoveFlag = false;
		m_catmull_U = 0.0f;
		if (m_upOrDown == true) {
			m_upBox = nullptr;
		}
	}

}

void Player::BoxDelete() {

	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//���������グ�ĂȂ��Ȃ�I��
	if (m_upBox == nullptr) {
		return;
	}
	//���̏グ���낵���Ȃ狭���I��
	if (m_boxMoveFlag == true) {
		return;
	}

	//�Ή�����{�^����������ĂȂ��Ȃ狭���I��
	if (HIWORD(GetAsyncKeyState(GameData::GetInstance()->GetBoxDeleteKey()))) {
		if (m_boxDeleteButtonFlag == false) {
			m_boxDeleteButtonFlag = true;
		}
		else {
			return;
		}
	}
	else {
		m_boxDeleteButtonFlag = false;
		return;
	}

	//���폜
	BoxMaker::GetInstance()->BoxDelete(m_upBox);
	m_upBox = nullptr;
	m_boxUpFlag = false;

}

CVector3 Player::BoxThrowSearch() {

	CVector3 MousePos = MouseSupporter::GetInstance()->GetMousePos_3D();

	btDiscreteDynamicsWorld* dw = g_physics->GetDynamicWorld();
	btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), MousePos);
	dw->rayTest((btVector3)g_camera3D.GetPosition(), MousePos, CRR_Callback);
	if (CRR_Callback.hasHit()) {

		//����
		CVector3 ThrowTarget = CVector3::Zero();
		float TargetLength = BoxThrowMaxLength;
		bool TargetSetFlag = false;
		LevelSet::Obj_Data* obj_data = StageSet::GetInstance()->GetObjData();

		for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
			if (wcscmp(obj_data->ObjName, L"") == 0) {
				//���O���Ȃ��I�����I��
				break;
			}
			else {
				//�������ēG�Ȃ�v�Z����
				ObjectClass* go = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(obj_data->nameKey);
				if (go != nullptr) {
					if (go->m_object == ObjectClass::ObjectClass_Tag::EnemyObj) {
						//�G�Ȃ̂ō��W���擾���ċ������߂��Ȃ�㏑��
						CVector3 diff = go->GetPosition() - CRR_Callback.m_hitPointWorld;
						float Len = diff.Length();
						if (Len <= TargetLength) {
							//�㏑��
							ThrowTarget = go->GetPosition();
							TargetLength = Len;
							TargetSetFlag = true;	//1�x�ł���������������true�ɂȂ�
						}
					}
				}
			}
			obj_data++;
		}

		//�ŏI����
		if (TargetSetFlag == true) {
			//�ړ����x���v�Z���ĕԂ�
			CVector3 diff = ThrowTarget - m_position;
			diff.Normalize();
			diff *= 100.0f;		//�ړ��p���[
			diff.y = -3.0f;		//����
			return diff;
		}
		else {
			//�ǂ��ɂ�����������Ȃ�����			
			CVector3 MoveSpeed = CRR_Callback.m_hitPointWorld - m_upBox->GetPosition();
			MoveSpeed.Normalize();
			MoveSpeed *= 100.0f;	//�ړ��p���[
			MoveSpeed.y = 1.0f;		//����
			return MoveSpeed;
		}

	}
	else {
		CVector3 MoveSpeed = m_moveSpeed;
		MoveSpeed.Normalize();
		MoveSpeed *= 100.0f;	//�ړ��p���[
		MoveSpeed.y = 1.0f;		//����
		return MoveSpeed;
	}

}

void Player::PlayerMiss(const CVector3& pos) {

	//�m�b�N�o�b�N�̌v�Z
	CVector3 Pos = m_position;
	CVector3 Move = m_moveSpeed;
	Move.Normalize();
	Pos += (Move * m_damage_knockback);
	m_nextPos = Pos;

	m_moveSpeed = CVector3::Zero();
	m_moveSpeed.y = m_damage_YHosei;
	m_damage_Flag = true;
	m_damage_JumpFlag = false;
}