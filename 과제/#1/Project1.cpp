/*
AI assignment #1
2015920056 computer_science 최현호

Making 1-layer perceptron
which has n-dimension.
Input is random weight & theta.
Output is same as and gate.

assumption : 2-dimension.

*/
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <math.h>
#include <ctime>

#define MAX 100000000
#define D_MAX 10 // dimension max

using namespace std;

float Dimension; // Dimension
float x[MAX]; // x
float w[MAX]; // weight
float output; // output
float t[MAX]; // Truth_Table
float Theta=0; // Theta
int fail = 0; // num of fail
int cnt = 0; // Num of Try
float net; // Sum

int main()
{
	// comment
	cout << "AI assignment #1\n";
	cout << "2015920056 computer_science 최현호\n\n";

	cout << "Making 1 - layer perceptron\n";
	cout << "which has n - dimension.\n\n";

	cout << "Input is random weight & theta.\n";
	cout << "Output is same as and gate.\n\n";

	cout << "assumption : 2 - dimension.\n\n\n";
	cout << "################################\n\n\n";

	cout << "Choose Dimension : ";
	cin >> Dimension;

	srand((unsigned int)time(0)); // seed
	Theta = (rand() % 100)/10.0+1; // 0 < theta <= 10"
	cout << "Theta : " << Theta << "\n\n";
	int k = pow(2, Dimension)-1;
	t[k] = 1; // And_Gate Truth_Table

	// loop
	do {
		fail = 0; // intialize Num of Fail
		cnt++; // intialize Num of Try
		cout << "####### " << cnt << "th try!!!" << "\n\n";
		// Choose Weight
		if (cnt == 1) { // firtt case
			for (int i = 0; i < Dimension; i++) {
				w[i] = (rand() % 100)/10.0 + 1; // 0 < weight <= 10"
				cout << "Weight " << i + 1 << " : " << w[i] << endl;
			}
		}
		else { // other case
			for (int i = 0; i < Dimension; i++) {
				cout << "Enter the " << i + 1 << "th weigth :";
				cin >> w[i];
			}
		}
		cout << "\n" << endl;

		// test 2^dimension case
		for (int i = 0; i < pow(2,Dimension); i++) {
			// x[n] with bit count
			for (int j = 0; j < Dimension; j++) {
				x[j] = bitset<D_MAX>(i)[j];
				cout << "x" << j << " : " << x[j] << endl;
				cout << "w" << j << " : " << w[j] << endl;

			}
			// sum(net)
			//net = x1*w1 + x2*w2;
			//if(net<Theta) return 0;
			//else return 1;
			net = 0;
			for (int j = 0; j < Dimension; j++) {
				net += x[j] * w[j];
			}
			cout << "net : " << net << "\n";
			// calculate the output
			if (net <= Theta)
				output = 0;
			else
				output = 1;
			cout << "output : " << output << "\n";
			cout << "Truth_table : " << t[i] << "\n";

			// compare with Truth_Table
			if (output != t[i]) {
				fail++;
			}
			cout << "\n";
		}

		if (fail != 0) {
			cout << "Num of Fail : " << fail << "\n\n";
			cout << "Try again... " << endl;
		}
	} while (fail!=0);

	cout << "\n#############################\n\nSuccess\n\n";
	cout << "you tried : " << cnt << "!!!\n\n";
}
