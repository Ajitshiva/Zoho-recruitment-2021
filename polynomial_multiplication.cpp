#include <bits/stdc++.h>
using namespace std;
class Term
{
	public:
		char sign; 
		int constant; 
		map<string, int> variables;
		Term(){}
		Term(char sign, int constant, map<string, int>& variables)
		{
			this->sign = sign;
			this->constant = constant;
			this->variables = variables;
		}
};

class ModifiedTerm
{
	public:
		char sign;
		int constant;
		string variables;
};

char assignSign(char first, char second)
{
	if(first == second)
	{
		return first;
	}
	else return '-';
}

ModifiedTerm convertTermtoString(Term t)
{
	ModifiedTerm res;
	res.sign = t.sign;
	res.constant = t.constant;
	string variables;
	for(auto it : t.variables)
	{
		variables += it.first;
		if(it.second != 1)
		{
			variables.push_back('^');
			variables += to_string(it.second);
		}
	}
	res.variables = variables;
	return res;
}
Term mul(Term A, Term B)
{
	Term C;
	C.sign = assignSign(A.sign, B.sign);
	C.constant = A.constant * B.constant;
	map<string, int> variables;
	for(auto it : A.variables)
	{
		variables[it.first] = it.second;
	}
	for(auto it : B.variables)
	{
		variables[it.first] += it.second;
	}
	C.variables = variables;
	return C;
}
vector<string> splitExpression(string expression)
{
	vector<string> terms;
	string single;
	bool start = false;
	for(int i = 0; i < expression.size(); i++)
	{		
		if(expression[i] == ')')
		{
			start = false;
		}
		if(start)
		{
			single.push_back(expression[i]); 
		}
		if(!start)
		{
			if(single.size() > 0)
			{
				terms.push_back(single);
			}
			single = "";
		}
		if(expression[i] == '(')
		{
			start = true;
		}
	}
	return terms;
}
vector<string> splitTerm(string s)
{
	vector<string> eachTerm;
	bool start = true;
	string single;
	for(int j = 0; j < s.size(); j++)
	{
		if(s[j] == '+' || s[j] == '-')
		{
			start = false;
			eachTerm.push_back(single);
			single = "";
		}
		single.push_back(s[j]);
	}
	eachTerm.push_back(single);
	return eachTerm;
}
Term stringToTerm(string t)
{
	char sign = '+';
	if(t[0] == '-')
	{
		sign = '-';
	}
	int constant = 0;
	int start = (t[0] == '-' || t[0] == '+' ? 1 : 0);
	map<string, int> variables;
	int j = start;
	for(; j < t.size(); j++)
	{
		if(!isdigit(t[j]))
		{
			break;
		}
		constant = constant * 10 + (t[j] - '0');
	}
	string var;
	int coefficient = 1;
	if(constant == 0) constant = 1;
	for(; j < t.size(); j++)
	{
		var.push_back(t[j]);
		if(var.size() == 1)
		{
			if(j+1 < t.size() && t[j+1] == '^')
			{
				j = j + 1;
				coefficient = 0;
				while(j + 1 < t.size() && isdigit(t[j+1]))
				{
					coefficient = coefficient * 10 + t[j+1] - '0';
					j++;
				}
			}
			variables[var] = coefficient;
			var.clear();
			coefficient = 1;
		}
	}
	return Term(sign, constant, variables);
}
vector<Term> multiplyExpression(vector<Term>& A, vector<Term>& B)
{
	vector<Term> ans;
	for(int i = 0; i < A.size(); i++)
	{
		for(int j = 0; j < B.size(); j++)
		{
			Term temp = mul(A[i], B[j]);
			ans.push_back(temp);
		}
	}
	return ans;
}


int main()
{
	string expression;
	cin >> expression;
	vector<string> terms = splitExpression(expression);
	vector<Term> A;
	vector<Term> B;	
	for(int i = 0; i < 2; i++)
	{
		vector<string> eachTerm = splitTerm(terms[i]);

		for(string t : eachTerm)
		{			
			Term temp = stringToTerm(t);
			if(i == 0)
			{
				A.push_back(temp);
			}
			else if(i == 1)
			{
				B.push_back(temp);

			}
		}
	}
	vector<Term> ans = multiplyExpression(A, B);
	A.clear();
	A = ans;
	ans.clear();

	for(int j = 2; j < terms.size(); j++)
	{
		vector<string> eachTerm = splitTerm(terms[j]);
		B.clear();		
		for(string t : eachTerm)
		{
			Term temp = stringToTerm(t);
			B.push_back(temp);		
		}
		ans = multiplyExpression(A, B);
		A = ans;
		ans.clear();
	}

	map<string, int> res;
	for(Term each : A)
	{
		ModifiedTerm t = convertTermtoString(each);
		if(t.sign == '+')
		{
			res[t.variables] += t.constant;
		}
		else if(t.sign == '-')
		{
			res[t.variables] -= t.constant;
		}
	}
	for(auto it : res)
	{
		if(it.second > 0) cout << '+';
		cout << it.second << it.first;
	}


}