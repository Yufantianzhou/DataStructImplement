#include<iostream>
#include<vector>
#include<string>
#include"Calculation.h"
#include"MathSign.h"
#include"Stack.h"

using namespace std;


void print(const vector<string>& v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	//变量定义
	const string nullStr = "";
	string formulasStr;//原始输入字符串
	vector<string> formulas;//表达式formulas,用于存放中缀表达式和后缀表达式
	Calculation calculation;//计算器
	double result;//计算式结果

	//提示信息
	cout << "计算器" << endl
		 << "该计算器基本实现在double类型范围内的数的加减乘除模" << endl
		 << "负数请在输入时加上括号，如-1写作(-1)"<<endl
		 << "输入end结束计算"<<endl;
	//执行部分
	while (true) {
		//清空数据，为下一次输入做准备
		formulasStr.clear();
		formulas.clear();
		//输入部分
		cout << ">>";
		getline(cin, formulasStr);
		//输入end结束计算
		if (formulasStr == "end")
			break;
		//将str转化为后缀表达式
		if (calculation.StrToFormulas(formulasStr, formulas) == false) {//字符串转为中缀
			//cout << "first step" << endl;
			cout << "ERROR!!!"<<endl;//返回值为假，输出错误
			continue;
		}
	//	print(formulas);
		if (calculation.InOrderToPost(formulas) == false) {//中缀转为后缀
			//cout << "second step" << endl;
			cout << "ERROR!!!"<<endl;
			continue;
		}
	//	print(formulas);
		//计算结果
		result = calculation.resultOfPostFormulas(formulas);
		if (result == ERROR_CODE) {
			//cout << "third step" << endl;
			cout << "ERROR!!!" << endl;
		}
		else
			cout << result << endl;
	}
	
	return 0;
}