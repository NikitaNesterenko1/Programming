
#include <iostream>
#include <string>
using namespace std;

const string maze[25] = {
	"####B######################",
	"# #       #   #      #    #",
	"# # # ###### #### ####### #",
	"# # # #       #   #       #",
	"#   # # ######### # ##### #",
	"# # # #   #       #     # #",
	"### ### ### ############# #",
	"# #   #     # #           #",
	"# # #   ####### ###########",
	"# # # #       # #         C",
	"# # ##### ### # # ####### #",
	"# # #     ### # #       # #",
	"#   ##### ### # ######### #",
	"######### ### #           #",
	"# ####### ### #############",
	"A           #   ###   #   #",
	"# ############# ### # # # #",
	"# ###       # # ### # # # #",
	"# ######### # # ### # # # F",
	"#       ### # #     # # # #",
	"# ######### # ##### # # # #",
	"# #######   #       #   # #",
	"# ####### ######### #######",
	"#         #########       #",
	"#######E############D######"
};

const int dir[4][2] = { { 1,0 }, { 0,1 }, { -1,0 }, { 0,-1 } };

int turn_right(int d) {
	return  d == 3 ? 0 : d + 1;
}

int turn_left(int d) {
	return  d == 0 ? 3 : d - 1;
}

string check(char c) {
	if (c != '#' && c != ' ') {
		string s;
		s = c;
		return s + " ";
	}
	return "";
}

string search(int column, int row) {
	int c = column;
	int r = row;
	int columns = maze[0].size();
	int rows = size(maze);
	int d = 0;
	string exits = check(maze[r][c]);
	// проверка границы
	while (r + dir[d][1] < 0 || c + dir[d][0] < 0 || r + dir[d][1] >= rows || c + dir[d][0] >= columns) {
		d = turn_right(d);
	}
	// найти стену или выход
	while (maze[r + dir[d][1]][c + dir[d][0]] == ' ') {
		c += dir[d][0];
		r += dir[d][1];
	}
	d = turn_right(d);
	// start position and direction
	column = c;
	row = r;
	int direction = d;
	// найти выходы
	bool find = false;
	int it = 0;
	while (true) {
		// cout << ++it << '=' << c << ':' << r << ':' << d << endl;
		// проверка стены
		int left = turn_left(d);
		if (
			// проверка границы
			!(r + dir[left][1] < 0 || c + dir[left][0] < 0 || r + dir[left][1] >= rows || c + dir[left][0] >= columns)
			&&
			//
			maze[r + dir[left][1]][c + dir[left][0]] != '#') {
			d = left;
		}
		else {
			int i = 0;
			while (++i < 4 && (
				// проверка границы
				r + dir[d][1] < 0 || c + dir[d][0] < 0 || r + dir[d][1] >= rows || c + dir[d][0] >= columns
				||
				//
				maze[r + dir[d][1]][c + dir[d][0]] == '#')) {
				d = turn_right(d);
			}
			if (i == 4) {
				return exits;
			}
		}

		if (find && d == direction && c == column && r == row) {
			return exits;
		}
		find = true;
		c += dir[d][0];
		r += dir[d][1];
		exits += check(maze[r][c]);

	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int c, r;
	cout << "Введите координаты "; cin >> c >> r;

	if (c >= maze[0].size() || r >= size(maze) || '#' == maze[r][c]) {
		cout << "Неверные координаты";
	}
	else {
		string exits = search(c, r);
		if (exits.size() == 0) {
			cout << "Выхода нет";
		}
		else {
			cout << exits;
		}
	}
}