#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int ar[17][17];
int i, j;
void ui();
void move();
void roll(char drc);
int numlen(int num);
int max();
void clear_screen();

int main()
{
	bool flg = 1, bol = 1, check = 1;
	int randj, randi;
	cout << "                                                 HELLO WELCOME TO 2048"<<endl;

	string str;
	cout << "inter the name of a  new/saved game: ";
	cin >> str;
	const char *filename = str.c_str();
	// saved
	fstream fcls;
	fcls.open(filename, ios::in);
	if (!fcls.fail())
	{
		fcls >> i;
		j = i;
		for (int c = 0; c < i; c++)
		{
			for (int a = 0; a < j; a++)
			{
				fcls >> ar[c][a];
			}
		}
	}
	// new
	else
	{
		// init
		cout << "intrer the size of game play ground(1< <15): ";
		cin >> i;
		j = i;
		for (int c = 0; c < i; c++)
		{
			for (int a = 0; a < j; a++)
			{
				ar[c][a] = 0;
			}
		}
		// random
		srand(time(0));
		ar[rand() % i][rand() % j] = 2;
		ar[rand() % i][rand() % j] = 2;
	}
	fcls.close();

	clear_screen();
	// guid
	char drc, up = 24, down = 25, left = 27, right = 26;
	cout << " HERE IS HOW TO PLAY: " << endl;
	cout << " use this characters as folows:" << endl
		 << "                 w" << endl
		 << "              a  s  d  ";
	cout << endl
		 << "   w(up)"
		 << "  s(down)"
		 << "  a(left)"
		 << "  d(right)" << endl;
	ui();

	while (flg == 1)
	{
		cout << "inter your next move: ";
		// check
		check = 1;
		while (check == 1)
		{
			check = 0;
			cin >> drc;
			if (drc != 'w' && drc != 'a' && drc != 's' && drc != 'd' && drc != 'u')
			{
				check = 1;
				cout << "try these keys to move: "
					 << "( w(up)"
					 << "  s(down)"
					 << "  a(left)"
					 << "  d(right) )" << endl;
			}
		}
		clear_screen();
		roll(drc);
		move();
		if (drc == 'a')
			drc = 'd';
		else if (drc == 'd')
			drc = 'a';
		roll(drc);
		// score board
		cout << " SCORE:     " << max() << endl;
		cout << "         -------" << endl;
		while (bol == 1)
		{
			randi = rand() % i;
			randj = rand() % j;
			if (ar[randi][randj] == 0)
			{
				ar[randi][randj] = 2;
				break;
			}
		}
		ui();
		// save
		fcls.open(filename, ios::out);
		fcls << i << endl;
		for (int c = 0; c < i; c++)
		{
			for (int a = 0; a < j; a++)
			{
				fcls << ar[c][a] << endl;
			}
		}

		fcls.close();
	}

	return 0;
}
// funcs
void move()
{
	int shom;

	for (int sot = 0; sot < j; sot++)
	{
		shom = i - 1;
		int temp = -1;
		for (int sat = i - 1; sat >= 0; sat--)
		{
			if (ar[sat][sot] && temp != ar[sat][sot])
			{
				temp = ar[sat][sot];
				ar[sat][sot] = ar[shom][sot];
				ar[shom][sot] = temp;
				shom--;
			}
			else if (ar[sat][sot])
			{
				ar[shom + 1][sot] = 2 * ar[shom + 1][sot];
				ar[sat][sot] = 0;
				temp = -1;
			}
		}
	}
}
void ui()
{
	int sat, sot;
	for (sat = 0; sat < i; sat++)
	{

		for (int top = 1; top <= j; top++)
		{
			cout << "   --------- ";
		}
		cout << endl;

		for (int u = 1; u <= 3; u++)
		{
			for (sot = 0; sot < j; sot++)
			{
				if (u == 2 && ar[sat][sot] != 0)
				{
					cout << "  |    " << ar[sat][sot];
					for (int space = 0; space < 5 - numlen(ar[sat][sot]); space++)
						cout << " ";
					cout << "|";
				}
				else
					cout << "  |         |";
			}
			cout << endl;
		}
		for (int dow = 1; dow <= j; dow++)
		{
			cout << "   --------- ";
		}
		cout << endl;
	}
}
void roll(char drc)
{
	int temp, rep;
	switch (drc)
	{
	case 's':
		rep = 0;
		break;
	case 'd':
		rep = 1;
		break;
	case 'w':
		rep = 2;
		break;
	case 'a':
		rep = 3;
		break;
	}
	while (rep--)
	{
		for (int sat = 0; sat < i; sat++)
		{
			for (int sot = 0; sot < j; sot++)
			{
				if (sat > sot)
				{
					temp = ar[sat][sot];
					ar[sat][sot] = ar[sot][sat];
					ar[sot][sat] = temp;
				}
			}
		}
		for (int sat = 0; sat < i; sat++)
		{
			for (int sot = 0; sot < j / 2; sot++)
			{
				temp = ar[sat][sot];
				ar[sat][sot] = ar[sat][j - sot - 1];
				ar[sat][j - sot - 1] = temp;
			}
		}
	}
}
int numlen(int num)
{
	int i = 0;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return i;
}
int max()
{
	int max;
	max = ar[0][0];
	for (int k = 0; k < i; k++)
	{
		for (int c = 0; c < j; c++)
		{
			if (ar[k][c] > max)
			{
				max = ar[k][c];
			}
		}
	}
	return max;
}

void clear_screen()
{
#ifdef WINDOWS
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif
}
