/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/
#include "BootContext.h"
#include "Ring.h"
#include "RingMultiplier.h"
#include "Ciphertext.h"
#include "EvaluatorUtils.h"
#include "Scheme.h"
#include "SchemeAlgo.h"
#include "SecretKey.h"
#include "StringUtils.h"
#include "TimeUtils.h"
#include "SerializationUtils.h"
#include "TestScheme.h"

#include <NTL/BasicThreadPool.h>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;


int main() {


//----------------------------------------------------------------------------------
//   STANDARD TESTS
//----------------------------------------------------------------------------------


//	TestScheme::testEncrypt(7, 10, 3);
       long logq = 7; 
       long logp = 10; 
       long logn = 3;
       cout<< "!!! START TEST ENCRYPT !!!" <<endl;
       srand(time(NULL));
       SetNumThreads(8);
       TimeUtils timeutils;
       Ring ring;
       SecretKey secretKey(ring);
       Scheme scheme(secretKey, ring);

       long n = (1 << logn);
       complex<double>* mvec = EvaluatorUtils::randomComplexArray(n);
       Ciphertext cipher;

       timeutils.start("Encrypt");
       scheme.encrypt(cipher, mvec, n, logp, logq);
       timeutils.stop("Encrypt");

       timeutils.start("Decrypt");
       complex<double>* dvec = scheme.decrypt(secretKey, cipher);
       timeutils.stop("Decrypt");

       StringUtils::compare(mvec, dvec, n, "val");

       cout<< "!!! END TEST ENCRYPT !!!" <<endl;


//	TestScheme::testEncryptSingle(15, 300, 30);
//	TestScheme::testBasic(16, 1200, 30, 4);
//	TestScheme::testimult(15, 300, 30, 4);


//----------------------------------------------------------------------------------
//   ROTATE & CONJUGATE
//----------------------------------------------------------------------------------


//	TestScheme::testRotateFast(16, 1200, 30, 4, 1);
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


	return 0;
}
