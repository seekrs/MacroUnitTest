#ifndef MLX_UT_PANEL
#define MLX_UT_PANEL

#include <Pch.h>

namespace mlxut
{
	class Panel
	{
		public:
			Panel(std::string name) : m_name(std::move(name)) {}

			virtual void OnAttach() {}
			virtual void OnOpen() {}
			virtual bool IsOpen() {}
			virtual void OnUpdate([[maybe_unused]] ivec2 size) {}
			virtual void OnQuit() {}

			inline const std::string& GetName() const noexcept { return m_name; }
			inline void SetName(std::string name) noexcept { m_name = std::move(name); }
			virtual ~Panel() = default;

		protected:
			std::string m_name;
	};
}

#endif
