/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/
#include "../src/HEAAN.h"

int main() {


//----------------------------------------------------------------------------------
//   STANDARD TESTS
//----------------------------------------------------------------------------------


//	TestScheme::testEncrypt(34, 23, 2);
//	TestScheme::testEncryptSingle(34, 23);
//*	TestScheme::testAdd(34, 23, 2);
//      TestScheme::testMult(105, 30, 4);
//	TestScheme::testimult(34, 23, 2);


//----------------------------------------------------------------------------------
//   ROTATE & CONJUGATE
//----------------------------------------------------------------------------------

//      If you want to change some code in lib, you should remake the libHEAAE.a.
//      Probabely it is related to the "static" key word in TestScheme.h from lib.
//      static void testRotateFast(...); /* in TestScheme.h from lib */
	TestScheme::testRotateFast(1200, 30, 4, 1);
//	TestScheme::testRotate(15, 300, 30, 4, 1);
//	TestScheme::testConjugate(15, 300, 30, 4);


//----------------------------------------------------------------------------------
//   POWER & PRODUCT
//----------------------------------------------------------------------------------


//	TestScheme::testPowerOf2(15, 300, 30, 4, 4);
//	TestScheme::testPower(15, 300, 30, 4, 13);
//	TestScheme::testProdOfPo2(15, 300, 30, 4, 4);
//	TestScheme::testProd(15, 300, 30, 4, 13);


//----------------------------------------------------------------------------------
//   FUNCTION
//----------------------------------------------------------------------------------


//	TestScheme::testInverse(15, 300, 25, 4, 6);
//	TestScheme::testLogarithm(15, 300, 30, 4, 7);
//	TestScheme::testExponent(15, 300, 30, 4, 7);
//	TestScheme::testSigmoid(15, 300, 30, 4, 7);
//	TestScheme::testSigmoidLazy(15, 300, 30, 4, 7);


//----------------------------------------------------------------------------------
//   DFT
//----------------------------------------------------------------------------------


//	TestScheme::testDFTBatch(15, 300, 30, 4, 3);
//	TestScheme::testDFTLazyBatch(15, 300, 30, 4, 3);
//	TestScheme::testDFTLazyBatchMultipleHadamard(15, 300, 30, 3, 3, 3);


//----------------------------------------------------------------------------------
//   BOOTSTRAPPING
//----------------------------------------------------------------------------------


//	TestScheme::testBootstrap(15, 23, 29, 620, 3, 2);
//	TestScheme::testBootstrapSingleReal(15, 23, 29, 620, 2);


//----------------------------------------------------------------------------------
//   OTHER
//----------------------------------------------------------------------------------


//	TestScheme::testCiphertextWriteAndRead(10, 65, 30, 2);
//	TestScheme::test();


// inTestScheme::
void             testRotateFast(long logq, long logp, long logn, long logr) {
	cout << "!!! START TEST ROTATE FAST !!!" << endl;

	srand(time(NULL));
	SetNumThreads(8);
	TimeUtils timeutils;
	Ring ring;
	SecretKey secretKey(ring);
	Scheme scheme(secretKey, ring);

	long n = (1 << logn);
	long r = (1 << logr);
	scheme.addLeftRotKey(secretKey, r);
	complex<double>* mvec = EvaluatorUtils::randomComplexArray(n);
	Ciphertext cipher;
	scheme.encrypt(cipher, mvec, n, logp, logq);

	timeutils.start("Left Rotate Fast");
	scheme.leftRotateFastAndEqual(cipher, r);
	timeutils.stop("Left Rotate Fast");

	complex<double>* dvec = scheme.decrypt(secretKey, cipher);

	EvaluatorUtils::leftRotateAndEqual(mvec, n, r);

    cout<<"mvec : ";
    for(int i=0;i!=n;++i) cout<<"\t"<<mvec[i];
    cout<<endl;
    cout<<"dvec : ";
    for(int i=0;i!=n;++i) cout<<"\t"<<dvec[i];
    cout<<endl;
    StringUtils::compare(mvec, dvec, n, "rot");

	cout << "!!! IT IS IMPOSSIBLE !!!" << endl;
}
	return 0;
}
