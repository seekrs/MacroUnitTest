#include <components/render_results.h>
#include <tests/tester.h>
#include <renderer.h>

namespace mlxut
{
	RenderResults::RenderResults(Tester* tester, const Renderer& renderer) : Panel("render_results"), _tester(tester), _renderer(renderer) {}

	void RenderResults::onUpdate(ivec2 size)
	{
		if(!ImGui::Begin("Render Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;
		auto& test = _tester->getAllTests()[_tester->getActiveTestIndex()];
		ImGui::TextUnformatted(test->getName().c_str());
		ImGui::SameLine();
		ImGui::TextUnformatted("Result");
		ImGui::SameLine(ImGui::GetWindowWidth() / 2.f + 6.f);
		ImGui::TextUnformatted(test->getName().c_str());
		ImGui::SameLine();
		ImGui::TextUnformatted("Reference");
		if(ImGui::BeginChild("Result", {ImGui::GetWindowWidth() / 2.f - 5.f, 0.f}, ImGuiChildFlags_Border))
		{
			if(!_tester->testsAreRunning())
			{
				if(test->getResult() == nullptr)
				{
					test->tryCreateResultTexture(_renderer);
					if(test->getResult() == nullptr)
						goto endChild;
				}
				float size_reference = ImGui::GetWindowWidth();
				if(size_reference > ImGui::GetWindowHeight())
					size_reference = ImGui::GetWindowHeight();
				if(size_reference > MLX_WIN_WIDTH)
					size_reference = MLX_WIN_WIDTH;
				ImVec2 size(size_reference - 16.f, size_reference - 16.f);
				ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, (ImGui::GetWindowHeight() - size.y) * 0.5f });
				ImGui::Image(static_cast<void*>(test->getResult()), size);
			}
endChild:
			ImGui::EndChild();
		}
		ImGui::SameLine();
		if(ImGui::BeginChild("Reference", {ImGui::GetWindowWidth() / 2.f - 5.f - 3.f, 0.f}, ImGuiChildFlags_Border))
		{
			float size_reference = ImGui::GetWindowWidth();
			if(size_reference > ImGui::GetWindowHeight())
				size_reference = ImGui::GetWindowHeight();
			if(size_reference > MLX_WIN_WIDTH)
				size_reference = MLX_WIN_WIDTH;
			ImVec2 size(size_reference - 16.f, size_reference - 16.f);
			ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, (ImGui::GetWindowHeight() - size.y) * 0.5f });
			ImGui::Image(static_cast<void*>(test->getReference()), size);

			ImGui::EndChild();
		}
		ImGui::End();
	}
}
