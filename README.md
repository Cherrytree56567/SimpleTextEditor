# Making a Simple Text Editor in C++

## The Basics

### Choosing your IDE
There are a variety or different IDEs to choose from, such as Code::Blocks for Windows, Mac and Linux or Visual Studio Code for Windows, Mac or Linux or Visual Studio for Windows and Mac. Visual Studio is recommended for users who have a lot of storage, have Windows or Mac and like an easy experience whereas Visual Studio Code is suggested for those who would either like a Lightweight code editor or those who don't have Windows or Mac.

### Setting Up Your Project
You want to name your project appropriately and keep it somewhere, where you can access it easily. I suggest you keep it on your desktop, as it is easily visible and easy to access. To start, Create a C++ Project and create a vendor folder. The vendor folder is where you will store your libraries and includes. Create a `main.cpp` file in your project root (Visual Studio will automatically do this for you.) and paste this code:
```cpp
#include <iostream>

int main() {
	std::cout << "Hello World!\n";
	return 0;
}
```

### Setting Up your Vendors
For this project, we will use the `FreeGLUT`, `GLFW` and `IMGui` libraries. you can download the precompiled binaries [here](https://github.com/Cherrytree56567/SimpleTextEditor/raw/main/vendor.zip). Now, set up your IDE to use the includes and binaries. Inside the Vendor and library folder (eg: FreeGLUT) you will find two to three folders, `include`, `bin` and `src`. Configure your IDE to include all the files inside the src folders for compilation and make sure you include the libraries and include folders in your project. NOTE: The IMGui vendor folder includes files that may cause errors such as: `imgui_impl_allegro5.cpp` or `imgui_impl_android.cpp`, please remove these files.

## Coding the Actual Project
### Including the Necessary files
For this project, we will use the `GLFW`, `IMGui`, `iostream`, `fstream` and `string` libraries.
```cpp
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <fstream>
#include <string>
```

### Read from File function
To make our Simple Text Editor we will need to Read the text from a file. To do this we will make a function called ReadFromFile that will take a `const std::string& filename` and output a `std::string`. First, we need to check if the file is open because we can't open a file that is in use. Then we will get the lines from the file using `getLine` to get all the lines inside the file and add them to the `std::string text;` which we will return.
```cpp
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
```

### Write to File function
If we want to save the file, we want to be able to write the modified text to the file. To do this, we will implement a function that will take the file name and the data and write it to the file. First, we need to check if the file is open and then we can write the modified data to the file. 
```cpp
void WriteToFile(const std::string& filename, const std::string& text) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
    }
}
```

## The Real Fun

### Initializing GLFW
Before we create a window we need to Initialize our Graphics Library called GLFW.
```cpp
if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
}
```

### Creating a Window
Now we can create a window using `glfwCreateWindow` . We will need to provide `glfwCreateWindow` with the window height, width and title.
```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "Text Editor", NULL, NULL);
if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
```

### Initializing ImGui
For this project, we will use ImGui to simplify the graphics rendering. First, we will need to specify the Current Context using `glfwMakeCurrentContext`. Then we can Create an ImGui Context and initialize OpenGL3 and GLFW.
```cpp
glfwMakeContextCurrent(window);
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGui_ImplOpenGL3_Init();
ImGui_ImplGlfw_InitForOpenGL(window, true);
```

### Set up variables
We will need to define a variable for the filename, data and if the save is requested.
```cpp
std::string filename = "input.txt";
std::string text = ReadFromFile(filename);
bool saveRequested = false;
```

### Main Loop
Now, we need to create an infinite loop, so that the window will only close when the close button is pressed and the events are handled properly.
```cpp
while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
}
```

### Start the ImGui Frame
Every time the window updates, we need to create a new OpenGL3 and GLFW Frame.
```cpp
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();
```

### The GUI
Now, we can get to the fun stuff. We need to create two buttons for the open and save operations and a text box to hold the file contents.
```cpp
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
```

### Rendering the Frame
We're almost done, now we need to just render the frame, draw the pixels and swap the buffers.
```cpp
ImGui::Render();
ImGui::EndFrame();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
glfwSwapBuffers(window);
```

### Save Button
If the Save button was pressed, then we need to change the `saveRequested` variable to `false` and print out that we have saved the file.
```cpp
if (saveRequested) {
    saveRequested = false;
    std::cout << "File saved." << std::endl;
}
glClear(GL_COLOR_BUFFER_BIT);
```

### Cleaning Up
After the Window is closed, we need to Destroy all the Contexts.
```cpp
ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplGlfw_Shutdown();
ImGui::DestroyContext();
glfwDestroyWindow(window);
glfwTerminate();
return 0;
```

Now you have successfully made a full working GUI Text Editor using ImGui, GLFW and FreeGLUT.
