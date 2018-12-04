#include <cstddef>
#include <ctime>
#include <cmath>
#include "FHE.h"
#include "EncryptedArray.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ.h>
#include <gmp.h>
#include <iterator>

class Timer{
	private: clock_t start;
	private: clock_t stop;
	private: double last;
	
	public: Timer(){
		this->start = clock();
	}
	public: double elapsed_time(){
		(*this).stop = clock();
		this->last = ( (double)stop - (double)start )/CLOCKS_PER_SEC;
		return last;
	}
	public: double tillNow(){
		return ( (double)clock() - (double)start )/CLOCKS_PER_SEC;
	}
	public: void reset(){
		start = clock();
	}
};


int main(int argc, char **argv)
{

    /*** BEGIN INITIALIZATION ***/
    long m = 0;                   // Specific modulus
    long p = 11;           // Plaintext base [default=2], should be a prime number
    long r = 1;                   // Lifting [default=1]
   
    long L = 3;                  // Number of levels in the modulus chain [default=heuristic]
    long c = 3;                   // Number of columns in key-switching matrix [default=2]
    long w = 64;                  // Hamming weight of secret key
    long d = 1;                   // Degree of the field extension [default=1]
    long k = 80;                  // Security parameter [default=80] 
    long s = 0;                   // Minimum number of slots [default=0]

    //m = FindM(k, L, c, p, d, s, 0); 
    // use the special cyclotomic polynomial where m is a power of 2.
    // PHIm(x) = x^(m/2) +1
    // if the degree of polynomial should be at least d,
    // m should be more than 2d and is a power of 2.
    m = FindM(k, L, c, p, d, s, 0); 
    //m = 8; // PHI8(x) = x^4 + 1 , the size of EncryptedArray.ea is important!     
    std::cout << "m = " << m << std::endl;
    FHEcontext context(m, p, r); 	          // Initialize context
    buildModChain(context, L, c);             // Modify the context, adding primes to the modulus chain
    FHESecKey sk(context);                    // Construct a secret key structure
    const FHEPubKey& pk = sk;                 // An "upcast": FHESecKey is a subclass of FHEPubKey
    sk.GenSecKey(w);                          // Actually generate a secret key with Hamming weight
    addSome1DMatrices(sk);                    // Extra information for relinearization

    std::cout<< "m = "<<m<<std::endl;
    // Arrays whose elements will be the coefficients of the polynomials U(x) and V(x)
    std::vector<long>  u = {1, 2, 3, 4};
    std::vector<long>  v = {1, 2, 3, 4};
    cout<<"u = "<<u<<endl;
    cout<<"v = "<<v<<endl;

    /********************** USE SUBFIELDS PACKING, MULTIPLY AND SUM **********************/
    // Creates a helper object based on the context
    EncryptedArray ea(context, context.alMod.getFactorsOverZZ()[0]); 
    cout<<"EncryptedArray ea.size() = "<<ea.size()<<std::endl;
    std::vector<long> U(u.begin(), u.end());
    std::vector<long> V(v.begin(), v.end());

    for (int i = u.size(); i < ea.size(); i++) {
		U.push_back(0);
		V.push_back(0);
    }

    // Ciphertexts that will hold the encrypted vectors
    Ctxt encU(pk);
    Ctxt encV(pk);

    Timer t1;
    // Encrypt the whole vector into one ciphertext using packing
    ea.encrypt(encU, pk, U);
    ea.encrypt(encV, pk, V);
    std::cout << "HElib subfield packing encryption: OK! " <<t1.tillNow()<< std::endl; 

    Timer t2;
    // Multiply ciphertexts and set the result to encU
    encU.multiplyBy(encV);
    std::cout << "HElib subfield packing multiply : OK! "<<t2.tillNow()<< std::endl;

    // Use the totalSums functions to sum all the elements
    // The result will have the sum in all positions of the vector
    totalSums(ea, encU);
    std::cout << "HElib subfield packing sum: OK!" <<  std::endl;   
  
    // Decrypt the result(i.e., the scalar product value)
    ZZX result;
    sk.Decrypt(result, encU);     

    ZZ method3Result = result[0];
    std::cout << "HElib with subfield packing method result: " << method3Result <<std::endl;

    long  ans = 0;
    for(int i=0; i<u.size(); ++i){
	   ans += u[i]*v[i];
    }
    cout<< "ans = " <<  ans <<std::endl; 
    cout<< "ans % p^r = " << ans % (long) (pow( p, r)) <<std::endl;


    return 0;
}
