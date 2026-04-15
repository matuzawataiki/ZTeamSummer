#include "stdafx.h"
#include "EffekseerManager.h"

void EffekseerManager::LoadAllEffects()
{
	auto engine = nsK2EngineLow::EffectEngine::GetInstance();

	//engine->ResistEffect((int)eEffectType::Explosion, u"Data/Effects/Explosion.efk");
}

int EffekseerManager::Play(eEffectType type,const Vector3& pos)
{
	auto effectRef = nsK2EngineLow::EffectEngine::GetInstance()->LoadEffect((int)type);

	int handle = nsK2EngineLow::EffectEngine::GetInstance()->Play(effectRef);

	nsK2EngineLow::EffectEngine::GetInstance()->UpdateEffectWorldMatrix(handle, pos, Quaternion(), Vector3(1, 1, 1));

	m_playingHandles.push_back(handle);

	return handle;
}

void EffekseerManager::StopAll()
{
	for (auto handle : m_playingHandles) {
		nsK2EngineLow::EffectEngine::GetInstance()->Stop(handle);
	}
	m_playingHandles.clear();
}