#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define MAX 9999

//holds all values
struct Act{
	int start;
	int end;
	int actNum;
};

//sorting array bubble
void sortAct(Act arr[], int n){
	bool swapped;
	do{
		swapped = false;
		for(int i = 0; i < n - 1; i++){
			if(arr[i].end > arr[i+1].end){
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
	}
	while(swapped);
}

//prints arr
void printArr(Act arr[], int n){
	for(int i = 0; i < n; i++){
		cout << arr[i].actNum << " ";
		cout << arr[i].start << " ";
		cout << arr[i].end << " ";
		cout << endl;
	}
	cout << endl;
}



int main(){
	int n;
	int set = 0;

	//open file
	ifstream fp;
	fp.open("act.txt");

	//array to store the actNum, start, and end times
	Act arr[MAX];
	while(fp >> n){
		//store data
		for(int i = 0; i < n; i++){
			fp >> arr[i].actNum;
			fp >> arr[i].start;
			fp>>arr[i].end;
		}

		int selected[MAX];
		int len = 0;

		//print test BEFORE sort
		//printArr(arr, n);

		//Sort the activities according to the finish time.
		sortAct(arr, n);

		//print test AFTER sort
		//printArr(arr, n);

		int i = 0;
		//first activity is in the optimal set
		selected[len] = arr[i].actNum;
		len++;

		for(int j = 1; j < n; j++){
			//find the next activity that has greater than or equal to the previous chosen activity
			if(arr[j].start >= arr[i].end){
				selected[len] = arr[j].actNum;
				len++;
				i = j;
			}
		}

		set++;
		cout << "Set " << set << endl;
		cout << "Number of activities selected = " << len << endl;
		cout << "Activities: ";

		for(int k = 0; k < len; k++){
			cout << selected[k] << " ";
		}
		cout << endl;
		cout << endl;
		}

	fp.close();
	return 0;
}