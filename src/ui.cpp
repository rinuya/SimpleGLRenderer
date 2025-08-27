#include "ui.hpp"

UI::UI(GLFWwindow* window)
    : window_(window), io_(ImGui::GetIO()), style_(ImGui::GetStyle()) {
  float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(
      glfwGetPrimaryMonitor());  // Valid on GLFW 3.3+ only

  (void)io_;
  io_.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io_.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  style_.ScaleAllSizes(main_scale);
  style_.FontScaleDpi = main_scale;

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window_, true);

  ImGui_ImplOpenGL3_Init("#version 130");
}

UI::~UI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UI::beginFrame() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void UI::drawUI() {
  ImGui::Begin("Hello, world!");
  ImGui::End();
};

void UI::renderFrame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};