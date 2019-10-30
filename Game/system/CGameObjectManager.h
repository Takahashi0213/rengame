#pragma once
#include <vector>
#include "IGameObject.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��c
/// </summary>
	class CGameObjectManager {
		static CGameObjectManager* m_instance;
	public:

		CGameObjectManager();
		~CGameObjectManager();

		/// <summary>
		/// �C���X�^���X���쐬
		/// </summary>]
		/// <param name="obName">�I�u�W�F�N�g��</param>
		/// <returns>�ǉ������I�u�W�F�N�g�̃|�C���^</returns>	
		template<class T>
		T* NewGO(const char* objName,const int priority = 0) {
			//�C���X�^���X�𐶐�����
			T* newObj = new T;
			//���������C���X�^���X���ϒ��z��ɒǉ�����
			m_goList.push_back(newObj);
			//�I�u�W�F�N�g����ݒ肷��
			newObj->SetObjectName(objName);
			//�D��x��ݒ肷��
			newObj->SetPriority(priority);
			//�ǉ������I�u�W�F�N�g��߂�
			return newObj;
		}

		/// <summary>
		/// �I�u�W�F�N�g�̍폜
		/// </summary>
		/// <param name="go">�폜����I�u�W�F�N�g</param>
		void DeleteGO(IGameObject* go) {

			//�폜����I�u�W�F�N�g���폜���X�g�ɒǉ����Ă���
			m_deleteList.push_back(go);

		}

		/// <summary>
		/// �I�u�W�F�N�g�̖��O�Ō���
		/// </summary>
		/// <param name="objName">�T�������I�u�W�F�N�g�̃l�[���L�[</param>
		/// <param name="queryflag">true�ɂ���Ɓc
		/// �E���������I�u�W�F�N�g�̃N�G���t���O��true�Ȃ�X���[����悤�ɂȂ�
		/// �E�Ԃ����I�u�W�F�N�g�̃N�G���t���O��true�ɂ���
		/// </param>
		/// <remarks>
		/// �l�[���L�[��MakeHash�ō���Ă�
		/// 
		/// ���T���v���R�[�h��
		/// //�v���C���[��T��
		/// 
		/// Player* p = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"),false);
		/// 
		/// ���n�b�V���l�𖈉񐶐�����̂��ʓ|�Ȃ�O�����Ăǂ����Ő������Ƃ��Ƃ����񂶂�Ȃ��ł�����
		/// </remarks>
		/// <returns>���������I�u�W�F�N�g�̃A�h���X</returns>
		template<class T>
		T* FindGO(const int objkey,bool queryflag = false) {
			
			bool m_findFlag = false; //����������true�ɂ���
			bool m_getFlag = false; //�Ԃ��̂����̃I�u�W�F�N�g�̃A�h���X�Ŗ{����OK�Ȃ�true
			T* ret;

			for (auto go : m_goList) {
				//���O����
				if (go->GetObjectName() == objkey) {
					//���O����v����

					m_getFlag = true; //�t���O�̏�����
					if (queryflag == true) { //�N�G���t���O�̊m�F
						if (go->GetQueryFlag() == true) {
							m_getFlag = false; //���̃I�u�W�F�N�g�̓N�G���t���O�I���Ȃ̂ł�߂悤��
						}
					}

					if (m_getFlag == true) { //true�Ȃ炱���Ō���

					m_findFlag = true;

					if (queryflag == true) { //�N�G���t���O��true�Ȃ�I�u�W�F�N�g�̃N�G���t���O��true�ɂ���
						go->SetQueryFlag(true);
					}

#ifdef _DEBUG
					ret = dynamic_cast<T*>(go);
					if (ret == nullptr) {
						//�^�ϊ��Ɏ��s�����B�^�Ԉ���ĂȂ��H�H�H
						std::abort();
					}
#else
					T* ret = (T*)go;
#endif
					}
				}
			}

			if (m_findFlag == true) {
				return ret;
			}
			else {
				return nullptr;
			}
		}

		/// <summary>
		/// ���݂̃I�u�W�F�N�g����Ԃ�
		/// </summary>
		/// <returns>�I�u�W�F�N�g��</returns>
		int AllObjects() {
			return (int)m_goList.size();
		}

		/// <summary>
		/// �N�G���t���O��S��false�ɂ���
		/// </summary>
		void QueryFlagReset() {
			for (auto go : m_goList) {
				go->SetQueryFlag(false);
			}
		}

		/// <summary>
		/// �����������O�̃I�u�W�F�N�g���������邩��Ԃ�
		/// </summary>
		/// <remarks>
		/// �I�u�W�F�N�g�̃N�G�����s���Ƃ��͂��̊֐����g���Ċ撣�낤�I
		/// �@���̊֐��Ō����ΏۂƂȂ�I�u�W�F�N�g��X���擾
		/// �AX�񃋁[�v���鏈������FindGO����
		/// �@�K���N�G���t���O�̈�����true�ɂ��Ď��s���邱��
		/// �B�N�G�����s��QueryFlagReset�����s����
		/// 
		/// ���T���v���R�[�h��
		/// //Enemy�ɑ΂��ăN�G���ōU�����s��
		/// 
		/// int co = CGameObjectManager::GetInstance()->ObjCount<Enemy>(Enemy�̃l�[���L�[);
		/// for( i = 0 ; i < co ; i++){ //��������Enemy�̐����[�v
		/// 
		///		Enemy* enemy = CGameObjectManager::GetInstance()->FindGO<Enemy>(Enemy�̃l�[���L�[,true);
		///		enemy->Attack();
		/// 
		/// }
		/// CGameObjectManager::GetInstance()->QueryFlagReset(); //�N�G���t���O�����Z�b�g�i��Еt���j
		/// 
		/// </remarks>
		/// <param name="objkey">�I�u�W�F�N�g�L�[</param>
		/// <returns>����������</returns>
		template<class T>
		int ObjCount(const int objkey) {
			int count = 0;
			//auto itr = m_goList.begin(); //�擪�̃C�e���[�^

			for (auto go : m_goList) {
				if (go->GetObjectName() == objkey) { //�I�u�W�F�N�g�𔭌��I
					count++;
				}
				//itr++; //���̍��ڂ�
			}
			return count;
		}

		/// <summary>
		/// �X�V�p�֐�
		/// </summary>
		void Execute();

		/// <summary>
		/// �C���X�^���X���擾�I
		/// </summary>
		/// <returns>�C���X�^���X�ł�</returns>
		static CGameObjectManager* CGameObjectManager::GetInstance() {

			if (m_instance == nullptr) { //�I�u�W�F�N�g������Ă��Ȃ���΍��
				m_instance = new CGameObjectManager;
			}
			return m_instance;
		}

	private:
		std::list<IGameObject*> m_goList; //�I�u�W�F�N�g�̃��X�g
		std::list<IGameObject*> m_deleteList; //�폜����I�u�W�F�N�g�̃��X�g

		/// <summary>
		/// �폜���X�g�ɐς񂾃I�u�W�F�N�g���܂Ƃ߂č폜����
		/// </summary>
		void CGameObjectManager::ExecuteDeleteGameObjects();

	};

	template<class T>
	/// <summary>
	/// �C���X�^���X���쐬
	/// </summary>
	/// <returns>�ǉ������I�u�W�F�N�g�̃|�C���^</returns>
	static T* NewGO(const char* objName, const int priority = 0) {

		return CGameObjectManager::GetInstance()->NewGO<T>(objName);
	}

	/// <summary>
	/// �I�u�W�F�N�g�̍폜
	/// </summary>
	/// <param name="go">�폜����I�u�W�F�N�g</param>
	static void DeleteGO(IGameObject* go) {

		CGameObjectManager::GetInstance()->DeleteGO(go);

	}

	/// <summary>
	/// �I�u�W�F�N�g�̖��O�Ō���
	/// </summary>
	/// <param name="objName">�T�������I�u�W�F�N�g��</param>
	/// <returns>���������I�u�W�F�N�g�̃A�h���X</returns>
	template<class T>
	static T* FindGO(const char* objName) {
		CGameObjectManager::GetInstance()->FindGO(objName);
	}
