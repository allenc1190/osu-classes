#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define MAX 10000

//merges the arrays together
void merge(int *arr, int l, int m, int r) {
	int i, j, k, n1, n2;

	n1 = m-l+1;
	n2 = r-m;

	//temp array
	int L[n1];
	int R[n2];

	//copy data to array
	for(i = 0; i<n1; i++){
		L[i] = arr[l+i];
	}

	for(j = 0; j<n2; j++){
		R[j] = arr[m+1+j];
	}

	//initial index of sub array
	i = 0;
	j = 0;
	k = l;

	while(i < n1 && j<n2){
		if(L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	//copies the left over data 
	while(i<n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j<n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int *arr, int l, int r) {
	int m;
	if(l < r){
		int m = l+(r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

//prints array
void printArr(int arr[], int n){
	for(int i = 0; i < n; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int arr[MAX] = {};
	srand(time(NULL));

	//OPEN FILE
	ifstream fp;
	fp.open("data.txt");
		int n = 0;
		while(fp >> arr[n]){
			n++;
		}

	fp.close();

	cout << "input" << endl;
	printArr(arr, n);
	cout << endl;
	
	//MERGE SORT DATA.TXT
	mergeSort(arr, 0, n - 1);

	//PRINT SORTED USING MERGESORT
	cout << "output (Merge)" << endl;
	printArr(arr, n);
	cout << endl;
	
	return 0;
}