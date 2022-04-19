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

		}
		void Update()
		{

		}
		void Render()
		{

			cRenderer.Clear();
			b.blockMove();
			if (b.x == p.x) {
				if (b.y == p.y) {
					b.blockcheck = true;
				}
			}
			if (b.x <= 10) {
				b.x = 40;
				b.blockcheck = false;
			}
			if (b.blockcheck) {
				cRenderer.Clear();
				cRenderer.MoveCursor(20, 6);
				cRenderer.DrawString("닿았대요 다시하고 싶으면 R눌러바");
				while (b.blockcheck) {
					if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x52) & 0x8001) { //R키=0x52 입력체크하기
						b.blockcheck = false;
						break;
					}
				}
				b.x = 40; b.y = 7; //B 초기화
			}
			cRenderer.MoveCursor(1, 1);
			cRenderer.DrawString(to_string(b.y));
			cRenderer.MoveCursor(1, 2);
			cRenderer.DrawString(to_string(p.y));

			cRenderer.MoveCursor(p.x, p.y);
			cRenderer.DrawString("P");


			cRenderer.MoveCursor(b.x, b.y);
			cRenderer.DrawString("B");


			cRenderer.MoveCursor(10, 20);


			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(20));
		}


		////cout << "Rendering speed : " << renderDuration.count() << "sec" << endl;

		//int remainingFrameTime = 100 - (int)(renderDuration.count() * 1000.0);
		//if (remainingFrameTime > 0)
		//	this_thread::sleep_for(chrono::milliseconds(remainingFrameTime));
	};
}