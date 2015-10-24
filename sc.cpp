/*
** By Dingo
** 2015/10/17
*/
#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
//check for balance of brace and legality of expression  
bool Legality_check(const string &str);
//transfor string expression into int expression
void Str_to_int(const string &str,vector<int> &vec){
	string sin;
	for(char i:str){
		if(isdigit(i))
			sin+=i;
		else{
			int n=stoi(sin);
			vec.push_back(n);
			vec.push_back(i);
			sin.erase(0);
		}
	}
	int n=stoi(sin);
	vec.push_back(n);
}
//transfor infix into postfix
//void Infix_to_postfix(const string &str,vector<char> &vec){
//	stack<char> Sym;		//store for operator
//	static map<char,int> PRI;		//priority level of operator
//	PRI['+']=1;
//	PRI['-']=1;
//	PRI['*']=2;
//	PRI['%']=2;
//	PRI['(']=3;
//	PRI[')']=3;
////	PRI['[']=4;
////	PRI[']']=4;
//	for(char i:str){
//		if(isalpha(i))	vec.push_back(i);
//		else if(i=='('&&i=='[')
//			Sym.push(i);
//		else if(i==')'){
//			while(Sym.top()!='('){
//				vec.push_back(Sym.top());
//				Sym.pop();
//			}
//			Sym.pop();
//		}
//		else{
//			while(!Sym.empty()){
//				if(PRI[Sym.top()]>=PRI[i]&&PRI[Sym.top()]<=2){
//					vec.push_back(Sym.top());
//					Sym.pop();
//				}else
//					break;
//			}
//			Sym.push(i);
//		}
//	}
//	while(!Sym.empty()){
//		vec.push_back(Sym.top());
//		Sym.pop();
//	}
//}
int Caculate_twonums(const int &a,const int &b,const char &o){
	//get operator for four stuation
	if(o=='+')
		return a+b;
	else if(o=='-')
		return b-a;
	else if(o=='*')
		return a*b;
	else
		return b/a;
}
int Caculate_expression(const string &str){
	static map<char,int> PRI;		//priority level of operator
	PRI['+']=1;
	PRI['-']=1;
	PRI['*']=2;
	PRI['%']=2;
	PRI['(']=3;
	PRI[')']=3;
	stack<char> Sym;		//store for the operator
	stack<int> Num;			//store for the number
	string int_s;
	for(auto v:str){
		if(isdigit(v))
			int_s+=v;
		else{
			int k=stoi(int_s);
			Num.push(k);
			int_s.erase(0);
			if(Sym.empty()||v=='(')
				Sym.push(v);
			else if(v==')'){
				while(Sym.top()!='('){
					int a=Num.top();
					Num.pop();
					int b=Num.top();
					Num.pop();
					char o=Sym.top();
					Sym.pop();
					int r=Caculate_twonums(a,b,o);
					Num.push(r);	
				}
				Sym.pop();
			}
			else{
				while(!Sym.empty()){
					if(PRI[Sym.top()]>=PRI[v]&&PRI[Sym.top()]<=2){
						int a=Num.top();//¿É¼ò»¯ 
						Num.pop();
						int b=Num.top();
						Num.pop();
						char o=Sym.top();
						Sym.pop();
						int r=Caculate_twonums(a,b,o);
						//2
						//cout<<r<<endl;
						Num.push(r);
					}else
						break;
				}
				Sym.push(v);
			}
		}
	}
	int k=stoi(int_s);
	Num.push(k);
	while(!Sym.empty()){
		int a=Num.top();
		Num.pop();
		int b=Num.top();
		Num.pop();
		char o=Sym.top();
		Sym.pop();
		int r=Caculate_twonums(a,b,o);
		//2
		//cout<<r<<endl;
		Num.push(r);
	}
	return Num.top();
}
int main(){
	string str;
	vector<char> vec_pf;
	vector<int> vec_it;
	cout<<"Enter The Fucking Expression:"<<endl;
	getline(cin,str);
	Str_to_int(str,vec_it);				//transfor string expression into int expression
	int result=Caculate_expression(str);
	cout<<result<<endl;
//	Infix_to_postfix(str,vec_pf);		//Infix expression to postfix
//	for(auto i:vec_pf)
//		cout<<i;
	return 0;
} 
