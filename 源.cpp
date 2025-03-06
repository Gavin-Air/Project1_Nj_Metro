#include<easyx.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
constexpr int LIM = 64;
using namespace std;
void button_print(int x1, int y1, int x2, int y2,int f, string name,bool b)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(178, 255, 255));
	if(b)fillrectangle(x1, y1, x2, y2);
	else solidrectangle(x1, y1, x2, y2);
	setbkmode(TRANSPARENT);
	settextstyle(f, 0, "黑体");
	outtextxy((x1 + x2 - textwidth(name.c_str())) / 2, (y1 + y2 - textheight(name.c_str())) / 2, name.c_str());
}
void model_print() 
{
	cleardevice();
	button_print(20, 120, 180, 180, 25, "信息查询",1);
	button_print(20, 240, 180, 300, 25, "票务查询",1);
	button_print(20, 360, 180, 420, 25, "退出",1);
	setfillcolor(BLACK);
	solidrectangle(200, 0, 200, 540);
}
int model_select(ExMessage msg) {
	if (msg.x > 20 && msg.x < 180 && msg.y>120 && msg.y < 180)
		return -10;
	if (msg.x > 20 && msg.x < 180 && msg.y>240 && msg.y < 300)
		return -20;
	if (msg.x > 20 && msg.x < 180 && msg.y>360 && msg.y < 420)
		return -30;
	return 0;
}
void list_print(int n, vector<string>& name,bool b)
{
	int i = 0;
	if (n < 33) {
		for (; i < n; ++i) {
			if (name[i].size() < 7)
				button_print(220 + (i % 4) * 120, 40 + (i / 4) * 60, 340 + (i % 4) * 120, 100 + (i / 4) * 60, 26, name[i], b);
			if (name[i].size() < 9 && name[i].size() > 7)
				button_print(220 + (i % 4) * 120, 40 + (i / 4) * 60, 340 + (i % 4) * 120, 100 + (i / 4) * 60, 22, name[i], b);
			if (name[i].size() < 13 && name[i].size() > 9)
				button_print(220 + (i % 4) * 120, 40 + (i / 4) * 60, 340 + (i % 4) * 120, 100 + (i / 4) * 60, 16, name[i], b);
			if ( name[i].size() > 13)
				button_print(220 + (i % 4) * 120, 40 + (i / 4) * 60, 340 + (i % 4) * 120, 100 + (i / 4) * 60, 14, name[i], b);
		}
	}
	else {
		for (; i < n; ++i) {
			if (name[i].size() < 7)
				button_print(220 + (i % 6) * 80, 40 + (i / 6) * 40, 300 + (i % 6) * 80, 80 + (i / 6) * 40, 18, name[i], b);
			if (name[i].size() < 9 && name[i].size() > 7)
				button_print(220 + (i % 6) * 80, 40 + (i / 6) * 40, 300 + (i % 6) * 80, 80 + (i / 6) * 40, 16, name[i], b);
			if (name[i].size() < 13 && name[i].size() > 9)
				button_print(220 + (i % 6) * 80, 40 + (i / 6) * 40, 300 + (i % 6) * 80, 80 + (i / 6) * 40, 12, name[i], b);
			if (name[i].size() > 13)
				button_print(220 + (i % 6) * 80, 40 + (i / 6) * 40, 300 + (i % 6) * 80, 80 + (i / 6) * 40, 8, name[i], b);
		}
	}
	button_print(220, 20, 280, 40, 12, "<-返回", 1);
}
int list_button(int n, ExMessage msg)
{
	int k = 0;
	if (n < 33) 
		k = ((msg.y - 40) / 60) * 4 + (msg.x - 220) / 120;
	else k= ((msg.y - 40) / 40) * 6 + (msg.x - 220) / 80;
	if ((msg.y-40)<0&&msg.x<280)k = -101;
	return k + 1;
}
struct Station {
	string name;
	string next_station1; string line1; int distance1; int seat1;
	string next_station2; string line2; int distance2; int seat2;
	string next_station3; string line3; int distance3; int seat3;
	string next_station4; string line4; int distance4; int seat4;
	string next_station5; string line5; int distance5; int seat5;
	string next_station6; string line6; int distance6; int seat6;
};
struct Lin {
	string name;
	int seat;
};
struct Road {
	string name;
	string line;
};
int find_next_station(int i, string line, string station, vector<Station>& tf) {
	if (tf[i].line1 == line && tf[i].next_station1 != station)
		return tf[i].seat1;
	if (tf[i].line2 == line && tf[i].next_station2 != station)
		return tf[i].seat2;
	if (tf[i].line3 == line && tf[i].next_station3 != station)
		return tf[i].seat3;
	if (tf[i].line4 == line && tf[i].next_station4 != station)
		return tf[i].seat4;
	if (tf[i].line5 == line && tf[i].next_station5 != station)
		return tf[i].seat5;
	if (tf[i].line6 == line && tf[i].next_station6 != station)
		return tf[i].seat6;
	return -1;
}
void store(int k, vector<Station>& tf,string line,string st2,int d,int i) {
	if (tf[i].next_station1.empty()) {
		tf[i].next_station1 = st2;
		tf[i].line1 = line;
		tf[i].distance1 = d;
		tf[i].seat1 = k;
	}
	else if (tf[i].next_station2.empty()) {
		tf[i].next_station2 = st2;
		tf[i].line2 = line;
		tf[i].distance2 = d;
		tf[i].seat2 = k;
	}
	else if (tf[i].next_station3.empty()) {
		tf[i].next_station3 = st2;
		tf[i].line3 = line;
		tf[i].distance3 = d;
		tf[i].seat3 = k;
	}
	else if (tf[i].next_station4.empty()) {
		tf[i].next_station4 = st2;
		tf[i].line4 = line;
		tf[i].distance4 = d;
		tf[i].seat4 = k;
	}
	else if (tf[i].next_station5.empty()) {
		tf[i].next_station5 = st2;
		tf[i].line5 = line;
		tf[i].distance5 = d;
		tf[i].seat5 = k;
	}
	else if (tf[i].next_station6.empty()) {
		tf[i].next_station6 = st2;
		tf[i].line6 = line;
		tf[i].distance6 = d;
		tf[i].seat6 = k;
	}
}
void line_push(vector<Road>& route1, vector<Road>& route2, int k) {
	for (int i = 0; i <= k; ++i) {
		route2[i].name = route1[i].name;
		route2[i].line = route1[i].line;
	}
	for (int i = k + 1; i < LIM;++i) {
		route2[i].name = "";
		route2[i].line = "";
	}
}
void find_road(vector<Station>& tf,int loca,vector<Road>& route1, vector<Road>& route2, vector<Road>& route3, int* d,int *s,int *c,string station,int k,int dis,int cha,string st2) {
	if (k>LIM-1)
		return;
	route3[k].name = tf[loca].name;
	if (tf[loca].name == st2) {
		route3[k].line = "";
		d[2] = dis;
		s[2] = k;
		c[2] = cha;
		if (d[0] > d[2]) {
			line_push(route3, route1, k);
			c[0] = c[2];
			d[0] = d[2];
			s[0] = s[2];
		}
		if (c[1] > c[2]||(c[1]==c[2]&&d[1]>d[2])) {
			line_push(route3, route2,k);
			s[1] = s[2];
			d[1] = d[2];
			c[1] = c[2];
		}
		return;
	}
	else {
		if (tf[loca].next_station1 != "" && tf[loca].next_station1 != station) {
			route3[k].line = tf[loca].line1;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat1, route1, route2, route3, d, s, c,tf[loca].name, k + 1, dis + tf[loca].distance1, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
		if (tf[loca].next_station2 != "" && tf[loca].next_station2 != station) {
			route3[k].line = tf[loca].line2;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat2, route1, route2, route3, d, s, c, tf[loca].name, k + 1, dis + tf[loca].distance2, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
		if (tf[loca].next_station3 != "" && tf[loca].next_station3 != station) {
			route3[k].line = tf[loca].line3;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat3, route1, route2, route3, d, s, c, tf[loca].name, k + 1, dis + tf[loca].distance3, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
		if (tf[loca].next_station4 != "" && tf[loca].next_station4 != station) {
			route3[k].line = tf[loca].line4;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat4, route1, route2, route3, d, s, c, tf[loca].name, k + 1, dis + tf[loca].distance4, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
		if (tf[loca].next_station5 != "" && tf[loca].next_station5 != station) {
			route3[k].line = tf[loca].line5;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat5, route1, route2, route3, d, s, c, tf[loca].name, k + 1, dis + tf[loca].distance5, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
		if (tf[loca].next_station6 != "" && tf[loca].next_station6 != station) {
			route3[k].line = tf[loca].line6;
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha += 1;
			find_road(tf, tf[loca].seat6, route1, route2, route3, d, s, c, tf[loca].name, k + 1, dis + tf[loca].distance6, cha, st2);
			if (k > 0 && route3[k - 1].line != route3[k].line)
				cha -= 1;
		}
	}
}
int main()
{
	initgraph(720, 540);
	HWND hnd1 = GetHWnd();
	HWND hnd2 = GetConsoleWindow();
	SetWindowText(hnd1, "南京地铁信息及票务查询程序");
	setbkcolor(RGB(255,237,188));
	cleardevice();
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(360 - textwidth("Loading...")/2, 270 - textheight("Loading...")/2, "Loading...");
	IMAGE img;
	ifstream fi;
	fi.open("./line_infor.txt", ios::in);
	int quantity = 0, i = 0, distance = 0;
	string line, stations, station1, station2,last_name;
	getline(fi, line);
	stringstream ss(line);
	ss >> quantity;
	vector<Lin>p(quantity, { "",0 });
	vector<Station>total_first;
	int k = 0;
	getline(fi, line);
	for (; i < quantity; ++i) {
		getline(fi, p[i].name);
		p[i].seat = k;
		while (getline(fi, line)) {
			if (line.empty())
				break;
			stringstream ss(line);
			ss >> stations >> distance;
			size_t index = stations.find("——");
			if (index != string::npos) {
				station1 = stations.substr(0, index);
				station2 = stations.substr(index + 4);
			}
			else {
				index = stations.find("-");
				station1 = stations.substr(0, index);
				station2 = stations.substr(index + 1);
			}
			int b1 = 0, b2 = 0, j1 = 0, j2 = 0;
			for (; j1 < k; ++j1) {
				if (station1 == total_first[j1].name && b1 == 0) {
					b1 = 1;
					break;
				}
			}
			for (; j2 < k; ++j2) {
				if (station2 == total_first[j2].name && b2 == 0) {
					b2 = 1;
					break;
				}
			}
			if (b1 == 0 && b2 == 0) {
				total_first.push_back({ station1,station2,p[i].name,distance,k+1 });
				total_first.push_back({ station2,station1,p[i].name,distance,k });
				k += 2;
			}
			if (b1 == 1 && b2 == 0) {
				total_first.push_back({ station2,station1,p[i].name,distance,j1 });
				store(k, total_first, p[i].name, station2, distance, j1);
				if (p[i].seat == k)
					p[i].seat = j1;
				k += 1;
			}
			if (b1 == 0 && b2 == 1) {
				total_first.push_back({ station1,station2,p[i].name,distance,j2 });
				store(k, total_first, p[i].name, station1, distance, j2);
				k += 1;
			}
			if (b1 + b2 == 2) {
				store(j2, total_first, p[i].name, station2, distance, j1);
				store(j1, total_first, p[i].name, station1, distance, j2);
			}
		}
	}
	loadimage(&img, "./map.jpg",500,526,1);
	model_print();
	putimage(210, 7, &img);
	settextstyle(14, 0, "黑体");
	outtextxy(100 - textwidth("Ver 1.1.2") / 2, 530 - textheight("Ver 1.1.2") / 2, "Ver 1.1.2");
	int b = 0;
	while (b==0) {
		ExMessage msg;
		getmessage(&msg, 1);
		if (msg.message == WM_LBUTTONDOWN)
			b = model_select(msg);
		if (b == -10)
			goto information_search;
		if (b == -20)
			goto ticket_search;
		if (b == -30)
			return 0;
	}
information_search:
	model_print();
	button_print(290, 100, 430, 240, 27, "站点查询",1);
	button_print(490, 300, 630, 440, 27, "线路查询",1);
	button_print(525, 150, 595, 190, 16, "南京地铁",0);
	button_print(325, 350, 395, 390, 16, "Nj Metro", 0);
	b = 0;
	while (b==0) {
		ExMessage msg;
		getmessage(&msg, 1);
		if (msg.message == WM_LBUTTONDOWN) {
			b = model_select(msg);
			if (b == -10)
				goto information_search;
			if (b == -20)
				goto ticket_search;
			if (b == -30)
				return 0;
			if (msg.x > 290 && msg.x < 430 && msg.y>100 && msg.y < 240)
				b = 1;
			if (msg.x > 490 && msg.x < 630 && msg.y>300 && msg.y < 440)
				b = 2;
		}
	}
	if (b == 1) {
		model_print();
		station1 = "";
		vector<string> names;
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, "黑体");
		outtextxy((920 - textwidth("请在控制台上输入需要查询的内容，按回车结束")) / 2, 270 - textheight("请")*3/2, "请在控制台上输入需要查询的内容，按回车结束");
		outtextxy((920 - textwidth("输入'c'以取消输入并返回上一级")) / 2, 270 - textheight("请")/2, "输入'c'以取消输入并返回上一级");
		outtextxy((920 - textwidth("若输入多个，则以第一个有结果的输入为准")) / 2, 270 + textheight("若")/2, "若输入多个，则以第一个有结果的输入为准");
		system("cls");
		ShowWindow(hnd2, SW_SHOWNA);
		cout << "请在这里输入需要查询的内容，按回车结束。" << endl;
		cout << "若需取消输入并返回上一级，请输入'c'并按下回车。" << endl;
		cout << "注：若输入多个，则以第一个有结果的输入为准。" << endl;
		while (names.size() == 0) {
			cin >> station1;
			if (station1 == "c") {
				ShowWindow(hnd1, SW_SHOWNA);
				goto information_search;
			}
			for (int j = 0; j < total_first.size(); ++j) {
				if (total_first[j].name.find(station1) != string::npos)
					names.push_back(total_first[j].name);
			}
			if (!names.size())
				cout << "无查询结果，请重新输入……" << endl;
		}
		cout << "共计查询到" << names.size() << "个结果，请在图形窗口查看。" << endl;
		ShowWindow(hnd1, SW_SHOWNA);
		model_print();
		list_print(names.size(), names, 1);
		cin.ignore(32, '\n');
		st_select:
		model_print();
		list_print(names.size(), names, 1);
		b = 0;
		while (b == 0) {
			ExMessage msg;
			getmessage(&msg, 1);
			if (msg.message == WM_LBUTTONDOWN)
				b = model_select(msg);
			if (b == -10)
				goto information_search;
			if (b == -20)
				goto ticket_search;
			if (b == -30)
				return 0;
			if (msg.x < 280 && msg.x>220 && msg.y > 20 && msg.y < 40 && msg.message == WM_LBUTTONDOWN)
				goto information_search;
			if (b == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520 && msg.message == WM_LBUTTONDOWN)
				b = list_button(names.size(), msg);
			if (b > names.size())b = 0;
		}
		vector<string>name;
		for (i = 0; i < total_first.size(); ++i) {
			if (total_first[i].name == names[b-1])
				break;
		}
		k = 1;
		name.push_back(total_first[i].line1);
		if (total_first[i].line2 != total_first[i].line1 && total_first[i].line2 != "") {
			name.push_back(total_first[i].line2);
			++k;
		}
		if (total_first[i].line3 != total_first[i].line2 && total_first[i].line3 != "") {
			name.push_back(total_first[i].line3);
			++k;
		}
		if (total_first[i].line4 != total_first[i].line3 && total_first[i].line4 != "") {
			name.push_back(total_first[i].line4);
			++k;
		}
		if (total_first[i].line5 != total_first[i].line4 && total_first[i].line5 != "") {
			name.push_back(total_first[i].line5);
			++k;
		}
		if (total_first[i].line6 != total_first[i].line5 && total_first[i].line6 != "") {
			name.push_back(total_first[i].line6);
			++k;
		}
		model_print();
		list_print(name.size(), name, 0);
		vector<string>().swap(name);
		b = 0;
		while (b == 0) {
			ExMessage msg;
			getmessage(&msg, 1);
			if (msg.message == WM_LBUTTONDOWN)
				b = model_select(msg);
			if (b == -10)
				goto information_search;
			if (b == -20)
				goto ticket_search;
			if (b == -30)
				return 0;
			if (msg.x < 280 && msg.x>220 && msg.y > 20 && msg.y < 40 && msg.message == WM_LBUTTONDOWN)
				goto st_select;
		}
	}
	else {line_select:
		model_print();
		vector<string> names(quantity);
		for (int j = 0; j < quantity; ++j)
			names[j] = p[j].name;
		list_print(quantity, names,1);
		b = 0;
		while (b == 0 || b > 12) {
			ExMessage msg;
			getmessage(&msg, 1);
			if (msg.message == WM_LBUTTONDOWN) {
				b = model_select(msg);
				if (b == -10)
					goto information_search;
				if (b == -20)
					goto ticket_search;
				if (b == -30)
					return 0;
				if (b == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
					b = list_button(12, msg);
				if (b == -100)
					goto information_search;
				if (b > -100 && b < 1)b = 0;
			}
		}
		b -= 1;
		vector<string>().swap(names);
		vector<string>name;
		k = p[b].seat;
		int K=0;
		while (k != -1) {
			name.push_back(total_first[k].name);
			last_name = total_first[K].name;
			K = k;
			k = find_next_station(k, p[b].name, last_name, total_first);
		}
		model_print();
		list_print(name.size(), name, 0);
		b = 0;
		vector<string>().swap(name);
		while (b == 0) {
			ExMessage msg;
			getmessage(&msg, 1);
			if (msg.message == WM_LBUTTONDOWN)
				b = model_select(msg);
			if (b == -10)
				goto information_search;
			if (b == -20)
				goto ticket_search;
			if (b == -30)
				return 0;
			if (msg.x < 280 && msg.x>220 && msg.y > 20 && msg.y < 40&& msg.message == WM_LBUTTONDOWN)
				goto line_select;
		}
	}
ticket_search:
	station1 = "";
	station2 = "";
	while (station1 == "" || station2 == "") {
		model_print();
		setbkmode(TRANSPARENT);
		settextstyle(28, 0, "黑体");
		outtextxy((920 - textwidth("请选择起点站和终点站")) / 2, 150 - textheight("请") / 2, "请选择起点站和终点站");
		button_print(290, 260, 430, 400, 24, "选择起点站", 1);
		button_print(490, 260, 630, 400, 24, "选择终点站", 1);
		b = 0;
		while (b == 0) {
			ExMessage msg;
			getmessage(&msg, 1);
			if (msg.message == WM_LBUTTONDOWN) {
				b = model_select(msg);
				if (b == -10)
					goto information_search;
				if (b == -20)
					goto ticket_search;
				if (b == -30)
					return 0;
				if (msg.x > 290 && msg.x < 430 && msg.y>260 && msg.y < 400)
					b = 1;
				if (msg.x > 490 && msg.x < 630 && msg.y>260 && msg.y < 400)
					b = 2;
			}
		}
		infor_s:
		int b1 = 0;
		if (b == 1) {
			if (station1 != "") {
				model_print();
				settextstyle(30, 0, "黑体");
				outtextxy((920 - textwidth("起点站已选择")) / 2, 150 - textheight("起") / 2, "起点站已选择");
				button_print(300, 300, 420, 360, 24, "<-返回", 1);
				button_print(500, 300, 620, 360, 24, "重新选择", 1);
				b1 = 0;
				while (b1 == 0) {
					ExMessage msg;
					getmessage(&msg, 1);
					if (msg.message == WM_LBUTTONDOWN) {
						b1 = model_select(msg);
						if (b1 == -10)
							goto information_search;
						if (b1 == -20)
							goto ticket_search;
						if (b1 == -30)
							return 0;
						if (msg.x > 300 && msg.x < 420 && msg.y>300 && msg.y < 360)
							b1 = 1;
						if (msg.x > 500 && msg.x < 620 && msg.y>300 && msg.y < 360)
							b1 = 2;
					}
				}
				if (b1 == 2)station1.clear();
				continue;
			}
			else {infor_s1:
				model_print();
				button_print(300, 180, 620, 240, 24, "通过站点查询选择起点", 1);
				button_print(300, 300, 620, 360, 24, "通过线路查询选择起点", 1);
				b1 = 0;
				while (b1 == 0) {
					ExMessage msg;
					getmessage(&msg, 1);
					if (msg.message == WM_LBUTTONDOWN) {
						b1 = model_select(msg);
						if (b1 == -10)
							goto information_search;
						if (b1 == -20)
							goto ticket_search;
						if (b1 == -30)
							return 0;
						if (msg.x > 300 && msg.x < 620 && msg.y>180 && msg.y < 240)
							b1 = 1;
						if (msg.x > 300 && msg.x < 620 && msg.y>300 && msg.y < 360)
							b1 = 2;
					}
				}
				if (b1 == 1) {
					model_print();
					station1 = "";
					vector<string> names;
					setbkmode(TRANSPARENT);
					settextstyle(20, 0, "黑体");
					outtextxy((920 - textwidth("请在控制台上输入需要查询的内容，按回车结束")) / 2, 270 - textheight("请") * 3 / 2, "请在控制台上输入需要查询的内容，按回车结束");
					outtextxy((920 - textwidth("输入'c'以取消输入并返回上一级")) / 2, 270 - textheight("请") / 2, "输入'c'以取消输入并返回上一级");
					outtextxy((920 - textwidth("若输入多个，则以第一个有结果的输入为准")) / 2, 270 + textheight("若") / 2, "若输入多个，则以第一个有结果的输入为准");
					system("cls");
					ShowWindow(hnd2, SW_SHOWNA);
					cout << "请在这里输入需要查询的内容，按回车结束。" << endl;
					cout << "若需取消输入并返回上一级，请输入'c'并按下回车。" << endl;
					cout << "注：若输入多个，则以第一个有结果的输入为准。" << endl;
					while (names.size() == 0) {
						cin >> station1;
						if (station1 == "c") {
							ShowWindow(hnd1, SW_SHOWNA);
							goto infor_s1;
						}
						for (int j = 0; j < total_first.size(); ++j) {
							if (total_first[j].name.find(station1) != string::npos)
								names.push_back(total_first[j].name);
						}
						if (!names.size())
							cout << "无查询结果，请重新输入……" << endl;
					}
					model_print();
					cout << "共计查询到" << names.size() << "个结果，请在图形窗口查看。" << endl;
					ShowWindow(hnd1, SW_SHOWNA);
					list_print(names.size(), names, 1);
					cin.ignore(32, '\n');
					int b2 = 0;
					while (b2 == 0 || b2 > names.size()) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(names.size(), msg);
							if (b2 == -100)
								goto infor_s1;
							if (b2 > -100 && b2 < 1)b = 0;
						}
					}
					b2 -= 1;
					station1 = names[b2];
					vector<string>().swap(names);
				}
				else {line_sel1:
					model_print();
					vector<string> names(quantity);
					for (int j = 0; j < quantity; ++j)
						names[j] = p[j].name;
					list_print(quantity, names, 1);
					int b2 = 0;
					while (b2 == 0 || b2 > 12) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(12, msg);
							if (b2 == -100)
								goto infor_s1;
							if (b2 > -100 && b2 < 1)b2 = 0;
						}
					}
					b2 -= 1;
					vector<string>().swap(names);
					vector<string>name;
					k = p[b2].seat;
					int K = 0;
					while (k != -1) {
						name.push_back(total_first[k].name);
						last_name = total_first[K].name;
						K = k;
						k = find_next_station(k, p[b2].name, last_name, total_first);
					}
					model_print();
					list_print(name.size(), name, 1);
					b2 = 0;
					while (b2 == 0 || b2 > name.size()) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(name.size(), msg);
							if (b2 == -100) {
								goto line_sel1;
								vector<string>().swap(name);
							}
							if (b2 > -100 && b2 < 1)b2 = 0;
						}
					}
					b2 -= 1;
					station1 = name[b2];
					vector<string>().swap(name);
				}
			}
		}
		else {
			if (station2 != "") {
				model_print();
				settextstyle(30, 0, "黑体");
				outtextxy((920 - textwidth("终点站已选择")) / 2, 150 - textheight("起") / 2, "终点站已选择");
				button_print(300, 300, 420, 360, 24, "<-返回", 1);
				button_print(500, 300, 620, 360, 24, "重新选择", 1);
				b1 = 0;
				while (b1 == 0) {
					ExMessage msg;
					getmessage(&msg, 1);
					if (msg.message == WM_LBUTTONDOWN) {
						b1 = model_select(msg);
						if (b1 == -10)
							goto information_search;
						if (b1 == -20)
							goto ticket_search;
						if (b1 == -30)
							return 0;
						if (msg.x > 300 && msg.x < 420 && msg.y>300 && msg.y < 360)
							b1 = 1;
						if (msg.x > 500 && msg.x < 620 && msg.y>300 && msg.y < 360)
							b1 = 2;
					}
				}
				if (b1 == 2)station2 = "";
				continue;
			}
			else {infor_s2:
				model_print();
				button_print(300, 180, 620, 240, 24, "通过站点查询选择终点", 1);
				button_print(300, 300, 620, 360, 24, "通过线路查询选择终点", 1);
				b1 = 0;
				while (b1 == 0) {
					ExMessage msg;
					getmessage(&msg, 1);
					if (msg.message == WM_LBUTTONDOWN) {
						b1 = model_select(msg);
						if (b1 == -10)
							goto information_search;
						if (b1 == -20)
							goto ticket_search;
						if (b1 == -30)
							return 0;
						if (msg.x > 300 && msg.x < 620 && msg.y>180 && msg.y < 240)
							b1 = 1;
						if (msg.x > 300 && msg.x < 620 && msg.y>300 && msg.y < 360)
							b1 = 2;
					}
				}
				if (b1 == 1) {
					model_print();
					station2 = "";
					vector<string> names;
					setbkmode(TRANSPARENT);
					settextstyle(20, 0, "黑体");
					outtextxy((920 - textwidth("请在控制台上输入需要查询的内容，按回车结束")) / 2, 270 - textheight("请") * 3 / 2, "请在控制台上输入需要查询的内容，按回车结束");
					outtextxy((920 - textwidth("输入'c'以取消输入并返回上一级")) / 2, 270 - textheight("请") / 2, "输入'c'以取消输入并返回上一级");
					outtextxy((920 - textwidth("若输入多个，则以第一个有结果的输入为准")) / 2, 270 + textheight("若") / 2, "若输入多个，则以第一个有结果的输入为准");
					system("cls");
					ShowWindow(hnd2, SW_SHOWNA);
					cout << "请在这里输入需要查询的内容，按回车结束。" << endl;
					cout << "若需取消输入并返回上一级，请输入'c'并按下回车。" << endl;
					cout << "注：若输入多个，则以第一个有结果的输入为准。" << endl;
					while (names.size() == 0) {
						cin >> station2;
						if (station2 == "c") {
							ShowWindow(hnd1, SW_SHOWNA);
							goto infor_s2;
						}
						for (int j = 0; j < total_first.size(); ++j) {
							if (total_first[j].name.find(station2) != string::npos)
								names.push_back(total_first[j].name);
						}
						if (!names.size())
							cout << "无查询结果，请重新输入……" << endl;
					}
					model_print();
					cout << "共计查询到" << names.size() << "个结果，请在图形窗口查看。" << endl;
					ShowWindow(hnd1, SW_SHOWNA);
					list_print(names.size(), names, 1);
					cin.ignore(32, '\n');
					int b2 = 0;
					while (b2 == 0 || b2 > names.size()) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(names.size(), msg);
							if (b2 == -100)
								goto infor_s2;
							if (b2 > -100 && b2 < 1)b = 0;
						}
					}
					b2 -= 1;
					station2 = names[b2];
					vector<string>().swap(names);
				}
				else {line_sel2:
					model_print();
					vector<string> names(quantity);
					for (int j = 0; j < quantity; ++j)
						names[j] = p[j].name;
					list_print(quantity, names, 1);
					int b2 = 0;
					while (b2 == 0 || b2 > 12) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(12, msg);
							if (b2 == -100)
								goto infor_s2;
							if (b2 > -100 && b2 < 1)b2 = 0;
						}
					}
					b2 -= 1;
					vector<string>().swap(names);
					vector<string>name;
					k = p[b2].seat;
					int K = 0;
					while (k != -1) {
						name.push_back(total_first[k].name);
						last_name = total_first[K].name;
						K = k;
						k = find_next_station(k, p[b2].name, last_name, total_first);
					}
					model_print();
					list_print(name.size(), name, 1);
					b2 = 0;
					while (b2 == 0 || b2 > name.size()) {
						ExMessage msg;
						getmessage(&msg, 1);
						if (msg.message == WM_LBUTTONDOWN) {
							b2 = model_select(msg);
							if (b2 == -10)
								goto information_search;
							if (b2 == -20)
								goto ticket_search;
							if (b2 == -30)
								return 0;
							if (b2 == 0 && msg.x > 220 && msg.x < 700 && msg.y>20 && msg.y < 520)
								b2 = list_button(name.size(), msg);
							if (b2 == -100)
								goto line_sel2;
							if (b2 > -100 && b2 < 1)b2 = 0;
						}
					}
					b2 -= 1;
					station2 = name[b2];
					vector<string>().swap(name);
				}
			}
		}
	}
	re_select:
	model_print();
	button_print(300, 120, 620, 180, 24, "起点站："+station1, 1);
	button_print(300, 240, 620, 300, 24, "终点站："+station2, 1);
	button_print(360, 360, 560, 420, 25, "出发->", 1);
	b = 0;
	while (b == 0) {
		ExMessage msg;
		getmessage(&msg, 1);
		if (msg.message == WM_LBUTTONDOWN) {
			b = model_select(msg);
			if (b == -10)
				goto information_search;
			if (b == -20)
				goto ticket_search;
			if (b == -30)
				return 0;
			if (msg.x > 300 && msg.x < 620 && msg.y>120 && msg.y < 180) {
				b = 1;
				station1 = "";
				goto infor_s;
			}
			if (msg.x > 300 && msg.x < 620 && msg.y>240 && msg.y < 300) {
				b = 2;
				station2 = "";
				goto infor_s;
			}
			if (msg.x > 360 && msg.x < 560 && msg.y>360 && msg.y < 420)
				b = 3;
		}
	}
	if (station1 == station2) {
		model_print();
		IMAGE img2;
		loadimage(&img2, "./nxz.jpg", 488, 514);
		putimage(214, 13, &img2);
		Sleep(1000);
		goto re_select;
	}
	vector<Road>route1(LIM);
	vector<Road>route2(route1);
	vector<Road>route3(route1);
	int dista[3] = { 0 };
	int steps[3] = { 0 };
	int chan[3] = { 0 };
	chan[1] = 12;
	dista[0] = 200000;
	steps[1] = LIM;
	for (i = 0; i < total_first.size(); ++i) {
		if (total_first[i].name == station1) {
			k = i;
			break;
		}
	}
	model_print();
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(460 - textwidth("Loading...") / 2, 270 - textheight("Loading...") / 2, "Loading...");
	find_road(total_first, k, route1, route2, route3, dista, steps, chan, "蓝鲸", 0, 0, 0, station2);//Core
	int price = 0;
	if (dista[0] < 4001)price = 2;
	else if (dista[0] < 9001)price = 3;
	else if (dista[0] < 14001)price = 4;
	else if (dista[0] < 21001)price = 5;
	else if (dista[0] < 28001)price = 6;
	else if (dista[0] < 37001)price = 7;
	else if (dista[0] < 48001)price = 8;
	else if (dista[0] < 61001)price = 9;
	else price = 10 + (dista[0] - 61001) / 15000;
	model_print();
	if (dista[0] == dista[1] && chan[0] == chan[1] && steps[0] == steps[1]) {
		if (chan[0] == 0)
			line = "直达：";
		else
			line = "·换乘" + to_string(chan[0]) + "次:";
		button_print(220, 40, 320, 100, 20, line, 0);
		button_print(220, 100, 280, 130, 16, to_string(steps[0]) + "站", 0);
		k = 0;
		for (i = 0; i < chan[0] + 1; ++i) {
			line = "";
			button_print(320, i * 60+40, 400, i * 60 + 100, 20, route1[k].line, 0);
			line += route1[k].name;
			while (route1[k].line == route1[k + 1].line)
				k += 1;
			k += 1;
			line += "—";
			line += route1[k].name;
			button_print(400, i * 60 + 40, 700, i * 60 + 100, 20, line, 0);
		}
		button_print(220, 460, 320, 500, 16, "票价：" + to_string(price) + "元", 0);
		button_print(220, 500, 460, 520, 12, "注：该结果仅供参考，请以实际价格为准。", 0);
	}
	else if(dista[1]>dista[0]+3000) {
		button_print(220, 40, 300, 80, 16, "路程最短:", 0);
		button_print(220, 80, 260, 100, 12, to_string(steps[0]) + "站", 0);
		k = 0;
		for (i = 0; i < chan[0] + 1; ++i) {
			line = "";
			button_print(300, i * 40 + 40, 360, i * 40 + 80, 16, route1[k].line, 0);
			line += route1[k].name;
			while (route1[k].line == route1[k + 1].line)
				k += 1;
			k += 1;
			line += "—";
			line += route1[k].name;
			button_print(360, i * 40 + 40, 700, i * 40 + 80, 16, line, 0);
		}
		button_print(220, 40 + (chan[0] + 1) * 40, 300, 80 + (chan[0] + 1) * 40, 16, "换乘最少:", 0);
		button_print(220, 80 + (chan[0] + 1) * 40, 260, 100 + (chan[0] + 1) * 40, 12, to_string(steps[1]) + "站", 0);
		k = 0;
		for (i = 0; i < chan[1] + 1; ++i) {
			line = "";
			button_print(300, 40 + i * 40 + (chan[0] + 1) * 40, 360, 80 + i * 40 + (chan[0] + 1) * 40, 16, route2[k].line, 0);
			line += route2[k].name;
			while (route2[k].line == route2[k + 1].line)
				k += 1;
			k += 1;
			line += "—";
			line += route2[k].name;
			button_print(360, i * 40 + (chan[0] + 1) * 40 + 40, 700, i * 40 + (chan[0] + 1) * 40 + 80, 16, line, 0);
		}
		button_print(220, 480, 300, 510, 14, "票价：" + to_string(price) + "元", 0);
		button_print(220, 510, 400, 520, 8, "注：该结果仅供参考，请以实际价格为准。", 0);
	}
	else {
		if(chan[1]==0)
			button_print(220, 40, 300, 80, 16, "直达：", 0);
		else button_print(220, 40, 300, 80, 16, "换乘最少:", 0);
		button_print(220, 80, 260, 100, 12, to_string(steps[1]) + "站", 0);
		k = 0;
		for (i = 0; i < chan[1] + 1; ++i) {
			line = "";
			button_print(300, i * 40 + 40, 360, i * 40 + 80, 16, route2[k].line, 0);
			line += route2[k].name;
			while (route2[k].line == route2[k + 1].line)
				k += 1;
			k += 1;
			line += "—";
			line += route2[k].name;
			button_print(360, i * 40 + 40, 700, i * 40 + 80, 16, line, 0);
		}
		if (chan[1] == 0) chan[1] = 1;
		button_print(220, 40 + (chan[1] + 1) * 40, 300, 80 + (chan[1] + 1) * 40, 16, "路程最短:", 0);
		button_print(220, 80 + (chan[1] + 1) * 40, 260, 100 + (chan[1] + 1) * 40, 12, to_string(steps[0]) + "站", 0);
		k = 0;
		for (i = 0; i < chan[0] + 1; ++i) {
			line = "";
			button_print(300, 40 + i * 40 + (chan[1] + 1) * 40, 360, 80 + i * 40 + (chan[1] + 1) * 40, 16, route1[k].line, 0);
			line += route1[k].name;
			while (route1[k].line == route1[k + 1].line)
				k += 1;
			k += 1;
			line += "—";
			line += route1[k].name;
			button_print(360, i * 40 + (chan[1] + 1) * 40 + 40, 700, i * 40 + (chan[1] + 1) * 40 + 80, 16, line, 0);
		}
		button_print(220, 480, 300, 510, 14, "票价：" + to_string(price) + "元", 0);
		button_print(220, 510, 400, 520, 8, "注：该结果仅供参考，请以实际价格为准。", 0);
	}
	button_print(220, 20, 280, 40, 12, "<-返回", 1);
	b = 0;
	while (b == 0) {
		ExMessage msg;
		getmessage(&msg, 1);
		if (msg.message == WM_LBUTTONDOWN)
			b = model_select(msg);
		if (b == -10)
			goto information_search;
		if (b == -20)
			goto ticket_search;
		if (b == -30)
			return 0;
		if (msg.x < 280 && msg.x>220 && msg.y > 20 && msg.y < 40 && msg.message == WM_LBUTTONDOWN)
			goto ticket_search;
	}
	return 0;
}