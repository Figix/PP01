namespace MuSeoun_Engine {
	class Player
	{
	public:
		short x, y;
		Player()
		{
			x = 20;
			y = 7;
		}
		~Player()
		{

		}

		void isKeyPressed()
		{
			y = 5;
		}

		void isKeyUnpressed()
		{
			y = 7;
		}

	};
}
