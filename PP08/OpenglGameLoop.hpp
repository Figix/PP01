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
			//�׷��� ���� �����͵��� ����̽�(�׷��ȿ����� ��� ��ġ)�� ����(�������ִ�)��
			//������ ������ â �������� �׸��� ���� �޼ҵ�
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
					cout << "�浹!!!!";
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
			//�������� �����ɸ� ��� �� ��ĥ�ϴ� �̸� ĥ�صΰ� �װ��� �����ִ°Ͱ� �ٲ�
			glfwPollEvents();
			//�̺�Ʈ���� �ߺ��� �̺�Ʈ���� �����ؼ� �������ִ� ��
			//�Լ��� ����Ǵ� �������� ���޹޴´�.

			glFinish();

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());

			this_thread::sleep_for(chrono::milliseconds(5));
			//��� �� 0.02�ʵ��� ���� �ð��� ������ �ٽ� ���ӷ�������
		}
	private:	
		void DrawTriAngles(float datX, float datY, float size) { //������, ũ��
			float h = sqrt(3) * size / 2;
			glBegin(GL_TRIANGLES);
				glVertex2f(datX, datY + h); // ���ﰢ�� ���� = ��Ʈ3*��/2
				glVertex2f(datX - size / 2, datY);
				glVertex2f(datX + size / 2, datY);
			glEnd();
		}
		void DrawTriAnglesinvert(float datX, float datY, float size) { //������, ũ��
			float h = sqrt(3) * size / 2;
			glBegin(GL_TRIANGLES);
				glVertex2f(datX, datY); // ���ﰢ�� ���� = ��Ʈ3*��/2
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
				//���� ���� ���鿡������ ���� ������ ������
				//���� �̹� 0���� ���� ���� ���� ���¿��� Ű�� ���� ���·� ������
				//0�� �� ������ �������� ������ ���� ��� �ٽ� �ö�
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