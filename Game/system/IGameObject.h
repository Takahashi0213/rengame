#pragma once

	class IGameObject
	{
	public:
		/// <summary>
		/// �I�u�W�F�N�g�^�O
		/// �ォ�珇�ԂɎ��s�����
		/// 
		/// t_BackSprite
		/// ��
		/// t_Other�i��{�͂���j
		/// ��
		/// �|�X�g�G�t�F�N�g
		/// ��
		/// t_Sprite
		/// 
		/// </summary>
		enum objectTag {
			t_BackSprite, //�w�i�X�v���C�g
			t_Other,
			t_Sprite,	//�X�v���C�g����Ȃ��Ă��|�X�g�G�t�F�N�g��Ƀ����_�����O���������̂͂����ɕ��ނ���Ƃ����Ǝv���܂��� �m��񂯂�
		};

		IGameObject();
		virtual ~IGameObject();
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
		void SetObjectName(const wchar_t* name) {
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
		void SetActiveFlag(const bool& flag) {
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
		void SetObjectTag(const objectTag tag) {
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
		/// <param name="priority">�D��x�i�ŏ���0�A�ő��MAX_PRIORITY�j</param>
		void SetPriority(int priority) {
			if (priority > MAX_PRIORITY) {
				priority = MAX_PRIORITY;
			}
			if (priority < 0) {
				priority = 0;
			}
			m_priority = priority;
		}

		/// <summary>
		/// �D��x���擾
		/// </summary>
		/// <returns>�D��x�i�ŏ���0�A�ő��MAX_PRIORITY�j</returns>
		int GetPriority() {
			return m_priority;
		}

	private:
		int m_nameKey = 0;						//�l�[���L�[
		int m_priority = 0;						//�D��x
		bool m_activeFlag = true;				//�A�N�e�B�u�t���O
		bool m_queryFlag = false;				//�N�G���p�t���O

		objectTag m_tag = t_Other;				//�I�u�W�F�N�g�^�O
	};

