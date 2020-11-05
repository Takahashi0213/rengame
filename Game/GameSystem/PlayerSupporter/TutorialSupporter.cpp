#include "stdafx.h"
#include "TutorialSupporter.h"


TutorialSupporter::TutorialSupporter()
{
	m_tutorialText = CGameObjectManager::GetInstance()->NewGO<FontRender>("TutorialText", 9);
}


TutorialSupporter::~TutorialSupporter()
{
}

void TutorialSupporter::TutorialChange(const Tutorial_Progress Progress) {

}