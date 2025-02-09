#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>
#include <cmath>

#define scale pow(10,3) //for time statistic, pow(10,3) is for ms
#define mxn 50000 //mxn is the maximum possible number of boxes

using namespace std;

struct Box
{
	int w;
	int d;
	int h;
	int area; //base area of each box, equals to w * d
};

int n = 5000;
Box b[3 * mxn];
int r[3 * mxn];
int msh[3 * mxn] = { 0 };
int cntr = 0;

void print_box(Box &b)
{
	cout << "h = " << b.h << "\tw = " << b.w << "\td = " << b.d  << "\tarea = " << b.area << endl;
}

bool cmp(const Box &a, const Box &b) //for sorting boxes in descending order
{
	return a.area > b.area;
}

void box_stacking_dp() //dp algorithm
{
	int mx_value = 0;
	for (int i = 0; i < 3 * n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (b[j].w > b[i].w && b[j].d > b[i].d)
			{
				mx_value = msh[j] + b[i].h;
				if (mx_value > msh[i])
				{
					msh[i] = mx_value;
					r[i] = j; //msh[i] comes from the msh[j] + vec_b[i].h, so here we record the "parent node" of msh[i], which is msh[j], in order to print the correct order of box stacking
				}
			}
		}
	}

	///*for printing the stacked boxes*/
	//__int64 start_idx = max_element(msh, msh + 3 * n) - msh, next_idx;
	//while (true)
	//{
	//	print_box(b[start_idx]); //print from the maximum element in msh[]
	//	next_idx = r[start_idx]; //next box to be printed = parent node of current printing box
	//	if (next_idx == start_idx) //we initialized the r[i] = i
	//	{
	//		break;
	//	}
	//	start_idx = next_idx; //print the next box
	//}
	
	cout << endl << "Maximum height = " << *(max_element(msh, msh + 3 * n)) << endl;
}

void input(int h, int w, int d) //3 possibilities for every box
{
	Box box;
	box.h = h;
	box.w = w;
	box.d = d;
	box.area = box.w * box.d;
	b[cntr++] = box;

	box.h = w;
	box.w = h;
	box.d = d;
	box.area = box.w * box.d;
	b[cntr++] = box;

	box.h = d;
	box.w = h;
	box.d = w;
	box.area = box.w * box.d;
	b[cntr++] = box;
}

int main()
{
	LARGE_INTEGER frec;
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;
	QueryPerformanceFrequency(&frec);
	while (n <= mxn)
	{
		cntr = 0;
		for (int i = 0; i < n; i++) //randomly generate boxes whose h, w, d are between [0,100]
		{
			input((rand() % 101) + 1, (rand() % 101) + 1, (rand() % 101) + 1);
		}
		//input(4, 6, 7);
		//input(4, 5, 6);
		//input(10, 12, 32);
		//input(1, 2, 3);
		sort(b, b + 3 * n, cmp); //sorting all boxes
		for (int i = 0; i < 3 * n; i++) // print all possible combination and initialize msh[] & r[]
		{
			msh[i] = b[i].h;
			r[i] = i;
			//print_box(vec_b[i]);
		}
		QueryPerformanceCounter(&strt);
		box_stacking_dp();
		QueryPerformanceCounter(&ed);
		cout << "Execution time when n = " << n << ": " << (ed.QuadPart - strt.QuadPart) * scale / frec.QuadPart << "ms" << endl;
		n += 5000;
	}
	
	return 0;
}