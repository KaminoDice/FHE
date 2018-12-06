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

  // Parameters //
  long logn = 3;  // useless in this case, slots = (1 << logn)
  long logq = 3;
  long logp = 2; ///< Larger logp will give you more correct result (smaller computation noise)
                  long slots = 8; ///< This should be power of two
		  long logr = 0; ///< It is used for scheme.addLeftRotKey(secretKey, (1 << logr)); 
  long numThread = 8;

  srand(time(NULL));
  SetNumThreads(slots);
  // Construct and Generate Public Keys //
  TimeUtils timeutils;
  Ring ring;
  SecretKey secretKey(ring);
  Scheme scheme(secretKey, ring);
cout<<"RUN 0"<<endl;
          scheme.addLeftRotKey(secretKey, (1<<logr)); ///< When you need left rotation for the vectorized message
          scheme.addRightRotKey(secretKey, (1<<logr)); ///< When you need right rotation for the vectorized message
cout<<"RUN H"<<endl;  
  // Make Random Array of Complex //
  complex<double>* mvec1 = EvaluatorUtils::randomComplexArray(slots);
  complex<double>* mvec2 = EvaluatorUtils::randomComplexArray(slots);
cout<<"RUN 1"<<endl;  
  // Encrypt Two Arry of Complex //
  Ciphertext cipher1;
  timeutils.start("Encrypt mvec1"); 
  scheme.encrypt(cipher1, mvec1, slots, logp, logq);
  timeutils.stop("Encrypt mvec1");
  Ciphertext cipher2; 
  timeutils.start("Encrypt mvec2");
  scheme.encrypt(cipher2, mvec2, slots, logp, logq);
  timeutils.stop("Encrypt mvec2");
 cout<<"RUN 2"<<endl;
  // Addition //
  Ciphertext cipherAdd;
  scheme.add(cipherAdd, cipher1, cipher2);
 cout<<"RUN 3"<<endl;
  // Multiplication And Rescale //
  Ciphertext cipherMult;
  scheme.mult(cipherMult, cipher1, cipher2);
  Ciphertext cipherMultAfterReScale;
  scheme.reScaleBy(cipherMultAfterReScale, cipherMult, logp);
 cout<<"RUN 4"<<endl;
  // Rotation //
  long idx = 1;
  Ciphertext cipherRot;
  scheme.leftRotateFast(cipherRot, cipher1, idx);
 cout<<"RUN 5"<<endl;
  // Decrypt //
  complex<double>* dvec1 = scheme.decrypt(secretKey, cipher1);
  complex<double>* dvec2 = scheme.decrypt(secretKey, cipher2);
  complex<double> plainRot = scheme.decryptSingle(secretKey, cipherRot);
  auto before = scheme.decryptSingle(secretKey, cipher1);
  cout<<"BEFORE ROTATION : "<<before<<endl;
  cout<<"AFTER  ROTATION : "<<plainRot<<endl;
cout<<"RUN 6"<<endl;

  return 0;

}
