#pragma once

/// <summary>
/// �C�x���g�̖��O�ƃC�x���gNo�̃f�[�^
/// </summary>
class EventData
{
public:
	//���O�ƈ�v����C�x���g�ԍ���Ԃ��i�s��v�Ȃ�-1�j
	int SearchEventNo(const wchar_t* eventName);

private:

	//�C�x���g�̖��O�ꗗ
	const wchar_t* Event_Data[10]{
		L"Tutorial_1"	//�`���[�g���A���c�X�C�b�`�Ɣ�
		L"Tutorial_2"	//�`���[�g���A���c���𓊂���
		L"Tutorial_3"	//�`���[�g���A���c�_�u���X�C�b�`
	};

};

