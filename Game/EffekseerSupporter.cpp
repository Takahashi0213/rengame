#include "stdafx.h"
#include "EffekseerSupporter.h"

EffekseerSupporter* EffekseerSupporter::m_instance = nullptr;

EffekseerSupporter::EffekseerSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


EffekseerSupporter::~EffekseerSupporter()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

Effekseer::Handle EffekseerSupporter::NewEffect(const wchar_t* EffectFileName, bool PostFlag,
	Effekseer::Vector3D DefPos) {

	//サンプルのエフェクトをロードする。
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectFileName);
	//エフェクトを再生する。
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, DefPos.X, DefPos.Y, DefPos.Z);

	//リストに追加や
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;
}

Effekseer::Handle EffekseerSupporter::NewEffect(const EffectData EffectFileName, bool PostFlag,
	Effekseer::Vector3D DefPos) {

	//サンプルのエフェクトをロードする。
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectDetaBase[EffectFileName]);
	//エフェクトを再生する。
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, DefPos.X, DefPos.Y, DefPos.Z);

	//リストに追加や
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;

}

Effekseer::Handle EffekseerSupporter::NewEffect_Vector(const EffectData EffectFileName,
	bool PostFlag, float X, float Y, float Z) {

	//変換
	Effekseer::Vector3D Pos;
	Pos.X = X;
	Pos.Y = Y;
	Pos.Z = Z;

	//サンプルのエフェクトをロードする。
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectDetaBase[EffectFileName]);
	//エフェクトを再生する。
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, Pos.X, Pos.Y, Pos.Z);

	//リストに追加や
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;

}

void EffekseerSupporter::EffectClear() {

	//削除処理
	std::list<Effect>::iterator it;
	it = m_effectList.begin();
	while (it != m_effectList.end()) {

		if (CGameObjectManager::GetInstance()->GetEffekseerManager()->Exists(it->Handle) == false) {
			it = m_effectList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

void EffekseerSupporter::NoPostStop() {

	for (auto go = m_effectList.begin();
		go != m_effectList.end();
		go++) {

		if (go->PostFlag == false) {
			CGameObjectManager::GetInstance()->GetEffekseerManager()->SetPaused(go->Handle, true);
		}

	}

}
void EffekseerSupporter::NoPostMove() {

	for (auto go = m_effectList.begin();
		go != m_effectList.end();
		go++) {

		if (go->PostFlag == false) {
			CGameObjectManager::GetInstance()->GetEffekseerManager()->SetPaused(go->Handle, false);
		}

	}

}
