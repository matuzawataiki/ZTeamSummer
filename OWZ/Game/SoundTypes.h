#pragma once
#include <string>
#include <array>
#include <cstddef>

enum class SoundKind
{
	BgmTitle,
	SeShot,
	SeExplosion,//爆発音
	Count
};


/** サウンドの情報の構造体 */
struct SoundInformation
{
	std::string assetPath;
	//
	SoundInformation(const std::string& path) : assetPath(path) {}
};

constexpr std::size_t ToIndex(SoundKind kind)
{
	return static_cast<std::size_t>(kind);
}

static std::array<SoundInformation, ToIndex(SoundKind::Count)> soundInformation =
{
	SoundInformation("Assets/sound/bgm_title.wav"),     // BgmTitle
	SoundInformation("Assets/sound/se_gun_shot.wav"),   // SeShot
	SoundInformation("Assets/sound/se_explosion.wav"),  // SeExplosion
};