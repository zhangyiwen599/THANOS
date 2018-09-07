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
/*��ͼ��С����*/
#define Map_col 50
#define Map_row 25  


/*�����ӡģʽ����*/
#define NORMAL   '1'      //��ͨ����
#define TRAP_CELL '2'     //����
#define BLACK_CELL '3'    //���
#define RED_GEM '4'			//�챦ʯ
#define GREEN_GEM '5'		//�̱�ʯ
#define BLUE_GEM '6'		//����ʯ
#define YELLOW_GEM '7'		//�Ʊ�ʯ
#define CYAN_GEM '8'		//�౦ʯ
#define PINK_GEM '9'   //�ϱ�ʯ

/*�����*/
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50


const char start_word[1000] = { "������Դ�Ͼ����ޣ�����ȴ���Ϸ��ܣ��������ͱ�Ȼ��������ѡ�����������������һ����������Դ�ά�����������ƽ�⣬ʣ�µ���һ����л����ø��á�������Ե��ƶ���������ޱ�ʯ��Ϊ�����������õ�δ��Ŭ���ɡ�" };
const char deadword[10][500]={{ "�Ϲ�����,�������ѡ� -- �����" },
{"�˵�һ��Ӧ�������ȹ�:��һ���˻�������ʱ,��������껪���ں�,Ҳ����µµ��Ϊ������;\n\
                                                                      ����,����������ʱ��,�ܹ�˵,�Ұ�����������ȫ���������׸�������������ҵ����Ϊ����Ľ�Ŷ��ܶ���\n\
                                                                                                                                                          --���������˹�����˹��"}
,{"�����Թ�˭��������ȡ�����պ��ࡣ  --������"}
,{"�������˽ܣ�����Ϊ���ۡ� --������"}
,{"ÿ���˶�����ȥ,������ÿ���˶��������������---���¸ҵ��ġ�"}
,{"��ʦδ������������ʹӢ����մ�� ���� �Ÿ�"}
};

const char gem_name[6][100] = { {"������ʯ"},{"ʱ�䱦ʯ"},{"�ռ䱦ʯ"},{"��걦ʯ"},{"��ʵ��ʯ"}, {"���鱦ʯ" } };

const char end_of_game[1000] = { "���ź�����Ҳ��Ϊ�˱�ѡ�е��Ƕ���֮һ������֮�ʣ���ͻȻ�������״���ȥ��ʶ������Ǹ����硣��ʱ��̩̹����һ��ԭʼ��������ʺ�«έ�ǳɵ����ӣ��غӰ��ſ����ļ��ĺ�ˮ�峺���ף��Ӱ���ůʯ��׹⻬����ʷǰ�޵�������������ʼ��������ﻹû�����֣��ᵽ��ʱ����������ָָ��㡣 ��Ҳ�ز�ȥ�˰������������ţ�������˫��" };

class Super_mario
{
public:
	bool alive;
	bool have_gem;
	void set_cmd_console()   const;  //�������� ��Ļ��С

	void Init_map(int Leval);                //���ļ��ж�ȡ ����ʼ����ͼ
	void paint_map() const;		//��ӡ��ͼ

	void paint_mario() const;      //��ӡ����
	void move_left();      //��������
	void move_right();    //��������
	void jump();         //������Ծ
	void gravity();        //��������----moveleft moveright jump ��������
	void mask_mario() const;     //�ƶ����ȥԭλ�õ������


	bool judge_end()  const; //�жϹؿ�����
	bool judge_dead()  const;  //�ж������Ƿ�����

	Super_mario();
		
	

private:
	void paint_cell(int col,int row,int mode) const; //��ӡһ������

	char map[Map_row][Map_col];
	int player_pos_x;
	int player_pos_y;
	int acclerrate;
	int speed;
	int time;    //�Ϳ�ʱ��

};


#pragma once
