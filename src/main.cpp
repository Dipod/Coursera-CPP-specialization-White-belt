/*
 Вспомним класс Rational, который мы реализовали в задачах, посвящённых перегрузке операторов.
 Там специально говорилось, что в тестах объекты класса Rational никогда не создаются с нулевым знаменателем и никогда не выполняется деление на ноль.
 Настало время избавиться от этого ограничения и научиться обрабатывать нулевой знаменатель и деление на ноль. В этой задаче вам предстоит это сделать.

 Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал исключение invalid_argument, если знаменатель равен нулю.
 Кроме того, переделайте реализацию оператора деления для класса Rational так, чтобы он выбрасывал исключение domain_error, если делитель равен нулю.

 Напомним, что вам надо реализовать интерфейс

 class Rational {
 public:
 Rational();
 Rational(int numerator, int denominator);

 int Numerator() const;
 int Denominator() const;
 };

 и оператор деления для класса Rational

 Rational operator / (const Rational& lhs, const Rational& rhs);

 Так же, как и в задачах на перегрузку операторов, вам будет предложен файл с заготовкой кода.
 Функция main в этом файле содержит ряд юнит-тестов, которые позволят вам проверить свою реализацию.
 При проверке вашего решения оно будет тестироваться на более полном наборе тестов,
 так что успешное прохождение всех юнит-тестов не гарантирует, что ваша реализация будет зачтена.

 Шаблон программы:

 #include <iostream>
 #include <exception>
 using namespace std;

 class Rational {
 // Вставьте сюда реализацию класса Rational
 };

 // Вставьте сюда реализацию operator / для класса Rational

 int main() {
 try {
 Rational r(1, 0);
 cout << "Doesn't throw in case of zero denominator" << endl;
 return 1;
 } catch (invalid_argument&) {
 }

 try {
 auto x = Rational(1, 2) / Rational(0, 1);
 cout << "Doesn't throw in case of division by zero" << endl;
 return 2;
 } catch (domain_error&) {
 }

 cout << "OK" << endl;
 return 0;
 }

 */

#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>

using namespace std;

int lcm(const int &first, const int &second) {
	return (first / __gcd(first, second)) * second;
}

class Rational {
public:
	Rational() {
		m_numerator = 0;
		m_denominator = 1;
	}

	Rational(const int &numerator, const int &denominator) {
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");
		}
		if (numerator == 0) {
			m_numerator = 0;
			m_denominator = 1;
			return;
		}

		int divisor = __gcd(numerator, denominator);
		m_numerator = numerator / divisor;
		m_denominator = denominator / divisor;

		if (m_denominator < 0) {
			m_numerator = -m_numerator;
			m_denominator = -m_denominator;
		}
	}

	int Numerator() const {
		return m_numerator;
	}

	int Denominator() const {
		return m_denominator;
	}

private:
	int m_numerator;
	int m_denominator;
};

bool operator==(const Rational &lhs, const Rational &rhs) {
	return (lhs.Numerator() == rhs.Numerator()
			&& lhs.Denominator() == rhs.Denominator());
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
	} else {
		int new_denominator = lcm(lhs.Denominator(), rhs.Denominator());
		int new_numerator = (new_denominator / lhs.Denominator())
				* lhs.Numerator()
				+ (new_denominator / rhs.Denominator()) * rhs.Numerator();
		return Rational(new_numerator, new_denominator);
	}
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
	} else {
		int new_denominator = lcm(lhs.Denominator(), rhs.Denominator());
		int new_numerator = (new_denominator / lhs.Denominator())
				* lhs.Numerator()
				- (new_denominator / rhs.Denominator()) * rhs.Numerator();
		return Rational(new_numerator, new_denominator);
	}
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}

	return Rational(lhs.Numerator() * rhs.Denominator(),
			lhs.Denominator() * rhs.Numerator());
}

istream& operator>>(istream &stream, Rational &fraction) {
	int numerator = fraction.Numerator(), denominator = fraction.Denominator();
	char separator = ' ';

	stream >> numerator >> separator >> denominator;

	if (!stream.fail() && separator == '/') {
		fraction = Rational(numerator, denominator);
	}

	return stream;
}

ostream& operator<<(ostream &stream, const Rational &fraction) {
	stream << fraction.Numerator() << '/' << fraction.Denominator();
	return stream;
}

bool operator<(const Rational &lhs, const Rational &rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() < rhs.Numerator();
	} else {
		int new_denominator = lcm(lhs.Denominator(), rhs.Denominator());
		return (new_denominator / lhs.Denominator()) * lhs.Numerator()
				< (new_denominator / rhs.Denominator()) * rhs.Numerator();
	}
}

int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	} catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	} catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}
