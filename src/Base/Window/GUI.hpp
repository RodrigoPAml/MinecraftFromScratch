#pragma once
#include <BuildCraft.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace BuildCraft { 
namespace Base 
{
	enum class GUIWindowFlags
	{
		None = ImGuiWindowFlags_None,
		TitleBar = ImGuiWindowFlags_NoTitleBar, 
		NoResize = ImGuiWindowFlags_NoResize, 
		NoMove = ImGuiWindowFlags_NoMove, 
		NoScrollbar = ImGuiWindowFlags_NoScrollbar,   
		NoScrollWithMouse = ImGuiWindowFlags_NoScrollWithMouse,   
		NoCollapse = ImGuiWindowFlags_NoCollapse,
		AlwaysAutoResize = ImGuiWindowFlags_AlwaysAutoResize,
		NoBackground = ImGuiWindowFlags_NoBackground,   
		NoSavedSettings = ImGuiWindowFlags_NoSavedSettings, 
		NoMouseInputs = ImGuiWindowFlags_NoMouseInputs,
		MenuBar = ImGuiWindowFlags_MenuBar,
		HorizontalScrollbar = ImGuiWindowFlags_HorizontalScrollbar, 
		NoFocusOnAppearing = ImGuiWindowFlags_NoFocusOnAppearing,
		NoBringToFrontOnFocus = ImGuiWindowFlags_NoBringToFrontOnFocus,
		AlwaysVerticalScrollbar = ImGuiWindowFlags_AlwaysVerticalScrollbar,
		AlwaysHorizontalScrollbar = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
		AlwaysUseWindowPadding = ImGuiWindowFlags_AlwaysUseWindowPadding,
		NoNavInputs = ImGuiWindowFlags_NoNavInputs,
		NoNavFocus = ImGuiWindowFlags_NoNavFocus,
		UnsavedDocument = ImGuiWindowFlags_UnsavedDocument, 
		NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
		NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
		NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
	};

	class GUI
	{
	private:
		static bool isInit;
	public:
		static void Initiatlize();
		static void Release();

		static void InitFrame();
		static void EndFrame();

		// texts
		static void MakeText(const std::string& text);
		static void MakeDisabledText(const std::string& text);
		static void MakeBulletText(const std::string& text);
		static void MakeColoredText(const std::string& text, const glm::vec4& color);
		static void MakeWrappedText(const std::string& text);

		// buttons & selectables
		static bool MakeCheckBox(std::string id, bool& checked);
		static bool MakeButton(const std::string& text);
		static bool MakeRadioButton(const std::string& text, bool& selected);
		static bool MakeSelectable(const std::string& text, bool& selected);

		// images
		static void MakeImage(TexturePtr texture, const glm::vec2& size, glm::vec2 uv1, glm::vec2 uv2);
	
		// inputs
		static void MakeInput(std::string id, std::string& text);
		static void MakeInput(std::string id, const std::string& hint, std::string& text);
		static void MakeInput(std::string id, double& val);
		static void MakeInput(std::string id, float& val);
		static void MakeInput(std::string id, int& val);
		static void MakeInput(std::string id, glm::vec2& val);
		static void MakeInput(std::string id, glm::vec3& val);
		static void MakeInput(std::string id, glm::vec4& val);
		static void MakeMultilineText(std::string id, std::string& text);

		// drags
		static void MakeDrag(std::string id, int& val);
		static void MakeDrag(std::string id, float& val);
		static void MakeDrag(std::string id, glm::vec2& val);
		static void MakeDrag(std::string id, glm::vec3& val);
		static void MakeDrag(std::string id, glm::vec4& val);

		// sliders
		static void MakeSlider(std::string id, const int max, const int min, int& val);
		static void MakeSlider(std::string id, const float min, const float max, float& val);
		static void MakeSlider(std::string id, const float min, const float max, glm::vec2& val);
		static void MakeSlider(std::string id, const float min, const float max, glm::vec3& val);
		static void MakeSlider(std::string id, const float min, const  float max, glm::vec4& val);

		// color
		static void MakeColorSelectable(std::string id, glm::vec3& color);
		static void MakeColorSelectable(std::string id, glm::vec4& color);

		// list box
		static bool MakeListBox(std::string id, const std::vector<std::string>& itens, int& currItem, const int heightInItems = 10);

		// combo box
		static void MakeComboBox(std::string id, const std::vector<std::string>& itens, int& currItem);

		// trees
		static bool BeginTreeNode(const std::string& text);
		static bool EndTreeNode();

		// Window Componentes
		static bool IsCurrentWindowAppearing();
		static bool IsCurrentWindowCollased();
		static bool IsCurrentWindowFocused();
		static bool IsCurrentWindowHovered();

		static void SetNextWindowPosition(const glm::vec2& pos);
		static void SetNextWindowSize(const glm::vec2& size);
		static glm::vec2 GetWindowPosition();
		static glm::vec2 GetWindowSize();

		static bool BeginWindow(const std::string& title, bool* open = nullptr, const std::set<GUIWindowFlags>& flags = {GUIWindowFlags::None});
		static void EndWindow();

		static void BeginHintWindow();
		static void EndHintWindow();

		static bool MakeHeader(const std::string& name);

		// Layouts
		static void ContinueSameLine(const float offset = 0, const float spacing = -1);
		static void MakeSeparator();
		static void MakeSpace();

		// GUI STATE
		static bool IsCurrentItemClicked();
		static bool IsCurrentItemActive();
		static bool IsCurrentItemFocused();
		static bool IsCurrentItemHovered();

		static void SetNextItemWidth(float width);

		// Menus
		static bool BeginMainMenuBar();
		static void EndMainMenuBar();

		static bool BeginMenuBar();
		static void EndMenuBar();

		static bool BeginMenu(const std::string& name, const bool enabled = true);
		static void EndMenu();    

		static bool MenuItem(const std::string& name, const std::string& shortcut, const bool enabled = true);
	};
}}