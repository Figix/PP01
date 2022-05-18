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
		bool moveOn=false;
		Player P;

		Block() {
			movex = 1;
			x = 70;
			y = rand()%10;
		}
		~Block()
		{

		}

		void blockMove() {
			if (moveOn) {
				x -= movex;
				if (x <= 10) {
					x = 50;
					y = rand() % 10;
				}
			}
		}
	};
}