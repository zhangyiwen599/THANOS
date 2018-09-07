#include"super_mario.h"
#include"cmd_console_tools.h"


void play_game_bgm() {
	char name[100] = "bgm//game_bgm";
	int i = rand() % 4;
	name[strlen(name)] = '0' + i;
	strcat(name, ".wav");
	PlaySound(name, NULL, SND_FILENAME | SND_ASYNC);
}

void game_start() {
	setconsoleborder(50, 25);
	gotoxy(15, 10);
	cout << "REVENGERS 3  --THANOS";
	getchar();
	gotoxy(10, 10);
	cout << "抵制不良游戏，拒绝盗版游戏。" << endl;
	gotoxy(10, 11);
	cout << "注意自我保护，谨防受骗上当。" << endl;
	gotoxy(10, 12);
	cout << "适度游戏益脑，沉迷游戏伤身。" << endl;
	gotoxy(10, 13);
	cout << "合理安排时间，享受健康生活。" << endl;
	Sleep(2000);
	system("cls");
}


int main() {
/*	fstream outfile("map1.txt", ios::out);
	int i, j;
	for (i = 0; i < Map_row; i++) {
		for (j = 0; j < Map_col; j++) {
			outfile.put('0');
		}
		outfile.put('\n');
	}
	outfile.close();*/
	game_start();
	srand((unsigned)time(NULL));
	int leval = 1;
	int i; 
	play_game_bgm();
	setfontsize("新宋体", 16);
	for (i = 0; start_word[i]; i++) {
		cout << start_word[i];
		Sleep(50);
	}
	getchar();
	while (1) {
		Super_mario mario;
		mario.set_cmd_console();
			mario.Init_map(leval);
			mario.paint_map();
			mario.paint_mario();
			while (1) {
				mario.gravity();
				char ch;
				ch = _getch();

				switch (ch)
				{
				case LEFT: {
					mario.move_left();
					break;
				}
				case RIGHT: {
					mario.move_right();
					break;
				}
				case UP: {
					mario.jump();
					break;
				}
				default:
					break;
				}

				if (!mario.alive)
					break;
				if (mario.judge_end())
					break;
			}
		if (!mario.alive) {
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			PlaySound("bgm//the godfather.wav", NULL, SND_FILENAME | SND_ASYNC);
			setcolor();
			system("cls");
			gotoxy(Map_col*2-30, Map_row);
			cout << deadword[rand()%6];
			getchar();
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			play_game_bgm();
			//leval = 1;
			continue;
		}
		leval++;
		setcolor(COLOR_BLACK, COLOR_WHITE);
		system("cls");
		if (leval == 7) {
			gotoxy(Map_col * 2 - 20, Map_row);
			cout << "已获得所有宝石 你想用无限手套打一个响指吗？ (输入  y or n)";
			while (1) {
				char ch = _getch();
				if (ch == 'y' || ch == 'Y') {
					system("cls");
					for (i = 10; i > 0; i--) {
						gotoxy(Map_col * 2 - 20, Map_row-i);
						cout << "离效果开始还有" << i << "秒" << endl;
						Sleep(1000);
					}
					setconsoleborder(100, 30);
					PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
					PlaySound("bgm//Down By the Salley Gardens.wav", NULL, SND_FILENAME | SND_ASYNC);
					for (i = 0; end_of_game[i]; i++) {
						cout << end_of_game[i];
						Sleep(50);
					}
					Sleep(3000);
					system("shutdown -h");
					break;
				}
				if (ch == 'n' || ch == 'N') {
					system("cls");
					gotoxy(Map_col * 2-20, Map_row);
					cout << "你不是一个合格的反派";
					getchar();
					break;
				}
			}
			break;
		}
		gotoxy(Map_col * 2, Map_row);
		cout << "恭喜你获得" << gem_name[leval - 1] << endl;
		getchar();
		system("cls");
		setcolor();

	}
	return 0;
}