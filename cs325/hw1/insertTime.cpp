#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

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

int main(){
	int arr[MAX] = {};
	srand(time(NULL));

	cout << "insert sort avg" << endl;
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
			insertSort(arr, n);
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