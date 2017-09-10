/*****************************×××××××**********/
/******  滑动窗口平均滤波/滑动窗口加权滤波 ******/
/**********************************************/
#include<iostream>
#include<fstream>
// 定义窗口大小
#define N 10
// 定义滑动滤波函数Filter
float Filter(float a);
// 定义存储窗口的数组
static float data[N] = {0};
// 定义加权滤波系数
static float Coeff[N] = {1.0/12,1.0/12,1.0/12,1.0/8,1.0/8,1.0/8,1.0/8,1.0/12,1.0/12,1.0/12};
static int i=0;
static int j=0;

int main(){
	// 定义原始数据输入文件名
	std::ifstream infile("acc.txt");
	// 定义滤波后的输出文件名
	std::ofstream outfile("acc_filter.txt");
	float a = 0.0;
	if(infile.is_open())
	{
		std::cout << "success to open the file" << std::endl;
	}
	if(outfile.is_open()){
		std::cout << "success to output the file" << std::endl;
	}
	while(infile.peek() != EOF){
		// 从文件中读取数据
		infile >> a;
		std::cout << "a: " << a  <<  "\n";
		// 进行滤波处理
		float acc_filter = Filter(a);
		// 将滤波后的数据保存到文件中
		outfile << acc_filter << "\n";
		std::cout << "acc_filter: " << acc_filter << "\n";
		// 判断读取数据是否结束，主要是避免最后一行数据会读两次(infile.peek()!=EOF这个判断会导致最后一行数据读两次)
		infile.get();
		if(infile.peek() == '\n')
			break;
	}
	// 关闭文件流
	infile.close();
	outfile.close();
	return 0;
}
float Filter(float a){
	float filter_sum = 0.0;
	data[i] = a;
	for(int count = 0; count < 10; count++){
		std::cout << "data: " << data[count] << ",";
		if(count == 9)
			std::cout << "\n";
	}
	// 记录数据的个数
	i = i + 1;
	j = j + 1;
	if(i >= 10)
		i = 0;
	if(j >= 10){
		for(int k = 0; k< 10; k++)
		{
			// 滑动平均滤波
			filter_sum += data[k];
			// 滑动加权滤波
			//filter_sum += data[k]*Coeff[k]; 
			//std::cout << "filter_sum: " << filter_sum << "\n";
		}
		// 滑动平均滤波
		return filter_sum / 10.0;
		// 滑动加权滤波
		// return filter_sum
	}
	else{
		return a;
	}
}
