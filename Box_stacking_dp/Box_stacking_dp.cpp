#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <cmath>
#include <algorithm>
#define scale pow(10,3)
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

void sort(string s)
{
	if (s == "b")
	{
		Box b_tmp;
		for (int i = 0; i < 3 * n; i++)
		{
			for (int j = i + 1; j < 3 * n; j++)
			{

				if (b[j].area > b[i].area)
				{
					b_tmp = b[j];
					b[j] = b[i];
					b[i] = b_tmp;
				}
			}
		}
	}
	else
	{
		int temp;
		for (int i = 0; i < 3 * n; i++)
		{
			for (int j = i + 1; j < 3 * n; j++)
			{
				if (msh[j] > msh[i])
				{
					temp = msh[j];
					msh[j] = msh[i];
					msh[i] = temp;
				}
			}
		}
	}
}

int get_max_idx()
{
	int max_idx = 0;
	for (int i = 0; i < 3 * n; i++)
	{
		if (msh[i] > msh[max_idx])
		{
			max_idx = i;
		}
	}
	return max_idx;
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

	/*for printing the stacked boxes*/
	//int start_idx = get_max_idx(), next_idx;
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

	sort("msh");
	cout << endl << "Maximum height = " << msh[0] << endl;
}

void input(int h, int w, int d) //3 possibilities for every box
{
	Box box;
	w = max(w, d);
	d = min(w, d);
	box.h = h;
	box.w = w;
	box.d = d;
	box.area = box.w * box.d;
	b[cntr++] = box;

	h = max(h, d);
	d = min(h, d);
	box.h = w;
	box.w = h;
	box.d = d;
	box.area = box.w * box.d;
	b[cntr++] = box;

	w = max(w, h);
	d = min(w, h);
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
		//input(4, 7, 9);
		//input(5, 8, 9);
		//input(11, 20, 40);
		//input(1, 2, 3);
		sort("b"); //sorting all boxes
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
