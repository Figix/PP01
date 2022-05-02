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
		Block *b = new Block[3];
		short addcounter = 0;
		bool blockcheck=false;
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
			b[0].moveOn = true;
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
			
			if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x52) & 0x8001) { //R키=0x52 입력체크하기
				blockcheck = false; //break;와 동일한 상황
				b[0].moveOn = true;
				b[1].moveOn = false;
				b[2].moveOn = false;
				for (short i = 0; i < 3; i++) {
					b[i].movex = 1; b[i].x = 70; b[i].y = rand() % 10; //B 위치 초기화 및 속도 초기화
				}
				addcounter = 0;
			}


		}
		void Update()
		{
			b[0].blockMove(p.x, p.y);
			b[1].blockMove(p.x, p.y);
			b[2].blockMove(p.x, p.y);
			for (short i = 0; i < 3; i++) {
				if (b[i].x == p.x) {
					if ((b[i].y+2) < p.y || (b[i].y-2) > p.y) {
					addcounter = 0;
					blockcheck = true;
					for (short j = 0; j < 3; j++) {
						b[j].moveOn = false;
					}
					}
				}
			}
			addcounter++;
			addcounter = addcounter % 15;
			if (addcounter == 0) {
				if (b[1].moveOn == true) {
					b[2].moveOn = true;
				}
				if (b[1].moveOn == false) {
					b[1].moveOn = true;
				}
			}
		}
		void Render()
		{
			cRenderer.Clear();
			if (blockcheck == false) {
				cRenderer.MoveCursor(1, 1);
				cRenderer.DrawString(to_string(b[0].y));
				cRenderer.MoveCursor(1, 2);
				cRenderer.DrawString(to_string(p.y));

				cRenderer.MoveCursor(p.x, p.y);
				cRenderer.DrawString("P");

				for (short i = 0 ; i < 3; i++) {
					if (b[i].moveOn == true) {
						//cRenderer.MoveCursor(b[i].x, b[i].y);/*
						//cRenderer.DrawString("B");*/
						for (short y = 0; y < 10; y++) {
							if (y >= b[i].y - 2 && y <= b[i].y + 2) { continue; }
							else {
								cRenderer.MoveCursor(b[i].x, y);
								cRenderer.DrawString("B");
							}
						}
					}
				}
			}
			if (blockcheck == true) {	//충돌시 blockeck가 true값이 되어서 해당 문장 들어감
				cRenderer.MoveCursor(10, 17);
				cRenderer.DrawString("닿았대요 다시하고 싶으면 R눌러바");
			}
			
			cRenderer.MoveCursor(10, 20);

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(20));
			//출력 후 0.02초동안 여유 시간을 가지고 다시 게임루프돌음
		}


		////cout << "Rendering speed : " << renderDuration.count() << "sec" << endl;

		//int remainingFrameTime = 100 - (int)(renderDuration.count() * 1000.0);
		//if (remainingFrameTime > 0)
		//	this_thread::sleep_for(chrono::milliseconds(remainingFrameTime));
	};
}