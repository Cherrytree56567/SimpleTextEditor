#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <fstream>
#include <string>

// Function to read text from a file
std::string ReadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string text;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            text += line + "\n";
        }
        file.close();
    }
    return text;
}

// Function to write text to a file
void WriteToFile(const std::string& filename, const std::string& text) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Text Editor", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Initialize Dear ImGui
    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGui_ImplOpenGL3_Init("#version 130");
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    // Set up variables
    std::string filename = "input.txt";
    std::string text = ReadFromFile(filename);
    bool saveRequested = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui code for the text editor
        ImGui::Begin("Text Editor");

        if (ImGui::Button("Open")) {
            text = ReadFromFile(filename);
        }

        ImGui::SameLine();
        if (ImGui::Button("Save")) {
            WriteToFile(filename, text);
            saveRequested = true;
        }

        ImGui::SameLine();
        ImGui::Text(filename.c_str());

        ImGui::InputTextMultiline("##source", &text[0], text.size() + 1, ImVec2(780, 550));

        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui::EndFrame();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        // Check if save was requested and if so, mark it as completed
        if (saveRequested) {
            saveRequested = false;
            std::cout << "File saved." << std::endl;
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
