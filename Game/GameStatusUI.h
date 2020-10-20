#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// スターマネー取得演出
/// EXP獲得演出
/// レベルアップ演出
/// 描画専用
/// </summary>
class GameStatusUI
{
public:
	GameStatusUI();
	~GameStatusUI();

	//予約処理追加
	void AddStarMoney(const int x) {
		StatusData addData = { Status_Anime::StarMoney ,x };
		m_statusList.push_back(addData);
	}
	void AddEXP(const int x) {
		StatusData addData = { Status_Anime::EXP ,x };
		m_statusList.push_back(addData);
	}

	//外部から呼んで更新してください
	void GameStatusUI_Update();

private:
	enum Status_Anime {
		StatusAnime_NULL,	//無
		StarMoney,
		EXP,
	};
	struct StatusData {
		Status_Anime StatusAnime = Status_Anime::StatusAnime_NULL;	//この演出の種類
		int Add = 0;												//この演出で加算される値
	};

	//関数
	/// <summary>
	/// エフェクト確定時の処理をまとめたもの 下記のエフェクト実行もここで行う
	/// </summary>
	/// <param name="it">確定したm_statusListのイテレータ</param>
	void StatusEffect_StartStandBy(const std::list<StatusData>::iterator it);
	//エフェクト確定時、エフェクトを実行する
	//もしエフェクトの種類が違う場合はフェードも行う
	void StatusEffect_Start();
	/// <summary>
	/// アニメーションをまとめてフェードする
	/// </summary>
	/// <param name="anime">フェードする範囲</param>
	/// <param name="alpha">フェード先のアルファ値</param>
	/// <param name="time">フェード時間</param>
	void Status_SpriteAlphaSet(const Status_Anime anime, const float alpha, const int time);
	/// <summary>
	/// エフェクトの内部更新
	/// </summary>
	void Status_EffectUpdate();

	//ステータス演出予約リスト
	std::list<StatusData>m_statusList;						//ステータス演出リスト
	std::list<StatusData>::iterator m_statusList_it;		//ステータス演出リストで、現在演出中の内容
	
	//ステータス演出
	bool m_statusEffectFlag = false;						//現在演出中？（trueで演出中！）
	Status_Anime m_nowStatusAnime = StatusAnime_NULL;		//現在演出中のアニメーションの種類

	//スターマネースプライト
	const CVector3 GameStatusUI_StarMoney_DefPos = { -500.0f,100.f,0.0f };	//スターマネー基本座標
	const CVector3 GameStatusUI_EXP_DefPos = { 0.0f,80.f,0.0f };			//EXP基本座標

	SpriteRender* m_starMoneySprite = nullptr;				//スターマネーアイコン
	const CVector2 StarMoneySpriteSize = { 60.0f,60.0f };	//スターマネーアイコンの大きさ

	SpriteRender* m_statusBase_StarMoney = nullptr;			//ステータス土台
	const CVector2 StarMoneyBaseSize = { 200.0f,60.0f };	//スターマネーウィンドウの大きさ

	FontRender* m_text_StarMoney = nullptr;					//テキスト！
	const float FontSize = 0.5f;							//フォントサイズ
	const CVector2 StarMoneyTextHosei = { -60.0f, 20.0f };	//フォントの位置補正

	//EXPスプライト
	SpriteRender* m_statusBase_EXP = nullptr;				//EXPステータス土台

	SpriteRender* m_statusBar_EXP = nullptr;				//EXPステータスバー
	const CVector2 EXP_Bar_Size = { 38.0f, 14.0f };			//EXPステータスバーの大きさ

	SpriteRender* m_statusCover_EXP = nullptr;				//EXPステータスカバー
	const CVector2 EXP_Cover_Size = { 54.0f, 18.0f };		//EXPステータスカバーの大きさ

	const CVector2 EXP_SizeHosei = { 3.0f, 2.0f };			//EXPステータスの補正


	const int SpritePriority = 9;							//優先度

	//エフェクト色々
	CVector3 m_point_1 = CVector3::Zero();					//終点寄り
	CVector3 m_point_2 = CVector3::Zero();					//始点
	CVector3 m_point_3 = CVector3::Zero();					//終点
	CVector3 m_point_4 = CVector3::Zero();					//始点寄り
	float m_kyokusen = 0.0f;								//ベジェ曲線で使う
	const float Y_Hosei = 50.0f;							//ベジェ曲線の最高到達点Y補正
	bool m_effectFlag = false;								//エフェクト表示中？

	//色々定数
	const int StatusAlphaTime = 12;							//ステータスのフェード時間


};

/// <summary>
/// スターマネーを獲得したり
/// 経験値を獲得した時に、ここの処理を呼ぶと
/// ・GameDataへの加算
/// ・画面描画
/// を自動で行ってくれる便利な処理群です
/// ※シングルトン
/// </summary>
class GameStatus_UISystem final : public IGameObject
{
	static GameStatus_UISystem* m_instance;
public:
	GameStatus_UISystem();
	~GameStatus_UISystem();
	void Update()override;
	void Render()override;

	//ここから加算処理用
	void AddStarMoney(const int x) {
		m_gameStatusUI.AddStarMoney(x);
	}
	void AddEXP(const int x) {
		m_gameStatusUI.AddEXP(x);
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameStatus_UISystem* GameStatus_UISystem::GetInstance() {
		return m_instance;
	}

private:
	GameStatusUI m_gameStatusUI;
};