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
	mergeSort3Way(arr, n);

	//PRINT SORTED USING MERGESORT
	cout << "output (Merge)" << endl;
	printArr(arr, n);
	cout << endl;
	
	return 0;
}