namespace MuSeoun_Engine {
	class Block
	{
	public:
		short x, y;
		bool blockcheck;


		Block()
		{
			x = 40;
			y = 7;
			blockcheck = false;
		}
		~Block()
		{

		}

		void blockMove() {
			x -= 1;
		}
	};
}