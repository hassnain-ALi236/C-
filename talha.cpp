#include<iostream>
#include<time.h>   //change random every time
#include<fstream>
#include<ctime>
#define RED  "\033[31m"   //colour code
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define reset "\033[0m"
using namespace std;
time_t start_time;
void  pattern();      //All void function 
void num(int i);
void timer();
void logic1();
void logic2();
void logic3();
void easy(int score);
void normal(int score);
void hard(int score);
void easyhighestset();
void normalhighestset();
void hardhighestset();
int Ehighest = 0, Ehighestid = 0;            
int  Nhighest = 0, Nhighestid = 0;
int Hhighest = 0, Hhighestid = 0;
int Eidlogin, Nidlogin, Hidlogin;
int score;
int over = 60;
int main()
{

	easyhighestset();
	normalhighestset();
	hardhighestset();

	cout << RED << "!------------Minesweper----------!" << reset << endl;
	

	int choice;
	cout << "Press 1 for Easy\n";            // User Choice
	cout << "Press 2 for Normal\n";
	cout << "Press 3 for Difficult\n";
	cout << "Please Enter Your Choice=";
	cin >> choice;
	num(choice);                               // Go to num void function 
	system("pause");
	return 0;
}
void timer()
{
	time_t end_time = time(0);
	int elapsed_time = static_cast<int>(end_time - start_time);
	int t = elapsed_time;
	if (t > over)
	{
		cout << "Game over,Time over";
		exit(0);
	}
	cout << " Time: " << elapsed_time << " seconds" << endl; 
}
void  pattern()          //   print pattern
{
	cout << RED;
	const int row = 9;
	const int colume = 9;
	cout << endl;
	for (int i = 0;i < colume;i++)
	{
		if (i == 0)
		{
			cout << "\t";
		}
		cout << "[" << i << "]  ";
	}
	cout << endl;
	cout << "____________________________________________________";
	cout << reset;
	cout << endl;
	for (int i = 0;i < row;i++)
	{
		cout << RED;
		cout << i << "|\t";
		cout << reset;

		for (int j = 0;j < colume;j++)
		{
			cout << "[0" << "]  ";
		}
		cout << endl;
	}


}
void num(int i)         // Three  Stages
{
	if (i == 1)
	{
		cout << RED << "Rank 1" << reset << endl;                                      // No 1 player score and id in Easy 
		cout << BLUE << "Rollno            " << Ehighestid << reset << endl;
		cout << BLUE << "Hihgest score     " << Ehighest  << reset << endl;
		cout << "please Login Your ID = ";
		cin >> Eidlogin;
		pattern();            // Draw Pattern
		logic1();             // Go to logic 1
	}
	else if (i == 2)
	{
		cout << RED << "Rank 1" << reset << endl;                                      //  No 1 player score and id in Normal                 
		cout << BLUE<<"Rollno               2" << Nhighestid <<reset<< endl;
		cout << BLUE<<"Hihgest score        " << Nhighest <<reset<< endl;
		cout << "please Login Your ID = ";
		cin >> Nidlogin;
		pattern();				// Draw Pattern
		logic2();               // Go to logic 2
	}
	else if (i == 3)
	{
		cout << RED << "Rank 1" << reset << endl;                                       // No 1 Player Score and id in Hard
		cout << BLUE<<"Rollno               " << Hhighestid <<reset<< endl;
		cout << BLUE<<"Hihgest score        " << Hhighest <<reset<< endl;
		cout << "please Login Your ID = ";
		cin >> Hidlogin;
		pattern();              // Draw Pattern
		logic3();               // Go to Logic 3
	}
}

void logic1()                                            // same as logic 1
{
	start_time = time(0);
	const int  row = 9;
	const int colume = 9;
	int data[9][9] = { 0 };
	int store[9][9];
	int  exist = 0, score = 0;
	int mines[row][colume];
	int array[row][colume];
	int number1, number2;
	srand(int(time(0)));
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			mines[i][j] = rand() % 9;
			if (mines[i][j] == 1)
			{
				array[i][j] = mines[i][j];
			}
		}
	}
	while (exist != -1)
	{
		timer();
		cout << "please enter the number of row=";
		cin >> number1;
		cout << "pleaee enter numbr of colume=";
		cin >> number2;
		system("cls");
		score++;
		cout << RED;
		cout << endl;
		for (int i = 0;i < colume;i++)
		{
			if (i == 0)
			{
				cout << "\t";
			}
			cout << "[" << i << "]  ";
		}
		cout << endl;
		cout << "__________________________________________________";
		cout << reset;
		cout << endl;
		int print = 0;
		for (int i = 0;i < row;i++)
		{
			cout << RED;
			cout << i << "|\t";
			cout << reset;
			for (int j = 0;j < colume;j++)
			{

				if (i == number1 && j == number2)
				{

					if (mines[i][j] == 1 )
					{
						score--;
						exist = -1;
					}
					if (mines[i][j - 1] == 1 )
					{
						print++;
					}
					if (mines[i][j + 1] == 1 )
					{
						print++;
					}
					if (mines[i + 1][j] == 1 )
					{
						print++;
					}
					if (mines[i + 1][j + 1] == 1 )
					{
						print++;
					}
					if (mines[i + 1][j - 1] == 1 )
					{
						print++;
					}
					if (mines[i - 1][j] == 1 )
					{
						print++;
					}
					if (mines[i - 1][j + 1] == 1 )
					{
						print++;
					}
					if (mines[i - 1][j - 1] == 1 )
					{
						print++;
					}
					if (exist == -1)
					{
						cout << RED << "[&" << "]   " << reset;
					}
					else
					{
						data[i][j] = print;
						cout << RED << "[" << print << "]   " << reset;
					}
					if (print == 0)
					{
						store[i][j] = print;
					}
				}
				else if (data[i][j] == 1 || data[i][j] == 2)
				{
					cout << YELLOW << "[" << data[i][j] << "]   " << reset;
				}
				else if (data[i][j] == 3 || data[i][j] == 4)
				{
					cout << GREEN << "[" << data[i][j] << "]   " << reset;
				}
				else if (data[i][j] == 5 || data[i][j] == 6 || data[i][j] == 7 || data[i][j] == 8)
				{
					cout << BLUE << "[" << data[i][j] << "]  " << reset;
				}
				else if (store[i][j] == 0)
				{
					cout << BLUE << "[" << store[i][j] << "]   " << reset;
				}
				else
				{
					cout << "[" << data[i][j] << "]   ";
				}
			}
			cout << endl;
		}
		if (exist != -1)
		{
			cout << "please enter -1 if you want to exist game otherwise any number=";
			cin >> exist;
		}
	}
	if (exist == -1)
	{
		cout << "You hit the mines!" << endl;
	}
	if (score < 10)
	{
		cout << "Bad Score\n";
	}
	else if (score < 15)
	{
		cout << "Good Score\n";
	}
	else
	{
		cout << "Outstanding Score\n";
	}
	if (score > Ehighest)
	{
		normal(score);
	}
	cout << "Your score is=" << score << endl;
	cout << "!~~~~~~~~~~~~Thanks!~~~~~~~~~~~!" << endl;
}
void logic2()                                            // same as logic 1
{
	start_time = time(0);
	const int  row = 9;
	const int colume = 9;
	int data[9][9] = { 0 };
	int store[9][9];
	int  exist = 0, score = 0; 
	int mines[row][colume];
	int array[row][colume];
	int number1, number2;
	srand(int(time(0)));                                                      
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			mines[i][j] = rand() % 9;
			if (mines[i][j] == 1 || mines[i][j] == 2)
			{
				array[i][j] = mines[i][j];
			}
		}
	}
	while (exist != -1)
	{
		timer();
		cout << "please enter the number of row=";
		cin >> number1;
		cout << "pleaee enter numbr of colume=";
		cin >> number2;
		system("cls");
		score++;
		cout << RED;
		cout << endl;
		for (int i = 0;i < colume;i++)
		{
			if (i == 0)
			{
				cout << "\t";
			}
			cout << "[" << i << "]  ";
		}
		cout << endl;
		cout << "__________________________________________________";
		cout << reset;
		cout << endl;
		int print = 0;
		for (int i = 0;i < row;i++)
		{
			cout << RED;
			cout << i << "|\t";
			cout << reset;
			for (int j = 0;j < colume;j++)
			{

				if (i == number1 && j == number2)
				{

					if (mines[i][j] == 1 || mines[i][j] == 2)
					{
						score--;
						exist = -1;
					}
					if (mines[i][j - 1] == 1 || mines[i][j - 1] == 2)
					{
						print++;
					}
					if (mines[i][j + 1] == 1 || mines[i][j + 1] == 2)
					{
						print++;
					}
					if (mines[i + 1][j] == 1 || mines[i + 1][j] == 2)
					{
						print++;
					}
					if (mines[i + 1][j + 1] == 1 || mines[i + 1][j + 1] == 2)
					{
						print++;
					}
					if (mines[i + 1][j - 1] == 1 || mines[i + 1][j - 1] == 2)
					{
						print++;
					}
					if (mines[i - 1][j] == 1 || mines[i - 1][j] == 2)
					{
						print++;
					}
					if (mines[i - 1][j + 1] == 1 || mines[i - 1][j + 1] == 2)
					{
						print++;
					}
					if (mines[i - 1][j - 1] == 1 || mines[i - 1][j - 1] == 2)
					{
						print++;
					}
					if (exist == -1)
					{
						cout << RED << "[&" << "]   " << reset;
					}
					else
					{
						data[i][j] = print;
						cout << RED << "[" << print << "]   " << reset;
					}
					if (print == 0)
					{
						store[i][j] = print;
					}
				}
				else if (data[i][j] == 1 || data[i][j] == 2)
				{
					cout << YELLOW << "[" << data[i][j] << "]   " << reset;
				}
				else if (data[i][j] == 3 || data[i][j] == 4)
				{
					cout << GREEN << "[" << data[i][j] << "]   " << reset;
				}
				else if (data[i][j] == 5 || data[i][j] == 6 || data[i][j] == 7 || data[i][j]==8)
				{
					cout << BLUE << "[" << data[i][j] << "]  " << reset;
				}
				else if (store[i][j] == 0)
				{
					cout << BLUE << "[" << store[i][j] << "]   " << reset;
				}
				else
				{
					cout << "[" << data[i][j] << "]   ";
				}
			}
			cout << endl;
		}
		if (exist != -1)
		{
			cout << "please enter -1 if you want to exist game otherwise any number=";
			cin >> exist;
		}
	}
	if (exist == -1)
	{
		cout << "You hit the mines!" << endl;
	}
	if (score < 10)
	{
		cout << "Bad Score\n";
	}
	else if (score < 15)
	{
		cout << "Good Score\n";
	}
	else
	{
		cout << "Outstanding Score\n";
	}
	if (score > Nhighest)
	{
		normal(score);
	}
	cout << "Your score is=" << score << endl;
	cout << "!~~~~~~~~~~~~Thanks!~~~~~~~~~~~!" << endl;
}
void logic3()                                     // same as logic 1 && 2
{
	start_time = time(0);
	const int  row = 9;
	const int colume = 9;
	int data[9][9] = { 0 };
	int store[9][9];
	int exist = 0, score = 0; 
	int mines[row][colume];
	int array[row][colume];
	int number1, number2;
	srand(int(time(0)));
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			mines[i][j] = rand() % 9;
			if (mines[i][j] == 1 || mines[i][j] == 2 || mines[i][j] == 3)
			{
				array[i][j] = mines[i][j];
			}
		}
	}
	while (exist != -1)
	{
		timer();
		cout << "please enter the number of row=";
		cin >> number1;
		cout << "pleaee enter numbr of colume=";
		cin >> number2;
		system("cls");
		score++;
		cout << RED;
		cout << endl;
		for (int i = 0;i < colume;i++)
		{
			if (i == 0)
			{
				cout << "\t";
			}
			cout << "[" << i << "]  ";
		}
		cout << endl;
		cout << "____________________________________________________________________";
		cout << reset;
		cout << endl;
		int print = 0;
		for (int i = 0;i < row;i++)
		{
			cout << RED;
			cout << i << "|\t";
			cout << reset;
			for (int j = 0;j < colume;j++)
			{

				if (i == number1 && j == number2)
				{

					if (mines[i][j] == 1 || mines[i][j] == 2 || mines[i][j] == 3)
					{
						score--;
						exist = -1;
					}
					if (mines[i][j - 1] == 1 || mines[i][j - 1] == 2 || mines[i][j - 1] == 3)
					{
						print++;
					}
					if (mines[i][j + 1] == 1 || mines[i][j + 1] == 2 || mines[i][j + 1] == 3)
					{
						print++;
					}
					if (mines[i + 1][j] == 1 || mines[i + 1][j] == 2 || mines[i + 1][j] == 3)
					{
						print++;
					}
					if (mines[i + 1][j + 1] == 1 || mines[i + 1][j + 1] == 2 || mines[i + 1][j + 1] == 3)
					{
						print++;
					}
					if (mines[i + 1][j - 1] == 1 || mines[i + 1][j - 1] == 2 || mines[i + 1][j - 1] == 3)
					{
						print++;
					}
					if (mines[i - 1][j] == 1 || mines[i - 1][j] == 2 || mines[i - 1][j] == 3)
					{
						print++;
					}
					if (mines[i - 1][j + 1] == 1 || mines[i - 1][j + 1] == 2 || mines[i - 1][j + 1] == 3)
					{
						print++;
					}
					if (mines[i - 1][j - 1] == 1 || mines[i - 1][j - 1] == 2 || mines[i - 1][j - 1] == 3)
					{
						print++;
					}
					if (exist == -1)
					{
						cout << RED << "[&" << "]  " << reset;
					}
					else
					{
						data[i][j] = print;
						cout << RED << "[" << print << "]  " << reset;
					}
					if (print == 0)
					{
						store[i][j] = print;
					}
				}
				else if (data[i][j] == 1 || data[i][j] == 2)
				{
					cout << BLUE << "[" << data[i][j] << "]  " << reset;
				}
				else if (data[i][j] == 3 || data[i][j] == 4)
				{
					cout << GREEN << "[" << data[i][j] << "]  " << reset;
				}
				else if (data[i][j] == 5 || data[i][j] == 6 || data[i][j] == 7|| data[i][j]==8)
				{
					cout << YELLOW << "[" << data[i][j] << "]  " << reset;
				}
				else if (store[i][j] == 0)
				{
					cout << BLUE << "[" << store[i][j] << "]  " << reset;
				}
				else
				{
					cout << "[" << data[i][j] << "]  ";
				}
			}
			cout << endl;
		}
		if (exist != -1)
		{
			cout << "please enter -1 if you want to exist game otherwise any number=";
			cin >> exist;
		}
	}
	if (exist == -1)
	{
		cout << "You hit the mines!" << endl;
	}
	if (score < 5)
	{
		cout << "Bad Score\n";
	}
	else if (score < 10)
	{
		cout << "Good Score\n";
	}
	else
	{
		cout << "Outstanding Score\n";
	}
	if (score > Hhighest)
	{
		hard(score);
	}
	cout << "Your score is=" << score << endl;
	cout << "!~~~~~~~~~~~~Thanks!~~~~~~~~~~~!" << endl;
}
void easy(int score)                   //save Highest score Easy stag
{
	remove("D:\\easy.txt");
	remove("D:\\Eloginid.txt");
	ofstream escorefile, eid;
	escorefile.open("D:\\easy.txt");
	escorefile << score;
	escorefile.close();
	eid.open("D:\\Eloginid.txt");
	eid << Eidlogin;
	eid.close();
}
void easyhighestset()                                   
{
	ifstream escores, eid;
	escores.open("D:\\easy.txt");
	escores >> Ehighest;
	escores.close();
	eid.open("D:\\Eloginid.txt");
	eid >> Ehighestid;
	eid.close();
}
void normal(int score)                         //save Highest score Easy stag
{
	remove("D:\\normal.txt");
	remove("D:\\Nloginid.txt");
	ofstream nscorefile, nid;
	nscorefile.open("D:\\normal.txt");
	nscorefile << score;
	nscorefile.close();
	nid.open("D:\\Nloginid.txt");
	nid << Nidlogin;
	nid.close();
}
void normalhighestset()
{
	ifstream nscores, nid;
	nscores.open("D:\\normal.txt");
	nscores >> Nhighest;
	nscores.close();
	nid.open("D:\\Nloginid.txt");
	nid >> Nhighestid;
	nid.close();
}
void hard(int score)                   //save Highest score Easy stag
{
	remove("D:\\hard.txt");
	remove("D:\\Hloginid.txt");
	ofstream hscorefile, hid;
	hscorefile.open("D:\\hard.txt");
	hscorefile << score;
	hscorefile.close();
	hid.open("D:\\Hloginid.txt");
	hid << Hidlogin;
	hid.close();
}
void hardhighestset()
{
	ifstream hscores, hid;
	hscores.open("D:\\hard.txt");
	hscores >> Hhighest;
	hscores.close();
	hid.open("D:\\Hloginid.txt");
	hid >> Hhighestid;
	hid.close();
}