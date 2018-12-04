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
