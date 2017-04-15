#ifndef INTERESTRATEPRICING_H
#define INTERESTRATEPRICING_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <thread>
#include "common.h"
#include <mutex>

std::mutex g_display_mutex;

using namespace std;

struct IR_results {
		
	IR_results(){}

	IR_results(vector<double> _datapoints, double _Value)
		: datapoints(_datapoints), Value(_Value) {}

	vector<double> datapoints;
	double Value;

};

class IR {

public:

	// Defualt constructor:

	IR() : notional(0), K(0.05), alpha(0.5), sigma(0.15), dT(0.5), N(4), M(10000) {}

	// Constructor from input arguments:

	// FOR IR1:

	IR(double _notional, double _K, double _alpha, double _sigma, double _dT, int _N, int _M)
		: notional(_notional), K(_K), alpha(_alpha), sigma(_sigma), dT(_dT), N(_N), M(_M) {}

	// For IR2:

	IR(double _K, double _alpha, double _sigma, double _dT, int _N, int _M)
		: K(_K), alpha(_alpha), sigma(_sigma), dT(_dT), N(_N), M(_M) {}

	// A function to extract the data and premium value:

	IR_results get_simulation_dataCap() const
	{
		return run_LIBOR_simulationsCap();
	}

	IR_results get_simulation_dataPlain() const
	{
		return run_LIBOR_simulationsPlain();
	}


	void fileRead(int selection, string file) {
		//cout << file; return;
		std::ifstream fin(file, std::ios::in);
		if (!fin) {           // If the file was not found, then file is 0, i.e. !file=1 or true.
			cout << "\nFile not found!\n";
			return;    // The file was not found.
		}
		cout << "return";
		//	return;
		int i = 0;
		if (selection == 1) {
			int i = 0;
			string line;
			while (!fin.eof()){
				float a, b, c, d, e, f, g;

				fin >> a >> b >> c >> d >> e >> f >> g;
			//	cout << a << b << c << d << e << f << g;
			//	(getline(fin, line));
					IR1run(a, b, c, d, e, f, g, "normal");
				system("pause"); cout << "Done with run # " << ++i;
			}
		}
		else if (selection == 2) {
			int i = 0;
			while (!fin.good()){
				float a, b, c, d, e, f;
				fin >> a >> b >> c >> d >> e >> f;
				IR2run(a, b, c, d, e, f);
				system("pause"); cout << "Done with run # " << i;
			}
		}
		else {
			cout << "Invalid input!";
		}




		fin.close();
	}

	void fileReadMultiThread(int selection, string file) {
		//cout << file; return;
		std::ifstream fin(file, std::ios::in);
		if (!fin) {           // If the file was not found, then file is 0, i.e. !file=1 or true.
			cout << "\nFile not found!\n";
			return;    // The file was not found.
		}
		IR localTest;

		int i = 0;
		if (selection == 1) {
			int i = 0;
			string line;
			while (!fin.eof()){
				float a, b, c, d, e, f, g;

				fin >> a >> b >> c >> d >> e >> f >> g;
				//cout << a << b << c << d << e << f << g;

			//	cout << "start thread #" << i << endl;
				std::thread t(&IR::IR1run, this, a, b, c, d, e, f, g, "multi-thread");
				t.join();
				i++;
				//IR1run(a, b, c, d, e, f, g);				
			}
			//system("pause"); cout << "Done with run # " << ++i;
		}

		else if (selection == 2) {
			int i = 0;
			while (!fin.good()){
				float a, b, c, d, e, f;
				fin >> a >> b >> c >> d >> e >> f;
				std::thread t(&IR::IR2run, this, a, b, c, d, e, f);
				t.join();
				i++;
				//IR2run(a, b, c, d, e, f);
			//	system("pause"); cout << "Done with run # " << i;
			}
		}
		else {
			cout << "Invalid input!";
		}




		fin.close();
	}

	// double a,b,c,d,e,f,g;
	void IR1run(double a, double b, double c, double d, double e, double f, double g, string runMode){

		cout << "\n *** Monte-Carlo Interest Rate Swap (IRS) *** \n\n";

		std::thread::id this_id = std::this_thread::get_id();

		g_display_mutex.lock();
		std::cout << "thread " << this_id << " is starting...\n";
		g_display_mutex.unlock();

		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		// Plain Vanilla IRS, pays fixed, receives floating
		// freq payments every 3M, maturity 1 year

		// STEP 1: INPUT PARAMETERS

		auto notional = a; // notional 
		auto K = b; // fixed rate IRS
		auto alpha = c; // daycount factor
		auto sigma = d; // fwd rates volatility
		auto dT = e;
		auto N = f; // number forward rates
		auto M = g; // number of simulations

		// Construct a IR object from the input parameters:

		IR ir1(notional, K, alpha, sigma, dT, N, M);

		// Obtain the value of premium from member function "get_premium()":

		auto results = ir1.get_simulation_dataPlain();

		// STEP 10: OUTPUT RESULTS

		auto sz = results.datapoints.size();
		int i = 0;
		if (runMode == "multi-thread") {
		//	cout << "\nstart thread #" << ++i <<"\n";
		}
		else {
			for (decltype(sz) nsim = 0; nsim < sz; ++nsim)
			{
				cout << "simIRS[" << nsim << "] = " << results.datapoints[nsim] << endl;
			}
		}

		cout << "\n *** IRS PV = " << results.Value << endl;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		cout << "\nMonte-Carlo Simulation elapsed: ";
		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " mS" << endl << endl;
		cout << "\n *** END Monte-Carlo Interest Rate Swap (IRS) *** \n";

	}

	// double a,b,c,d,e,f;
	void IR2run(double a, double b, double c, double d, double e, double f) {

		std::cout << "\n *** START Interest rate swap with a cap *** \n\n";
		std::thread::id this_id = std::this_thread::get_id();

		g_display_mutex.lock();
		std::cout << "thread " << this_id << " is starting...\n";
		g_display_mutex.unlock();
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		// STEP 1: INPUT PARAMETERS
		auto K = a; // strike caplet 
		auto alpha = b; // daycount factor
		auto sigma = c; // fwd rates volatility
		auto dT = d;
		auto N = e; // number forward rates
		auto M = f; // number of simulations

		// Construct a IR object from the input parameters:

		IR ir2(K, alpha, sigma, dT, N, M);

		// Obtain the value of premium from member function "get_premium()":

		auto results = ir2.get_simulation_dataCap();

		// STEP 10: OUTPUT RESULTS

		auto sz = results.datapoints.size();

		for (decltype(sz) nsim = 0; nsim < sz; ++nsim)
		{
			cout << "Vcap[" << nsim << "] = " << results.datapoints[nsim] << endl;
		}

		cout << "\n *** IRS cap = " << results.Value << "\n";
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		cout << "\nMonte-Carlo Simulation elapsed: ";
		cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " mS" << endl << endl;
		cout << "\n *** END Interest rate swap with a cap *** \n";

	}
private:

	// Data members:

	double notional; // notional
	double K; // strike caplet
	double alpha; // daycount factor
	double sigma; // fwd rates volatility
	double dT;
	int N; // number forward rates
	int M; // number of simulations

	// A function to evaluate data_and_premium:

	IR_results run_LIBOR_simulationsPlain() const
	{
		matrix<double> L; // forward rates
		matrix_resize(L, N + 1, N + 1);
		matrix<double> D; // discount factors
		matrix_resize(D, N + 2, N + 2);

		vector<double> dW(N + 1); // discount factors
		vector<double> FV(N + 2); // future value payment
		vector<double> FVprime(N + 2); // numeraire-rebased FV payment
		vector<double> V(M); // simulation payoff

		 

		NormDstSampler normal;

		double df_prod = 1.0;
		double drift_sum = 0.0;

		double sumPV = 0.0;
		double PV = 0.0;

		// STEP 2: INITIALISE SPOT RATES

		L[0][0] = 0.05;
		L[1][0] = 0.05;
		L[2][0] = 0.05;
		L[3][0] = 0.05;

		// start main MC loop

		for (int nsim = 0; nsim < M; ++nsim)
		{

			// STEP 3: BROWNIAN MOTION INCREMENTS

			dW[1] = sqrt(dT)*normal();
			dW[2] = sqrt(dT)*normal();
			dW[3] = sqrt(dT)*normal();

			// STEP 4: COMPUTE FORWARD RATES TABLEAU

			for (int n = 0; n < N; ++n)
			{
				for (int i = n + 1; i < N + 1; ++i)
				{
					drift_sum = 0.0;
					for (int k = i + 1; k < N + 1; ++k)
					{
						drift_sum += (alpha*sigma*L[k][n]) / (1 + alpha*L[k][n]);
					}
					L[i][n + 1] = L[i][n] * exp((-drift_sum*sigma - 0.5*sigma*sigma)*dT + sigma*dW[n + 1]); // cout <<“L: i= “ << i <<“, n+1 = “ << n+1 “ << L[i][n+1] << “\n”;
				}
			}
			// STEP 5: COMPUTE DISCOUNT RATES TABLEAU

			for (int n = 0; n < N + 1; ++n)
			{
				for (int i = n + 1; i < N + 2; ++i)
				{
					df_prod = 1.0;
					for (int k = n; k < i; k++)
					{
						df_prod *= 1 / (1 + alpha*L[k][n]);
					}
					D[i][n] = df_prod;
					// cout <<“D: i = “ << i <<“, n = “ << n <<“, D[i][n] = “ << D[i][n] << “\n”;
				}
			}

			// STEP 6: COMPUTE EFFECTIVE FV PAYMENTS

			FV[1] = notional*alpha*(L[0][0] - K);
			FV[2] = notional*alpha*(L[1][1] - K);
			FV[3] = notional*alpha*(L[2][2] - K);
			FV[4] = notional*alpha*(L[3][3] - K);

			// STEP 7: COMPUTE NUMERAIRE-REBASED PAYMENT

			FVprime[1] = FV[1] * D[1][0] / D[4][0];
			FVprime[2] = FV[2] * D[2][1] / D[4][1];
			FVprime[3] = FV[3] * D[3][2] / D[4][2];
			FVprime[4] = FV[4] * D[4][3] / D[4][3];

			// STEP 8: COMPUTE IRS NPV

			V[nsim] = FVprime[1] * D[1][0] + FVprime[2] * D[2][0] + FVprime[3] * D[3][0] + FVprime[4] * D[4][0];
		}
		// end main MC loop

		// STEP 9: COMPUTE DISCOUNTED EXPECTED PAYOFF

		sumPV = 0.0;
		for (int nsim = 0; nsim < M; nsim++)
		{
			sumPV += V[nsim];
		}

		PV = sumPV / M;

		IR_results results(V, PV);

		return results;
	}

	IR_results run_LIBOR_simulationsCap() const
	{
		matrix<double> L; // forward rates
		matrix_resize(L, N + 1, N + 1);
		matrix<double> D; // discount factors
		matrix_resize(D, N + 2, N + 2);

		vector<double> dW(N + 1); // discount factors
		vector<double> V(N + 2); // caplet payoff
		vector<double> Vprime(N + 2); // numeraire-rebased caplet payoff
		vector<double> Vcap(M); // simulation payoff

	

		NormDstSampler normal;

		double df_prod = 1.0;
		double drift_sum = 0.0;

		double sumcap = 0.0;
		double payoff = 0.0;

		// STEP 2: INITIALISE SPOT RATES

		L[0][0] = 0.05;
		L[1][0] = 0.05;
		L[2][0] = 0.05;
		L[3][0] = 0.05;
		L[4][0] = 0.05;

		// start main MC loop

		for (int nsim = 0; nsim < M; ++nsim)
		{

			// STEP 3: BROWNIAN MOTION INCREMENTS

			dW[1] = sqrt(dT)*(normal());
			dW[2] = sqrt(dT)*(normal());
			dW[3] = sqrt(dT)*(normal());
			dW[4] = sqrt(dT)*(normal());

			// STEP 4: COMPUTE FORWARD RATES TABLEAU

			for (int n = 0; n < N; ++n)
			{
				for (int i = n + 1; i < N + 1; ++i)
				{
					drift_sum = 0.0;
					for (int k = i + 1; k < N + 1; ++k)
					{
						drift_sum += (alpha*sigma*L[k][n]) / (1 + alpha*L[k][n]);
					}
					L[i][n + 1] = L[i][n] * exp((-drift_sum*sigma - 0.5*sigma*sigma)*dT
						+ sigma*dW[n + 1]);
					// cout <<“L: i = “ << i <<“, n+1 = “ << n+1 <<“, = “ << L[i][n+1] << “\n”;
				}
			}

			// STEP 5: COMPUTE DISCOUNT RATES TABLEAU

			for (int n = 0; n < N + 1; ++n)
			{
				for (int i = n + 1; i < N + 2; ++i)
				{
					df_prod = 1.0;
					for (int k = n; k < i; k++)
					{
						df_prod *= 1 / (1 + alpha*L[k][n]);
					}
					D[i][n] = df_prod;
					// cout <<“D: i = “ << i <<“, n = “ << n <<“, D[i][n] = “ 
					//		<< D[i][n] << “\n”;
				}
			}

			// STEP 6: COMPUTE CAPLETS

			double diff;

			diff = L[0][0] - K;
			V[1] = max(diff, 0.0);

			diff = L[1][1] - K;
			V[2] = max(diff, 0.0);

			diff = L[2][2] - K;
			V[3] = max(diff, 0.0);

			diff = L[3][3] - K;
			V[4] = max(diff, 0.0);

			diff = L[4][4] - K;
			V[5] = max(diff, 0.0);

			// STEP 7: COMPUTE NUMERAIRE-REBASED CAPLETS

			Vprime[1] = V[1] * D[1][0] / D[5][0];
			Vprime[2] = V[2] * D[2][1] / D[5][1];
			Vprime[3] = V[3] * D[3][2] / D[5][2];
			Vprime[4] = V[4] * D[4][3] / D[5][3];
			Vprime[5] = V[5] * D[5][4] / D[5][4];

			// STEP 8: COMPUTE CAP PAYOFF

			Vcap[nsim] = Vprime[1] + Vprime[2] + Vprime[3] + Vprime[4] + Vprime[5];
		}
		// end main MC loop

		// STEP 9: COMPUTE DISCOUNTED EXPECTED PAYOFF

		sumcap = 0.0;

		for (int nsim = 0; nsim < M; ++nsim)
		{
			sumcap += Vcap[nsim];
		}

		payoff = D[N + 1][0] * sumcap / M;

		IR_results results(Vcap, payoff);

		return results;
	}
};





#endif
