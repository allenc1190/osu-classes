#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

//returns the max from array
int max(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}
  
//recursive
int knapSack(int val[], int n, int weight, int wt[]) { 
  
	//base case 
	if(n == 0 || weight == 0){
			return 0; 
	}

	//check if index n is > than weight. if yes move to next index of weight array
	if(wt[n - 1] > weight){
		return knapSack(val, n - 1, weight, wt);
	}

	//return max value for items that are going in sack and out of sack
	else{
		return max(val[n - 1] + knapSack(val, n - 1, weight - wt[n - 1], wt), knapSack(val, n - 1, weight, wt));
	}
}

int knapSackDyn(int val[], int n, int weight, int wt[]){ 
	int wIdx; 
	int arr2[n + 1][weight + 1]; 

	//sets up array
	for(int i = 0; i <= n; i++)  { 
		for(wIdx = 0; wIdx <= weight; wIdx++){ 
			if(i == 0 || wIdx == 0){
				arr2[i][wIdx] = 0; 
			}
			else if(wt[i - 1] <= wIdx){
				arr2[i][wIdx] = max(val[i - 1] + arr2[i - 1][wIdx - wt[i - 1]], arr2[i - 1][wIdx]);
			}
			else{
				arr2[i][wIdx] = arr2[i - 1][wIdx]; 
			}
		} 
	} 

	return arr2[n][weight]; 
}
  
int main() { 
	srand(time(NULL));
	int val[80] = {};
	int wt[80] = {};
	int weight = 100; 
	int n; 

	for(n = 10; n <= 80; n+=10){
		//cout << n << endl;
		for(int i = 0; i < n; i++){
			val[i] = rand() % 100;
			wt[i] = rand() % 100;
		}

		//calculates run time in microseconds
		//from https://www.geeksforgeeks.org/chrono-in-c/
		auto start = chrono::steady_clock::now();
		knapSack(val, n, weight, wt);
		auto end = chrono::steady_clock::now();

		auto start2 = chrono::steady_clock::now();
		knapSackDyn(val, n, weight, wt);
		auto end2 = chrono::steady_clock::now();

		
		cout << "N = " << n
		<< "  W = " << weight
		<< "  Rec time = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs"
		<< "  DP time = " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << "μs"
		<< "  max Rec = " << knapSack(val, n, weight, wt)
		<< "  max DP = " << knapSackDyn(val, n, weight, wt)
		<< endl;
	}


	return 0;
} 