#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "RCube.h"
#include "Cube_Logic/RSolver.hpp"


int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Use the core profile to enforce our own implementation of a vertex array
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1200, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);



    // Synchronize the refresh rate with our native refresh rate
    glfwSwapInterval(1);

    // Initialize Glew
    if (glewInit() != GLEW_OK)
        std::cout << "glewInit error!" << std::endl;

    // Log the OpenGL version used because we can
    //std::cout << glGetString(GL_VERSION) << std::endl;
                
    {

        GLcall(glEnable(GL_BLEND));
         GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClearDepth(-50);                   // Set background depth to farthest
        glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
        glDepthFunc(GL_GREATER);    // Set the type of depth-test
        glShadeModel(GL_SMOOTH);   // Enable smooth shading
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glDepthMask(GL_TRUE);
        glDepthRange(50.0f, -50.0f);

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 50.0f, -50.0f);

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::vec3 translation_vec(0, 0, -1000);
        glm::vec3 scale_vec(1.0f, 1.0f, 1.0f);
        glm::vec3 rotations_vec(0.0f, 0.0f, 0.0f);

        int FPS = 10;

        RCube rcube;
        RLogicCube lcube;
        rcube.SetLogicCube(lcube);
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
               renderer.Clear();

               ImGui_ImplGlfwGL3_NewFrame();
               glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_vec);
               glm::mat4 scale = glm::scale(glm::mat4(1.0f), scale_vec);
               glm::mat4 rotation_x = glm::rotate(glm::mat4(1.0f), rotations_vec.x, glm::vec3(1.0f, 0.0f, 0.0f));
               glm::mat4 rotation_y = glm::rotate(glm::mat4(1.0f), rotations_vec.y, glm::vec3(0.0f, 1.0f, 0.0f));
               glm::mat4 rotation_z = glm::rotate(glm::mat4(1.0f), rotations_vec.z, glm::vec3(0.0f, 0.0f, 1.0f));

               glm::mat4 mvp = projection * view * model * rotation_x * rotation_y * rotation_z* scale;

               {
                   ImGui::SliderInt("Rotation speed", &FPS, 1, 60);

                   ImGui::SliderFloat("Translate Z", &translation_vec.z, -1800.0f, -1000.0f);
                   ImGui::SliderFloat2("Translate XY", &translation_vec.x, -200.0f, 200.0f);

                   ImGui::SliderFloat3("Scale", &scale_vec.x, 0.0f, 10.0f);
                   ImGui::SliderFloat3("Rotation", &rotations_vec.x, -PI, PI);

                   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                   if (ImGui::Button("Up"))
                   {
                       rcube.Rotate("U", FPS);
                       rcube.GetLogicCube().rotate("U");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Down"))
                   {
                       rcube.Rotate("D", FPS);
                       rcube.GetLogicCube().rotate("D");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Front"))
                   {
                       rcube.Rotate("F", FPS);
                       rcube.GetLogicCube().rotate("F");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Back"))
                   {
                       rcube.Rotate("B", FPS);
                       rcube.GetLogicCube().rotate("B");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Right"))
                   {
                       rcube.Rotate("R", FPS);
                       rcube.GetLogicCube().rotate("R");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Left"))
                   {
                       rcube.Rotate("L", FPS);
                       rcube.GetLogicCube().rotate("L");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Rotate Back"))
                   {
                       rcube.Rotate("^", FPS);
                       rcube.GetLogicCube().rotate("^");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Rotate Right"))
                   {
                       rcube.Rotate(">", FPS);
                       rcube.GetLogicCube().rotate(">");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Rotate Left"))
                   {
                       rcube.Rotate(">'", FPS);
                       rcube.GetLogicCube().rotate("<");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Rotate Front"))
                   {
                       rcube.Rotate("^'", FPS);
                       rcube.GetLogicCube().rotate("v");
                       rcube.GetLogicCube().print_cube();

                   }
                   if (ImGui::Button("Shuffle"))
                   {
                       std::string scram = RSolver::shuffle(rcube.GetLogicCube());
                       std::cout << scram << "\n\n";
                       rcube.GetLogicCube().print_cube();

                       rcube.Rotate(scram, FPS);
                   }
                   if (ImGui::Button("Solve"))
                   {
                       std::string solution = RSolver::genetic_solution(rcube.GetLogicCube()).first;
                       rcube.GetLogicCube().rotate(solution);
                       std::cout << solution << "\n\n\n";
                       rcube.GetLogicCube().print_cube();

                       rcube.Rotate(solution, FPS);
                   }
               }

               rcube.Update();

               auto& arr = rcube.GetCube();
               for (auto& val : arr)
               {
                   val.cube.Bind();
                   val.cube.GetShader().SetUniformMat4f("u_MVP", mvp * val.GetModel());
                  // val.cube.GetShader().SetUniform4f("u_Color")
                   renderer.Draw(val.cube.GetVerArr(), val.cube.GetIndBuf(), val.cube.GetShader());
                   val.cube.Unbind();
               }

               ImGui::Render();
               ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

               /* Swap front and back buffers */
               glfwSwapBuffers(window);
   
               /* Poll for and process events */
               glfwPollEvents();
        }
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}