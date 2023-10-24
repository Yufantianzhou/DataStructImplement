#ifndef _MATHSIGN_H_
#define _MATHSIGN_H_

#include<limits>
#include<math.h>
#include<iostream>
using namespace std;

//错误码
const double ERROR_CODE= std::numeric_limits<double>::max();

//数学符号总数
const int MATH_SIGN_NUM = 9;

//数学符号储存数组
const string MATH_SIGN[MATH_SIGN_NUM] = { "","+","-","*","/","%","(",")","=" };

//数学符号枚举类
enum class Sign:int {
	ERROR=0,
	PLUS=1,
	MINUX=2,
	MULTIPLY=3,
	EXCEPT=4,
	SURPLUS=5,
	LEFT_BRACKET=6,
	RIGHT_BRACKET=7,
	EQUAL=8
};

 //判断str字符串是否为数学字符
 bool IsMathSign(const string str) {
	 for (int i = 0; i < MATH_SIGN_NUM;i++) {
		 if (str == MATH_SIGN[i])
			 return true;
	 }
	 return false;
}

 //对于给定的str返回为数学符号类值
 Sign str_to_sym(const string& str) { //根据 String 类型 返回 sign 类型值
	 if (str == MATH_SIGN[static_cast<int>(Sign::PLUS)])
		 return Sign::PLUS;
	 if (str == MATH_SIGN[static_cast<int>(Sign::MINUX)])
		 return Sign::MINUX;
	 if (str == MATH_SIGN[static_cast<int>(Sign::MULTIPLY)])
		 return Sign::MULTIPLY;
	 if (str == MATH_SIGN[static_cast<int>(Sign::EXCEPT)])
		 return Sign::EXCEPT;
	 if (str == MATH_SIGN[static_cast<int>(Sign::SURPLUS)])
		 return Sign::SURPLUS;
	 if (str == MATH_SIGN[static_cast<int>(Sign::LEFT_BRACKET)])
		 return Sign::LEFT_BRACKET;
	 if (str == MATH_SIGN[static_cast<int>(Sign::RIGHT_BRACKET)])
		 return Sign::RIGHT_BRACKET;
	 if (str == MATH_SIGN[static_cast<int>(Sign::EQUAL)])
		 return Sign::EQUAL;
	 return Sign::ERROR;
 }

 //给定两个数和数学符号，求值
 double Compute(Sign sign, double a, double b ) {
	 if (sign == Sign::ERROR||sign==Sign::LEFT_BRACKET||sign==Sign::RIGHT_BRACKET)
		 return ERROR_CODE;
	 if (sign == Sign::PLUS)
		 return a + b;
	 if (sign == Sign::MINUX)
		 return a-b;
	 if (sign == Sign::MULTIPLY)
		 return a==0||b==0?0:a * b;
	 if (sign == Sign::EXCEPT)
		 return b==0?ERROR_CODE:a / b;
	 if (sign == Sign::SURPLUS&&a==floor(a)&&b==floor(b))
		 return b==0?a : static_cast<double>(static_cast<int>(a) % static_cast<int>(b));
	 return ERROR_CODE;
 }


 //数学符号优先级枚举类
 enum class Priority {
	 HIGHER, EQUAL, LOWER, NOT_COEXIST
 };


 Priority Compare(const Sign& signOutStack, const Sign& signInStack) {
	 if (signOutStack == Sign::ERROR ||signOutStack==Sign::EQUAL|| signInStack == Sign::ERROR||signInStack==Sign::EQUAL)
		 return Priority::NOT_COEXIST;
	 if (signOutStack == Sign::PLUS || signOutStack == Sign::MINUX) {
		 if ( signInStack == Sign::LEFT_BRACKET)
			 return Priority::HIGHER;
		 return Priority::LOWER;
	 }
	 if (signOutStack == Sign::MULTIPLY || signOutStack == Sign::EXCEPT || signOutStack == Sign::SURPLUS) {
		 if (signInStack == Sign::LEFT_BRACKET||signInStack==Sign::PLUS||signInStack==Sign::MINUX)
			 return Priority::HIGHER;
		 return Priority::LOWER;
	 }
	 if (signOutStack == Sign::LEFT_BRACKET) {
		 if (signInStack == Sign::RIGHT_BRACKET)
			 return Priority::NOT_COEXIST;
		 return Priority::HIGHER;
	 }
	 if (signOutStack == Sign::RIGHT_BRACKET)
		 return Priority::LOWER;
	// return Priority::NOT_COEXIST;
 }

#endif