#pragma once
#include"Canvas.h"
namespace nsK2EngineLow
{
	class UISystem : public Noncopyable
	{
	private:
		/**
		* @brief ŠO•”‚©‚ç¶¬‚Å‚«‚È‚¢
		*/
		UISystem();

		/**
		* @bref CanvasType‚ğsize_t‚É•ÏŠ·
		*/
		constexpr size_t ToIndex(CanvasType type)
		{
			return static_cast<size_t>(type);
		}

		std::array<std::unique_ptr<Canvas>, static_cast<size_t>(CanvasType::Count)> m_canvases;

	public:

		//ƒ€[ƒu‚à‹Ö~‚·‚é
		UISystem(UISystem&&) = delete;
		UISystem& operator=(UISystem&&) = delete;

		~UISystem() = default;

		Canvas& GetCanvas(CanvasType type)
		{
			size_t index = ToIndex(type);
			return *m_canvases[index];
		}

		void Update();
		void Render(RenderContext& rc);

	};
}

