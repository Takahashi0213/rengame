#pragma once

	class IGameObject
	{
	public:
		/// <summary>
		/// �I�u�W�F�N�g�^�O
		/// �ォ�珇�ԂɎ��s�����
		/// </summary>
		enum objectTag {
			t_Other,
			t_Sprite,
		};

		IGameObject();
		~IGameObject();
		virtual void Update() = 0;
		virtual void Render() = 0;

		/// <summary>
		/// �I�u�W�F�N�g������l�[���L�[��ݒ�
		/// </summary>
		/// <param name="name">�ݒ肷��I�u�W�F�N�g��</param>
		void SetObjectName(const char* name) {
			int m_name = Hash::MakeHash(name);
			m_nameKey = m_name;
		}

		/// <summary>
		/// �l�[���L�[��Ԃ�
		/// </summary>
		/// <returns>�l�[���L�[</returns>
		int GetObjectName() {
			return m_nameKey;
		}

		/// <summary>
		/// �A�N�e�B�u�t���O���Z�b�g����
		/// </summary>
		/// <param name="flag">�ݒ肷��t���O</param>
		void SetActiveFlag(bool flag) {
			m_activeFlag = flag;
		}

		/// <summary>
		/// �A�N�e�B�u�t���O���擾����
		/// </summary>
		/// <returns>���̃I�u�W�F�N�g�̃A�N�e�B�u�t���O</returns>
		bool GetActiveFlag() {
			return m_activeFlag;
		}

		/// <summary>
		/// �N�G���t���O���Z�b�g����
		/// </summary>
		/// <param name="flag">�ݒ肷��t���O</param>
		void SetQueryFlag(bool flag) {
			m_queryFlag = flag;
		}

		/// <summary>
		/// �N�G���t���O���擾����
		/// </summary>
		/// <returns>���̃I�u�W�F�N�g�̃N�G���t���O</returns>
		bool GetQueryFlag() {
			return m_queryFlag;
		}

		/// <summary>
		/// �I�u�W�F�N�g�^�O��ݒ肷��
		/// </summary>
		/// <param name="tag">�^�O</param>
		void SetObjectTag(objectTag tag) {
			m_tag = tag;
		}

		/// <summary>
		/// �I�u�W�F�N�g�^�O���擾����
		/// </summary>
		/// <returns>�^�O</returns>
		objectTag GetObjectTag() {
			return m_tag;
		}

		/// <summary>
		/// �D��x��ݒ�
		/// </summary>
		/// <param name="priority">�D��x�i�ő��MAX_PRIORITY�j</param>
		void SetPriority(int priority) {
			if (priority > MAX_PRIORITY) {
				priority = MAX_PRIORITY;
			}
			m_priority = priority;
		}

		/// <summary>
		/// �D��x���擾
		/// </summary>
		/// <returns>�D��x�i�ő��MAX_PRIORITY�j</returns>
		int GetPriority() {
			return m_priority;
		}

	private:
		int m_nameKey = 0; //�l�[���L�[
		int m_priority = 0; //�D��x
		bool m_activeFlag = true; //�A�N�e�B�u�t���O
		bool m_queryFlag = false; //�N�G���p�t���O

		objectTag m_tag = t_Other; //�I�u�W�F�N�g�^�O
	};
