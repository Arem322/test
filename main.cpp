#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	int i, j, random, Kk, Knum, choice, N = 4, buscount = 0, bustime = 0, comtime = 0;
	float Pnn, Krr;
	bool bus = true;
	int** proc;
	bool **coms;
	int mas[] = {0, 0, 0, 0};
	int masw[] = {0, 0, 0, 0};
	int commasw[4][4] = { {0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0} };
	int pbustime[] = {0, 0, 0, 0};
	int pcomtime[] = { 0, 0, 0, 0 };
	bool com[] = { true, true, true, true };
	bool busmas[] = { false, false, false, false };
	bool didwork[] = { false, false, false, false };
	bool commas[4][4] = { {false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false} };
	float Pn[] = { 0.9, 0.7 };
	float Kr[] = { 0.9, 0.8, 0.6 };
	int K[] = { 2, 5, 10 };
	cout << "За честь и отвагу!\nКоличество процессоров и блоков памяти: 4\nВведите данные для работы программы:\nДоступные вероятности Pn:\n";
	for (i = 0; i < 2; i++)
		cout << i + 1 << ")" << Pn[i] << endl;
	cout << "Выберите вероятность Pn: ";
	cin >> choice;
	Pnn = Pn[choice - 1];
	cout << "\nДоступные вероятности Kr:\n";
	for(i = 0; i < 3; i++)
		cout << i + 1 << ")" << Kr[i] << endl;
	cout << "Выберите вероятность Kr: ";
	cin >> choice;
	Krr = Kr[choice - 1];
	cout << "\nДоступные значения единиц времени K:\n";
	for (i = 0; i < 3; i++)
		cout << i + 1 << ")" << K[i] << endl; 
	cout << "Выберите K: ";
	cin >> choice;
	Kk = K[choice - 1];
	cout << "\nВведите количество команд в программе: ";
	cin >> Knum; 
	int queue[] = { Kk, Kk, Kk, Kk };
	
	system("cls");
	cout << "Данные, которые будут использованы:\nКоличество процессоров и блоков памяти : 4\nВероятность Pn: " << Pnn << "\nВероятность Kr: " << Krr << "\nЗначение K: " << Kk << "\nКоличество команд в программе: " << Knum << endl;
	system("pause");
	coms = new bool * [N];
	for (i = 0; i < N; i++)
		coms[i] = new bool[Knum];
	for(i = 0; i < N; i++)
		for (j = 0; j < Knum; j++)
		{
			random = rand() % 10 + 1;
			if (random <= Krr * 10)
				coms[i][j] = 0;
			else
				coms[i][j] = 1;
		}
	proc = new int* [N];
	for (i = 0; i < N; i++)
		proc[i] = new int[Knum];
	for(i = 0; i < N; i++)
		for (j = 0; j < Knum; j++)
		{
			random = rand() % 10 + 1;
			if (coms[i][j] == 0)
				proc[i][j] = 0;
			else
			{
				if (random <= Pnn * 10)
					proc[i][j] = i + 1;
				else
				{
					if (Pnn == 0.7)
					{
						if (i == 0)
							proc[i][j] = 10 - random + 2;
						if (i == 1)
						{
							if (10 - random == 0)
								proc[i][j] = 10 - random + 1;
							else
								proc[i][j] = 10 - random + 2;
						}
						if (i == 2)
						{
							if (10 - random == 2)
								proc[i][j] = 10 - random + 2;
							else
								proc[i][j] = 10 - random + 1;
						}
						if (i == 3)
							proc[i][j] = 10 - random + 1;
					}
					else
					{
						if (i == 0)
							proc[i][j] = rand() % 3 + 2;
						if (i == 1)
						{
							random = rand() % 3 + 1;
							if (random == 1)
								proc[i][j] = random;
							else
								proc[i][j] = random + 1;
						}
						if (i == 2)
						{
							random = rand() % 3 + 1;
							if (random == 3)
								proc[i][j] = random + 1;
							else
								proc[i][j] = random;
						}
						if (i == 3)
							proc[i][j] = rand() % 3 + 1;

					}
				}
			}
		}

	for (i = 0; i < N; i++)
	{
		cout << "\nКоманды " << i + 1 << "-го процессора: ";
		for (j = 0; j < Knum; j++)
			cout << coms[i][j] << " ";
	}
	cout << "\n0 - Команда не требует обращения к памяти; 1 - Требует;\n";

	for (i = 0; i < N; i++)
	{
		cout << "\nРасположение команд " << i + 1 << "-го процессора по блокам памяти: ";
		for (j = 0; j < Knum; j++)
			cout << proc[i][j] << " ";
	}
	cout << "\n0 - Команда не требует обращения к памяти\n";
	system("pause");

	while (mas[0] < Knum || mas[1] < Knum || mas[2] < Knum || mas[3] < Knum)
	{
		if (mas[0] < Knum)
		{
			if (coms[0][mas[0]] == 0)
				mas[0]++;
			else
			{
				if (busmas[1] == false && busmas[2] == false && busmas[3] == false && masw[0] >= masw[1] && masw[0] >= masw[2] && masw[0] >= masw[3])
				{
					if (queue[0] == Kk)
						busmas[0] = true;
					queue[0]--;
					if (queue[0] == 0)
					{
						mas[0]++;
						masw[0] = 0;
						bus = false;
						queue[0] = Kk;
					}
					
				}
				masw[0]++;
			}
			if (mas[0] == Knum)
				pbustime[0] = bustime + 1;
		}

		if (mas[1] < Knum)
		{
			if (coms[1][mas[1]] == 0)
				mas[1]++;
			else
			{
				if (busmas[0] == false && busmas[2] == false && busmas[3] == false && masw[1] >= masw[0] && masw[1] >= masw[2] && masw[1] >= masw[3])
				{
					if (queue[1] == Kk)
						busmas[1] = true;
					queue[1]--;
					if (queue[1] == 0)
					{
						mas[1]++;
						masw[1] = 0;
						bus = false;
						queue[1] = Kk;
					}
					
				}
				masw[1]++;
			}
			if (mas[1] == Knum)
				pbustime[1] = bustime + 1;
		}

		if (mas[2] < Knum)
		{
			if (coms[2][mas[2]] == 0)
				mas[2]++;
			else
			{
				if (busmas[0] == false && busmas[1] == false && busmas[3] == false && masw[2] >= masw[0] && masw[2] >= masw[1] && masw[2] >= masw[3])
				{
					if (queue[2] == Kk)
						busmas[2] = true;
					queue[2]--;
					if (queue[2] == 0)
					{
						mas[2]++;
						masw[2] = 0;
						bus = false;
						queue[2] = Kk;
					}
					
				}
				masw[2]++;
			}
			if (mas[2] == Knum)
				pbustime[2] = bustime + 1;
		}

		if (mas[3] < Knum)
		{
			if (coms[3][mas[3]] == 0)
				mas[3]++;
			else
			{
				if (busmas[0] == false && busmas[1] == false && busmas[2] == false && masw[3] >= masw[0] && masw[3] >= masw[1] && masw[3] >= masw[2])
				{
					if (queue[3] == Kk)
						busmas[3] = true;
					queue[3]--;
					if (queue[3] == 0)
					{
						mas[3]++;
						masw[3] = 0;
						bus = false;
						queue[3] = Kk;
					}
					
				}
				masw[3]++;
			}
			if (mas[3] == Knum)
				pbustime[3] = bustime + 1;
		}

		if (bus == false)
		{
			busmas[0] = false; 
			busmas[1] = false; 
			busmas[2] = false; 
			busmas[3] = false; 
			bus = true;
		}

		bustime++;
	}

	mas[0] = 0;
	mas[1] = 0;
	mas[2] = 0;
	mas[3] = 0;  

	while (mas[0] < Knum || mas[1] < Knum || mas[2] < Knum || mas[3] < Knum)
	{
		if (mas[0] < Knum)
		{
			if (proc[0][mas[0]] == 0)
				mas[0]++;
			else
			{
				if (proc[0][mas[0]] == 1)
				{
					commasw[0][0]++;
					if (commas[0][1] == false && commas[0][2] == false && commas[0][3] == false && commasw[0][0] >= commasw[0][1] && commasw[0][0] >= commasw[0][2] && commasw[0][0] >= commasw[0][3])
					{
						if (queue[0] == Kk)
							commas[0][0] = true;
						queue[0]--;
						if (queue[0] == 0)
						{
							mas[0]++;
							commasw[0][0] = 0;
						    com[0] = false;
							queue[0] = Kk;
						}

					}
					
					didwork[0] = true;
				}
				if (proc[0][mas[0]] == 2 && didwork[0] == false)
				{
					commasw[1][0]++;
					if (commas[1][1] == false && commas[1][2] == false && commas[1][3] == false && commasw[1][0] >= commasw[1][1] && commasw[1][0] >= commasw[1][2] && commasw[1][0] >= commasw[1][3])
					{
						if (queue[0] == Kk)
							commas[1][0] = true;
						queue[0]--;
						if (queue[0] == 0)
						{
							mas[0]++;
							commasw[1][0] = 0;
							com[1] = false;
							queue[0] = Kk;
						}
					}
					
					didwork[0] = true;
				}
				if (proc[0][mas[0]] == 3 && didwork[0] == false)
				{
					commasw[2][0]++;
					if (commas[2][1] == false && commas[2][2] == false && commas[2][3] == false && commasw[2][0] >= commasw[2][1] && commasw[2][0] >= commasw[2][2] && commasw[2][0] >= commasw[2][3])
					{
						if (queue[0] == Kk)
							commas[2][0] = true;
						queue[0]--;
						if (queue[0] == 0)
						{
							mas[0]++;
							commasw[2][0] = 0;
							com[2] = false;
							queue[0] = Kk;
						}
					}
					
					didwork[0] = true;
				}
				if (proc[0][mas[0]] == 4 && didwork[0] == false)
				{
					commasw[3][0]++;
					if (commas[3][1] == false && commas[3][2] == false && commas[3][3] == false && commasw[3][0] >= commasw[3][1] && commasw[3][0] >= commasw[3][2] && commasw[3][0] >= commasw[3][3])
					{
						if (queue[0] == Kk)
							commas[3][0] = true;
						queue[0]--;
						if (queue[0] == 0)
						{
							mas[0]++;
							commasw[3][0] = 0;
							com[3] = false;
							queue[0] = Kk;
						}
					}
					
				}
				didwork[0] = false;
				
			}
			if (mas[0] == Knum)
				pcomtime[0] = comtime + 1;
		}

		if (mas[1] < Knum)
		{
			if (proc[1][mas[1]] == 0)
				mas[1]++;
			else
			{
				if (proc[1][mas[1]] == 1)
				{
					commasw[0][1]++;
					if (commas[0][0] == false && commas[0][2] == false && commas[0][3] == false && commasw[0][1] >= commasw[0][0] && commasw[0][1] >= commasw[0][2] && commasw[0][1] >= commasw[0][3])
					{
						if (queue[1] == Kk)
							commas[0][1] = true;
						queue[1]--;
						if (queue[1] == 0)
						{
							mas[1]++;
							commasw[0][1] = 0;
							com[0] = false;
							queue[1] = Kk;
						}

					}
					
					didwork[1] = true;
				}
				if (proc[1][mas[1]] == 2 && didwork[1] == false)
				{
					commasw[1][1]++;
					if (commas[1][0] == false && commas[1][2] == false && commas[1][3] == false && commasw[1][1] >= commasw[1][0] && commasw[1][1] >= commasw[1][2] && commasw[1][1] >= commasw[1][3])
					{
						if (queue[1] == Kk)
							commas[1][1] = true;
						queue[1]--;
						if (queue[1] == 0)
						{
							mas[1]++;
							commasw[1][1] = 0;
							com[1] = false;
							queue[1] = Kk;
						}

					}
					didwork[1] = true;
				}
				if (proc[1][mas[1]] == 3 && didwork[1] == false)
				{
					commasw[2][1]++;
					if (commas[2][0] == false && commas[2][2] == false && commas[2][3] == false && commasw[2][1] >= commasw[2][0] && commasw[2][1] >= commasw[2][2] && commasw[2][1] >= commasw[2][3])
					{
						if (queue[1] == Kk)
							commas[2][1] = true;
						queue[1]--;
						if (queue[1] == 0)
						{
							mas[1]++;
							commasw[2][1] = 0;
							com[2] = false;
							queue[1] = Kk;
						}

					}
					
					didwork[1] = true;
				}
				if (proc[1][mas[1]] == 4 && didwork[1] == false)
				{
					commasw[3][1]++;
					if (commas[3][0] == false && commas[3][2] == false && commas[3][3] == false && commasw[3][1] >= commasw[3][0] && commasw[3][1] >= commasw[3][2] && commasw[3][1] >= commasw[3][3])
					{
						if (queue[1] == Kk)
							commas[3][1] = true;
						queue[1]--;
						if (queue[1] == 0)
						{
							mas[1]++;
							commasw[3][1] = 0;
							com[3] = false;
							queue[1] = Kk;
						}

					}
					
				}
				didwork[1] = false;
			}
			if (mas[1] == Knum)
				pcomtime[1] = comtime + 1;
		}

		if (mas[2] < Knum)
		{
			if (proc[2][mas[2]] == 0)
				mas[2]++;
			else
			{
				if (proc[2][mas[2]] == 1)
				{
					if (commas[0][0] == false && commas[0][1] == false && commas[0][3] == false && commasw[0][2] >= commasw[0][0] && commasw[0][2] >= commasw[0][1] && commasw[0][2] >= commasw[0][3])
					{
						commasw[0][2]++;
						if (queue[2] == Kk)
							commas[0][2] = true;
						queue[2]--;
						if (queue[2] == 0)
						{
							mas[2]++;
							commasw[0][2] = 0;
							com[0] = false;
							queue[2] = Kk;
						}

					}
					didwork[2] = true;
				}
				if (proc[2][mas[2]] == 2 && didwork[2] == false)
				{
					commasw[1][2]++;
					if (commas[1][0] == false && commas[1][1] == false && commas[1][3] == false && commasw[1][2] >= commasw[1][0] && commasw[1][2] >= commasw[1][1] && commasw[1][2] >= commasw[1][3])
					{
						if (queue[2] == Kk)
							commas[1][2] = true;
						queue[2]--;
						if (queue[2] == 0)
						{
							mas[2]++;
							commasw[1][2] = 0;
							com[1] = false;
							queue[2] = Kk;
						}

					}
					didwork[2] = true;
				}
				if (proc[2][mas[2]] == 3 && didwork[2] == false)
				{
					commasw[2][2]++;
					if (commas[2][0] == false && commas[2][1] == false && commas[2][3] == false && commasw[2][2] >= commasw[2][0] && commasw[2][2] >= commasw[2][1] && commasw[2][2] >= commasw[2][3])
					{
						if (queue[2] == Kk)
							commas[2][2] = true;
						queue[2]--;
						if (queue[2] == 0)
						{
							mas[2]++;
							commasw[2][2] = 0;
							com[2] = false;
							queue[2] = Kk;
						}

					}
					didwork[2] = true;
				}
				if (proc[2][mas[2]] == 4 && didwork[2] == false)
				{
					commasw[3][2]++;
					if (commas[3][0] == false && commas[3][1] == false && commas[3][3] == false && commasw[3][2] >= commasw[3][0] && commasw[3][2] >= commasw[3][1] && commasw[3][2] >= commasw[3][3])
					{
						if (queue[2] == Kk)
							commas[3][2] = true;
						queue[2]--;
						if (queue[2] == 0)
						{
							mas[2]++;
							commasw[3][2] = 0;
							com[3] = false;
							queue[2] = Kk;
						}

					}
					
				}
				didwork[2] = false;
			}
			if (mas[2] == Knum)
				pcomtime[2] = comtime + 1;
		}

		if (mas[3] < Knum)
		{
			if (proc[3][mas[3]] == 0)
				mas[3]++;
			else
			{
				if (proc[3][mas[3]] == 1)
				{
					commasw[0][3]++;
					if (commas[0][0] == false && commas[0][1] == false && commas[0][2] == false && commasw[0][3] >= commasw[0][0] && commasw[0][3] >= commasw[0][1] && commasw[0][3] >= commasw[0][2])
					{
						if (queue[3] == Kk)
							commas[0][3] = true;
						queue[3]--;
						if (queue[3] == 0)
						{
							mas[3]++;
							commasw[0][3] = 0;
							com[0] = false;
							queue[3] = Kk;
						}

					}
					didwork[3] = true;
				}
				if (proc[3][mas[3]] == 2 && didwork[3] == false)
				{
					commasw[1][3]++;
					if (commas[1][0] == false && commas[1][1] == false && commas[1][2] == false && commasw[1][3] >= commasw[1][0] && commasw[1][3] >= commasw[1][1] && commasw[1][3] >= commasw[1][2])
					{
						if (queue[3] == Kk)
							commas[1][3] = true;
						queue[3]--;
						if (queue[3] == 0)
						{
							mas[3]++;
							commasw[1][3] = 0;
							com[1] = false;
							queue[3] = Kk;
						}

					}
					
					didwork[3] = true;
				}
				if (proc[3][mas[3]] == 3 && didwork[3] == false)
				{

					commasw[2][3]++;
					if (commas[2][0] == false && commas[2][1] == false && commas[2][2] == false && commasw[2][3] >= commasw[2][0] && commasw[2][3] >= commasw[2][1] && commasw[2][3] >= commasw[2][2])
					{
						if (queue[3] == Kk)
							commas[2][3] = true;
						queue[3]--;
						if (queue[3] == 0)
						{
							mas[3]++;
							commasw[2][3] = 0;
							com[2] = false;
							queue[3] = Kk;
						}

					}
					didwork[3] = true;
				}
				if (proc[3][mas[3]] == 4 && didwork[3] == false)
				{

					commasw[3][3]++;
					if (commas[3][0] == false && commas[3][1] == false && commas[3][2] == false && commasw[3][3] >= commasw[3][0] && commasw[3][3] >= commasw[3][1] && commasw[3][3] >= commasw[3][2])
					{
						if (queue[3] == Kk)
							commas[3][3] = true;
						queue[3]--;
						if (queue[3] == 0)
						{
							mas[3]++;
							commasw[3][3] = 0;
							com[3] = false;
							queue[3] = Kk;
						}

					}
					
				}
				didwork[3] = false;
			}
			if (mas[3] == Knum)
				pcomtime[3] = comtime + 1;
		}

		if (com[0] == false)
		{
			commas[0][0] = false;
			commas[0][1] = false;
			commas[0][2] = false;
			commas[0][3] = false;
			com[0] = true;
		}

		if (com[1] == false)
		{
			commas[1][0] = false;
			commas[1][1] = false;
			commas[1][2] = false;
			commas[1][3] = false;
			com[1] = true;
		}

		if (com[2] == false)
		{
			commas[2][0] = false;
			commas[2][1] = false;
			commas[2][2] = false;
			commas[2][3] = false;
			com[2] = true;
		}

		if (com[3] == false)
		{
			commas[3][0] = false;
			commas[3][1] = false;
			commas[3][2] = false;
			commas[3][3] = false;
			com[3] = true;
		}

		comtime++;
	}

	cout << "\n\nРезультаты симуляции системы с общей шиной:\n";
	
	for (i = 0; i < 4; i++)
	{
		cout << "Время работы " << i + 1 << "-го процессора: " << pbustime[i] << endl;
	}
	cout << "Общее время работы системы с общей шиной для " << Knum << " команд: " << bustime << endl << endl;

	cout << "Результаты симуляции системы на коммутаторе:\n";

	for (i = 0; i < 4; i++)
	{
		cout << "Время работы " << i + 1 << "-го процессора: " << pcomtime[i] << endl;
	}

	cout << "Общее время работы системы на коммутаторе для " << Knum << " команд: " << comtime << endl << endl;


	for (i = 0; i < N; i++)
	{
		delete[] coms[i];
		delete[] proc[i];
	}	
	delete[] coms;
	delete[] proc;

	return 0;
}