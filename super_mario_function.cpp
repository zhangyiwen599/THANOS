#include"super_mario.h"
#include"cmd_console_tools.h"

Super_mario::Super_mario() {
	player_pos_x=0;
	 player_pos_y=0;
	 acclerrate=1;
	 speed=0;
	 alive=true;
	 have_gem = false;
}

void Super_mario::set_cmd_console() const{
	setconsoleborder(Map_col*4, Map_row*2);
}

void Super_mario::Init_map(int Leval) {
	char str[30];
	char txt_name[50]="map//map";
	sprintf(str, "%d", Leval);
	strcat(txt_name, str);
	strcat(txt_name, ".txt");
	fstream infile(txt_name,ios::in|ios::binary);
	if (infile.is_open() == 0) {
		cout << "打开关卡地图文件失败" << endl;
	}
	int i,j;
	for (i = 0; i <Map_row; i++) {
		for (j = 0; j <  Map_col; j++) {
			map[i][j] = infile.get();
		}
		infile.get();
		infile.get();
	}
	infile.close();
}

void Super_mario::paint_cell(int col,int row,int mode) const{
	if (mode == NORMAL) {
		/*   
			 ****
		     ****     
		*/
		showstr(col * 4, row*2, "    ", COLOR_HWHITE, COLOR_HWHITE);
		showstr(col * 4, row*2 + 1, "    ", COLOR_HWHITE, COLOR_HWHITE);
	}
	else if (mode == TRAP_CELL) {
		/*     **    
			  ****	*/	
		showstr(col * 4+1, row*2, "  ", COLOR_RED, COLOR_RED);
		showstr(col * 4, row*2 + 1, "    ", COLOR_RED, COLOR_RED);
	}
	else if (mode ==BLACK_CELL) {
		/*     **
			   **		*/
		showstr(col * 4 , row*2, "  ", COLOR_BLACK, COLOR_BLACK);
		showstr(col * 4, row*2 + 1, "  ", COLOR_BLACK, COLOR_BLACK);
	}
	else if (mode == RED_GEM) {
		/*     ****
				**	*/
		showstr(col * 4, row * 2, "    ", COLOR_HRED, COLOR_HRED);
		showstr(col * 4+1, row * 2 + 1, "  ", COLOR_HRED, COLOR_HRED);
	}
	else if (mode == GREEN_GEM) {
		/*     ****
		**	*/
		showstr(col * 4, row * 2, "    ", COLOR_HGREEN, COLOR_HGREEN);
		showstr(col * 4+1, row * 2 + 1, "  ", COLOR_HGREEN, COLOR_HGREEN);
	}
	else if (mode == BLUE_GEM) {
		/*     ****
		**	*/
		showstr(col * 4, row * 2, "    ", COLOR_BLUE, COLOR_BLUE);
		showstr(col * 4+1, row * 2 + 1, "  ", COLOR_BLUE, COLOR_BLUE);
	}
	else if (mode == YELLOW_GEM) {
		/*     ****
		**	*/
		showstr(col * 4, row * 2, "    ", COLOR_HYELLOW, COLOR_HYELLOW);
		showstr(col * 4+1, row * 2 + 1, "  ", COLOR_HYELLOW, COLOR_HYELLOW);
	}
	else if (mode == CYAN_GEM) {
		/*     ****
		**	*/
		showstr(col * 4, row * 2, "    ", COLOR_CYAN, COLOR_CYAN);
		showstr(col * 4+1, row * 2 + 1, "  ", COLOR_CYAN, COLOR_CYAN);
	}
	else if (mode == PINK_GEM) {
		/*     ****
		**	*/
		showstr(col * 4, row * 2, "    ", COLOR_HPINK, COLOR_HPINK);
		showstr(col * 4 + 1, row * 2 + 1, "  ", COLOR_HPINK, COLOR_HPINK);
	}


}

void Super_mario::paint_map() const{
	int i, j;
	for (i = 0; i <Map_row; i++) {
		for (j = 0; j < Map_col; j++) {
			if(map[i][j]!='0')
				paint_cell(j, i, map[i][j]);
		}
	}

}

void Super_mario::paint_mario() const{
	int pos_x = player_pos_x * 4;
	int pos_y = player_pos_y * 2;
	/*   
		  **   
		 **** 
		  **
		 *  *   
	*/
	showstr(pos_x + 1, pos_y, "  ", COLOR_PINK, COLOR_PINK); //head


	showstr(pos_x , pos_y+1, "    ", COLOR_HBLUE, COLOR_HBLUE);   //body
	showstr(pos_x, pos_y + 2, " ", COLOR_BLACK, COLOR_BLACK);
	showstr(pos_x+1, pos_y + 2, "  ", COLOR_HBLUE, COLOR_HBLUE);
	showstr(pos_x + 3, pos_y + 2, " ", COLOR_BLACK, COLOR_BLACK);


	showstr(pos_x , pos_y + 3, " ", COLOR_HBLUE, COLOR_HBLUE);    //foot
	showstr(pos_x+1, pos_y + 3, "  ", COLOR_BLACK, COLOR_HBLUE);
	showstr(pos_x+3, pos_y + 3, " ", COLOR_HBLUE, COLOR_HBLUE);

}

void  Super_mario::mask_mario() const {
	int pos_x = player_pos_x * 4;
	int pos_y = player_pos_y * 2;
	/*
		 **
		****
		 **
		*  *
	*/
	showstr(pos_x + 1, pos_y, "  ", COLOR_BLACK, COLOR_BLACK);
	showstr(pos_x, pos_y + 1, "    ", COLOR_BLACK, COLOR_BLACK);
	showstr(pos_x + 1, pos_y + 2, "  ", COLOR_BLACK, COLOR_BLACK);
	showstr(pos_x, pos_y + 3, " ", COLOR_BLACK, COLOR_BLACK);
	showstr(pos_x + 3, pos_y + 3, " ", COLOR_BLACK, COLOR_BLACK);

}

void Super_mario::move_left() {
	if (!alive)
		return;
	if (player_pos_x>0&&map[player_pos_y][player_pos_x - 1] != '1'&&map[player_pos_y+1][player_pos_x - 1] != '1') {
		mask_mario();
		player_pos_x--;
		paint_mario();
	}
	if (map[player_pos_y][player_pos_x] >= '3' || map[player_pos_y + 1][player_pos_x] >= '3')
		have_gem = true;
	if (judge_dead())
		alive = false;
}

void Super_mario::move_right() {
	if (!alive)
		return;
	if (player_pos_x<Map_col-1 && map[player_pos_y][player_pos_x + 1] != '1'&&map[player_pos_y+1][player_pos_x + 1] != '1') {
		mask_mario();
		player_pos_x++;
		paint_mario();
	}
	if (map[player_pos_y][player_pos_x] >= '3'|| map[player_pos_y+1][player_pos_x] >= '3')
		have_gem = true;

	if (judge_dead()) 
		alive = false;
}

void Super_mario::gravity() {
	if (map[player_pos_y + 2][player_pos_x] == '1') {
		speed = 0;
		return;
	}
	else {
		speed = 1;
		acclerrate = 1;
	}
	//player_pos_y += speed;

	int i=0,flag=0;
	while (1) {
		if (flag == 2) {
			speed += acclerrate;
			i = 0;
			flag = 0;
		}
		while (!_kbhit()) {
			if (judge_dead()) {
				alive = false;
				return;
			}
			if (map[player_pos_y + 2][player_pos_x] != '0' ) {
				flag=1;
				break;
			}
			else if (i == speed) {
				flag = 2;
				break;
			}
			mask_mario();
			player_pos_y++;
			paint_mario();
			Sleep(150 - speed * 20);
			i++;
		}
		if (flag == 1)
			break;
		if (!alive)
			return;

		if (flag == 0) {
			char ch;
			ch = _getch();
			if (ch == 0x4b)
				move_left();
			if (ch == 0x4d)
				move_right();

			if (!alive)
				return;
		}
	}
}

void Super_mario::jump() {
	if (map[player_pos_y - 1][player_pos_x] == '1') {
		return;
	}
	speed = -4;
	acclerrate = 1;
	int flag = 0, i = 0;
//	int ret,X,Y,maction,keycode1;
	char keycode2;
/*	while (1) {
		if (flag == 2) {
			speed += acclerrate;
			i = 0;
			flag = 0;
			if (speed == 0) {
				Sleep(500);
				gravity();
				return;
			}
		}
		while (!_kbhit()) {
			if (judge_dead()) {
				alive = false;
				return;
			}
			if (map[player_pos_y -1][player_pos_x] != '0') {
				flag=1;
				break;
			}
			if (i == speed) {
				flag = 2;
				break;
			}
			mask_mario();
			player_pos_y--;
			paint_mario();
			Sleep(50-10*i);
			i--;
		}

		if (flag == 0) {
			char ch;
			ch = _getch();
			if (ch == 0x4b)
				move_left();
			if (ch == 0x4d)
				move_right();

			if (!alive)
				return;
		}
		if (flag == 1)
			break;
	}*/
	while (1) {
		if (flag == 2) {
			speed += acclerrate;
			i = 0;
			flag = 0;
			if (speed == 0) {
				Sleep(100);
				gravity();
				return;
			}
		}
		while (1) {
			if (_kbhit()) {
				keycode2 = _getch();
				if (keycode2 == KB_ARROW_LEFT)
					move_left();
				if (keycode2 == KB_ARROW_RIGHT)
					move_right();
			}
			if (map[player_pos_y - 1][player_pos_x] != '0') {
				flag = 1;
				break;
			}
			if (i == speed) {
				flag = 2;
				break;
			}
			mask_mario();
			player_pos_y--;
			paint_mario();
			Sleep(40 - 10 * i);
			i--;
		}
		if (flag == 1)
			break;
	}
}

bool Super_mario::judge_end()  const {
	if (player_pos_x == Map_col-1&& have_gem)
		return true;
	return false;
}

bool Super_mario::judge_dead()  const {
	if (map[player_pos_y + 2][player_pos_x]==TRAP_CELL)
		return true;
	if (player_pos_y + 1 ==Map_row-1)
		return true;

	return false;
}
