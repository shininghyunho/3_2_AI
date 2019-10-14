/*
AI assignment #2
2015920056 computer_science 최현호

Making Multi-layer perceptron
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
#include <random>

#define MAX 10 // Maximum
#define C 0.1 // adjust constant
#define Dimension 2
#define AND 0
#define OR 1
#define XOR 2
#define INVXOR 3
#define DONUT 4
#define LIMIT 0.01
#define CASENUM 4

using namespace std;

vector<float> t_and; // And Truth_Table
vector<float> t_or; // Or Truth_Table
vector<float> t_xor; // Xor Truth_Table
vector<float> t_invxor; // Inversed Xor Truth_Table
vector<float> t_donut; // Donut Truth_Table
vector<vector<float>> donut_arr; // 도넛 input 값 설정
// 파일에 저장하기위한 변수 설정
vector<vector<float>> save_input_arr; 
vector<vector<float>> save_weight_arr;
vector<vector<float>> save_bias_arr;
vector<float> save_err;

void Comment();// My explain comment
float Rand_num();// make random number
void Set_TT();// set Truth_Table
float sigmoid(float z);
float sigmoid_prime(float z);
float relu(float z);
float relu_prime(float z);
float leaky_relu(float z);
float leaky_relu_prime(float z);
float bent(float z);
float bent_prime(float z);
float active(float z);
float active_prime(float z);
int Do_learning(int gate);// Multi-layerd Perceptron을 이용하여 학습
void View_Perceptron(string s, int k);// Perceptron 성공실패 유무 시각화

void Comment() {
	cout << "\n\n" << "AI assignment #3\n";
	cout << "2015920056 computer_science 최현호\n\n";

	cout << "Making Multi - layer perceptron\n";
	cout << "with chain rule back propagation.\n\n";

	cout << "#################################################\n\n\n";

}
float Rand_num() {
	float num;
	num = ((rand() % 100) / 10.0 - 5.0); // -5 < theta <= 5"
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

	t_invxor.push_back(1);
	t_invxor.push_back(0);
	t_invxor.push_back(0);
	t_invxor.push_back(1);

	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(0);
	t_donut.push_back(1);

	// 도넛값
	vector<float> v;
	v.clear();
	v.push_back(0);
	v.push_back(0);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(0);
	v.push_back(1);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(1);
	v.push_back(0);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(1);
	v.push_back(1);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(0.5);
	v.push_back(1);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(1);
	v.push_back(0.5);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(0.5);
	v.push_back(0);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(0);
	v.push_back(0.5);
	donut_arr.push_back(v);
	v.clear();
	v.push_back(0.5);
	v.push_back(0.5);
	donut_arr.push_back(v);
}
// 시그모이드 함수
float sigmoid(float z) {
	return (1.0 / (1 + exp(-z)));
}
// 시그모이드 미분
float sigmoid_prime(float z) {
	return sigmoid(z)* (1 - sigmoid(z));
}
// 랠루
float relu(float z) {
	return(z >= 0) ? z : 0;
}
// 랠루 미분
float relu_prime(float z) {
	return(z >= 0) ? 1 : 0;
}
// 리키 랠루
float leaky_relu(float z) {
	return(z >= 0) ? z : 0.1*z;
}
// 리키 랠루 미분
float leaky_relu_prime(float z) {
	return(z >= 0) ? 1 : 0.1;
}
// 밴트
float bent(float z) {
	return (pow(pow(z, 2) + 1, 0.5) - 1) / 2 + z;
}
// 밴트 미분
float bent_prime(float z) {
	return z / (2 * pow((pow(z, 2) + 1), 0.5)) + 1;
}
// 활성화 함수 설정
float active(float z) {
	return sigmoid(z);
}
// 활성화 함수 미분값 설정
float active_prime(float z) {
	return sigmoid_prime(z);
}
// 노드는 input을 받으면 주어진 weight에 따라 output을 출력해줍니다.
class Node {
private:
	vector<float> input;
	vector<float> weight;
	float bias=1000;
	float theta = 0; // fix the theta 0
	float net = 0;
	float output = 0;
	float delta_prime = 0;
public:
	// 입력을 설정합니다.
	void Set_input(vector<float> input) {
		this->input.clear();
		for (int i = 0; i < input.size(); i++) {
			this->input.push_back(input[i]);
			//cout << "input " << i << " : " << this->input.at(i) << endl;
		}
	}
	// weight를 설정합니다.
	void Set_weight(vector<float> weight) {
		this->weight.clear();
		for (int i = 0; i < weight.size(); i++) {
			this->weight.push_back(weight[i]);
			//cout << "weight " << i << " : " << this->weight.at(i) << endl;
		}
	}
	// bias 설정
	void Set_bias(float bias) {
		this->bias = bias;
		//cout << "bias : " << bias << endl;
	}
	// weight들의 합(backpropagation시 사용)
	float Get_sum_weight(void) {
		float sum = 0;
		for (int i = 0; i < weight.size(); i++)
			sum += weight[i];
		return sum;
	}
	// input과 weight의 곱을 더해줍니다.
	float Calc_net(void) {
		net = 0.0;
		net += this->bias;
		for (int i = 0; i < this->input.size(); i++) {
			net += this->weight.at(i) * this->input.at(i);
		}
		//cout << "-------net : " << net << endl;
		return net;
	}
	// output 계산
	float Calc_output() {
		//cout << "------------output : " << active(net) << "\n\n";
		return active(net);
	}
	float Calc_output_last() {
		//cout << "------------output : " << sigmoid(net) << "\n\n";
		return active(net);
	}
	// 델타 설정(델타 프라임)
	void Set_delta(float delta) {
		this->delta_prime = delta;
		//cout << "        delta_prime : " << delta << "\n\n";
	}
	// 델타 반환(델타 프라임)
	float Get_delta(void) {
		return this->delta_prime;
	}
	// 넷 반환
	float Get_net(void) {
		return this->net;
	}
};

class Layer {
private:
	Node* n = new Node[MAX];
	int node_num = 0;
	vector<float> input;
	int input_size;
	vector<vector<float>> w_arr;
	vector<float> weight;
	vector<float> bias;
	vector<float> n_out;
public:
	// 입력을 설정합니다.
	void Set_input(vector<float> input) {
		this->input.clear();
		for (int i = 0; i < input.size(); i++) {
			this->input.push_back(input[i]);
		}
		input_size = input.size();
	}
	// k번째 인풋 반환
	float Get_kth_input(int k) {
		return input[k];
	}
	// 노드 갯수 설정
	void Set_nodeNum(int num) {
		this->node_num = num;
	}
	// weight를 설정합니다.
	void Set_weight(vector<vector<float> > w_arr) {
		this->w_arr.clear();
		for (int i = 0; i < node_num; i++) {
			this->weight.clear();
			for (int j = 0; j < input_size; j++) {
				this->weight.push_back(w_arr[i][j]);
				//cout << "weight " << j << " : " << this->weight.at(j) << endl;
			}
			this->w_arr.push_back(this->weight);
		}
	}
	// bias 설정
	void Set_bias(vector<float> bias) {
		this->bias.clear();
		for (int i = 0; i < node_num; i++) {
			this->bias.push_back(bias[i]);
		}
	}
	// 노드 계산
	void Calc_Node(void) {
		n_out.clear();
		for (int i = 0; i < node_num; i++) {
			//cout << "-------" << i << "th node" << endl;
			n[i].Set_input(input);
			n[i].Set_weight(w_arr[i]);
			n[i].Set_bias(bias[i]);
			n[i].Calc_net();
			this->n_out.push_back(n[i].Calc_output());
		}
	}
	// 마지막 노드는 따로 계산
	void Calc_Node_last(void) {
		n_out.clear();
		for (int i = 0; i < node_num; i++) {
			//cout << "-------" << i << "th node" << endl;
			n[i].Set_input(input);
			n[i].Set_weight(w_arr[i]);
			n[i].Set_bias(bias[i]);
			n[i].Calc_net();
			this->n_out.push_back(n[i].Calc_output_last());
		}
	}
	// i번째 node output
	float Get_ith_Out(int ith) {
		return n_out[ith];
	}
	// delta설정(delta prime)
	void Set_delta(vector<float> delta_prime) {
		for (int i = 0; i < delta_prime.size(); i++) {
			n[i].Set_delta(delta_prime[i]);
		}
	}
	// delta반환(delta prime)
	vector<float> Get_delta(void) {
		vector<float> delta;
		delta.clear();
		for (int i = 0; i < input_size; i++) {
			float sum = 0;
			for (int j = 0; j < this->node_num; j++) {
				sum = sum + (w_arr[j][i]*n[j].Get_delta()*active_prime(n[j].Get_net()));
			}
			delta.push_back(sum);
		}
		return delta;
	}
	// j번째 활성화 함수(net)의 미분 반환
	float j_th_prime_net(int j) {
		return active_prime(n[j].Get_net());
	}
	// j번째 델타값 반환
	float j_th_delta(int j) {
		return n[j].Get_delta();
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
	//float f_input;
	int inputNum = 0;
	vector<float> weight;
	vector<vector<float> > w_arr;
	vector<vector<vector<float> > > w_layer;
	vector<float> bias;
	vector<vector<float>> bias_arr;
	int layerNum = 1;
	vector<int> layer_per_nodeNum;
	vector<vector<float> > ith_layer_out;
	vector<float> layer_out;
	vector<int> t; // Truth_Table
	vector<float> p_out; // output
	Layer* layer = new Layer[MAX];
	int errNum = 0; // number of err
public:
	Perceptron() {} // Constructor
	Perceptron(int gate) { // Constructor Overloading : 어떤 게이트인지 정함
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
		case INVXOR:
			for (int i = 0; i < pow(2, Dimension); i++)
				t.push_back(t_invxor[i]);
			break;
		case DONUT:
			for (int i = 0; i < 9; i++)
				t.push_back(t_donut[i]);
			break;
		}
	}
	// i번째 진리값 반환
	float Get_t(int i) {
		return t.at(i);
	}
	// Input 갯수 설정
	void Set_input_num(void) {
		cout << "Input Num : ";
		cin >> this->inputNum;
	}
	// 레이어 갯수 설정
	void Set_layerNum(void) {
		cout << "Layer Num : ";
		cin >> layerNum;
	}
	// 레이어 갯수 반환
	int Get_layerNum(void) {
		return layerNum;
	}
	// 레이어 당 노드 수 설정
	void Set_layer_per_nodeNum(void) {
		for (int i = 0; i < layerNum; i++) {
			int num = 0;
			cout << i << "th layer nodeNum : ";
			cin >> num;
			layer_per_nodeNum.push_back(num);
		}
	}
	// 맨처음 input 설정(x0는 1로 고정)
	void Set_ith_gate_input(int ith) {
		this->input.clear();
		//f_input = ith;
		for (int j = 0; j < inputNum; j++) {
			input.push_back(bitset<MAX>(ith)[j]);
			cout << "x" << j << " : " << input[j] << endl;
		}
	}
	// i번째 도넛 input 설정
	void Set_ith_donut_input(int ith) {
		this->input.clear();
		//f_input = ith;
		for (int i = 0; i < donut_arr[ith].size(); i++){
			this->input.push_back(donut_arr[ith][i]);
		}
	}
	// 이후 전 layer에서 얻은 output 사용
	void Set_ith_layer_input(int ith) {
		this->input.clear();
		for (int j = 0; j < this->layer_per_nodeNum[ith - 1]; j++) {
			input.push_back(layer[ith - 1].Get_ith_Out(j));
			//cout << "x" << j << " : " << input[j] << endl;
		}
	}
	// bias 랜덤 설정
	void Rand_bias(void) {
		bias_arr.clear();
		for (int i = 0; i < layerNum; i++) {
			//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  " << i << "th layer" << endl;
			bias.clear();
			for (int j = 0; j < layer_per_nodeNum[i]; j++) {
				//cout << "\n-----------------------------------" << j << "th node" << endl;
				this->bias.push_back(Rand_num());
				//cout << "bias " << j << " : " << this->bias.at(j) << endl;
			}
			bias_arr.push_back(this->bias);
		}
	}
	// bias 설정
	void Set_bias(void) {
		bias_arr.clear();
		for (int i = 0; i < layerNum; i++) {
			//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  " << i << "th layer" << endl;
			bias.clear();
			for (int j = 0; j < layer_per_nodeNum[i]; j++) {
				//cout << "\n-----------------------------------" << j << "th node" << endl;
				float var = 0.0;
				//cout <<i<<" th layer " << j << "node bias : ";
				cin >> var;
				this->bias.push_back(var);
				//cout << "bias " << j << " : " << this->bias.at(j) << endl;
			}
			bias_arr.push_back(this->bias);
		}
	}
	// 초기 weight값만 랜덤으로 설정
	void Rand_weight(void) {
		w_layer.clear();
		w_arr.clear();
		//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  0th layer" << endl;
		// 1번째 레이어는 초기 input을 따로 받음
		for (int i = 0; i < layer_per_nodeNum[0]; i++) {
			//cout << "-----------------------------------" << i << "th node" << endl;
			this->weight.clear();
			for (int j = 0; j < inputNum; j++) {
				this->weight.push_back(Rand_num());
				//Save_w(to_string(j), this->weight.back());
				//cout << "weight " << j << " : " << this->weight.at(j) << endl;
			}
			w_arr.push_back(this->weight);
		}
		w_layer.push_back(this->w_arr);

		for (int i = 1; i < layerNum; i++) {
			//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  " << i << "th layer" << endl;
			w_arr.clear();
			for (int j = 0; j < layer_per_nodeNum[i]; j++) {
				//cout << "\n-----------------------------------" << j << "th node" << endl;
				this->weight.clear();
				for (int k = 0; k < layer_per_nodeNum[i - 1]; k++) {
					this->weight.push_back(Rand_num());
					//Save_w(to_string(k), this->weight.back());
					//cout << "weight " << k << " : " << this->weight.at(k) << endl;
				}
				w_arr.push_back(this->weight);
			}
			w_layer.push_back(this->w_arr);
		}
	}
	// weight 값 설정
	void Set_weight(void) {
		w_layer.clear();
		w_arr.clear();
		//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  0th layer" << endl;
		// 1번째 레이어는 초기 input을 따로 받음
		for (int i = 0; i < layer_per_nodeNum[0]; i++) {
			//cout << "-----------------------------------" << i << "th node" << endl;
			this->weight.clear();
			for (int j = 0; j < inputNum; j++) {
				float var = 0.0;
				//cout << "0 th layer " << i << " node "<<j<<" th weight : ";
				cin >> var;
				this->weight.push_back(var);
				//cout << "weight " << j << " : " << this->weight.at(j) << endl;
			}
			w_arr.push_back(this->weight);
		}
		w_layer.push_back(this->w_arr);

		for (int i = 1; i < layerNum; i++) {
			//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  " << i << "th layer" << endl;
			w_arr.clear();
			for (int j = 0; j < layer_per_nodeNum[i]; j++) {
				//cout << "\n-----------------------------------" << j << "th node" << endl;
				this->weight.clear();
				for (int k = 0; k < layer_per_nodeNum[i - 1]; k++) {
					float var = 0.0;
					//cout <<i<< " th layer " << j << " node " << k << " th weight : ";
					cin >> var;
					this->weight.push_back(var);
					//cout << "weight " << k << " : " << this->weight.at(k) << endl;
				}
				w_arr.push_back(this->weight);
			}
			w_layer.push_back(this->w_arr);
		}
	}
	// i번째 레이어 계산
	void ith_layer_Calc(int ith) {
		layer[ith].Set_nodeNum(w_layer[ith].size());
		layer[ith].Set_input(this->input); // Layer에게 설정한 input을 입력
		save_input_arr.push_back(this->input);
		layer[ith].Set_weight(w_layer[ith]);
		layer[ith].Set_bias(bias_arr[ith]);
		save_bias_arr.push_back(bias_arr[ith]);
		if (ith == (layerNum - 1))
			layer[ith].Calc_Node_last();
		else
			layer[ith].Calc_Node();
		layer_out.clear();
		for (int i = 0; i < layer_per_nodeNum[ith]; i++)
			layer_out.push_back(layer[ith].Get_ith_Out(i));

	}
	// 마지막 레이어의 output 반환
	float Get_final_layer_output(void) {
		float out = layer_out[0];
		printf("output %f\n",out);
		return out;
	}
	// i번째 레이어 delta 설정
	void Set_ith_layer_delta(int ith,vector<float> delta) {
		layer[ith].Set_delta(delta);
	}
	// i번째 레이어 delta 반환
	vector<float> Get_ith_layer_delta(int ith) {
		return layer[ith].Get_delta();
	}
	// delta 계산
	void Calc_delta() {
		// 마지막 델타는 따로 구해놓음
		for (int i = layerNum-2; i >= 0; i--) {
			Set_ith_layer_delta(i, Get_ith_layer_delta(i + 1));
		}
	}
	// 마지막 델타는 따로 구함
	void Set_last_delta(vector<float> delta) {
		layer[layerNum - 1].Set_delta(delta);
	}
	// back sweep 단계
	void Correct_weight(void) {
		for (int i = 0; i < w_layer.size(); i++) {
			for (int j = 0; j < w_layer[i].size(); j++) {
				for (int k = 0; k < w_layer[i][j].size(); k++) {
					w_layer[i][j][k] += -1*C * layer[i].j_th_prime_net(j) * layer[i].j_th_delta(j) * layer[i].Get_kth_input(k);
				}
				bias_arr[i][j] += -1*C * layer[i].j_th_prime_net(j) * layer[i].j_th_delta(j) * 1;
			}
		}
	}
	// 루트 스퀘어의 sum으로 에러를 계산
	float Get_errSum(vector<float> err) {
		float err_sum = 0;
		for (int i = 0; i < CASENUM; i++) {
			err_sum += pow((t[i] - err[i]), 2);
		}
		save_err.push_back(err_sum);
		return err_sum;
	}
	vector<vector<vector<float>>> Get_w_layer(void) {
		return this->w_layer;
	}

	// Err 갯수 초기화
	void Init_errNum(void) {
		this->errNum = 0;
	}
	// Err 값 반환
	int Get_errNum(void) {
		return this->errNum;
	}
	// 문서로 저장
	void Save(void) {
		this->Save_input_arr();
		this->Save_w_layer();
		this->Save_bias_arr();
	}
	void Save_w_layer() {
		vector<vector<vector<float>>> w_layer = this->w_layer;
		ofstream out("w_layer.csv", fstream::out | fstream::app);
		for (int i = 0; i < w_layer.size(); i++) {
			for (int j = 0; j < w_layer[i].size(); j++) {
				for (int k = 0; k < w_layer[i][j].size(); k++) {
					out << w_layer[i][j][k] << ",";
				}
			}
		}
		out << endl;
		out.close();
	}
	void Save_input_arr(void) {
		ofstream out("input.csv", fstream::out | fstream::app);
		for (int i = 0; i < save_input_arr.size(); i++) {
			for (int j = 0; j < save_input_arr[i].size(); j++) {
				out << save_input_arr[i][j] << ",";
			}
		}
		out << endl;
		save_input_arr.clear();
		out.close();
	}
	
	void Save_bias_arr(void) {
		ofstream out("bias.csv", fstream::out | fstream::app);
		for (int i = 0; i < save_bias_arr.size(); i++) {
			for (int j = 0; j < save_bias_arr[i].size(); j++) {
				out << save_bias_arr[i][j] << ",";
			}
		}
		out << endl;
		save_bias_arr.clear();
		out.close();
	}
	void Save_err(void) {
		ofstream out("err.csv", fstream::out | fstream::app);
		for (int i = 0; i < save_err.size(); i++) {
			out << save_err[i]<<endl;
		}
		save_err.clear();
		out.close();
	}
};
// 학습 
int Do_learning(int gate) {
	Perceptron p(gate); // Perceptron 생성
	p.Set_input_num();
	p.Set_layerNum();
	int layerNum = p.Get_layerNum(); // Layer 갯수
	p.Set_layer_per_nodeNum(); // Layer 당 Node 수
	p.Rand_weight(); // 초기 weight값 랜덤하게 설정
	//p.Set_weight(); // 임의 랜덤값 설정
	p.Rand_bias(); // 초기 bias값 랜덤하게 설정
	//p.Set_bias(); // 임의 랜덤값 설정
	vector<float> final_output;
	vector<float> delta;

	cout << "\n\n             Learning Start!! \n\n\n\n";
	for (int i = 0; i < 100000; i++) {
		printf("###########################Iter : %d\n", i + 1);
		p.Init_errNum();
		final_output.clear();
		// 맨 처음 input 설정
		for (int j = 0; j < CASENUM; j++) {
			//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << j << "th input" << "\n\n";
			//cout << "-----------------------------------" << "0th Layer" << endl;
			//p.Set_ith_gate_input(j); // input을 설정
			p.Set_ith_donut_input(j);
			p.ith_layer_Calc(0);
			int k;
			for (k = 1; k < p.Get_layerNum(); k++) {
				//cout << "-----------------------------------" << k << "th Layer" << endl;
				p.Set_ith_layer_input(k);
				p.ith_layer_Calc(k);
			}
			final_output.push_back(p.Get_final_layer_output());
			//p.Save();
			// 마지막 델타만 예외적으로 구함
			delta.clear();
			delta.push_back(-(p.Get_t(j) - final_output[j]));
			//cout << "        delta_last_prime : " << delta.back() << "\n\n";
			p.Set_last_delta(delta);
			p.Calc_delta();

			// weight수정
			p.Correct_weight();
		}
		//cout << "----------------------------------\n";
		float err = p.Get_errSum(final_output);
		//p.Save_err();
		printf("Err : %f\n", err);
		//cout << "   Final Err : " << p.Get_errSum(final_output) << "\n";
		if ((err < LIMIT) ? true : false) {
			cout << "\n\nSuccess!! "<< endl;
			return i;
		}
	}
	return -1;
}
void View_Perceptron(string s, int k) {
	if (k >= 0)
		cout << s << " Successed : " << k + 1 << "th" << endl;
	else
		cout << s << " Failed" << endl;
}

int main()
{
	srand((unsigned int)time(0)); // seed값 설정
	Set_TT(); // Truth Table 설정
	//cout << "############################### AND" << endl;
	//int i_and = Do_learning(AND);
	//cout << "############################### OR" << endl;
	//int i_or = Do_learning(OR);
	//cout << "############################### XOR" << endl;
	int i_xor = Do_learning(XOR);
	//int i_donut = Do_learning(DONUT);
	//int i_invxor = Do_learning(INVXOR);

	Comment(); // comment
	//View_Perceptron("And", i_and);
	//View_Perceptron("Or", i_or);
	View_Perceptron("Xor", i_xor);
	//View_Perceptron("Donut", i_donut);
	//View_Perceptron("InvXor", i_invxor);
}