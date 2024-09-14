#include "calculator.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_settings.h"
#include <GL/gl.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
using namespace ImGui;

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

  IMGUI_UI_SETTINGS();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  io.Fonts->AddFontFromFileTTF(
      "../assets/fonts/JetBrainsMonoNerdFontMono-Regular.ttf", 22.0f);
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
                       ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

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
