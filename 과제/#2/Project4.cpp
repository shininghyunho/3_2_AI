/*
AI assignment #2
2015920056 computer_science 최현호

Making 1-layer perceptron
with back propagation.

assumption : 2-dimension.

*/
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <math.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>

#define MAX 10 // Maximum
#define D_MAX 10 // dimension max
#define C 1.5 // adjust constant
#define Dimension 2
#define AND 0
#define OR 1
#define XOR 2

using namespace std;

vector<float> t_and; // Truth_Table
vector<float> t_or; // Truth_Table
vector<float> t_xor; // Truth_Table

void Comment();// My explain comment
float Rand_num();// make random number
void Set_TT();// set Truth_Table
int Do_learning(int gate);// 1-layerd Perceptron을 이용하여 학습
void View_Perceptron(string s, int k);// Perceptron 성공실패 유무 시각화

void Comment() {
	cout <<"\n\n"<< "AI assignment #2\n";
	cout << "2015920056 computer_science 최현호\n\n";

	cout << "Making 1 - layer perceptron\n";
	cout << "with back propagation.\n\n";

	cout << "################################\n\n\n";

}
float Rand_num() {
	float num;
	num = (rand() % 100) / 10.0 - 5.0; // -5 < theta <= 5"
	return num;
}
void Set_TT() {
	t_and.push_back(0);
	t_and.push_back(0);
	t_and.push_back(0);
	t_and.push_back(1);

	t_or.push_back(0);
	t_or.push_back(1);
	t_or.push_back(1);
	t_or.push_back(1);

	t_xor.push_back(0);
	t_xor.push_back(1);
	t_xor.push_back(1);
	t_xor.push_back(0);
}
// 노드는 input을 받으면 주어진 weight에 따라 output을 출력해줍니다.
class Node {
private:
	vector<float> input;
	vector<float> weight;
	float theta=0; // fix the theta 0
	float net=0;
	int output=0;
public:
	// 입력을 설정합니다.
	void Set_input(vector<float> input) {
		this->input.clear();
		for (int i = 0; i < Dimension + 1; i++) {
			this->input.push_back(input[i]);
		}
	}
	// weight를 설정합니다.
	void Set_weight(vector<float> weight) {
		this->weight.clear();
		for (int i = 0; i < Dimension + 1; i++) {
			this->weight.push_back(weight[i]);
			cout << "weight " << i << " : " << this->weight.at(i)<<endl;
		}
	}
	// input과 weight의 곱을 더해줍니다.
	float Calc_net() {
		net = 0.0;
		for (int i = 0; i < Dimension + 1; i++) {
			net += this->weight.at(i) * this->input.at(i);
			cout << "weight : " << this->weight.at(i) << endl;
			cout << "input : " << this->input.at(i)<<endl;
		}
		return net;
	}
	// 활성화 함수입니다.
	int Calc_output() {
		if (net > theta)
			output = 1;
		else
			output = 0;
		return output;
	}
};

/*
 Perceptron은 Node에게 input과 weight를 주고
 output을 얻어내는 forward과정과
 weight를 수정하는 backward 과정으로 이루어져있습니다.
*/
class Perceptron {
private:
	vector<float> input;
	vector<float> weight;
	vector<int> t; // Truth_Table
	vector<int> p_out; // output
	Node node; // 학습을 위한 노드 생성
	int errNum = 0; // number of err
public:
	Perceptron(){} // Constructor
	Perceptron(int gate){ // Constructor Overloading : 어떤 게이트인지 정함
		t.clear();
		switch (gate) {
		case AND:
			for (int i = 0; i < pow(2, Dimension); i++)
				t.push_back(t_and[i]);
			break;
		case OR:
			for (int i = 0; i < pow(2, Dimension); i++)
				t.push_back(t_or[i]);
			break;
		case XOR:
			for (int i = 0; i < pow(2, Dimension); i++)
				t.push_back(t_xor[i]);
			break;
		}
	}
	// input 설정(x0는 1로 고정)
	void Set_ith_input(int ith) {
		this->input.clear();
		input.push_back(1);
		cout << "x0 : " << input[0] << endl;
		for (int j = 0; j < Dimension; j++) {
			input.push_back(bitset<D_MAX>(ith)[j]);
			cout << "x" << j + 1 << " : " << input[j + 1] << endl;
		}
	}
	// 초기 weight값만 랜덤으로 설정
	void Rand_weight(void) {
		this->weight.clear();
		this->weight.push_back(Rand_num()-5.0); // 1번째 weight만 음수값으로 설정
		Save_w(to_string(0), this->weight.back());
		cout << "weight " << 0 << " : " << this->weight.at(0) << endl;
		for (int i = 1; i < Dimension + 1; i++) {
			this->weight.push_back(Rand_num());
			Save_w(to_string(i), this->weight.back());
			cout << "weight " << i << " : " << this->weight.at(i) << endl;
		}
	}
	// 학습하는 과정
	void Forward(int ith) {
		Set_ith_input(ith); // input을 설정
		node.Set_input(input); // Node에게 설정한 input을 입력
		node.Set_weight(weight); // Node에게 weight를 입력

		cout << "net : " << node.Calc_net() << endl; // net를 구햐고
		float out= node.Calc_output(); // output을 구함
		cout << "output "<<ith<<" : " << out << "\n\n";

		p_out.push_back(out); // output 저장

		if (t[ith] != p_out.back()) { // output을 진리표와 비교해서 틀린갯수 체크
			errNum++;
		}
	}
	// weight를 수정하는 과정
	void Backward(int ith) {
		Save_w(to_string(0), this->weight[0]);
		for (int k = 1; k < Dimension+1; k++) {
			cout << "before weight " << ith << k << " : " << this->weight[k] << endl;
			this->weight[k] += C * (t[ith] - p_out.back()) * input[k]; // back progation 과정
			Save_w(to_string(k), this->weight[k]);
			cout << "after weight " << ith << k << " : " << this->weight[k] << "\n\n";
		}
		p_out.clear();
	}
	// Err 갯수 초기화
	void Init_errNum(void) {
		this->errNum = 0;
	}
	// Err 값 반환
	int Get_errNum(void) {
		return this->errNum;
	}
	// 시각화를 위해 weight들을 csv로 저장
	void Save_w(string ith, float weight) {
		ofstream out(ith + "_weight.csv", fstream::out | fstream::app);
		out << weight << endl;
		out.close();
	}
	// Err 값 저장
	void Save_err(void) {
		ofstream out("errNum.csv", fstream::out | fstream::app);
		out << this->errNum << endl;
		out.close();
	}
};
int Do_learning(int gate) {
	Perceptron p(gate); // Perceptron 생성
	p.Rand_weight(); // 초기 weight값 랜덤하게 설정

	for (int i = 0; i < MAX; i++) {
		cout <<"##################################Iter : "<< i+1 << "\n\n";
		p.Init_errNum();
		// 2^Dimension 만큼의 학습과 weight 조정이 한 Cycle
		for (int j = 0; j < pow(2,Dimension); j++) {
			p.Forward(j);
			p.Backward(j);
		}
		p.Save_err();
		// 한 Cycle이 끝나면 Err 갯수 체크
		if (p.Get_errNum() == 0) { // Err 갯수가 0이면 탈출
			cout << "Success!! : " <<i+1<<"th"<< endl;
			return i;
		}
		else {
			cout <<"errNum : "<< p.Get_errNum() << "\n\n";
		}
	}
	return -1;
}
void View_Perceptron(string s,int k) {
	if (k >= 0)
		cout <<s<< " Successed : " << k+1 << "th" << endl;
	else
		cout <<s<< " Failed" << endl;
}

int main()
{
	srand((unsigned int)time(0)); // seed값 설정
	Set_TT(); // Truth Table 설정

	//cout << "############################### AND" << endl;
	//int i_and=Do_learning(AND);
	//cout << "############################### OR" << endl;
	//int i_or=Do_learning(OR);
	//cout << "############################### XOR" << endl;
	int i_xor=Do_learning(XOR);

	Comment(); // comment
	//View_Perceptron("And", i_and);
 	//View_Perceptron("Or", i_or);
	View_Perceptron("Xor", i_xor);
}
