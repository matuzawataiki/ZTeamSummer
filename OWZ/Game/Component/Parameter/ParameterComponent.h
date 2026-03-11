#pragma once
#include "gameObject/Component.h"
#include "Json/json.hpp"
#include <iostream>
#include <fstream>


#define appParameter(name)  \


struct IParameter
{
};


struct EnemyWalkParameter : public IParameter
{
	appParameter(EnemyWalkParameter)


		float m_hp;
	float m_speed;
	float m_attackPower;
};


class ParameterComponent : public Component
{
private:
	ParameterComponent();
	~ParameterComponent();


private:
	using ParameterVector = std::vector<IParameter*>;
	using ParameterMap = std::map<uint32_t, ParameterVector>;
	ParameterMap m_parameterMap;
	static ParameterComponent* m_instance;


public:
	void Update() override {};


	/**
	  * パラメーターの読み込み
	  */
	template <typename T>
	void LoadParameter(const char* path, const std::function<void(const nlohmann::json& j, T& p)>& func)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			return;
		}

		nlohmann::json jsonRoot;
		file >> jsonRoot;

		std::vector<IParameter*> parameters;
		for (const auto& j : jsonRoot)
		{
			T* parameter = new T();
		}
	}


	/**
	  * パラメーターの解放
	  */
	template <typename T>
	void UnloadParameter()
	{
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			auto& parameters = it->second;
			for (auto* p : parameters) {
				delete p;
			}
			m_parameterMap.erase(it);
		}
	}


	/**
	  * 1つだけパラメーターの取得
	  */
	template <typename T>
	const T* GetParameter(const int index = 0) const
	{
		const auto parameters = GetParameters<T>();
		if (parameters.size() == 0) { return nullptr; }
		if (parameters.size() <= index) { return nullptr; }
		return parameters[index];
	}


	/**
	  * 複数のパラメーターの取得
	  */
	template <typename T>
	inline const std::vector<T*> GetParameters() const
	{
		std::vector<T*> parameters;
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			for (auto* parameter : it->second) {
				parameters.push_back(static_cast<T*>(parameter));
			}
		}
		return parameters;
	}


	/**
	  * パラメーターをラムダ式で回すForEach
	  */
	template <typename T>
	void ForEach(std::function<void(const T&)> func) const
	{
		const std::vector<T*> parameters = GetParameters<T>();
		for (const T* paramter : parameters) {
			func(*paramter);
		}
	}


public:
	/**
	  * インスタンスの生成
	  */
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new ParameterComponent();
		}
	}


	static ParameterComponent* Get()
	{
		return m_instance;
	}


	static void DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

