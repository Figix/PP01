namespace MuSeoun_Engine {
	class Player
	{
	public:
		short x, y;
		short moveY;

		Player()
		{
			x = 20;
			y = 7;

			moveY = 1;
		}
		~Player()
		{

		}

		void isKeyPressed()
		{
			//y = 5;
			// 나누는 용도 //
			y -= moveY;
		}

		void isKeyUnpressed()
		{
			//y = 7;
			// 나누는 용도 //
			y += moveY;
			if (y >= 9) { y = 9; }
			if (y <= 1) { y = 1; }
		}



	};
}
