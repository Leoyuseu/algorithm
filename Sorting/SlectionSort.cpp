#include <iostream>  
using namespace std;

template <class T>
void SelectionSort(T a[], int n)
{//��ʱ��ֹ��ѡ������
	bool sorted = false;
	for (int size = n; !sorted && (size>1); size--)
	{
		int pos = 0;
		sorted = true;
		//�����Ԫ��
		for (int i = 1; i<size; i++)
		if (a[pos] <= a[i])
			pos = i;//����Ѿ��������У���ô�Ͳ�����else�Ļ��ᣬsortedҲ��һֱΪtrue����콫��ֹ�ⲿforѭ����
		else
			sorted = false;//��δ�������У���ʾ��Ҫ�ⲿforѭ��
		Swap(a[pos], a[size - 1]);
		show(a, n);
	}
}

template<class T>
void Swap(T&a, T&b)
{
	T temp = a;
	a = b;
	b = temp;
	return;
}

template <class T>
void show(T arr, int n){
	for (int i = 0; i<n - 1; i++){
		cout << arr[i] << ",";
	}
	cout << arr[n - 1] << endl;
}

void main()
{
	int inputNumber[] = { 2, 7, 5, 9, 1, 4, 6, 3, 8 };
	int count = 9;
	cout << "ԭʼ���飺" << endl;
	show(inputNumber, count);
	cout << "������̣�" << endl;
	SelectionSort(inputNumber, count);
	cout << "��������" << endl;
	show(inputNumber, count);
}