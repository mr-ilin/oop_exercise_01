#include <iostream>

using namespace std;

class Pair {
public:
	Pair(const int& left = 0, const int& right = 0) {
		left_ = left;
		right_ = right;
	}

	int left() const {
		return left_;
	}

	int& left() {
		return left_;
	}

	int right() const {
		return right_;
	}

	int& right() {
		return right_;
	}

private:
	int left_;
	int right_;
};

Pair operator+(const Pair& lhs, const Pair& rhs) {
	return { lhs.left() + rhs.left(), lhs.right() + rhs.right() };
}

void Print(const Pair& p) {
	cout << p.left() << " " << p.right() << endl;
}

ostream& operator<<(ostream& output, const Pair& p) {
	output << "(" << p.left() << ", " << p.right() << ")";
	return output;
}

istream& operator>>(istream& input, Pair& p) {
	input >> p.left() >> p.right();
	return input;
}

//  Создать класс vector3D, задаваемый тройкой координат. Обязательно должны быть реализованы: операции сложения и вычитания векторов, векторное произведение векторов, скалярное произведение векторов, умножения на скаляр, сравнение векторов на совпадение, вычисление длины вектора, сравнение длины векторов, вычисление угла между векторами.
//

int main() {
	Pair p(1);
	Print(p);

	p.left() = 4;
	p.right() = 10;
	Print(p);

	Pair a(4, 5);
	Pair b(1, 2);
	Print(a + b);

	cout << p << " " << a << " " << b;

	try {
		throw 1;
		throw runtime_error("Текст ошибки");
	}
	catch (exception& ex) {
		cerr << ex.what() << endl;//выводим текст ошибки
	}
	catch (runtime_error& er) {
		//ловим конкретный тип ошибки
	}
	catch (int n) {
		//ловим числовую ошибку
	}
	catch (...) {
		//ловим все, что не поймали
	}

	return 0;
}
