#include "ui.hpp"

UI::UI(GLFWwindow* window, Scene* scene)
    : window_(window),
      io_(ImGui::GetIO()),
      style_(ImGui::GetStyle()),
      scene_(scene) {
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
  glfwGetFramebufferSize(window_, &displayWidth_, &displayHeight_);
  drawSceneGraph();
  if (selectedEntity_ != NULL) {
    drawEntity();
  }
};

void UI::renderFrame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

void UI::drawSceneGraph() {
  ImVec2 minSize(SCENE_WINDOW_MIN_WIDTH, (float)displayHeight_);
  ImVec2 maxSize(displayWidth_, (float)displayHeight_);

  ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

  ImGui::Begin("Scene Graph");

  for (const auto& rootEntity : scene_->rootEntities_) {
    Entity* entityPtr = rootEntity.get();
    auto entityRow = ImGui::Selectable(entityPtr->label_.c_str(),
                                       selectedEntity_ == entityPtr);
    // if selected
    if (entityRow) {
      selectedEntity_ = entityPtr;
    }
  }

  ImGui::End();
}

void UI::drawEntity() {
  ImGui::Begin("Entity");

  if (auto meshEntity = dynamic_cast<MeshEntity*>(selectedEntity_)) {
    ImGui::SeparatorText("Mesh Entity");
    ImGui::ColorEdit3("Color", glm::value_ptr(meshEntity->color_));
  } else if (auto modelEntity = dynamic_cast<ModelEntity*>(selectedEntity_)) {
    ImGui::SeparatorText("Model Entity");
    ImGui::Text("No Model specific fields yet");
  } else {
    ImGui::Text("Unknown entity type");
  }

  ImGui::SeparatorText("Transform");
  ImGui::DragFloat3(
      "Position", glm::value_ptr(selectedEntity_->transform_.position_), 0.1f);

  ImGui::DragFloat3("Scale", glm::value_ptr(selectedEntity_->transform_.scale_),
                    0.1f);

  ImGui::End();
}