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
			
			if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x52) & 0x8001) { //RŰ=0x52 �Է�üũ�ϱ�
				blockcheck = false; //break;�� ������ ��Ȳ
				b[0].moveOn = true;
				b[1].moveOn = false;
				b[2].moveOn = false;
				for (short i = 0; i < 3; i++) {
					b[i].movex = 1; b[i].x = 70; b[i].y = rand() % 10; //B ��ġ �ʱ�ȭ �� �ӵ� �ʱ�ȭ
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
			if (blockcheck == true) {	//�浹�� blockeck�� true���� �Ǿ �ش� ���� ��
				cRenderer.MoveCursor(10, 17);
				cRenderer.DrawString("��Ҵ�� �ٽ��ϰ� ������ R������");
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