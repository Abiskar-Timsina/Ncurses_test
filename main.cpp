#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>

int menu_screen();
void screen0();
void screen1();
void screen2();

std::ifstream header_file("./header",std::ios::in);
std::ifstream footer_file("./footer",std::ios::in);

int main(int arg, char* argv[]){
	initscr();
	cbreak();
	noecho();

	int ret = menu_screen();
	switch (ret){
		case 0:
			screen0();
			break;
		case 1:
			screen1();
			break;
		case 2:
			screen2();
			break;			
	}

	getch();
	endwin();
	return 0;
}

int menu_screen(){
	//menu settings / messages do not change variable names.
	std::vector <std::string> choices = {"1. Choice","2. Choice","3. Choice","4. Choice","5. Choice"};	
	std::string welcome_msg = " Welcome! "; //positioned at the center of the screen 
	std::string header_text;
	std::string footer_text; //currently unused 


	
		
	//screen config - Dynamically Programmed no need to change	
	int start_y, start_x,height,width; //initializing basic window config parameters

	getbegyx(stdscr,start_y,start_x); // getting the starting left/ right of the standard screen 
	getmaxyx(stdscr,height,width); // getting the height and width of the screen 
	
	//setting up windows 
	curs_set(0);
	WINDOW* mainWindow = newwin(height, width, start_y,start_x);	
	WINDOW* menu = newwin(height/4,width/8,height/2 - 10,width/2 - 10);
	keypad(menu,true);
	box(mainWindow,1,0); // box for the main window
	box(menu,0,0); //box for the menu window
	refresh();
	
	//print msgs welcome msg, header, footer
	int window_start=2;
	
	mvwprintw(mainWindow,0,width/2,welcome_msg.c_str()); // 1 so that it starts at the first line and width/2 so that it starts at the center
	
	while(getline(header_file,header_text)){
	mvwprintw(mainWindow,window_start,2,header_text.c_str());
	window_start++;
	wrefresh(mainWindow);
	}

	int window_end = window_start+25;
	
	while(getline(footer_file,footer_text)){
	mvwprintw(mainWindow,window_end,2,footer_text.c_str());
	window_end++;
	wrefresh(mainWindow);
	}


	
	int inp,curr=0,op_1 = 1;
	
	for (std::string choice : choices){
		mvwprintw(menu,op_1,1,choice.c_str());
		op_1++;
	}
	wrefresh(menu);
	
	op_1 = 1;
	wattron(menu,A_REVERSE);
	mvwprintw(menu,op_1,1,choices[curr].c_str());
	wattroff(menu,A_REVERSE);
	wrefresh(menu);
	
	for (;;){
		inp = wgetch(menu);
			
		switch (inp){			
				case KEY_DOWN:{
					curr++;
					op_1++;
					if (curr > (choices.size() - 1)){
						curr = 0;
						op_1 = 1;
					}

					break;
				}
				
				case KEY_UP:{
					curr--;
					op_1--;
					if (curr < 0){
					curr = (choices.size() - 1);
					op_1 = choices.size();
					}

					break;
				}
				default:
					break;
		}
		
		int op_1_new = 1;
		for (std::string choice : choices){
			if (op_1_new == op_1){
				wattron(menu,A_REVERSE);
				mvwprintw(menu,op_1,1,choices[curr].c_str());
				wattroff(menu,A_REVERSE);
				op_1_new++;
				continue;
			}
			mvwprintw(menu,op_1_new,1,choice.c_str());
			op_1_new++;

		}
		wrefresh(menu);

		if (inp == 10){
			return curr;
		}
	}
}

void screen0(){
	clear();
	
	int start_y, start_x,height,width; //initializing basic window config parameters

	getbegyx(stdscr,start_y,start_x); // getting the starting left/ right of the standard screen 
	getmaxyx(stdscr,height,width); // getting the height and width of the screen 

	WINDOW* window = newwin(height,width,start_y,start_x);
	WINDOW* pass_field = newwin(height/10,width/3,height/2 -10,width/2 -10);	
	refresh();
	
	box(window,1,0);
	wrefresh(window);
	mvwprintw(window,0,width/2,"Your choice was option 2 so you get this :D ");
	box(pass_field,0,0);
	mvwprintw(pass_field,0,0," Password ");
	wmove(pass_field,1,1);
	curs_set(1);
	wrefresh(pass_field);
	wrefresh(window);
	
	
	int inp = wgetch(pass_field),i=1;
	std::string text,character="*";
	
	while (inp != 10){
		mvwprintw(pass_field,1,i,character.c_str());
		wrefresh(pass_field);
		text += (char) inp;
		i++;
		inp = wgetch(pass_field);
	}
	wprintw(window,text.c_str());
	wrefresh(window);
	refresh();
}

void screen1(){
	clear();
	
	int start_y, start_x,height,width; //initializing basic window config parameters

	getbegyx(stdscr,start_y,start_x); // getting the starting left/ right of the standard screen 
	getmaxyx(stdscr,height,width); // getting the height and width of the screen 
	
	WINDOW* window = newwin(height,width,start_y,start_x);
	refresh();
	box(window,1,0);
	mvwprintw(window,0,width/2,"Your choice was option 2 so you get this :D ");
	wrefresh(window);
}

void screen2(){
	clear();
	
	int start_y, start_x,height,width; //initializing basic window config parameters

	getbegyx(stdscr,start_y,start_x); // getting the starting left/ right of the standard screen 
	getmaxyx(stdscr,height,width); // getting the height and width of the screen 
	
	WINDOW* window = newwin(height,width,start_y,start_x);
	refresh();
	box(window,1,0);
	mvwprintw(window,0,width/2,"Your choice was option 2 so you get this :D ");
	wrefresh(window);
}
