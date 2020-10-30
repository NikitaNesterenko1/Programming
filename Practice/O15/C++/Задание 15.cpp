#include<iostream>;
#include<ctime>;
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int k, mb, n = rand() % 101;
	for (int i = 0; i < 5;)
	{
		cout << "Введите предполагаемое число от 0 до 100: ";
		cin >> mb;
		while (isalpha(mb))
			cin >> mb;
		if (mb == n)
		{
			cout << "Поздравляю! Вы угадали " << endl;
			cout << "Хотите начать сначала ? (1 - ДА)";
			cin >> k;
			if (k == 1)
			{
				return main();
			}
			else return(0);
		}
		else if (mb <= n)
		{
			if (i == 4)
				break;
			else
				cout << "Загаданное число больше" << endl;
		}
		else if (mb >= n)
		{
			if (i == 4)
				break;
			else
				cout << "Загаданное число меньше" << endl;
		}
		i++;

	}
	cout << "Вы проиграли. Было загадано: " << n << endl;
	cout << "Хотите начать сначала ? (1 - ДА): ";
	cin >> k;
	if (k == 1)
	{
		return main();
	}
	else return(0);

}