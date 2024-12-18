#ifndef MLX_UT_CORE_EVENT_LISTENER
#define MLX_UT_CORE_EVENT_LISTENER

#include <Pch.h>
#include <Core/EventBase.h>

namespace mlxut
{
	class EventListener
	{
		public:
			EventListener() = delete;
			EventListener(std::function<void(const EventBase&)> functor, std::string name);

			[[nodiscard]] inline const std::string& GetName() const { return m_name; }
			inline void Call(const EventBase& event) const noexcept { m_listen_functor(event); }

			~EventListener() = default;

		private:
			std::function<void(const EventBase&)> m_listen_functor;
			std::string m_name;
	};
}

#endif
