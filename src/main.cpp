#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "calculator.h"
#include "imgui.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
using namespace ImGui;

#define N_SPACING(n)                                                           \
  do {                                                                         \
    for (int i = 0; i < n; ++i) {                                              \
      ImGui::Spacing();                                                        \
    }                                                                          \
  } while (0)

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char **) {
  int WindowWidth = 700;
  int WindowHeight = 490;

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight,
                                        "BMI Calculator", nullptr, nullptr);
  if (window == nullptr)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  IMGUI_CHECKVERSION();
  CreateContext();
  ImGuiIO &io = GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
  //

  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] =
      ImVec4(252.f / 255.f, 224.f / 255.f, 176.f / 255.f, 1.f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] =
      ImVec4(33.0f / 255.0f, 33.0f / 255.0f, 33.0f / 255.0f, 1.0f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 0.54f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] =
      ImVec4(33.0f / 255.0f, 33.0f / 255.0f, 33.0f / 255.0f, 0.55f);

  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(8.00f, 8.00f);
  style.FramePadding = ImVec2(5.00f, 2.00f);
  style.CellPadding = ImVec2(6.00f, 6.00f);
  style.ItemSpacing = ImVec2(6.00f, 6.00f);
  style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
  style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
  style.IndentSpacing = 25;
  style.ScrollbarSize = 15;
  style.GrabMinSize = 10;
  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 1;
  style.TabBorderSize = 1;
  style.WindowRounding = 4;
  style.ChildRounding = 4;
  style.FrameRounding = 3;
  style.PopupRounding = 4;
  style.ScrollbarRounding = 9;
  style.GrabRounding = 3;
  style.LogSliderDeadzone = 4;
  style.TabRounding = 4;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 22.0f);
  ImFont *HeadingFont =
      io.Fonts->AddFontFromFileTTF("../assets/fonts/DejaVuSansMono.ttf", 50.0f);
  ImFont *NormalFont = io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 24.0f);
  ImFont *ButtonFont = io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 33.0f);
  ImFont *BmiFont = io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 45.0f);
  ImFont *AboutFont = io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 25.0f);

  ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    PushStyleVar(ImGuiStyleVar_FrameRounding, 18);
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 9));
    GetStyle().WindowRounding = 0.0f;
    NewFrame();
    {
      static bool is_open;
      static float height, weight;
      static char const *message;

      bool b = false;
      if (BeginMainMenuBar()) {
        if (BeginMenu("About")) {
          b = true;
          EndMenu();
        }
        EndMainMenuBar();
      }

      if (b) {
        OpenPopup("About");
      }

      if (BeginPopupModal("About", nullptr, ImGuiWindowFlags_NoResize)) {
        PushFont(AboutFont);
        TextWrapped(
            "This is the BMI calculator made in C++ using ImGui library");
        ImGui::Indent(WindowWidth / 5.0f);
        if (Button("Close", ImVec2(70, 40))) {
          CloseCurrentPopup();
        }
        ImGui::Unindent(WindowWidth / 5.0f);
        PopFont();
        EndPopup();
      }

      ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(23, 23, 23, 255));
      ImGui::PushFont(NormalFont);
      ImGui::Begin("BMI Calculator", &is_open,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoSavedSettings |
                       ImGuiWindowFlags_NoTitleBar);

      ImGui::SetWindowSize(ImVec2(WindowWidth, WindowHeight));
      ImGui::SetWindowPos(ImVec2(0, 25));

      N_SPACING(2);
      PushFont(BmiFont);
      ImGui::Indent(WindowWidth / 4.0f);
      ImGui::Text("BMI Calculator");
      PopFont();
      ImGui::Unindent(WindowWidth / 4.0f);

      ImGui::Indent(WindowWidth / 8.0f);
      ImGui::Spacing();
      ImGui::PushItemWidth(ImGui::GetFontSize() * -8);
      ImGui::Text("Height:");
      ImGui::SameLine();
      ImGui::InputFloat("(m)", &height, 0.0f, 0.0f, "%.1f");
      ImGui::Text("Weight:");
      ImGui::SameLine();
      ImGui::InputFloat("(kg)", &weight, 0.0f, 0.0f, "%.1f");
      ImGui::Unindent(WindowWidth / 8.0f);
      ImGui::PopItemWidth();

      ImGui::Indent(WindowWidth / 6.5f);
      ImGui::Spacing();
      ImGui::PushFont(ButtonFont);
      if (ImGui::Button("Calculate", ImVec2(WindowWidth / 1.5f, 40))) {
        bmi = BMI(height, weight);
        if (bmi < 18.5f) {
          message = "Please focus on your health, You are UNDERWEIGHT!";
        } else if (bmi >= 18.5f && bmi <= 25.0f) {
          message = "         YO man you are Good to Go!";
        } else if (bmi > 25.0f) {
          message = "Please focus on your health, You are OVERWEIGHT";
        }
      }
      ImGui::PopFont();
      ImGui::Unindent(WindowWidth / 6.5f);

      ImGui::Indent(WindowWidth / 3.0f);
      if (bmi) {
        N_SPACING(4);
        ImGui::PushFont(BmiFont);
        ImGui::Text("BMI: %.2f", bmi);
        ImGui::PopFont();
      }
      ImGui::Unindent(WindowWidth / 4.0f);

      if (message) {
        N_SPACING(3);
        ImGui::Indent(WindowWidth / 200.0f);
        ImGui::PushFont(NormalFont);
        ImGui::Text("%s", message);
        ImGui::PopFont();
        ImGui::Unindent(WindowWidth / 200.0f);
      }
      ImGui::PopStyleColor();
      ImGui::End();
      ImGui::PopFont();
    }

    // Rendering
    Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

    glfwSwapBuffers(window);
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
