#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

namespace OpenGL_Engine
{
	class OpenGLGameLoop
	{
	private:
		bool _isGameRunning;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		
	public:
		OpenGLGameLoop() { }
		~OpenGLGameLoop() {}

		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}

		void Run()
		{
			GLFWwindow* window;
			glfwSetErrorCallback(error_callback);
			if (!glfwInit())
			{
				std::exit(EXIT_FAILURE);
			}
			window = glfwCreateWindow(800, 800, "Simple example", NULL, NULL);

			Initialize(window);
			startRenderTimePoint = chrono::system_clock::now();
			while (!glfwWindowShouldClose(window))
			{

				Input(window);
				Update(window);
				Render(window);

			}
			Release(window);
		}

	private:
		float intriX = 1; float intriY = 0;
		float triX = 0; float triY = 0;
		bool transcol = false;

		void Initialize(GLFWwindow* window)
		{
			if (!window)
			{
				glfwTerminate();
				std::exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(window);
			glfwSetKeyCallback(window, key_callback);
		}
		void Release(GLFWwindow* window)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			std::exit(EXIT_SUCCESS);
		}

		void Input(GLFWwindow* window)
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				triY += 0.2f;
			}
			else {
				triY -= 0.2f;
			}
		}
		void Update(GLFWwindow* window)
		{
			if (triY <= 0) {
				triY = 0;
			}
			if (intriX < -1.f) {
				intriX = 1.f;
			} else {
				intriX -= 0.05f;
			}
			if (triX + 0.1f >= intriX && triX - 0.1f <= intriX) {
				if (triY == intriY) {
					transcol = transcol ? false : true;
				}
			}

		}
		void Render(GLFWwindow* window)
		{
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;

			glClearColor(1,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT);

			glColor4f(1, 0, 0, 1);
			if (transcol) { glColor4f(0,1,0,1); }
			DrawTriAngles(triX, triY, 0.2f);

			glColor4f(0, 0, 1, 1);
			DrawTriAnglesinvert(intriX, intriY, 0.2f);
			

			glfwSwapBuffers(window);
			glfwPollEvents();

			glFinish();

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());

			this_thread::sleep_for(chrono::milliseconds(20));
			//출력 후 0.02초동안 여유 시간을 가지고 다시 게임루프돌음
		}
	private:	
		void DrawTriAngles(float datX, float datY, float size) { //기준점, 크기
			float h = sqrt(3) * size / 2;
			glBegin(GL_TRIANGLES);
				glVertex2f(datX, datY + h); // 정삼각형 높이 = 루트3*변/2
				glVertex2f(datX - size / 2, datY);
				glVertex2f(datX + size / 2, datY);
			glEnd();
		}
		void DrawTriAnglesinvert(float datX, float datY, float size) { //기준점, 크기
			float h = sqrt(3) * size / 2;
			glBegin(GL_TRIANGLES);
			glVertex2f(datX, datY); // 정삼각형 높이 = 루트3*변/2
			glVertex2f(datX - size / 2, datY+h);
			glVertex2f(datX + size / 2, datY+h);
			glEnd();
		}

	};
}