#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <chrono>
#include "Matrix.h"
#define Mat Numeric_lib
#define SIZE 10
using namespace std;
using namespace std::chrono;
Mat::Matrix<int,1> v(SIZE);
Mat::Matrix<int,2> M(SIZE,SIZE),I(SIZE,SIZE),result(SIZE,SIZE);
void initialise(){
for(int i=0;i<SIZE;i++) I[i][i]=1;
for(int i=0;i<SIZE;i++) M[i][i]=i+1;
}
void thFun(Mat::Matrix<int,2> &a, Mat::Matrix<int,2> &b, int idx){
	for(int i=0;i < SIZE;i++){
		int sum=0,j;
		for(j=0;j<SIZE;j++)
			sum+=a[i][j]*b[j][idx];
		result[i][idx]=sum;
	}
}
void show(Mat::Matrix<int,2> &N){
for(int i=0;i<SIZE;i++){
	for(int j=0;j<SIZE;j++)
		cout<<N[i][j]<<" ";
	cout<<endl;
	}
}
int main()
{
	vector<thread> workers;
	Mat::Matrix<int,1> m(SIZE);
	initialise();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	for(int i=0;i<SIZE;i++)
		workers.push_back(thread(&thFun, ref(M), ref(I), i));
	for_each(workers.begin(),workers.end(),[](thread &th){th.join();});
	/*
	for(int i=0;i<SIZE;i++)
		thFun(M,I,i);
	*/
	std::chrono::high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2-t1).count();
	cout<<" \nDuration(in usec)\t"<<duration; 
	//show(result);
	return 0;
}
