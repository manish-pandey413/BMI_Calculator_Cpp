#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "calculator.h"
#include "imgui.h"
#include <iostream>
#include <stdio.h>
#include <string>
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
      static float bmi_int;
      static char const *bmi_char;
      static char const *message;

      bool b = false;
      if (BeginMainMenuBar()) {
        if (BeginMenu("Theme")) {
          if (MenuItem("Light")) {
            StyleColorsLight();
          }
          if (MenuItem("Dark")) {
            StyleColorsDark();
          }
          EndMenu();
        }
        if (BeginMenu("About")) {
          b = true;
          EndMenu();
        }
        EndMainMenuBar();
      }

      if (b) {
        OpenPopup("About");
      }

      if (BeginPopupModal("About", nullptr)) {
        PushFont(AboutFont);
        Text("This is the BMI calculator made in C++ using ImGui library");
        if (Button("Close", ImVec2(WindowWidth / 1.5, 40))) {
          CloseCurrentPopup();
        }
        PopFont();
        EndPopup();
      }
      Begin("##", &is_open,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

      // Setting heigh & width of inner window
      SetWindowSize(ImVec2(WindowWidth, WindowHeight));
      SetWindowPos(ImVec2(0, 25));

      // Heading
      Indent(WindowWidth / 4);
      PushFont(HeadingFont);
      Text("BMI CALCULATOR");
      PopFont();
      Unindent(WindowWidth / 4);

      // Creaating height input box
      Indent(WindowWidth / 8);
      Spacing();
      PushItemWidth(GetFontSize() * -8);
      Text("Height:");
      SameLine();
      InputFloat("(m)", &height, 0.0f, 0.0f, "%.1f");
      //
      // Creaating weight input box
      Text("Weight:");
      SameLine();
      InputFloat("(kg)", &weight, 0.0f, 0.0f, "%.1f");
      Unindent(WindowWidth / 8);
      PopItemWidth();

      // Creating Calculate Button
      Indent(WindowWidth / 6.5);
      Spacing();
      PushFont(ButtonFont);
      if (Button("Calculate", ImVec2(WindowWidth / 1.5, 40))) {
        bmi_int = BMI(height, weight);

        // Dertermining message based on BMI
        if (bmi_int < 18.5) {
          message = "Please focus on your health, You are UNDERWEIGHT!";
        } else if (bmi_int >= 18.5 and bmi_int <= 25.0) {
          message = "          YO man you are Good to Go!";
        } else if (bmi_int > 25.0) {
          message = "Please focus on your health, You are OVERWEIGHT";
        } else {
          return 1;
        }
        string bmi_string = to_string(bmi_int);
        bmi_char = bmi_string.c_str();
      }
      PopFont();
      Unindent(WindowWidth / 6.5);

      // Printing BMI
      Indent(WindowWidth / 3);
      if (bmi_char) {
        Spacing();
        Spacing();
        Spacing();
        Spacing();
        PushFont(BmiFont);
        Text("BMI: %.5s", bmi_char);
        PopFont();
      }
      Unindent(WindowWidth / 4);

      // Printing Message generated above
      if (message) {
        Spacing();
        Spacing();
        Spacing();
        Indent(WindowWidth / 30);
        PushFont(NormalFont);
        Text(message);
        PopFont();
        Unindent(WindowWidth / 30);
      }

      End();
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
