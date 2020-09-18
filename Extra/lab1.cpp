#include <iostream>

using namespace std;

class FazzyNumber {
public:
	FazzyNumber(const double& x = 0, const double& e = 0) {
		x_ = x;
		e_ = e;
	}

	double left() const {
		return x_ - e_;
	}

	double num() const {
		return x_;
	}

	double& num() {
		return x_;
	}

	double right() const {
		return x_ + e_;
	}

	double epsilon() const {
		return e_;
	}

	double& epsilon() {
		return e_;
	}

private:
	double x_;
	double e_;
};

FazzyNumber operator+(const FazzyNumber& lhs, const FazzyNumber& rhs) {
	return { lhs.num() + rhs.num(), lhs.epsilon() + rhs.epsilon() };
}//(A+B)+(a+b)

FazzyNumber operator-(const FazzyNumber& lhs, const FazzyNumber& rhs) {
	return { lhs.num() - rhs.num(), lhs.epsilon() + rhs.epsilon() };
}//(A-B)+(a+b)

FazzyNumber operator*(const FazzyNumber& lhs, const FazzyNumber& rhs) {
	return { lhs.num() * rhs.num(), lhs.num() * rhs.epsilon() + lhs.epsilon() * rhs.num() + lhs.epsilon() * rhs.epsilon() };
}//(A*B)+(A*b+B*A*a*b)

void IsPositiveCheck(const FazzyNumber& fazzyNumber) {
	if (fazzyNumber.left() <= 0) {
		throw runtime_error("Делитель меньше или равен 0");
	}
}

FazzyNumber operator/(const FazzyNumber& lhs, const FazzyNumber& rhs) {
	IsPositiveCheck(rhs);
	double right = (lhs.num() + lhs.epsilon()) / (rhs.num() - rhs.epsilon());
	double num = lhs.num() / rhs.num();
	return { num, right - num };
}//(A+a)/(B-b) -> (A/B)+(...)

FazzyNumber operator/(const double& lhs, const FazzyNumber& rhs) {
	IsPositiveCheck(rhs);
	double right = lhs / (rhs.num() - rhs.epsilon());
	double num = lhs / rhs.num();
	return { num, right - num };
}

ostream& operator<<(ostream& output, const FazzyNumber& fuzzyNumber) {
	output << "(" << fuzzyNumber.left() << ", " << fuzzyNumber.num() << ", " << fuzzyNumber.right() << ")";
	return output;
}

istream& operator>>(istream& input, FazzyNumber& fuzzyNumber) {
	input >> fuzzyNumber.num() >> fuzzyNumber.epsilon();
	return input;
}

int main() {
	try {
		/*FazzyNumber a(2, 3);
		FazzyNumber b(1, 1);*/
		FazzyNumber a;
		FazzyNumber b;
		cin >> a >> b;
		cout << a << " " << b << "\n";
		cout << "Test+: " << a + b << "\n";
		cout << "Test-: " << a - b << "\n";
		cout << "Test*: " << a * b << "\n";
		cout << "Test/: " << a / b << "\n";
		cout << "Test1/: " << 1 / a << "\n";
	}
	catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}

// ./a.out <<file
// сделать ввод из файла