#pragma once

/// <summary>
/// ゲームのステータスはこちら
/// ※シングルトン
/// </summary>
class GameData
{
	static GameData* m_instance;
public:
	enum Place_Data {		//場所データ
		Null_Place,		//空白
		Warehouse,		//倉庫
		Meadow,			//草原
	};

	GameData();
	~GameData();

	////°˖✧◝(⁰▿⁰)◜✧˖°////
	////データ用関数/////////
	////°˖✧◝(⁰▿⁰)◜✧˖°////

	/// <summary>
	/// 進行度加算
	/// </summary>
	void ProgressPlus() {
		m_progress++;
	}
	/// <summary>
	/// 進行度取得
	/// </summary>
	/// <returns>進行度</returns>
	int GetProgress() {
		return m_progress;
	}

	/// <summary>
	/// 現在位置変更
	/// </summary>
	/// <param name="pd">新しい現在位置</param>
	void SetPlace(Place_Data pd) {
		m_nowPlace = pd;
	}
	/// <summary>
	/// 現在位置取得
	/// </summary>
	/// <returns>イマココ！</returns>
	Place_Data GetPlace() {
		return m_nowPlace;
	}

	/// <summary>
	/// メニューフラグの変更と取得
	/// </summary>
	void SetMenuFlag(bool flag) {
		m_menuFlag = flag;
	}
	bool GetMenuFlag() {
		return m_menuFlag;
	}

	/// <summary>
	/// スターマネーの変更
	/// </summary>
	/// <param name="money">加算値（負の数も可）</param>
	void StarMoneyPlus(int money) {
		m_starMoney += money;
		if (m_starMoney > MAX_STAR_MONEY) {	//上限
			m_starMoney = MAX_STAR_MONEY;
		}
		if (m_starMoney < 0) {	//下限
			m_starMoney = 0;
		}
	}
	/// <summary>
	/// スターマネーを取得
	/// </summary>
	/// <returns>おかね</returns>
	int GetStarMoney() {
		return m_starMoney;
	}

	/// <summary>
	/// 現在魔力の設定
	/// </summary>
	/// <param name="power">これ</param>
	void SetMagicPower(int power) {
		m_magicPower = power;
		if (m_magicPower > m_magicPower_MAX) {	//上限
			m_magicPower = m_magicPower_MAX;
		}
		if (m_magicPower < 0) {	//下限
			m_magicPower = 0;
		}
	}
	/// <summary>
	/// 現在魔力の加算
	/// </summary>
	/// <param name="power">加算値（負の数も可）</param>
	void MagicPowerPlus(int power) {
		m_magicPower += power;
		if (m_magicPower > m_magicPower_MAX) {	//上限
			m_magicPower = m_magicPower_MAX;
		}
		if (m_magicPower < 0) {	//下限
			m_magicPower = 0;
		}
	}
	/// <summary>
	/// 魔力の取得
	/// </summary>
	/// <returns>現在値</returns>
	int GetMagicPower() {
		return m_magicPower;
	}

	/// <summary>
	/// 最大魔力の設定と取得
	/// </summary>
	void SetMaxMagic(int max) {
		m_magicPower_MAX = max;
	}
	int GetMaxMagic() {
		return m_magicPower_MAX;
	}

	/// <summary>
	/// 現在体力の設定
	/// </summary>
	/// <param name="hp">これ</param>
	void SetHP(int hp) {
		m_hp = hp;
	}
	/// <summary>
	/// 現在体力の加算
	/// </summary>
	/// <param name="hp">加算値（負の数も可）</param>
	void HP_Plus(int hp) {
		m_hp += hp;
		if (m_hp > m_hp_MAX) {	//上限
			m_hp = m_hp_MAX;
		}
		if (m_hp < 0) {	//下限
			m_hp = 0;
		}
	}
	/// <summary>
	/// 体力の取得
	/// </summary>
	/// <returns>現在値</returns>
	int GetHP() {
		return m_hp;
	}

	/// <summary>
	/// 最大体力の設定と取得
	/// </summary>
	void SetMaxHP(int max) {
		m_hp_MAX = max;
	}
	int GetMaxHP() {
		return m_hp_MAX;
	}

	/// <summary>
	/// メッセージスピードの設定と取得
	/// </summary>
	void SetMessageSpeed(int speed) {
		m_messageSpeed = speed;
	}
	int GetMessageSpeed() {
		return m_messageSpeed;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameData* GameData::GetInstance() {
		return m_instance;
	}

private:

	//基本
	int m_progress = 0;		//進行度
	Place_Data m_nowPlace = Null_Place;		//現在位置
	bool m_menuFlag = false;				//今メニュー開ける？

	//解放要素
	struct GameFlag {
		bool m_boxMakerFlag;	//箱生成能力
		bool m_equipmentFlag;	//装備変更
		bool m_teleportFlag;	//メニューからのテレポート
	};
	GameFlag m_gameFlag;	//要素解放フラグ

	//スターマネー
	int m_starMoney = 0;
	const int MAX_STAR_MONEY = 99999;	//最大所持金

	//プレイヤーステータス
	int m_level = 1;		//レベル
	int m_nextExp = 10;		//次のレベルに必要な経験値
	int m_nowExp = 0;		//現在の経験値
	int m_totalExp = 0;		//累計経験値
	//
	int m_magicPower = 100;	//現在マナ
	int m_magicPower_MAX = 100;	//マナ最大値
	int m_hp = 300;		//現在体力
	int m_hp_MAX = 300;	//最大体力

	//コンフィグ
	int m_messageSpeed = 2;		//会話のメッセージ送りスピード

};

