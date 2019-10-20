/*flapy_bird*/
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <time.h>
#include <queue>


#define SINEHEIGHT 20
#define DEGREESTEP 5


//初始化游戏中的数据
int IS_NOT_CRACK = 1;
int bird_x, bird_y, bird_v;//鸟儿的位置和掉落的速度
//int hinder_w, hinder_h, hinder_v, hinder_x, hinder_y; //障碍物的位置、长、宽和运动的速度
int score{ 0 },score_x, score_y; //得分和得分显示的位置
int level{ 0 }, level_x, level_y;//关卡和关卡显示的位置
int HEIGHT = 30;
int WIDTH = 200;
const int window_width = 115;
const int window_height = 25;
int flag = 0;//循环产生新的障碍物


using color = char;
color* framebuffer{ nullptr };
int framebuffer_width, framebuffer_height;
color clear_color{ ' ' };
color boundry_color{ '|' };
color wall_color{ '=' };
color bird_color{ '@' };
color hinder_color{ 'z' };

using namespace std;

//定义障碍类
class hinder 
{
public:
	int hinder_w = 10;
	int hinder_h = 8;
	int hinder_x = 100;
	int hinder_y;
	int hinder_v = 1;
	hinder(int high);
	void move() {
		//障碍物移动
		this->hinder_x -= this->hinder_v;
	}
	bool iscrack() {
		//判断是否碰撞
		if (bird_x >= this->hinder_x && bird_x <= this->hinder_x + hinder_w)
			if (bird_y < this->hinder_y || bird_y > this->hinder_y + this->hinder_h)
				return true;
			else
				return false;
		else if (bird_y > 25)
			return true;
		else
			return false;
	}

};
hinder::hinder(int high)
{
	hinder_y = high;
}

queue<hinder> q;	//存放障碍的队列

void clearWindow() {
	// clear the window
	for (int y = 0; y < framebuffer_height; y++)
		for (int x = 0; x < framebuffer_width; x++)
			framebuffer[y*framebuffer_width + x] = clear_color;
}

void setPixel(const int x, const int y, color c) {
	//设置某一块区域的颜色
	framebuffer[y*framebuffer_width + x] = c;
}

bool initWindow(int width, int height) {
	// init the window
	framebuffer = new color[width*height];
	if (!framebuffer) return false;
	framebuffer_width = width;
	framebuffer_height = height;
	clearWindow();
	return true;
}

void show() {
	for (int y = 0; y < framebuffer_height; y++) {
		for (int x = 0; x < framebuffer_width; x++)
			std::cout << framebuffer[y*framebuffer_width + x];
		std::cout << '\n';
	}
}

bool init(const int window_width = 115, const int window_height = 25) {
	//窗口宽115 高25
	// init the window
	if (!initWindow(window_width, window_height))
		return false;
	// init the location of the bird
	bird_x = window_width / 4;
	bird_y = window_height / 2;
	bird_v = -1;
	score = 0;
	score_x = 8;
	score_y = 3;
	//初始化随机函数 生成第一个障碍
	srand(unsigned(time(NULL)));
	hinder x(rand() % 15);
	q.push(x);
	
	return true;
}

void draw_background() {
	// draw the wall and boundry_color
	clearWindow();
	int &window_width = framebuffer_width, &window_height = framebuffer_height;
	auto right{ window_width - 1 };
	for (int y = 0; y < window_height; y++) {
		setPixel(0, y, boundry_color);
		setPixel(right, y, boundry_color);
	}
	int bottom = window_height - 1;
	for (int x = 0; x < window_width; x++) {
		setPixel(x, 0, wall_color);
		setPixel(x, bottom, wall_color);
	}
}

void draw_spirits() {
	//打印精灵
	setPixel(bird_x, bird_y, bird_color);
	//打印分数
	std::string s{ std::to_string(score) };
	std::string s1{ "score:" };
	for (auto i = 0; i < s1.size(); i++)
		setPixel(score_x + i, score_y, s1[i]);
	for (auto i = 0; i < s.size(); i++)
		setPixel(score_x + i + s1.size(), score_y, s[i]);
	//打印障碍物
	for (int e = 0; e < q.size(); e++) 
	{
		q.push(q.front());
		for (int s = 1; s < q.front().hinder_y; s++)
			for (int t = q.front().hinder_x; t < q.front().hinder_x + q.front().hinder_w; t++)
				setPixel(t, s, hinder_color);
		for (int s = q.front().hinder_y + q.front().hinder_h; s < window_height - 1; s++)
			for (int t = q.front().hinder_x; t < q.front().hinder_x + q.front().hinder_w; t++)
				setPixel(t, s, hinder_color);
		q.pop();
	}

}

void gotoxy(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void render_scene() {
	//在屏幕上打印元素
	gotoxy(0, 0);
	hideCursor();
	draw_background();
	draw_spirits();
	show();
}

int processInput() {
	//接受用户输入
	char key;
	if (_kbhit()) {
		key = _getch();
		if (key == 'w' || key == 'W')
			bird_v = 1;
	}
	return 1;
}

void update() {
	//防止小球下落速度过快
	//Sleep(50);
	//Sleep(2000);
	bird_y -= bird_v;
	bird_v = -1;
	//障碍物移动
	for (int e = 0; e < q.size(); e++)
	{
		q.front().move();
		q.push(q.front());
		q.pop();
	}
	//生成新的障碍物
	flag++;
	if (flag == 25) 
	{
		int seed;
		if (score == 6)
			seed = 25;
		else
			seed = rand() % 15;
		hinder x(seed);
		q.push(x);
		flag = 0;
	}
	//得分，并弹出当前第一个障碍物
	if (q.front().hinder_x + 10 == bird_x)
	{
		score++;
		q.pop();
	}
	
	//判断碰撞
	if (q.front().iscrack()) {
		printf("You lose!\nyour final score is %d", score);
		system("pause");
		Sleep(500);
		IS_NOT_CRACK = 0;
	}
}

int main() {
	init();
	while (IS_NOT_CRACK) {
		if (processInput() < 0)break;
		update();
		render_scene(); 
		if (score == 10)
		{
			string raw_flag = "_]Irl*{k$*OU,m|wpm},6YuJ";
			int s1[24] = { 9, 2, 50, 49, 45, 96, 4, 36, 5, 84, 9, 11, 51, 8, 9, 4, 27, 78, 12, 66, 6, 17, 2, 99 };
			int s2[24] = { 12, 1, 40, 7, 23, 33, 6, 0, 80, 3, 9, 47, 80, 6, 8, 2, 23, 95, 62, 28, 73, 42, 3, 68 };
			for (int i = 0; i < 24; i++)
				printf("%c", raw_flag[i] ^ s1[i] ^ s2[i] ^ 16);
			break;
		}

	}
	system("pause");
}