#pragma once

/// <summary>
/// 箱を削除するコマンド！！
/// </summary>
class Menu_BoxAllDelete
{
public:
	Menu_BoxAllDelete();
	~Menu_BoxAllDelete();

	//あっぷでーーーーーーと
	void DeleteCheckUpdate();

private:

	//がぞん
	std::vector<SpriteRender*> m_spriteRenderList;
	std::vector<FontRender*> m_fontRenderList;

	//箱を消すときの確認メッセ
	const wchar_t* CheckText = L"全ての箱を破壊して\nマナを全回復しますか？";
	const wchar_t* YesText = L"破壊";
	const wchar_t* NoText = L"やめる";

	//れんだ～～
	SpriteRender* MenuWindow;		//ウィンドウ
	SpriteRender* ButtonWindow_Left;	//左ウィンドウ
	SpriteRender* ButtonWindow_Right;	//右ウィンドウ
	//
	FontRender* Check_Font;	//消しますか？のテキスト
	FontRender* Yes_Font;	//はいのテキスト
	FontRender* No_Font;	//いいえのテキスト

};

