/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include "PhysicsObjectBase.h"

/*!
* @brief	�ÓI�����I�u�W�F�N�g
*/
class PhysicsStaticObject : public PhysicsObjectBase {
public:
	/*!
		* @brief	�R���X�g���N�^�B
		*/
	PhysicsStaticObject();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~PhysicsStaticObject()
	{
		Release();
	}
	/*!
	* @brief	����B
	*/
	void Release() override final;
	/*!
	* @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
	*@param[in]	skinModel	�X�L�����f���B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot);
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scl);

	/*!
	* @brief	���W�Ɖ�]��ݒ�B
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		m_rigidBody.SetPositionAndRotation(pos, rot);
	}

	MeshCollider* GetMeshCollider() {
		return &m_meshCollider;
	}

	RigidBody* GetRigidBody() {
		return &m_rigidBody;
	}

private:
	/*!
	* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot) override final;

	MeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
	RigidBody m_rigidBody;				//!<���́B
	bool m_rigidFlag = false;
};
