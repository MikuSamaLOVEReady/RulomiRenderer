#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include <fstream>
#include<string>
#include<sstream>

//contains tuple
#include<utility>
#include <functional>
#include "renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include"Texture.h"

#include"Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //�������л��� ���ʱ�� �����õĻ� �Ͱ�����ʾ����ˢ������
    //glfwSwapInterval(10);


    //glew ������valid context֮���������
    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR" << std::endl;
    }


    float positions[] = {
               -50.0f,   -50.0f,  0.0f, 0.0f,    //0
                50.0f,  -50.0f, 1.0f, 0.0f,  //1
                50.0f,   50.0f, 1.0f, 1.0f,    //2
               -50.0f,   50.0f , 0.0f, 1.0f   //3
    };


    //����������
    unsigned int indeies[] = {
        0,1,2,
        2,3,0
    };

    //��������� ֱ�Ӵ���һ��vb ���Ұ� ��ID�Զ��洢�ڶ�����
    VertexBuffer VB(positions, 4*4 * sizeof(float));
 
    //��������˹���
    VertexArray VA;
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    VA.AddBuffer(VB, layout);
   

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //һ����blend Դ����ɫϵ����Ĭ����1 �����ı�Դ��ɫ �������ߣ�
    //destinition ��ɫϵ��Ĭ����0  ��opengl ��Ĭ��ȫ��ɫ���ǡ����������ߣ�
   //glBlendFunc()

    //glBlendEquation(mode) �����ʾ������ɫ ����κϳɵ�   // ����RGB���⻹����Aͨ����ɫ Ĭ����+
    //



    IndexBuffer IB(indeies, 6);

    //opengl math
    //znear �� zfar �����ƽ��ͶӰ
    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f,-1.0f,1.0f);
    //glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f,-1.0f,1.0f);
    //orthͶӰ��������Ǹ���Ŀ�����ؿ�ȵ�ô  0.0 640�����½�����

    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    //view ����������ƶ� ��������ֻ�ܲٿ� object ������matrix�Ƿ����
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //����ǲٿ�����
  /*  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;*/

   /* glm::vec4 vp(160.0f, 360.0f, 0.0f, 1.0f);
    glm::vec4 result = proj*vp;*/
    glm::vec3 translation(0, 200, 0);

    glm::vec3 translationB(400, 200, 0);


    /*ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    unsigned int  shader = CreateShader(source.vertexSource, source.fragmentSoruce);
    glUseProgram(shader);*/
    Shader shader("res/shaders/basic.shader");
    shader.Bind();
    //��opengl ��shader every uniform ��������һ��ID ��Ϊ����
    //�ڲ��ҵ�ʱ�� ֱ�Ӳ�uniform�����־Ϳ�����
  /*  int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 8.0f, 0.4f, 5.0f, 1.0f);*/
    shader.SetUniform4f("u_Color", 8.0f, 0.4f, 5.0f, 1.0f);

    Texture texture("res/textures/12.jpg");
    //texture ���ڵڶ��������
    texture.Bind(2);
    shader.SetUniform1i("u_Texture", 2);
   /* shader.SetUniformMat4f("u_MVP", mvp);*/
    
    //�����
    VA.UnBind();
    VB.UnBind();
    IB.UnBind();
    shader.UnBind();
    
    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    //float r = 0.0f;
    //float increment = 0.05f;

    test::TestClearColor test;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       // glClear(GL_COLOR_BUFFER_BIT);
        renderer.Clear();

        //�����ʱû��
        //test.OnUpdate(0.0f);

        //
        //test.OnRender();

        ImGui_ImplOpenGL3_NewFrame();
        //test.OnImGuiRender();
         ImGui_ImplGlfw_NewFrame();
         ImGui::NewFrame();


        //����ֵ�ı���position ����VB��û�иı�
        //��ȷ��������batch rendering �����ж���ϳɵ�һ��VB��
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(VA, IB, shader);
        }

        //draw out another image
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(VA, IB, shader);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {

            ImGui::SliderFloat("TranslationX", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //�ڶ���������һ������ָ�� ��ָ��ľ���һ��flaot[3] array�ڴ� ����ֻ�� .x ������������������Ȼ���� .y .z
            
            //
            ImGui::SliderFloat3("Translation A", &translation.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //if (ImGui::Button("Button"))                            
            // Buttons return true when clicked (most widgets return true when edited/activated)
            //    counter++;
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            //��ʾ��ǰ֡��
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //ImGui::End();
        }

        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}