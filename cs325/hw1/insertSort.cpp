#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define MAX 10000

void insertSort(int *arr, int n){
	int i;
	int j;
	int token;

	//loop through how many elements in data
	for(i = 1; i < n; i++){
		token = arr[i];
		j = i-1;
		
		//check and move numbers that are greater than token
		while(j >= 0 && arr[j] > token){
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = token;
	}
}

//prints array
void printArr(int arr[], int n){
	for(int i = 0; i < n; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(){
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

	//INSERT SORT DATA.TXT
	insertSort(arr, n);

	//PRINT SORTED USING INSERT SORT
	cout << "output (insert)" << endl;
	printArr(arr, n);
	cout << endl;

	return 0;
}