#include<stdio.h>
#include<stdlib.h>


int knapsack(int item[101][2], int choseItem[101], int n, int* memItem, int famCap){
	int idx;
	int arr[101][201];

	//sets up array for item
	for(int i=0;i<101;i++){
		arr[i][0] = 0;
	}

	//sets up array for weight
	for(int i=0;i<201;i++){
		arr[0][i] = 0;
	}
	
	//loops through every inext of array to and compare cost and capacity
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= famCap; j++){
			if(j - item[i][1] >= 0 ){
				int cost = arr[i - 1][j - item[i][1]] + item[i][0];

				if(cost < arr[i - 1][j]){
					arr[i][j] = arr[i-1][j];
				}

				else{
					arr[i][j] = cost;
				}
			}

			else{
				arr[i][j] = arr[i-1][j];
			}
		}
	}

	//the capacity of the family is the weight to compare
	int weight = famCap;
	idx = 0;

	//loops through every item in array depending on how many items
	for(int i = n; i > 0; i--){
		if(weight - item[i][1] >= 0 ){
			if(arr[i - 1][weight-item[i][1]] + item[i][0] > arr[i - 1][weight] ){
				choseItem[idx++] = i;
				weight -= item[i][1];
			}
		}
	}

	*memItem = idx;

	return(arr[n][famCap]);
}

int main(){
	int n;
	int t;
	int f;
	int item[101][2];
	int memItem[31];
	int famCap[31];
	int choseItem[31][101];
	int test = 1;

	FILE *inShop = fopen("shopping.txt", "r");
	FILE *outResult = fopen("results.txt", "w");

	fscanf(inShop, "%d", &t);

	for(int a = t; a > 0; a--){
		fscanf(inShop, "%d", &n);

		//goes through how many items in test case
		for(int i = 1; i <= n; i++){
			fscanf(inShop, "%d%d", &item[i][0], &item[i][1]);
		}

		fscanf(inShop, "%d", &f);

		//goes through each family member
		for(int i = 0; i < f; i++){
			fscanf(inShop, "%d", &famCap[i]);
		}

		int totalCost = 0;
		fprintf(outResult, "Test Case %d", test);
		fprintf(outResult, "\n");

		//calculate total cost of item by using the return max in knapsack
		for(int i = 0; i < f; i++){
			totalCost += knapsack(item, choseItem[i], n, &memItem[i], famCap[i]);
		}

		fprintf(outResult, "Total Price %d ", totalCost);
		fprintf(outResult, "\n");

		fprintf(outResult, "Member Items ");
		fprintf(outResult, "\n");

		//loops through each family member with item they chose and price
		for(int i = 0; i < f; i++){
			fprintf(outResult, "%d:", i+1);

			for(int j = memItem[i] - 1; j >= 0; j--){
				fprintf(outResult, " %d", choseItem[i][j]);
			}
			fprintf(outResult, "\n");
		}

		fprintf(outResult, "\n");
		test++;

	}

	fclose(inShop);
	fclose(outResult);

	return(0);
}