#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

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
	
	cout << "Merge sort avg" << endl;
	int n;
	double total = 0;
	for(n = 1000; n <= 10000; n+=1000){
		//loop through 10 times
		for(int i = 0; i < 10; i++){
			//fill array		
			for(int j = 0; j < n; j++){
				arr[j] = rand() % 10000;
			}

			clock_t tStart = clock();
			mergeSort(arr, 0, n - 1);
			clock_t tEnd = clock();
			//calculate runtime
			double runtime = (double)(tEnd - tStart)/(CLOCKS_PER_SEC/1000);
			total+= runtime;
		}
		//get avg
		double average = total/10;
		cout << n << " " << fixed << setprecision(4) << average << endl;
	}
	
	return 0;
}