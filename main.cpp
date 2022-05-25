#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cstring>

#include <sys/ioctl.h>
#include <unistd.h>

#include <curses.h>
#include <menu.h>

using namespace std;


struct HV {
    char    HoLot[30];
    char    Ten[30];
    char    Ngaysinh[8];
    char    Noisinh[40];
	int 	D_WIN;
	int 	D_WORD;
	int 	D_EXCEL;
	int 	TONGDIEM;
	char	X_LOAI[20];
	HV() 
	{
		memset(this, 0, sizeof(HV));
	}
	void 	checkConstraint()
	{
		assert(D_WIN < 10 && D_WIN >= 0);
		assert(D_WORD < 10 && D_WORD >= 0);
		assert(D_EXCEL < 10 && D_EXCEL >= 0);		
	}
};

class menu
{
private:
	vector<string> rows;
	int selection = 0;
	ITEM **items;
	MENU *_menu;
public:
	menu()
	{
	}
	
	void addRow(string rowDesc)
	{
		rows.push_back(rowDesc);
	}
	
	void mvSelect(int inc)
	{
		selection += inc;
		if (selection < 0) selection = 0;
		else if(selection >= rows.size()) {
			selection = rows.size() - 1;
		}
	}
	inline int getSelection()
	{
		return selection;
	}
	ITEM **getITEMS() 
	{
		items = new ITEM*[rows.size()+1];
		string *num = new string[rows.size()];
		for(int i=0; i<rows.size(); i++) {
			num[i] = to_string(i);
			items[i] = new_item(num[i].c_str(), rows[i].c_str());
		}
		items[rows.size()] = (ITEM *)NULL;
		return items;
	}
	MENU *getMENU()
	{
		_menu = new_menu(getITEMS());
		return _menu;
	}

	~menu()
	{
		for(int i=0; i<rows.size(); i++) {
			free_item(items[i]);
		}
		free_menu(_menu);

		delete[] items;
	}
};


int main() 
{
	menu *menu1 = new menu;

	menu1->addRow("GHI DANH");
	menu1->addRow("NHAP DIEM");
	menu1->addRow("DANH SACH HOC VIEN");
	menu1->addRow("KET QU THI");
	menu1->addRow("EXIT");

	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	MENU *my_menu = menu1->getMENU();
	int c;

	mvprintw(LINES - 2, 0, "Press Q to Exit");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != 'Q' && c != 'q')
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				menu1->mvSelect(1);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				menu1->mvSelect(-1);
				break;
			case '\n':	
				int s = menu1->getSelection();			
				cout << s << endl;
				getch();
				endwin();
				delete menu1;
				return 0;
				break;
		}
	}	

	delete menu1;
	endwin();

	return 0;
}