#include <iostream>
#include <string>

using namespace std;

bool is_game_running = false;
//atomic value?

class GameObject {
public :
	GameObject() {
		cout << "게임 오브젝트 생성!\n";
	};
	virtual ~GameObject() {
		cout << "게임 오브젝트 삭제!\n";
	};
	virtual void Start() {
		cout << "게임 오브젝트 스타트!\n";
	}
	virtual void Update() {
		cout << "게임 오브젝트 업데이트!\n";
	}
	/*void Start() {
		cout << "게임 오브젝트 초기화!\n";
	};
	void Update() {
		cout << "게임 오브젝트 업데이트!\n";
	};*/
};

class Player : public GameObject
{
public:
	int HP = 100;
	Player(){
		cout << "이현진 생성!!!\n";
	};
	~Player() {
		cout << "이현진 삭제!!!\n";
	};

	void Start(){
		cout << "이현진의 HP는" << HP << "입니다!\n";
	}
	void Update() {
		cout << "이현진 업데이트!!!\n";
	}
};
class Enemy : public GameObject
{
public:
	int HP = 100;
	Enemy() {
		cout << "적 생성!!!\n";
	}
	~Enemy() {
		cout << "적 삭제!!!\n";
	}
	void Start(){
		cout << "적의 HP는" << HP << "입니다!\n";
	}
	void Update() {
		cout << "적 업데이트!!!\n";
	}
};


int main() {
	static bool is_game_running = true;

	//GameObject go[2];

	GameObject* p = new Player();
	GameObject* e = new Enemy();

	/*go[0] = *p;
	go[1] = *e;*/

	p->Start();
	e->Start();

	/*GameObject *Player = new GameObject();

	Player->Start();*/

	while (is_game_running) {
		//Player->Update();
		p->Update();
		e->Update();
		cout << "입력해주세요 (1:게임 종료 , 2: 게임 계속): ";
		int input;
		cin >> input;
		if (input == 1) {
			is_game_running = false;
		}
	}
	
	delete(p);
	delete(e);

	return 0;
}


//class Player {
//public :		
//	Player()	//생성자
//	{
//		cout << "주인공1 두둥등장!" << endl;
//		
//	}
//	~Player()	//소멸자 C++의 유일하게 생긴 것
//	{
//		cout << "주인공1 퇴장!" << endl;
//
//	}
//};
//class Player2 {
//public:
//	Player2()	//생성자
//	{
//		cout << "주인공2 두둥두둥등장등장!" << endl;
//
//	}
//	~Player2()	//소멸자 C++의 유일하게 생긴 것
//	{
//		cout << "주인공2 퇴퇴장장!" << endl;
//
//	}
//};
//
//int main() {
//	Player2 pl;
//
//	Player *player = new Player();
//	delete(player); //왜 다른 클래스까지도 삭제되었을까?
//	//Player player;
//	
//	return 0;
//}



//int main() {
//	int* a = (int*)malloc(sizeof(int) * 2);
//	free(a);
//
//	int* b = new int[2];
//	delete(b);
//
//	return 0;
//}




//namespace nomal {
//	void print(std::string str) {
//		std::cout << str;
//	}
//}
//namespace visual_novel {
//	void print(std::string str) {
//		std::cout << "이은석 : " << str;
//	}
//}
//
//using namespace visual_novel;
////using namespace nomal;
////ㄴusing은 어떻게 닫아야 할까?
//
//int main() {
//	visual_novel::print("평화롭고 아름다운 프로그래밍 패턴시간\n");
//	nomal::print("평화롭고 아름다운 프로그래밍 패턴시간\n");
//	print("평화롭고 아름다운 프로그래밍 패턴시간\n");
//	return 0;
//}