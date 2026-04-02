#include "stdafx.h"
#include "ParameterManager.h"


ParameterManager* ParameterManager::m_instance = nullptr;

ParameterManager::ParameterManager()
{
	m_parameterMap.clear();
}

ParameterManager::~ParameterManager()
{
	for (auto& it : m_parameterMap)
	{
		auto& parameters = it.second;
		for (auto* parameter : parameters)
		{
			delete parameter;
		}
		parameters.clear();
	}
	m_parameterMap.clear();
}

void ParameterManager::Update()
{
#ifdef APP_PARAM_HOT_RELOAD
	for (auto& paramPair : m_parameterMap)
	{
		auto& parameters = paramPair.second;
		if (parameters.empty()) continue;

		auto* firstParam = parameters[0];
		// 最新の更新時間を「一度だけ」取得
		time_t newTime = GetFileLastWriteTime(firstParam->m_path.c_str());

		// 前回の読み込み時間より新しい場合のみ処理
		if (newTime > firstParam->m_lastWriteTime)
		{
			std::ifstream file(firstParam->m_path);
			if (!file.is_open()) continue;

			nlohmann::json jsonRoot;
			file >> jsonRoot;

			// JSONの構造が配列で、かつ要素数が一致しているかチェック
			if (jsonRoot.is_array() && jsonRoot.size() == parameters.size())
			{
				for (size_t i = 0; i < parameters.size(); ++i)
				{

					parameters[i]->Load(jsonRoot[i]);

				}
			}

			// 成功しても失敗しても、このファイルの「処理済み時間」を更新する
			// これにより、JSONにミスがあっても毎フレーム解析が走るのを防げる
			for (auto* param : parameters)
			{
				param->m_lastWriteTime = newTime;
			}
		}
	}
#endif
}