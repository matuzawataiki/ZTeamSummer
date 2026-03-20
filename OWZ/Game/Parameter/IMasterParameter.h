#pragma once
#include "Util/Json/Json.h"
#include "util/CRC32.h"


/**
  * NOTE: ホットリロード … デバッグ中に、Jsonファイルを変更した際に、ゲームを再起動せずに変更を反映させる機能
  */
#ifdef K2_DEBUG
#define APP_PARAM_HOT_RELOAD
#endif


/**
  * NOTE: ホットリロードを使わない時は "#define APP_PARAM_HOT_RELOAD" をコメントアウトする。
  */
#ifdef APP_PARAM_HOT_RELOAD

#define appParameter(name) \
public:\
static constexpr uint32_t ID() {return Hash32(#name);}\
std::function<void(const nlohmann::json& j, name& p)> LoadFunc; \
void Load(const nlohmann::json& j) override { \
	if (LoadFunc) { \
		LoadFunc(j, *this); \
	} \
}\


#else

#define appParameter(name) \
public:\
static constexpr uint32_t ID() {return Hash32(#name);}\

#endif


/** 基底クラス */
class IMasterParameter
{
public:
	virtual ~IMasterParameter() = default;
#ifdef APP_PARAM_HOT_RELOAD
	std::string m_path;								// パラメーターのファイルパス（ホットリロード用）
	time_t m_lastWriteTime = 0;							// 最終更新時刻
	virtual void Load(const nlohmann::json& j) {}
#endif // APP_PARAM_HOT_RELOAD


};

