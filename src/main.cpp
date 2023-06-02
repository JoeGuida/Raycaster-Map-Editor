#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem.hpp>
#include <ray.hpp>
#include <renderer.hpp>
#include <shader.hpp>

#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float ASPECT_RATIO = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);
const int GRID_LINES_COUNT = 100;
const float GRID_SPACING = 0.1f;

const std::string SHADER_PATH = FileSystem::GetPath("/src/shaders/");

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
std::vector<Ray> generateGridRays(const Material& material);

int main() { 
    
    // ---------------------------------------------------------------------------------------------------- 
    // Setup GLFW, GLAD, ImGUI
    // ---------------------------------------------------------------------------------------------------- 

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window and set callbacks
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map Editor", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); 
    glfwSetKeyCallback(window, processInput);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // ---------------------------------------------------------------------------------------------------- 
    // Render Loop
    // ---------------------------------------------------------------------------------------------------- 

    // Create default shader
    Shader shader(SHADER_PATH, "default.vert", "default.frag");

    // Create grid of rays
    std::vector<Ray> gridRays = generateGridRays(Material(shader, glm::vec3(0.275f)));

    // Create the renderer
    Renderer renderer = Renderer();

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < gridRays.size(); i++) {
            renderer.draw(gridRays[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

std::vector<Ray> generateGridRays(const Material& material) {
    std::vector<Ray> rays;
    static const glm::vec3 horizontalDirection = glm::vec3(1.0f, 0.0f, 0.0f);
    static const glm::vec3 verticalDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    for(int i = 0; i < GRID_LINES_COUNT; i++) {
        float horizontalPosition = -1.0f * GRID_SPACING * i * ASPECT_RATIO;
        float verticalPosition = -1.0f * GRID_SPACING * i;

        Ray horizontalRay(glm::vec3(-100.0f, -0.5f, 0.0f), horizontalDirection);
        horizontalRay.setMaterial(material);
        horizontalRay.setTransform(Transform(glm::vec3(0.0f, horizontalPosition, 0.0f)));

        Ray verticalRay(glm::vec3(-0.5f, -0.5f, 0.0f), verticalDirection);
        verticalRay.setMaterial(material);
        verticalRay.setTransform(Transform(glm::vec3(verticalPosition, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));

        rays.push_back(horizontalRay);
        rays.push_back(verticalRay);
    }

    return rays;
}