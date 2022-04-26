#pragma once
#include <chrono>
#include <thread>
#include "MConsolUtil.hpp"
#include "Player.hpp"
#include "Block.hpp"

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning;
		MConsoleRenderer cRenderer;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player p;
		Block b;
	public:
		MGameLoop() { _isGameRunning = false; }
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			startRenderTimePoint = chrono::system_clock::now();
			while (_isGameRunning)
			{

				Input();
				Update();
				Render();

			}
			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}

	private:
		void Initialize()
		{
			Block* b2 = new Block(rand()%7);
		}
		void Release()
		{
		}

		void Input()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				p.isKeyPressed();
			}
			else
			{
				p.isKeyUnpressed();
			}
			
			if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x52) & 0x8001) { //RŰ=0x52 �Է�üũ�ϱ�
				b.blockcheck = false; //break;�� ������ ��Ȳ
				b.movex = 1; b.x = 40; b.y = 7; //B ��ġ �ʱ�ȭ �� �ӵ� �ʱ�ȭ
			}


		}
		void Update()
		{
			if (b.x == p.x && b.y == p.y) {
				b.blockcheck = true;
			}
			if (b.blockcheck) {				//�浹�� blockeck�� true���� �Ǿ �ش� ���� ��
				b.movex = 0;
			}
		}
		void Render()
		{
			cRenderer.Clear();
			
			b.blockMove(p.x, p.y);
			

			cRenderer.MoveCursor(1, 1);
			cRenderer.DrawString(to_string(b.y));
			cRenderer.MoveCursor(1, 2);
			cRenderer.DrawString(to_string(p.y));

			cRenderer.MoveCursor(p.x, p.y);
			cRenderer.DrawString("P");

			cRenderer.MoveCursor(b.x, b.y);
			cRenderer.DrawString("B");

			if (b.blockcheck) {	//�浹�� blockeck�� true���� �Ǿ �ش� ���� ��
				cRenderer.MoveCursor(10, 17);
				cRenderer.DrawString("��Ҵ�� �ٽ��ϰ� ������ R������");
				b.movex = 0;
			}
			
			cRenderer.MoveCursor(10, 20);

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(20));
			//��� �� 0.02�ʵ��� ���� �ð��� ������ �ٽ� ���ӷ�������
		}


		////cout << "Rendering speed : " << renderDuration.count() << "sec" << endl;

		//int remainingFrameTime = 100 - (int)(renderDuration.count() * 1000.0);
		//if (remainingFrameTime > 0)
		//	this_thread::sleep_for(chrono::milliseconds(remainingFrameTime));
	};
}