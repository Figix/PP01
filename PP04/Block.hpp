using namespace std;
#include "MConsolUtil.hpp"

namespace MuSeoun_Engine {
	class Block
	{
	private:
		MConsoleRenderer cRenderer;

	public:
		short x, y;
		short movex;
		bool blockcheck;
		Player P;

		Block() {
			movex = 1;
			x = 40;
			y = 7;
			blockcheck = false;
		}
		Block(short newY)
		{
			movex = 1;
			x = 40;
			y = newY;
			blockcheck = false;
		}
		~Block()
		{

		}

		void blockMove(short anotherX, short anotherY) {
			x -= movex;
			if (x <= 10) {
				x = 40;
			}
		}
	};
}