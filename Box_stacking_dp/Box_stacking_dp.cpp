#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#define n 4 //n is the number of boxes

using namespace std;

struct Box
{
	int w;
	int d;
	int h;
	int area; //base area of each box, equals to w * d
};

vector <int> r(3 * n);
vector <Box> vec_b;
vector <int> msh(3 * n, 0);

void print_box(Box &b)
{
	cout << "h = " << b.h << "\tw = " << b.w << "\td = " << b.d  << "\tarea = " << b.area << endl;
}

bool cmp(Box &a, Box &b) //for sorting boxes
{
	return a.area > b.area;
}

int box_stacking_dp() //dp algorithm
{
	int mx_value = 0;
	for (int i = 0; i < 3 * n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (vec_b[j].w > vec_b[i].w && vec_b[j].d > vec_b[i].d)
			{
				mx_value = msh[j] + vec_b[i].h;
				if (mx_value > msh[i])
				{
					msh[i] = mx_value;
					r[i] = j;
				}
			}
		}
	}
	int start_idx = (int) (max_element(msh.begin(), msh.end()) - msh.begin());
	int next_idx;
	while (true)
	{
		print_box(vec_b[start_idx]);
		next_idx = r[start_idx];
		if (next_idx == start_idx)
		{
			break;
		}
		start_idx = next_idx;
	}
	return *(max_element(msh.begin(), msh.end()));
}

void input(int h, int w, int d) //3 possibilities for every box
{
	Box b;
	b.h = h;
	b.w = w;
	b.d = d;
	b.area = b.w * b.d;
	vec_b.push_back(b);

	b.h = w;
	b.w = h;
	b.d = d;
	b.area = b.w * b.d;
	vec_b.push_back(b);

	b.h = d;
	b.w = h;
	b.d = w;
	b.area = b.w * b.d;
	vec_b.push_back(b);
}

int main()
{
	//for (int i = 0; i < n; i++) //randomly generate boxes whose h, w, d are between [0,100]
	//{
	//	input((rand() % 101) + 1, (rand() % 101) + 1, (rand() % 101) + 1);
	//}
	input(4, 6, 7);
	input(4, 5, 6);
	input(10, 12, 32);
	input(1, 2, 3);

	sort(vec_b.begin(), vec_b.end(), cmp); //sorting all boxes
	for (int i = 0; i < 3 * n; i++) // print all possible combination
	{
		msh[i] = vec_b[i].h;
		r[i] = i;
		//print_box(vec_b[i]);
	}
	cout << endl << "Maximum height = " << box_stacking_dp() << endl;
	return 0;
}