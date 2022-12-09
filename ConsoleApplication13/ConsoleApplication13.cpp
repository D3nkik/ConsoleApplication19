#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool is_leap_year(int year)
{
    if ((year % 400) == 0) return true; //— высокосный
    if ((year % 100) == 0) return false; //— невысокосный
    if ((year % 4) == 0) return true; // — высокосные
    return false; // — невисокосные
}

void first_weekdays_table()
{
    ofstream file("weekdays.txt", ios_base::out);
    int weekday = 3;
    for (int i = 1801; i <= 3000; ++i)
    {
        file << weekday;
        if ((i % 100) != 0)
        {
            file << " ";
        }
        else
        {
            file << endl;
        }
        weekday += is_leap_year(i) ? 2 : 1;
        weekday %= 7;
    }

    file.close();
}

int get_weekday(int year, int month, int day)
{
    int weekdays[] = { 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 0, 1, 2, 4, 5, 6, 0, 2, 3, 4, 5 };
    //Последовательность дней недели на первое января в двадцативосьмилетнем цикле
    int shift_not_leap[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };//таблица смещений дней недели на первое число каждого месяца для невисокосного года
    int shift_leap[] = { 0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 }; //таблица смещений дней недели на первое число каждого месяца для высокосного
   
    bool a = is_leap_year(year);

    year -= 1;
    year %= 400;

    int century = year / 100;
    year %= 100;
    int index = (year + (4 * century)) % 28;
    int weekday = weekdays[index];
    weekday += a ? shift_leap[month - 1]
        : shift_not_leap[month - 1];
    weekday += (day - 1);
    weekday %= 7;
    return weekday;
}

int get_weekday_x(int year, int month, int day)
{
    int weekdays[] = { 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 0, 1, 2, 4, 5, 6, 0, 2, 3, 4, 5 };
    int shifts[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

    bool is_leap = is_leap_year(year);

    year -= 1;
    year %= 400;

    int century = year / 100;
    year %= 100;
    int index = (year + (4 * century)) % 28;
    int weekday = weekdays[index];
    int shift = shifts[month - 1];
    if (is_leap and (month > 2))
    {
        shift += 1;
        shift %= 7;
    };

    weekday += shift + (day - 1);
    weekday %= 7;

    return weekday;
}

int get_weekday_c(int year, int month, int day)
{
    int shifts[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

    int shift = shifts[month - 1];

    if (is_leap_year(year) and (month > 2))
    {
        shift += 1;
    };
    year = (year - 1) % 400;
    int century = year / 100;
    int index = ((4 * century) + (year % 100)) % 28;
    int weekday = (index + (index / 4)) + shift + (day - 1);

    return (weekday % 7);
}

void print_weekday_name(int weekday)
{
    string dni_nedeli[] = { "Понедельник","Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье", };
    cout << dni_nedeli[weekday] << endl;
}

void pervich_vopros()
{
    int year, month, day;
   
    while (true)
    {
      
        cout << "Введите дату" << endl;
        cin >> day;
        cout << "Введите месяц" << endl;
        cin >> month;
        cout << "Введите год" << endl;
        cin >> year;

        if (day == 31 && month != 1 && month != 3 && month != 5 && month != 7 && month != 8 && month != 10 && month != 12) {
            cout << "Перебор дней" << endl;
            break;
        }
        if (day == 30 && month != 4 && month != 6 && month != 9 && month != 11) {
            cout << "Перебор дней" << endl;
            break;
        }
        if (day == 29 && month != 2) {
            cout<< "Перебор дней" <<endl;
            break;
        }
        if (month > 12) {
            cout << "Всего 12 месяцев";
            break;
        }
        if ((year > 0) and (month > 0) and (month <= 12) and (day > 0))
        {
            print_weekday_name(get_weekday_c(year, month, day));
            break;
        }






        else
        {
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    pervich_vopros();
    return 0;
}






























/*#include <iostream>
using namespace std;

int main()
{
	
	setlocale(LC_ALL, "Russian");
	int a[12] = { 1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 };
	int date = 0, month = 0, year = 0, b = 0, z = 0,c = 0, e = 0;
	cout << "Введите дату" << endl;
	cin >> date ;
	cout << "Введите месяц" << endl;
	cin >> month;
	cout << "Введите год" << endl;
	cin >> year;
	b = year % 100;
	z = date + b + (b/4) + a[month - 1];
	c = z % 7;

	if (year >= 1600 && year <= 1699) {
		e = c + 5;
	}
	 else if (year >= 1700 && year <= 1799) {
		e = c + 3;
	}
	else if (year >= 1800 && year <= 1899) {
		e = c + 1;
	}
	else if (year >= 1900 && year <= 1999) {      //В зависемости от века, пребовляем или отнимае код века
		e = c;
	}
	else if (year >= 2000 && year <= 2099) {
		e = c - 1;
	}
	else if (year >= 2100 && year <= 2199) {
		e = c - 3;
	}
	else if (year >= 2200 && year <= 2299) {
		e = c - 5;
	}
	cout << e << endl;

	if (e < 0) {
		e = e + 7;

	}

	if (e == 0) {
		cout << "Суббота";
	}
	if (e == 1) {
		cout << "Воскресенье";
	}
	if (e == 2) {
		cout << "Понедельник";
	}
	if (e == 3) {
		cout << "Вторник";
	}
	if (e == 4) {
		cout << "Среда";
	}
	if (e == 5) {
		cout << "Четверг";
	}
	if (e == 6 ) {
		cout << "Пятница";
	}
}*/