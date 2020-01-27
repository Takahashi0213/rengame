#pragma once

/// <summary>
/// グラフィック関連の変数色々
/// </summary>
class GameGraphic {
public:

	//演出用変数
	float m_blurIntensity = 0.0f;		//画面にブラーをかけるポストエフェクトの数値
	const int m_blurPriority = 6;		//この数値以下のt_spriteはブラーの対象になる

};