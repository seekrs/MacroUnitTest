#ifndef MLX_UT_PANEL
#define MLX_UT_PANEL

#include <PreCompiled.h>

namespace mlxut
{
	class Panel
	{
		public:
			Panel(const std::string& name) : m_name(name) {}

			virtual void OnAttach() {}
			virtual void OnOpen() {}
			bool IsOpen() { return m_is_open; }
			virtual void OnUpdate([[maybe_unused]] ImVec2 size) {}
			virtual void OnQuit() {}

			inline const std::string& GetName() const noexcept { return m_name; }
			inline void SetName(const std::string& name) noexcept { m_name = name; }
			virtual ~Panel() = default;

		protected:
			std::string m_name;
			bool m_is_open;
	};
}

#endif
