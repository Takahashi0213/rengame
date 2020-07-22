#pragma once

/// <summary>
/// �M�����󂯎���ď㉺�ړ������
/// </summary>
class Door : public IGameObject, public ObjectClass
{
public:
	Door();
	~Door();
	void Update()override;
	void Render()override;

	//�t���O����
	void SetFlag(bool flag) {
		m_upDownFlag = flag;
	}
	bool GetFlag() {
		return m_upDownFlag;
	}

private:

	bool m_upDownFlag = false;		//�㉺��� faise=�~�� true=�㏸

};

