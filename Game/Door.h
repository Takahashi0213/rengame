#pragma once

/// <summary>
/// M†‚ğó‚¯æ‚Á‚Äã‰ºˆÚ“®‚·‚é”à
/// </summary>
class Door : public IGameObject, public ObjectClass
{
public:
	Door();
	~Door();
	void Update()override;
	void Render()override;

	//ƒtƒ‰ƒO‘€ì
	void SetFlag(bool flag) {
		m_upDownFlag = flag;
	}
	bool GetFlag() {
		return m_upDownFlag;
	}

private:

	bool m_upDownFlag = false;		//ã‰ºó‘Ô faise=~‰º true=ã¸

};

