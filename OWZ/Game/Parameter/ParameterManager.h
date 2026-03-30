#pragma once
#include "IMasterParameter.h"

class ParameterManager : public IGameObject
{
public:
	ParameterManager();
	~ParameterManager();


private:
	/** 複数パラメーターがあってもいいように */
	using ParameterVector = std::vector<IMasterParameter*>;
	/** 各パラメーターごとに保持する */
	using ParameterMap = std::map<uint32_t, ParameterVector>;


private:
	ParameterMap m_parameterMap;			//パラメーターの保持
	static ParameterManager* m_instance;    //インスタンス


public:
	void Update();


	/** パラメーター読み込み */
	template <typename T>
	void LoadParameter(const char* path, const std::function<void(const nlohmann::json& j, T& p)>& func)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			return;
		}

		nlohmann::json jsonRoot;
		file >> jsonRoot;

		std::vector<IMasterParameter*> parameters;
		for (const auto& j : jsonRoot) {
			T* parameter = new T();
#ifdef APP_PARAM_HOT_RELOAD
			parameter->m_path = std::string(path);
			parameter->m_lastWriteTime = GetFileLastWriteTime(path);
			
#endif
			func(j, *parameter);
			parameters.push_back(static_cast<IMasterParameter*>(parameter));
		}

		auto insertResult = m_parameterMap.emplace(T::ID(), parameters);
		if (!insertResult.second)
		{
			for (auto* p : parameters)
			{
				delete p;
			}
		}
	}


	/** パラメーターの解放 */
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


	/** 1つだけパラメーターを取得する */
	template <typename T>
	const T* GetParameter(const int index = 0) const
	{
		const auto parameters = GetParameters<T>();
		if (parameters.size() == 0) { return nullptr; }
		if (parameters.size() <= index) { return nullptr; }
		return parameters[index];
	}


	/** 複数のパラメーターを取得する */
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


	/** パラメーターをラムダ式で回すForEach */
	template <typename T>
	void ForEach(std::function<void(const T&)> func) const
	{
		const std::vector<T*> parameters = GetParameters<T>();
		for (const T* parameter : parameters) {
			func(*parameter);
		}
	}

#ifdef APP_PARAM_HOT_RELOAD
	/**
	 * ファイル更新日時取得
	 */
	static time_t GetFileLastWriteTime(const char* path)
	{
		struct stat result;
		// stat関数でファイル情報を取得 (0なら成功)
		if (stat(path, &result) == 0) {
			return result.st_mtime;
		}
		return 0;
	}


	/**
	* ファイル更新チェック
	*/
	static bool CheckFileModified(const IMasterParameter* param)
	{
		if (GetFileLastWriteTime(param->m_path.c_str()) > param->m_lastWriteTime)
		{
			return true;
		}
		return false;
	}

#endif // APP_PARAM_HOT_RELOAD


	/** シングルトン */
public:
	/** インスタンスの取得 */
	static ParameterManager* GetInstance()
	{
		return m_instance;
	}


	/** インスタンスの生成 */
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new ParameterManager();
		}
	}


	/**	インスタンスの破棄 */
	static void DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

