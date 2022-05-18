#include <iostream>
#include <string>

using namespace std;

bool is_game_running = false;
//atomic value?

class GameObject {
public :
	GameObject() {
		cout << "���� ������Ʈ ����!\n";
	};
	virtual ~GameObject() {
		cout << "���� ������Ʈ ����!\n";
	};
	virtual void Start() {
		cout << "���� ������Ʈ ��ŸƮ!\n";
	}
	virtual void Update() {
		cout << "���� ������Ʈ ������Ʈ!\n";
	}
	/*void Start() {
		cout << "���� ������Ʈ �ʱ�ȭ!\n";
	};
	void Update() {
		cout << "���� ������Ʈ ������Ʈ!\n";
	};*/
};

class Player : public GameObject
{
public:
	int HP = 100;
	Player(){
		cout << "������ ����!!!\n";
	};
	~Player() {
		cout << "������ ����!!!\n";
	};

	void Start(){
		cout << "�������� HP��" << HP << "�Դϴ�!\n";
	}
	void Update() {
		cout << "������ ������Ʈ!!!\n";
	}
};
class Enemy : public GameObject
{
public:
	int HP = 100;
	Enemy() {
		cout << "�� ����!!!\n";
	}
	~Enemy() {
		cout << "�� ����!!!\n";
	}
	void Start(){
		cout << "���� HP��" << HP << "�Դϴ�!\n";
	}
	void Update() {
		cout << "�� ������Ʈ!!!\n";
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
		cout << "�Է����ּ��� (1:���� ���� , 2: ���� ���): ";
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
//	Player()	//������
//	{
//		cout << "���ΰ�1 �εյ���!" << endl;
//		
//	}
//	~Player()	//�Ҹ��� C++�� �����ϰ� ���� ��
//	{
//		cout << "���ΰ�1 ����!" << endl;
//
//	}
//};
//class Player2 {
//public:
//	Player2()	//������
//	{
//		cout << "���ΰ�2 �εյεյ������!" << endl;
//
//	}
//	~Player2()	//�Ҹ��� C++�� �����ϰ� ���� ��
//	{
//		cout << "���ΰ�2 ��������!" << endl;
//
//	}
//};
//
//int main() {
//	Player2 pl;
//
//	Player *player = new Player();
//	delete(player); //�� �ٸ� Ŭ���������� �����Ǿ�����?
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
//		std::cout << "������ : " << str;
//	}
//}
//
//using namespace visual_novel;
////using namespace nomal;
////��using�� ��� �ݾƾ� �ұ�?
//
//int main() {
//	visual_novel::print("��ȭ�Ӱ� �Ƹ��ٿ� ���α׷��� ���Ͻð�\n");
//	nomal::print("��ȭ�Ӱ� �Ƹ��ٿ� ���α׷��� ���Ͻð�\n");
//	print("��ȭ�Ӱ� �Ƹ��ٿ� ���α׷��� ���Ͻð�\n");
//	return 0;
//}