#pragma once

/// <summary>
/// ���x���A�b�v���̃C�x���g
/// </summary>
enum LevelUpEvent {
	None = 0,			//�C�x���g����
	Up_Mana = 1,		//�}�i�̌���
	Up_Hp = 1 << 1,		//HP����
	Up_Mp = 1 << 2,
};
/// <summary>
/// ���x���A�b�v�f�[�^
/// </summary>
struct LevelUpData {
	unsigned int levelUpEvent;
	int manaUp;	//�}�i�̏㏸�ʁB

};
/// <summary>
/// ���x���A�b�v�f�[�^�e�[�u���B
/// </summary>
static LevelUpData LEVEL_UP_DATA_TABLE[] = {
	{ None				,	0	},		//���x��0�B�C�x���g�͉����Ȃ�
	{ None				,	0	},		//���x��1�B�C�x���g�͉����Ȃ�
	{ Up_Mana			,	10	},		//���x��2�B
	{ Up_Hp				,	0	},		//���x��3�B
	{ Up_Mana			,	10	},		//���x��4�B
	{ Up_Mana			,	5	},		//���x��5�B
	{ Up_Mana			,	5	},		//���x��6�B
	{ Up_Mana | Up_Hp	,	5	},		//���x��7�BHP�ƃ}�i�������ɏ㏸����
	{ Up_Mana			,	5	},		//���x��8�B
	{ Up_Mana			,	5	},		//���x��9�B
	{ Up_Mana			,	10	},		//���x��10�B
};
