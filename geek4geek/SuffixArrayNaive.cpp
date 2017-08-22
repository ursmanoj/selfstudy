#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct Suffix {
	char *suff;
	int index(char * str) {
		return suff - str;
	}
};

#define MAX_ARR_SIZE 50

static Suffix suffArr[MAX_ARR_SIZE];
static int suffCount;

static void quickSort(int first, int last);

static void buildSuffixArray(char *txt) {
	int i;
	for (i = 0; txt[i]; i++) {
		suffArr[i].suff = txt + i;
	}
	suffCount = i;
	quickSort(0, suffCount - 1);
}

static bool search(char * pat) {
	int f = 0, l = suffCount - 1;
	int mid = (f + l) / 2;

	int patLen = strlen(pat);

	while (f <= l) {
		int diff = strncmp(pat, suffArr[mid].suff, patLen);

		if (diff == 0)
			return true;

		if (diff <= 0)
			l = mid - 1;
		else
			f = mid + 1;

		mid = (f + l) / 2;
	}
	return false;
}

void main_suffArrNaive() {
	char * txt = "my name is khan. and i am not a terrorist!";

	buildSuffixArray(txt);

	char * pattern = "is khan t";

	cout << pattern << " is" <<(search(pattern)?" ":" NOT ")<< "found in string" << endl;
}

#define MAX_NUM MAX_ARR_SIZE

static Suffix * input = suffArr;

static void quickSort(int first, int last)
{
	int pivot;
	int i;
	int j;
	Suffix temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (strcmp(input[i].suff, input[pivot].suff)<=0 && i < last)
			{
				i++;
			}
			while (strcmp(input[j].suff, input[pivot].suff)>0)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}