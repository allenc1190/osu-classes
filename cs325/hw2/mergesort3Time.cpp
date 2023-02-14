#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;
#define MAX 10000
  
//Merge the 3 arrays together
void merge(int arr[], int low, int m1, int m2, int high, int tempArr[])  {  
    int i = low;
		int j = m1;
		int k = m2;
		int l = low;  

	//get min of the 3 arrays
	while((i < m1) && (j < m2) && (k < high)){  
		if(arr[i] < arr[j]){ 
			if(arr[i] < arr[k]){ 
				tempArr[l++] = arr[i++]; 
			} 
			else{ 
				tempArr[l++] = arr[k++]; 
			} 
		} 
		else{ 
			if(arr[j] < arr[k]){ 
				tempArr[l++] = arr[j++]; 
			} 
			else{ 
				tempArr[l++] = arr[k++]; 
			} 
		} 
	}  

	//if 1st and 2nd arr have remaining elements
	while((i < m1) && (j < m2)){  
		if(arr[i] < arr[j]){ 
			tempArr[l++] = arr[i++]; 
		} 
		else{ 
			tempArr[l++] = arr[j++]; 
		} 
	}  

	//if 2nd and 3rd arr have remaining elements
	while((j < m2) && (k < high)){  
		if(arr[j] < arr[k]){ 
			tempArr[l++] = arr[j++]; 
		} 
		else{ 
			tempArr[l++] = arr[k++]; 
		}  
	}  

	//if 1st and 3rd arr have remaining elements
	while((i < m1) && (k < high))  {  
		if(arr[i] < arr[k]){ 
			tempArr[l++] = arr[i++]; 
		} 
		else{ 
			tempArr[l++] = arr[k++]; 
		}  
	}  

	//copy 1st array to temp arr  
	while(i < m1){
		tempArr[l++] = arr[i++]; 
	} 

	//copy 2nd arr to temp
	while(j < m2){
		tempArr[l++] = arr[j++];  
	}

	//copy 3rd arr to temp 
	while(k < high){
		tempArr[l++] = arr[k++]; 
	} 
}  
  
  
//sorts the array by splitting to 3
void mergeSort3WayRec(int arr[], int low, int high, int tempArr[]){  
	//check if array size is less
	if(high - low < 2){
		return;
	}

	//split into 3
	int m1 = low + ((high - low) / 3);  
	int m2 = low + 2 * ((high - low) / 3) + 1;  

	//sort 3 arrays
	mergeSort3WayRec(tempArr, low, m1, arr);  
	mergeSort3WayRec(tempArr, m1, m2, arr);  
	mergeSort3WayRec(tempArr, m2, high, arr);  

	//merge the arrays after being sorted 
	merge(tempArr, low, m1, m2, high, arr);  
} 
  
void mergeSort3Way(int arr[], int n){  
	int tempArr[n];  

	//copy to temp
	for(int i = 0; i < n; i++){
		tempArr[i] = arr[i];
	}

	//sorting
	mergeSort3WayRec(tempArr, 0, n, arr);  

	//copy back to original array
	for(int i = 0; i < n; i++){
		arr[i] = tempArr[i];
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
			
			//start time
			double tStart = clock();
			mergeSort3Way(arr, n);
			double tEnd = clock();
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