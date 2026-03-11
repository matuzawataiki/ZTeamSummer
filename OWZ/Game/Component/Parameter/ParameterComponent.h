#pragma once
#include "Component.h"
#include "Json/Json.hpp"
#include "util/CRC32.h"

#define appParameter(name)	\

struct IParameter {};

struct EnemyWalkParameter : public IParameter
{
	appParametor(EnemyWalkParameter);

	float m_hp;
	float m_speed;
	float m_attackPower;
};


class ParametorComponent : public Component
{
	ParametorComponent();
	~ParametorComponent();


private:
{
	using ParametorVector = std::Vector<IParametorComponent*>;
	using ParametorMap = std::map<uint32_t, ParametorVector>;
	static ParamatorComponent* m_instance;


}


public:
{
	/**
	  * 更新処理。
	  */
	void Update() override;


	/**
	  * パラメータを読み込む関数。
	  * @param path ファイルのパス。
	  * @param func パラメータを読み込む関数。
	  */
	*/
	template<typename T>
	void LoadParametor(const char* path, const std::function<void(const nlohmann::json& j,T& p)>& func)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			return;
		}


		nlohmann::json jsonPoot;
		file >> jsonPoot;

		std::vector<IParametorComponent*> parameters;
		for (const auto& j : jsonRoot)
		{
			T* parametor = new T();
		}
	}


	/**
	  * インスタンスを生成する関数。
	  */
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new ParametorComponent();
		}
	}


	/**
	  * パラメータを解放する関数。
	  */
	template<typename T>
	void UnloadParametor()
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
	  * 1つだけパラメータを取得する関数。
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
	  * 複数のパラメータを取得する関数。
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
	  * パラメータを全てに対して処理を行う関数。
	  */
	template <typename T>
	void ForEach(std::function<void(const T&)> func) const
	{
		const std::vector<T*> parameters = GetParameters<T>();
		for (const T* paramter : parameters) {
			func(*paramter);
		}
	}


	/**
	  * インスタンスを取得する関数。
	  */
	static void ParametorComponent& Get()
	{
		return *m_instance;
	}


	/**
	  * インスタンスを削除する関数。
	  */
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

};

