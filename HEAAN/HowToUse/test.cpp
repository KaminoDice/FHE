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

void print(complex<double>* &vec, long slots)
{
	for(int i=0;i!=slots;++i)
		cout<<"\t"<<vec[i];
}

int main() {

  // Parameters //
  long logn = 3;  // useless in this case, slots = (1 << logn)
  long logq = 7;
  long logp = 0; ///< Larger logp will give you more correct result (smaller computation noise)
                  long slots = 4; ///< This should be power of two
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
  //complex<double>* mvec1 = EvaluatorUtils::randomComplexArray(slots);
  complex<double>* mvec1 = new complex<double>[slots];
  for(int i=0; i!=slots; ++i) mvec1[i] = i+1;
  //complex<double>* mvec2 = EvaluatorUtils::randomComplexArray(slots);
  complex<double>* mvec2 = new complex<double>[slots];
  for(int i=0; i!=slots; ++i) mvec2[i] = i+1;
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
  complex<double> mmval(4, 0);
  Ciphertext ccval;
  scheme.encryptSingle(ccval,mmval, logp, logq);
  complex<double> ddval = scheme.decryptSingle(secretKey, ccval);
  long idx = 1;
  Ciphertext ccrot;
  scheme.leftRotateFast(ccrot, ccval, idx);
  complex<double> mmrot = scheme.decryptSingle(secretKey, ccrot);
 cout<<"RUN 5"<<endl;
  // Decrypt //
  complex<double>* dvec1 = scheme.decrypt(secretKey, cipher1);
  complex<double>* dvec2 = scheme.decrypt(secretKey, cipher2);
  complex<double>* dadd  = scheme.decrypt(secretKey, cipherAdd);
  complex<double>* dmult = scheme.decrypt(secretKey, cipherMult);
  complex<double>* dmres = scheme.decrypt(secretKey, cipherMultAfterReScale);
  

  cout<<"# mvec1 :";print(mvec1, slots);cout<<"#"<<endl;
  cout<<"# mvec2 :";print(mvec2, slots);cout<<"#"<<endl;
  cout<<"# dvec1 :";print(dvec1, slots);cout<<"#"<<endl;
  cout<<"# dvec2 :";print(dvec2, slots);cout<<"#"<<endl;
  cout<<"# dadd  :";print(dadd, slots); cout<<"#"<<endl;
  cout<<"# dmult :";print(dmult, slots);cout<<"#"<<endl;
  cout<<"# dmres :";print(dmres, slots);cout<<"#"<<endl;
  cout<<"# mval :"<<mmval<<endl;
  cout<<"# dval :"<<ddval<<endl;
  cout<<"# mrot :"<<mmrot<<endl;
 
  cout<<"RUN 6"<<endl;

  return 0;

}
