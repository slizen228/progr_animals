// progr_animals.cpp: определяет точку входа для приложения.
//
#include <iostream>
using namespace std;



class Animal {
public:
	int m_age;
	int m_x;
	int m_y;
	int m_direction;
	int m_constancy;
	bool m_dead;
public:
	Animal();
public:
	virtual void Add_aging() = 0;
	virtual void Move() = 0;
	virtual int Breed() = 0;
	virtual void Eat()=0;
	virtual bool Is_Rabbit()=0;
	virtual bool operator==(Animal&)=0;
};

class Rabbit: public Animal{
public:
	Rabbit();
	Rabbit(int,int,int,int,int);
public:
	void Add_aging();
	void Move();
	int Breed();
	void Eat();
	bool Is_Rabbit();
	bool operator==(Animal&);
};

class Wolf: public Animal{
public:
	int m_count_rabbits;
	int m_hunger;
public:
	Wolf();
	Wolf(int, int, int, int, int);
public:
	void Add_aging();
	void Move();
	int Breed();
	void Eat();
	bool Is_Rabbit();
	bool operator==(Animal&);
};

class Simulation {
public:
	int** m_field;
	int m_n;
	int m_m;
	Animal** m_creatures;
	int m_count_creatures;
public:
	Simulation();
	Simulation(int,int,int,int);
	~Simulation();
public:
	void Add_creature(Animal&);
	void Delete_creature(int);
	void Do_Movements();
	void Eat();
	void Aging();
	void Breed();
	void Die();
	void Print(int);
};

Simulation::Simulation() {
	m_n = 0;
	m_m = 0;
	m_field = nullptr;
	m_creatures = nullptr;
	m_count_creatures = 0;
}

Simulation::Simulation(int _n, int _m, int _r_c, int _w_c) {
	int _x, _y, _dir, _cons;
	m_n = _n;
	m_m = _m;
	int ** m_field = new int* [_n];
	for (int i = 0; i < _n; i++) {
		m_field[i] = new int [_m];
	}
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _m; j++) {
			m_field[i][j] = 0;
		}
	}
	m_creatures = nullptr;
	m_count_creatures = 0;
	for (int i = 0; i < _r_c; i++) {
		cin >> _x;
		cin >> _y;
		cin >> _dir;
		cin >> _cons;
		Rabbit _a(0, _x, _y, _dir, _cons);
		Add_creature(_a);
	}
	for (int i = 0; i < _w_c; i++) {
		cin >> _x;
		cin >> _y;
		cin >> _dir;
		cin >> _cons;
		Wolf _a(0, _x, _y, _dir, _cons);
		Add_creature(_a);
	}
}

Simulation::~Simulation() {
	if (m_field != nullptr) {
		for (int i = 0; i < m_n; i++) {			
			delete[] m_field[i];
		}
		delete[] m_field;
	}
	if (m_creatures != nullptr) {
		delete[] m_creatures;
	}
}

void Simulation::Add_creature(Animal& _creature) {
	m_count_creatures += 1;
	Animal** _mas_creatures = new Animal* [m_count_creatures] ;

	for (int i = 0; i < m_count_creatures - 1; i++) {
		_mas_creatures[i] = m_creatures[i];
	}
	_mas_creatures[m_count_creatures - 1] = &_creature;
	if (m_creatures != nullptr) {
		delete[] m_creatures;
	}
	m_creatures = new Animal*[m_count_creatures];
	for (int i = 0; i < m_count_creatures; i++) {
		m_creatures[i] = _mas_creatures[i];
	}
	
	delete[] _mas_creatures;
	m_creatures[1];
}

void Simulation::Delete_creature(int _num) {
	m_count_creatures -= 1;
	if(m_count_creatures!=0){
		Animal** _mas_creatures = new Animal * [m_count_creatures];
		for (int i = 0; i < _num; i++) {
			_mas_creatures[i] = m_creatures[i];
		}
		for (int i = _num; i < m_count_creatures; i++) {
			_mas_creatures[i] = m_creatures[i + 1];
		}
		if (m_creatures != nullptr) {
			delete[] m_creatures;
		}
		m_creatures = new Animal * [m_count_creatures];
		for (int i = 0; i < m_count_creatures; i++) {
			m_creatures[i] = _mas_creatures[i];
		}
	}
}

void Simulation::Do_Movements() {
	int index;
	for (index = 0; index < m_count_creatures; index++) {
		cout << index << " " << m_creatures[index]->m_dead<<endl;
		(*m_creatures[index]).Move();
		if ((*m_creatures[index]).m_x > 0) {
			m_creatures[index]->m_x = m_creatures[index]->m_x % m_n;
		}
		if (m_creatures[index]->m_x < 0) {
			m_creatures[index]->m_x =m_n + m_creatures[index]->m_x;
		}
		if (m_creatures[index]->m_y > 0) {
			m_creatures[index]->m_y = m_creatures[index]->m_y % m_n;
		}
		if (m_creatures[index]->m_y < 0) {
			m_creatures[index]->m_y = m_n + m_creatures[index]->m_y;
		}
	}
}

void Simulation::Eat() {
	for (int i = 0; i < m_count_creatures; i++) {
		if (!(m_creatures[i]->Is_Rabbit())) {
			for (int j = 0; j < m_count_creatures; j++) {
				if ((*m_creatures[i]) == (*m_creatures[j]) && i != j && m_creatures[j]->m_dead == false) {
					m_creatures[i]->Eat();
					m_creatures[j]->m_dead = true;
				}
			}
		}
	}
}

void Simulation::Aging() {
	for (int i = 0; i < m_count_creatures; i++) {
		m_creatures[i]->Add_aging();
	}
}

void Simulation::Breed() {
	for (int i = 0; i < m_count_creatures; i++) {
		if ((m_creatures[i]->Breed()) && (m_creatures[i]->Is_Rabbit())) {
			Rabbit a(0, m_creatures[i]->m_x, m_creatures[i]->m_y, m_creatures[i]->m_direction, m_creatures[i]->m_constancy);
			Add_creature(a);
		}
		if ((m_creatures[i]->Breed()) && (!(m_creatures[i]->Is_Rabbit()))) {
			Wolf a(0, m_creatures[i]->m_x, m_creatures[i]->m_y, m_creatures[i]->m_direction, m_creatures[i]->m_constancy);
			Add_creature(a);
		}
	}
}

void Simulation::Die() {
	for (int i = 0; i < m_count_creatures; i++) {
		if (m_creatures[i]->m_dead) {
			Delete_creature(i);
		}
	}
	for (int i = 0; i < m_count_creatures; i++) {
		if (m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] > 0) {
			m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] += 1;
		}
		if (m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] < 0) {
			m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] -= 1;
		}
		if (m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] == 0) {
			m_field[m_creatures[i]->m_x][m_creatures[i]->m_y] = 1;
		}
	}
}

void Simulation::Print(int _num) {
	m_creatures[1];
	for (int i = 0; i < _num; i++) {
		Do_Movements();
		Eat();
		Aging();
		Breed();
		Die();
	}
	for (int i = 0; i < m_n; i++) {
		for (int j = 0; j < m_m; j++) {
			if (m_field[i][j]==0) {
				cout << "#";
			}
			else {
				cout << "m_field[i][j]";
			}
		}
		cout << "/n";
	}
}

Animal::Animal() {
	m_age = 0;
	m_x = 0;
	m_y = 0;
	m_direction = 0;
	m_constancy = 0;
	m_dead = false;
}

Rabbit::Rabbit(){
	m_age = 0;
	m_x = 0;
	m_y = 0;
	m_direction = 0;
	m_constancy = 0;
	m_dead = false;
}
Wolf::Wolf(){
	m_age = 0;
	m_x = 0;
	m_y = 0;
	m_direction = 0;
	m_constancy = 0;
	m_dead = false;
	m_count_rabbits = 0;
	m_hunger = 0;
}
Rabbit::Rabbit(int _age, int _x, int _y, int _direction, int _constancy) {
	m_age = _age;
	m_x = _x;
	m_y = _y;
	m_direction = _direction;
	m_constancy = _constancy;
	m_dead = false;
}
Wolf::Wolf(int _age, int _x, int _y, int _direction, int _constancy){
	m_age = _age;
	m_x = _x;
	m_y = _y;
	m_direction = _direction;
	m_constancy = _constancy;
	m_dead = false;
	m_count_rabbits = 0;
	m_hunger = 0;
}

void Rabbit::Add_aging(){
	m_age += 1;
	if (m_age != 0 && m_age % m_constancy == 0) {
		m_direction = (m_direction + 1) % 4;
	}
	if (m_age >= 10) {
		m_dead = true;
	}
}

void Wolf::Add_aging() {
	m_age += 1;
	if (m_age != 0 && m_age % m_constancy == 0) {
		m_direction = (m_direction + 1) % 4;
	}
	if (m_age >= 15) {
		m_dead = true;
	}
}

void Rabbit::Move() {
	cout << m_dead<<endl;
	if (m_direction == 0) {
		m_x -= 1;
	}
	if (m_direction == 1) {
		m_y += 1;
	}
	if (m_direction == 2) {
		m_x += 1;
	}
	if (m_direction == 3) {
		m_y -= 1;
	}
	cout << m_dead<<endl;
}

void Wolf::Move() {
	if (m_direction == 0) {
		m_x -= 2;
	}
	if (m_direction == 1) {
		m_y += 2;
	}
	if (m_direction == 2) {
		m_x += 2;
	}
	if (m_direction == 3) {
		m_y -= 2;
	}
}

int Rabbit::Breed() {
	if (m_age == 5 || m_age == 10) {
		return 1;
	}
	return 0;
}

int Wolf::Breed() {
	if (m_hunger == 1) {
		m_hunger = 0;
		return 1;
	}
	return 0;
}

void Rabbit::Eat() {
	return;
}

bool Rabbit::Is_Rabbit() {
	return true;
}

bool Wolf::Is_Rabbit() {
	return false;
}

void Wolf::Eat() {
	m_count_rabbits = (m_count_rabbits + 1);
	if (m_count_rabbits == 2) {
		m_hunger = 1;
		m_count_rabbits = 0;
	}
}

bool Rabbit::operator==(Animal& _creature) {
	if (m_x == _creature.m_x && m_y == _creature.m_y) {
		return true;
	}
	return false;
}

bool Wolf::operator==(Animal& _creature) {
	if (m_x == _creature.m_x && m_y == _creature.m_y) {
		return true;
	}
	return false;
}

int main()
{
	int n, m, t,r_c,w_c;
	cin >> n;
	cin >> m;
	cin >> t;
	cin >> r_c;
	cin >> w_c;
	Simulation s(n,m,r_c,w_c);
	s.Print(t);
	return 0;
}
