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
	bool StrToFormulas(const string& formulasStr,vector<string>& inOrderFormulas);//��ѧ���������ַ��룬�����ʽ�����򷵻�false
	bool InOrderToPost(vector<string>& inOrderFormulas);//��׺���ʽת��Ϊ��׺���ʽ,�������򷵻�false
	double resultOfPostFormulas(const vector<string>& postOrderFormulas);//��׺���ʽ����
};

bool Calculation::StrToFormulas(const string& formulasStr, vector<string>& inOrderFormulas) {
	string c_formulasStr = formulasStr;
	if (c_formulasStr.back() != equalSign)
		c_formulasStr.push_back(equalSign);
	//ȥ���ո�
	c_formulasStr.erase(std::remove(c_formulasStr.begin(), c_formulasStr.end(), ' '), c_formulasStr.end());
	//������޷Ƿ��ַ�
	for (int i = 0; i < c_formulasStr.size(); i++) {
		string temStr;
		temStr = c_formulasStr[i];
		if (isdigit(c_formulasStr[i])!=0 || c_formulasStr[i] == point || str_to_sym(temStr) != Sign::ERROR)
			continue;
		return false;
	}
	//�������ַ�����
	string numString="";
	bool flag = false;//��Ǹ���
	for (int i = 0; i < c_formulasStr.size(); i++) {
		char elemOfChar = c_formulasStr[i];
		string temStr(1, elemOfChar);

		//����Ƿ�Ϊ����
		if (str_to_sym(temStr) == Sign::ERROR) {
			numString.push_back(elemOfChar);
			continue;
		}
		//��numstringѹ��������
		inOrderFormulas.push_back(numString);
		numString.clear();
		if (str_to_sym(temStr) == Sign::MINUX&&i>0 && c_formulasStr[i-1]=='(')
			inOrderFormulas.push_back(zeroStr);
		inOrderFormulas.push_back(temStr);
		continue;
	}
	//ȥ�����ں�
	inOrderFormulas.pop_back();
	return true;
}

bool Calculation::InOrderToPost(vector<string>& inOrderFormulas) {
	vector<string> postOrderFormulas;
	Stack<string> signStack;
	Sign sign;
	//����׺���ʽ���б�����תΪ��׺
	for (int i = 0; i < inOrderFormulas.size(); i++) {
		string elem = inOrderFormulas[i];
		sign = str_to_sym(elem);
		//elemΪ���֣������׺���ʽ
		if (sign== Sign::ERROR) {
			postOrderFormulas.push_back(elem);
			//cout << i << "  " << elem << endl;
			continue;
		}
		//elemΪ��ѧ����
		    //��ջΪ�գ���ջ����elem���ȼ���ջ��Ԫ�ظߣ���ջ
		if (signStack.Len() == 0 || signStack.Len() != 0 && Compare(sign, str_to_sym(signStack.GetTop())) == Priority::HIGHER) {//���ȼ��ߣ���ջ
			signStack.Push(elem);
			continue;
		}
			//ջ��Ϊ�գ�elem��ջ�����ȼ��ȽϷ���NOT_COEXIST���򷵻�false����������
		if (Compare(sign, str_to_sym(signStack.GetTop())) == Priority::NOT_COEXIST)
			return false;

			//ջ��Ϊ�գ�elem��ջ��Ԫ�����ȼ��Ƚϣ�elem���ȼ���
			//�������������elemΪ�����ź�elem��Ϊ������
		while (signStack.Len() >0) {
			string temElem = signStack.Pop();//����ջ��Ԫ�ص�temElem
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
		//���sign��Ϊ�����ţ���sign��ջ��
		if (sign != Sign::RIGHT_BRACKET)
				signStack.Push(elem);
	}
	//������ջʣ��Ԫ�س�ջ�����׺���ʽ
	while (signStack.Len() != 0) {
		postOrderFormulas.push_back(signStack.Pop());
	}
	//����ո�
	vector<string> postStr;
	for (int i = 0; i < postOrderFormulas.size(); i++) {
		if (postOrderFormulas[i].size() != 0) {
			postStr.push_back(postOrderFormulas[i]);
		}
	}
	//����׺���ʽ�滻Ϊ��׺���ʽ
	inOrderFormulas.clear();
	inOrderFormulas = postStr;
	return true;
}

double Calculation::resultOfPostFormulas(const vector<string>& postOrderFormulas) {
	Stack<double> resultStack;

	for(int cursor=0;cursor<postOrderFormulas.size();cursor++) {
		string elem = postOrderFormulas[cursor];
		if (str_to_sym(elem) == Sign::ERROR) {//stringΪ���֣���ջ
			double num = atof(&elem[0]);
			resultStack.Push(num);
			continue;
		}
		double num1, num2;
		Sign sign = str_to_sym(elem);//stringΪ��ѧ����
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