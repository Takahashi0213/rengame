#pragma once

/// <summary>
/// 信号を受け取って上下移動する扉
/// </summary>
class Door : public IGameObject, public ObjectClass
{
public:
	Door();
	~Door();
	void Update()override;
	void Render()override;

	//フラグ操作
	void SetFlag(bool flag) {
		m_upDownFlag = flag;
	}
	bool GetFlag() {
		return m_upDownFlag;
	}

private:

	bool m_upDownFlag = false;		//上下状態 faise=降下 true=上昇

};

