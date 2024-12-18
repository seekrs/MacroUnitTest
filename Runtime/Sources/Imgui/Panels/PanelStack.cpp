#include <components/panel_stack.h>

namespace mlxut
{
	void PanelStack::addPanel(Panel* const panel)
	{
		_panels.push_back(panel);
		panel->onAttach();
	}

	void PanelStack::removePanel(Panel* const panel)
	{
		auto it = std::find(_panels.cbegin(), _panels.cend(), panel);
		if(it != _panels.cend())
		{
			(*it)->onQuit();
			_panels.erase(it);
		}
	}

	void PanelStack::removePanel(const std::string& name)
	{
		auto it = std::find_if(_panels.cbegin(), _panels.cend(), [&](Panel* panel)
		{
			return panel->getName() == name;
		});

		if(it != _panels.cend())
		{
			(*it)->onQuit();
			_panels.erase(it);
		}
	}

	Panel* const PanelStack::getPanel(const std::string& name)
	{
		auto it = std::find_if(_panels.cbegin(), _panels.cend(), [&](Panel* panel)
		{
			return panel->getName() == name;
		});

		if(it != _panels.cend())
			return *it;
		return nullptr;
	}

	Panel* const PanelStack::getPanel(std::size_t index)
	{
		return index < _panels.size() ? _panels[index] : nullptr;
	}
}
