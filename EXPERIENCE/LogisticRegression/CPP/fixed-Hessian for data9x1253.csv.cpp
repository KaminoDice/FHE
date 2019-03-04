#include<cstdio>
#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;

double sigmoid(double x)
{
	return 1.0/(1.0 + exp(-x));
}

int main(int argc, char *argv[])
{
	// Input: 
	//       X(N, d+1): trainig data with in each row the values for the covariates for one record 
	//                  and starting with a column of ones to account for the constant coefficient
	//       Y(N, 1): labels of the training data
	//       u0: start value for the Newton-Raphson iteration that computes the inverse
	//       k: the required number of iterations
	// Output: the parameters of the logistic regression model
	vector<vector<double>> zline;
	int factorDim = 1; 	// dimension of x
	int sampleDim = 0;	// number of samples
	string path = "data9x1253.csv";
	ifstream openFile(path.data());
	if(openFile.is_open()) {
		string line, temp;
		getline(openFile, line);
		long i;
		size_t start=0, end;
		for(i = 0; i < line.length(); ++i) if(line[i] == ',' ) factorDim++;

		while(getline(openFile, line)){
			vector<double> vecline;
			do {
				end = line.find_first_of (',', start);
				temp = line.substr(start,end);
				vecline.push_back(atof(temp.c_str()));
				start = end + 1;
			} while(start);
			zline.push_back(vecline);
			sampleDim++;
		}
	} else {
		cout << "Error: cannot read file" << endl;
	}

	double** zData = new double*[sampleDim];
	double * yData = new double [sampleDim];
	if(1/*first elem in each row is the label*/) {
		for(long j = 0; j < sampleDim; ++j){
			double* zj = new double[factorDim];
			// each row started with a 1
			zj[0] = 1.;
			for(long i = 1; i < factorDim; ++i){
				zj[i] = zline[j][i];
			}
			zData[j] = zj;
			// shift y{0,1} to y{-1,+1}
			yData[j] = 2*zline[j][0]-1;
		}
	} 

	// ¦Â = 0.001 * ones(d + 1, 1)
	double * W = new double [factorDim];
	for(int i=0;i<factorDim;++i) W[i] = 0.001;
	// sum = zeros(N, 1)
	double * sum = new double [sampleDim];
	for(int i=0;i<sampleDim;++i) sum[i] = 0.0;
	// for i = 1 : N do
	//    for j = 1 : d+1 do
	//       sum(i) += X(i)(j)
	//    end for
	// end for
	for(int i=0;i<sampleDim;++i)
		for(int j=0;j<factorDim;++j)
		sum[i] += zData[i][j];
	// for j = 1 : d+1 do
	//    temp = 0;
	//    for i = 1 : N do
	//       temp += X(i)(j) * sum(i);
	//    end for
	//    H(j) = -1/4*temp;
	//    1/H(j) = 2*u0 - H(j)*u0*u0;
	// end for
	double * H = new double [factorDim];
	for(int j=0;j<factorDim;++j)
	{
		double temp = 0.0;
		for(int i=0;i<sampleDim;++i)
			temp += zData[i][j]*sum[i];
		double Hj = -0.25*temp;
		H[j] = 1/Hj;
	}
	// for it = 1 : k do
	//    for i = 1 : N do
	//       // compute the grad
	//       g = (1/2 + 1/4*Y(i)*X(i,:)*W)*Y(i)*X(i,:);
	//    end for
	//    // W = W - H_*g
	//    W = W - H_*g
	// end for
	int n = 1200;
	for(int iter=0;iter<n;++iter)
	{
		double *g = new double [factorDim]();
		for(int i=0;i<factorDim;++i) g[i] = 0.0;
		for(int i=0;i<sampleDim;++i)
		{
			double WXi = 0.0;
			for(int k=0;k<factorDim;++k)
				WXi += W[k]*zData[i][k];

			for(int j=0;j<factorDim;++j)
				g[j] += (1-sigmoid(yData[i]*WXi)) *yData[i]*zData[i][j];
		}

		// print Weights
		for(int i=0;i<factorDim;++i)
			cout<<setw(15)<<W[i];
		
		for(int i=0;i<factorDim;++i)
			W[i] = W[i] - H[i]*g[i];

		// compute the hit rate
		int hit = 0;
		for(int i=0;i<sampleDim;++i)
		{
			double WXi = 0.0;
			for(int k=0;k<factorDim;++k)
				WXi += W[k]*zData[i][k];
			if(1/( 1+sigmoid(-WXi) )>=0.5)
			{
				// in this case, classify y=1
				if(yData[i]==1) ++hit;
			}else
			{
				if(yData[i]==-1) ++hit;
			}
		}
		cout<<setw(15)<<"HIT RATE: "<<setw(5)<<(double)hit/sampleDim<<endl;
		//cout<<setw(3)<<iter<<"-th: "<<hit<<" / "<<sampleDim
		//	<<" = "<<(double)hit/sampleDim<<endl;
	}
	

	return 0;
}
