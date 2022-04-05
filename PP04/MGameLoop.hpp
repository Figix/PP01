#pragma once
#include <chrono>
#include <thread>
#include "MConsolUtil.hpp"

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private :
		bool _isGameRunning;	
		MConsoleRenderer cRenderer;
		chrono::system_clock::time_point starttime;
		
	public :
		MGameLoop() 	{	_isGameRunning = false;		}
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			while (_isGameRunning)
			{
				
				Input();
				Update();
				Render();
				;
			}
			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}

	private :
		void Initialize()
		{
			
		}
		void Release() 
		{
		}

		void Input()
		{
		/*	if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{ 
		
			}
			else 
			{
			
			}*/
			starttime = chrono::system_clock::now();
		}
		void Update()
		{
			
		}
		void Render()
		{
			chrono::system_clock::time_point startRenderTimePoint = chrono::system_clock::now();
			//now는 클럭타임을 사람이 이해할 수있는 초단위로 OS가 바꿔줌
			//그래서 chrono::syste_clock::now()
			 
			cRenderer.Clear();
			
			cRenderer.MoveCursor(10, 20);


			//chrono::duration<double> renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			//
			////현재 시각- 과거의 시각 = 각각의 시각 차이는 걸린시간
			//string fps = "FPS(milliseconds) : " + to_string(int(renderDuration.count()));
			//cRenderer.DrawString(fps);

			chrono::duration<double> EndDuration = chrono::system_clock::now() - starttime;
			EndDuration *= 1000;
			cout << " 1FPS(milliseconds) : " + to_string(int(EndDuration.count()));
			system("PAUSE");
		}


			////cout << "Rendering speed : " << renderDuration.count() << "sec" << endl;

			//int remainingFrameTime = 100 - (int)(renderDuration.count() * 1000.0);
			//if (remainingFrameTime > 0)
			//	this_thread::sleep_for(chrono::milliseconds(remainingFrameTime));
		

				
		
	};

	


	

}