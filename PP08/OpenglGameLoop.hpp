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
		float intriX = 1; float intriY = -1;
		float triX = 0; float triY = 0;
		float trispd;
		bool transcol = false;
		
		float boxX1size = 0.1f;
		float boxX1 = 0, boxY1 = 0;
		float boxX2size = 0.2f;
		float boxX2 = 0-(boxX2size/2), boxY2 = 0-(boxX2size/2);

		float chargePower = 0;
		float maxcharge = 0;
		float mincharge = 0;
		bool chargeONOFF = true;
		//

		void Initialize(GLFWwindow* window)
		{
			if (!window)
			{
				glfwTerminate();
				std::exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(window);
			//그래픽 관련 데이터들을 디바이스(그래픽에서는 출력 장치)를 매핑(연결해주는)것
			//지정한 윈도우 창 기준으로 그리기 위한 메소드
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
			TriAnglesinputs();
			boxinputs();
		}
		void Update(GLFWwindow* window)
		{
			cout << chargePower << "\n";

			TriAnglesUpdate();

			if (boxX1 < -1) {
				boxX1 = 1;
			}
			if (boxX1 > 1) {
				boxX1 = -1;
			}
			if (boxY1 < -1) {
				boxY1 = 1;
			}
			if (boxY1 > 1) {
				boxY1 = -1;
			}

			//box1 maxX : boxX1 + boxX1size/2
			//box1 minX : boxX1 - boxX1size/2
			//box1 maxY : boxY1 + boxX1size/2
			//box1 minY : boxY1 - boxX1size/2

			//box2 maxX : boxX2 + boxX2size/2
			//box2 minX : boxX2 - boxX2size/2
			//box2 maxY : boxY2 + boxX2size/2
			//box2 minY : boxY2 - boxX2size/2

			// box1 maxX > box2 minX && box1 minX < box2 maxX
			// box1 maxY > box2 minY && box1 minY < box2 maxY

			if (boxX1 + boxX1size / 2 > boxX2 - boxX2size / 2 && boxX1 - boxX1size / 2 < boxX2 + boxX2size / 2) {
				if (boxY1 + boxX1size / 2 > boxY2 - boxX2size / 2 && boxY1 - boxX1size / 2 < boxY2 + boxX2size / 2) {
					cout << "충돌!!!!";
				}
			}
		}
		void Render(GLFWwindow* window)
		{
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

			glClearColor(0.3,0.3,0.3,1);
			glClear(GL_COLOR_BUFFER_BIT);

			glColor4f(1, 0, 0, 1);
			if (transcol) { glColor4f(0,1,0,1); }
			DrawTriAngles(triX, triY, 0.05f);

			glColor4f(0, 0, 1, 1);
			DrawTriAnglesinvert(intriX, intriY, 0.05f);
			
			glColor4f(0, 1, 0 , 1);
			DrawBox(boxX1, boxY1, boxX1size);

			glColor4f(1, 0, 1, 1);
			DrawBox(boxX2, boxY2, boxX2size);

			glfwSwapBuffers(window);
			//렌더링이 오래걸릴 경우 다 못칠하니 미리 칠해두고 그것을 현재있는것과 바꿈
			glfwPollEvents();
			//이벤트에서 중복된 이벤트들을 정리해서 전달해주는 것
			//함수가 실행되는 순간마다 전달받는다.

			glFinish();

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());

			this_thread::sleep_for(chrono::milliseconds(5));
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
		void DrawBox(float datX, float datY, float size) {
			glBegin(GL_QUADS);
				glVertex2f(datX-(size/2), datY-(size/2));
				glVertex2f(datX-(size/2), datY+(size/2));
				glVertex2f(datX+(size/2), datY+(size/2));
				glVertex2f(datX+(size/2), datY-(size/2));
			glEnd();
		}
		void boxinputs() {
			//W: 0x57, A : 0x41 S : 0x53, D : 0x44
			#define VK_W  0x57
			#define VK_A  0x41
			#define VK_S  0x53
			#define VK_D  0x44
			if (GetAsyncKeyState(VK_W) & 0x8000 || GetAsyncKeyState(VK_W) & 0x8001) {
				boxY1 += 0.05f;
			}
			else {
			}

			if (GetAsyncKeyState(VK_A) & 0x8000 || GetAsyncKeyState(VK_A) & 0x8001) {
				boxX1 -= 0.05f;
			} else{
			}

			if (GetAsyncKeyState(VK_S) & 0x8000 || GetAsyncKeyState(VK_S) & 0x8001) {
				boxY1 -= 0.05f;
			}
			else {
			}
			
			if (GetAsyncKeyState(VK_D) & 0x8000 || GetAsyncKeyState(VK_D) & 0x8001) {
				boxX1 += 0.05f;
			}
			else {
			}
		}
		void TriAnglesinputs() {
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				trispd = 0.2f;
			}
			else {
				trispd = -0.2f;
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001) {
				if (chargeONOFF) { chargePower++; }
				else {
					chargePower--;
					if (chargePower <= 0) {
						chargeONOFF = true;
						chargePower = 0;
					}
				}
				//현재 힘은 지면에서있을 때만 충전이 가능함
				//힘이 이미 0보다 높은 값을 가진 상태에서 키를 눌른 상태로 있으면
				//0이 될 때까지 내려가고 누르는 동안 계속 다시 올라감
			}
			else {
				if (chargePower <= 0) {
					chargeONOFF = true;
					chargePower = 0;
				}
				else {
					chargeONOFF = false;
					mincharge++;
					chargePower--;
					trispd = 0;
					trispd = chargePower / 3 * 0.02f;
				}
			}
		}
		void TriAnglesUpdate() {
			triY += trispd;

			if (triY <= -1.f) {
				triY = -1;
			}
			else if (triY >= 0.8f) {
				triY = 0.8f;
			}
			if (intriX < -1.f) {
				intriX = 1.f;
			}
			else {
				intriX -= 0.02f;
			}
			if (triX + 0.1f >= intriX && triX - 0.1f <= intriX) {
				if (triY == intriY) {
					transcol = transcol ? false : true;
				}
			}
		}
	};
}