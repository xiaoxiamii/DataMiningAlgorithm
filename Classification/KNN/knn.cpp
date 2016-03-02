#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<stack>
#include<queue>
#include<limits.h>
#include<numeric>
#include<cstring>
#include<map>
#include<set>
#ifndef _AAA
#define _AAA
//#include "a.h"
//#include "a.cpp"

#endif

//kNN 

using namespace std;

struct sample {
	char label;
	double distance;
};

bool labelCmp( pair<char, int> a, pair<char, int> b) {
	if (a.second == b.second)  return a.first < b.first;
	return a.second < b.second;
}

bool distCmp(sample a, sample b) {
	if (a.distance == b.distance) {
		return a.label < b.label;
	}
	return a.distance < b.distance;
}

//Read train data
void readTrainData(vector< vector<double> > &trainData, vector< char > &trainLabel, int L, int M) {
	for (int i = 0; i < M; ++i) {
		//Read Feature;
		vector< double > lineData;
		double tmpData;
		for (int j = 0; j < L; ++j) {
			cin >> tmpData;
			lineData.push_back(tmpData);
		}

		trainData.push_back(lineData);

		//Read Feature;
		char label;
		cin >> label;
		trainLabel.push_back(label);
	}
}

//Read test data
void readTestData(vector < vector<double> > &testData, int L, int N) {
	for (int i = 0; i < N; ++i) {
		vector< double > lineData;
		double tmpData;
		for (int j = 0; j < L; ++j) {
			cin >> tmpData;
			lineData.push_back(tmpData);
		}
		testData.push_back(lineData);
	}
}

double calDistance(vector<double> data1, vector<double>data2) {
	int length = data1.size();
	double distance = 0.0;
	for (int i = 0; i < length; ++i) {
		distance += pow(data1[i] - data2[i], 2);
	}
	return sqrt(distance);
}

void KNN(vector< vector<double> > trainData, vector< char > trainLabel, vector< vector<double> > testData, vector< char > &testLabel,
	int k, int L, int M, int N) {

	for (int i = 0; i < N; ++i) {
		vector<sample> distances;

		// 计算测试样本和训练样本的距离
		for (int j = 0; j < M; ++j) {
			sample tmpDistance;
			tmpDistance.distance = calDistance(testData[i], trainData[j]);
			tmpDistance.label = trainLabel[j];
			distances.push_back(tmpDistance);
		}

		sort(distances.begin(), distances.end(), distCmp);

		map<char, int> labelMap;
		for (int j = 0; j < k; ++j) {
			// label not exit
			if (!labelMap[distances[j].label]) {
				labelMap[distances[j].label] = 0;
			}
			labelMap[distances[j].label] += 1;
		}

		//第J个例子和k-1例子的距离是否一样
		for (int j = k; j < M; ++j) {
			if (distances[j].distance == distances[k - 1].distance) {
				if (!labelMap[distances[j].label]) {
					labelMap[distances[j].label] = 0;
				}
				labelMap[distances[j].label] += 1;
			}
		}
		vector< pair<char, int> > labelVec;
		for (map<char, int>::iterator it = labelMap.begin(); it != labelMap.end(); ++it) {
			labelVec.push_back(make_pair(it->first, it->second));
		}
		
		sort(labelVec.begin(), labelVec.end(), labelCmp);

		string res = "";
		for (int j = 0; j < labelVec.size(); ++j) {
			res += labelVec[j].first;
			if (j + 1 >= labelVec.size() || labelVec[j].second != labelVec[j + 1].second)
				break;
		}

		cout << res << endl;

	}
}


int main() {
	int k, L, M, N;
	cin >> k >> L >> M >> N;
	vector< vector<double> > trainData;
	vector< vector<double> > testData;
	vector< char > trainLabel;
	vector< char > testLabel;

	readTrainData(trainData, trainLabel, L, M);
	readTestData(testData, L, N);

	KNN(trainData, trainLabel, testData, testLabel, k, L, M, N);

	system("pause");
	return 0;
}
