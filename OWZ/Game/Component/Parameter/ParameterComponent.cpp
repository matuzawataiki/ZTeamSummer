#include "stdafx.h"
#include "ParameterComponent.h"


/**
  * 初期化。
  */
ParameterManager* ParameterManager::m_instance = nullptr; 

ParameterManager::ParameterManager()
{
	m_parameterMap.clear();
}

ParameterManager::~ParameterManager()
{
	for (auto& it : m_parameterMap) {
		auto& parameters = it.second;
		for (auto* parameter : parameters) {
			delete parameter;
		}
		parameters.clear();
	}
	m_parameterMap.clear();
}
