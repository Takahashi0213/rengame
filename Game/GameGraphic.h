#pragma once

/// <summary>
/// グラフィック関連の変数色々
/// </summary>
class GameGraphic {
public:

	//演出用変数
	float m_blurIntensity = 0.0f;		//画面にブラーをかけるポストエフェクトの数値
	const int m_blurPriority = 6;		//この数値以下のt_spriteはブラーの対象になる
	bool m_dofFlag = true;				//Dofを実行する？
	const int TransitionTime = 60;		//場面転換トランジションフレーム数

	const CVector3 LoadingAnimePos = { 480.0f,-220.0f,0.0f };	//ローディングアニメーションの座標

	CVector3 m_playerPos = CVector3::Zero();	//ディザリングに使う

};