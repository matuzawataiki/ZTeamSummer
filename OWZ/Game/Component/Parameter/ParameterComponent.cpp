#include "stdafx.h"
#include "ParameterComponent.h"


ParameterComponent* ParameterComponent::m_instance = nullptr; //初期化

ParameterComponent::ParameterComponent()
{
	m_parameterMap.clear();
}

ParameterComponent::~ParameterComponent()
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