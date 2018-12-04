#include<iostream>
#include<gmpxx.h>
#include<NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	mpz_class a;

	a = 1;
	for(int i=0;i<1000; i++) a *= 2;

	cout<<"2^1000 = "<<a<<endl;

	mpz_class b, c;
	b = -123456;
        c = "987654321234567898765432123456789";
	cout<<"b * c = "<<b*c<<endl;

	ZZ aa,bb,cc;
	cout<<"INPUT aa : ";
	cin>>aa;
	cout<<"INPUT bb : ";
	cin>>bb;

	cc = (aa+1)*(bb+1);
	cout<<cc<<endl;

	return 0;
}

/*
root@vultr:/home# g++ -pthread test.cpp -lntl -lgmp -lgmpxx
root@vultr:/home# ./a.out                          
2^1000 = 10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376
b * c = -121931851882334814509985188233481342784
INPUT aa : 4
INPUT bb : 5
30
root@vultr:/home# 
*/
