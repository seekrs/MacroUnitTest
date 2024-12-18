#ifndef MLX_UT_CORE_EVENT_BUS
#define MLX_UT_CORE_EVENT_BUS

#include <Pch.h>
#include <Core/EventBase.h>
#include <Core/EventListener.h>

namespace mlxut
{
	class EventBus
	{
		public:
			EventBus() = delete;
			static void Send(const std::string& listener_name, const EventBase& event);
			static void SendBroadcast(const EventBase& event);
			inline static void RegisterListener(const EventListener& listener) { s_listeners.push_back(listener); }
			~EventBus() = delete;

		private:
			inline static std::vector<EventListener> s_listeners;
	};
}

#endif
