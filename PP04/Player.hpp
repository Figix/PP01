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
			// ������ �뵵 //
			y -= moveY;
		}

		void isKeyUnpressed()
		{
			//y = 7;
			// ������ �뵵 //
			y += moveY;
			if (y >= 8) { y = 7; }
		}



	};
}
