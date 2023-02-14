#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

#define MAX 9999

//hold cordinate data
struct Point{
		int x;
		int y;
};

//calculates weight from the given equation
int calc(Point arr[], int n){
	int result;
	int j = 0;
	
	for(int i = 0; i < n; i++){
		j++;

		if(j == n){
			j = 0;
		}

		//cout << "sqrt((" << arr[i].x << " - " << arr[j].x << ")^2" << " + " << "(" << arr[i].y << " - " << arr[j].y << ")^2)" << endl;

		//adds weights together from all points
		result += sqrt(pow(arr[i].x - arr[j].x, 2) + pow(arr[i].y - arr[j].y, 2));
	}
	//cout << "RESULT ===== " << result << endl;
	

return result;
}

int main() {
  int k;
	int n;
	int result;
	int q = 0;
	Point arr[MAX];

	//open file
	ifstream fp;
	fp.open("graph.txt");

	//while in file
	while(fp >> k){

		//loop number of test cases
		for(int i = 0; i < k; i++){
			q++;
			fp >> n;

			//loop number of vertices
			for(int i = 0; i < n; i++){

				//put coordinates in array
				fp >> arr[i].x;
				fp >> arr[i].y;
				//cout << arr[i].x << " " << arr[i].y << endl;
			}
			
			//calculate weight
			result = calc(arr, n);

			cout << "Test case " << q << ": " << "MST weight " << result << endl; 
		}
	}
	fp.close();
}