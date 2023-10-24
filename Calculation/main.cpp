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
	//��������
	const string nullStr = "";
	string formulasStr;//ԭʼ�����ַ���
	vector<string> formulas;//���ʽformulas,���ڴ����׺���ʽ�ͺ�׺���ʽ
	Calculation calculation;//������
	double result;//����ʽ���

	//��ʾ��Ϣ
	cout << "������" << endl
		 << "�ü���������ʵ����double���ͷ�Χ�ڵ����ļӼ��˳�ģ" << endl
		 << "������������ʱ�������ţ���-1д��(-1)"<<endl
		 << "����end��������"<<endl;
	//ִ�в���
	while (true) {
		//������ݣ�Ϊ��һ��������׼��
		formulasStr.clear();
		formulas.clear();
		//���벿��
		cout << ">>";
		getline(cin, formulasStr);
		//����end��������
		if (formulasStr == "end")
			break;
		//��strת��Ϊ��׺���ʽ
		if (calculation.StrToFormulas(formulasStr, formulas) == false) {//�ַ���תΪ��׺
			//cout << "first step" << endl;
			cout << "ERROR!!!"<<endl;//����ֵΪ�٣��������
			continue;
		}
	//	print(formulas);
		if (calculation.InOrderToPost(formulas) == false) {//��׺תΪ��׺
			//cout << "second step" << endl;
			cout << "ERROR!!!"<<endl;
			continue;
		}
	//	print(formulas);
		//������
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