#ifndef _CALCULATION_H_
#define _CALCULATION_H_

#include"Stack.h"
#include"MathSign.h"
#include<vector>
#include<stdlib.h>
#include<iostream>
using namespace std;

const char zero = '0';
const string zeroStr = "0";
const char point = '.';
const char equalSign = '=';


class Calculation
{
public:
	bool StrToFormulas(const string& formulasStr,vector<string>& inOrderFormulas);//数学符号与数字分离，若表达式有误则返回false
	bool InOrderToPost(vector<string>& inOrderFormulas);//中缀表达式转化为后缀表达式,若有误则返回false
	double resultOfPostFormulas(const vector<string>& postOrderFormulas);//后缀表达式计算
};

bool Calculation::StrToFormulas(const string& formulasStr, vector<string>& inOrderFormulas) {
	string c_formulasStr = formulasStr;
	if (c_formulasStr.back() != equalSign)
		c_formulasStr.push_back(equalSign);
	//去除空格
	c_formulasStr.erase(std::remove(c_formulasStr.begin(), c_formulasStr.end(), ' '), c_formulasStr.end());
	//检查有无非法字符
	for (int i = 0; i < c_formulasStr.size(); i++) {
		string temStr;
		temStr = c_formulasStr[i];
		if (isdigit(c_formulasStr[i])!=0 || c_formulasStr[i] == point || str_to_sym(temStr) != Sign::ERROR)
			continue;
		return false;
	}
	//数字与字符分离
	string numString="";
	bool flag = false;//标记负数
	for (int i = 0; i < c_formulasStr.size(); i++) {
		char elemOfChar = c_formulasStr[i];
		string temStr(1, elemOfChar);

		//检查是否为符号
		if (str_to_sym(temStr) == Sign::ERROR) {
			numString.push_back(elemOfChar);
			continue;
		}
		//将numstring压入容器中
		inOrderFormulas.push_back(numString);
		numString.clear();
		if (str_to_sym(temStr) == Sign::MINUX&&i>0 && c_formulasStr[i-1]=='(')
			inOrderFormulas.push_back(zeroStr);
		inOrderFormulas.push_back(temStr);
		continue;
	}
	//去除等于号
	inOrderFormulas.pop_back();
	return true;
}

bool Calculation::InOrderToPost(vector<string>& inOrderFormulas) {
	vector<string> postOrderFormulas;
	Stack<string> signStack;
	Sign sign;
	//对中缀表达式进行遍历，转为后缀
	for (int i = 0; i < inOrderFormulas.size(); i++) {
		string elem = inOrderFormulas[i];
		sign = str_to_sym(elem);
		//elem为数字，进入后缀表达式
		if (sign== Sign::ERROR) {
			postOrderFormulas.push_back(elem);
			//cout << i << "  " << elem << endl;
			continue;
		}
		//elem为数学符号
		    //若栈为空，进栈；若elem优先级比栈顶元素高，入栈
		if (signStack.Len() == 0 || signStack.Len() != 0 && Compare(sign, str_to_sym(signStack.GetTop())) == Priority::HIGHER) {//优先级高，入栈
			signStack.Push(elem);
			continue;
		}
			//栈不为空，elem与栈顶优先级比较返回NOT_COEXIST，则返回false，结束运行
		if (Compare(sign, str_to_sym(signStack.GetTop())) == Priority::NOT_COEXIST)
			return false;

			//栈不为空，elem与栈顶元素优先级比较，elem优先级低
			//存在两种情况，elem为右括号和elem不为右括号
		while (signStack.Len() >0) {
			string temElem = signStack.Pop();//储存栈顶元素的temElem
			if (Compare(sign, str_to_sym(temElem)) == Priority::NOT_COEXIST)
				return false;
			if (sign == Sign::RIGHT_BRACKET && str_to_sym(temElem) == Sign::LEFT_BRACKET) {
				break;
			}
			if (Compare(sign, str_to_sym(temElem)) == Priority::LOWER) {
				postOrderFormulas.push_back(temElem);
				continue;
			}
			if (Compare(sign, str_to_sym(temElem)) == Priority::HIGHER) {
				signStack.Push(temElem);
				break;
			}
		}
		//如果sign不为右括号，则将sign入栈；
		if (sign != Sign::RIGHT_BRACKET)
				signStack.Push(elem);
	}
	//将符号栈剩余元素出栈进入后缀表达式
	while (signStack.Len() != 0) {
		postOrderFormulas.push_back(signStack.Pop());
	}
	//清除空格
	vector<string> postStr;
	for (int i = 0; i < postOrderFormulas.size(); i++) {
		if (postOrderFormulas[i].size() != 0) {
			postStr.push_back(postOrderFormulas[i]);
		}
	}
	//将中缀表达式替换为后缀表达式
	inOrderFormulas.clear();
	inOrderFormulas = postStr;
	return true;
}

double Calculation::resultOfPostFormulas(const vector<string>& postOrderFormulas) {
	Stack<double> resultStack;

	for(int cursor=0;cursor<postOrderFormulas.size();cursor++) {
		string elem = postOrderFormulas[cursor];
		if (str_to_sym(elem) == Sign::ERROR) {//string为数字，入栈
			double num = atof(&elem[0]);
			resultStack.Push(num);
			continue;
		}
		double num1, num2;
		Sign sign = str_to_sym(elem);//string为数学符号
		if (resultStack.Pop(num2) == false || resultStack.Pop(num1) == false)
			return ERROR_CODE;
		if (sign == Sign::ERROR)
			return ERROR_CODE;
		if (sign == Sign::EQUAL)
			break;
		resultStack.Push(Compute(sign, num1, num2));
	}
	return resultStack.Len() == 1 ? resultStack.Pop() : ERROR_CODE;
}



#endif