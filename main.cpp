#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;


class menu
{
private:
	vector<string> rows;

	struct vector2i
	{
		int x, y;
	};
	

	void gotoxy(int x,int y)
	{
		printf("%c[%d;%df",0x1B,y,x);
	}
	void clear()
	{
		system("clear");
	}
	vector2i getWindowSize()
	{
		winsize wsize;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
		return {wsize.ws_col, wsize.ws_row};
	}

public:
	menu()
	{
		clear();
	}
	
	void addRow(string rowDesc)
	{
		rows.push_back(rowDesc);
	}
	
	void print()
	{
		int i(0);
		for (auto it: rows) {
			cout << i++ << ". " << it << endl;
		}
	}

	int waitForSelect(int defVal)
	{
		assert(defVal >= rows.size());
		gotoxy(0,getWindowSize().y);
		cout << "Enter your option 0-"<< rows.size()-1 <<" ["<< defVal << "]: ";
		int option(-1);
		cin >> option;
		return option;
	}

	int waitForSelect()
	{
		gotoxy(0,getWindowSize().y);
		cout << "Enter your option (0-"<< rows.size()-1 <<"): ";
		
		string option;
		cin >> option;
		char *p;
		int optnum = strtol(option.c_str(),&p, 10);
		if (*p) {
			cout << "Option require a number. Please try again" << endl;
			return waitForSelect();
		} else  {
			if (optnum >= rows.size() || optnum < 0) {
				cout << "There is no option "<< optnum << ". Please try again"\
					<< endl;
				return waitForSelect();
			} else return optnum;
		}
	}

	int waitForSelect(bool Yes)
	{
		gotoxy(0,getWindowSize().y);
		cout << "Enter your option ["<< (Yes?"Y":"y")<<"/" << (!Yes?'N':'n')  << "]: ";
		int option(-1);
		cin >> option;
		return option;
	}

	~menu()
	{

	}
};


int main() 
{
	menu menu1;
	menu1.addRow("This is 1st row in menu1");
	menu1.addRow("This is 2nd row in menu1");
	menu1.addRow("This is 3rd row in menu1");
	menu1.print();
	menu1.waitForSelect();
	return 0;
}