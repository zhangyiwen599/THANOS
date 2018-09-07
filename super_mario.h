#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<cstring>
#include <conio.h>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include <mmsystem.h>
//#include<dsound.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
/*地图大小定义*/
#define Map_col 50
#define Map_row 25  


/*方块打印模式定义*/
#define NORMAL   '1'      //普通方块
#define TRAP_CELL '2'     //陷阱
#define BLACK_CELL '3'    //金币
#define RED_GEM '4'			//红宝石
#define GREEN_GEM '5'		//绿宝石
#define BLUE_GEM '6'		//蓝宝石
#define YELLOW_GEM '7'		//黄宝石
#define CYAN_GEM '8'		//青宝石
#define PINK_GEM '9'   //紫宝石

/*方向键*/
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50


const char start_word[1000] = { "宇宙资源毕竟有限，生命却不断繁衍，这种膨胀必然会带来灾难。如果能随机消灭宇宙一半的生命，以此维持整个宇宙的平衡，剩下的另一半便有机会活得更好。控制灭霸的移动来获得无限宝石，为宇宙生命美好的未来努力吧。" };
const char deadword[10][500]={{ "鞠躬尽瘁,死而后已。 -- 诸葛亮" },
{"人的一生应当这样度过:当一个人回首往事时,不因虚度年华而悔恨,也不因碌碌无为而羞愧;\n\
                                                                      这样,在他临死的时候,能够说,我把整个生命和全部精力都献给了人生最宝贵的事业——为人类的解放而奋斗。\n\
                                                                                                                                                          --尼古拉·奥斯特洛夫斯基"}
,{"人生自古谁无死，留取丹心照汗青。  --文天祥"}
,{"生当作人杰，死亦为鬼雄。 --李清照"}
,{"每个人都会死去,但不是每个人都曾经真正活过。---《勇敢的心》"}
,{"出师未捷身先死，长使英雄泪沾襟。 —— 杜甫"}
};

const char gem_name[6][100] = { {"力量宝石"},{"时间宝石"},{"空间宝石"},{"灵魂宝石"},{"现实宝石"}, {"心灵宝石" } };

const char end_of_game[1000] = { "很遗憾，你也成为了被选中的那二分之一。弥留之际，你突然回想起父亲带你去见识冰块的那个下午。那时的泰坦星是一个原始的星球，篱笆和芦苇盖成的屋子，沿河岸排开，湍急的河水清澈见底，河岸里暖石洁白光滑宛如史前巨蛋。世界新生伊始，许多事物还没有名字，提到的时候尚需用手指指点点。 再也回不去了啊，你这样想着，闭上了双眼" };

class Super_mario
{
public:
	bool alive;
	bool have_gem;
	void set_cmd_console()   const;  //设置字体 屏幕大小

	void Init_map(int Leval);                //从文件中读取 并初始化地图
	void paint_map() const;		//打印地图

	void paint_mario() const;      //打印人物
	void move_left();      //人物左移
	void move_right();    //人物右移
	void jump();         //人物跳跃
	void gravity();        //重力函数----moveleft moveright jump 函数调用
	void mask_mario() const;     //移动后除去原位置的马里奥


	bool judge_end()  const; //判断关卡结束
	bool judge_dead()  const;  //判断人物是否死亡

	Super_mario();
		
	

private:
	void paint_cell(int col,int row,int mode) const; //打印一个方块

	char map[Map_row][Map_col];
	int player_pos_x;
	int player_pos_y;
	int acclerrate;
	int speed;
	int time;    //滞空时间

};


#pragma once
