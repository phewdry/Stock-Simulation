#include <cctype>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "common.h"
#include "InterestRatePricing.h"
#include <thread>
using namespace std;

int  cpptest(float a, float b, float c, float d, float e)
//int cpptest()
{
	std::cout << "C++11 MULTITHREADING\n";
	//std::cout << a << "," << b << endl;
	for (int i = 0; i < 10; i++)
		std::cout << i << " ";
	return 0;
};
//
//     //This function will be called from a thread
//
//    void call_from_thread() {
//	         std::cout << "Hello, World" << std::endl;
//	
//}
//
	//int main() {
	//	//Launch a thread
	//	for (int i = 0; i < 5; i++) {
	//		std::thread t1(cpptest,1,2,3,4,5);

	//		//Join the thread with the main thread
	//		t1.join();

	//	}

	//	system("pause");
	//	return 0;
	//}
int main(){
	
	bool flag = true;
	char input;
	IR test;
//	IR1run();
//	IR2run();


	do {
		cout << "\n\n-----------------------WELCOME TO CIS29 MONTE CARLO SIMULATOR-------------------\n\n";
		cout << "Please select an option # below: \n1. pricing of an IRS (Interest Rate Swap)\n2. Return on an IRS Cap (Variable IRS Profits)\n3. Options explained\n4. Exit Program\n";
		cin >> input;

		if (input =='1') {
			cout << "\n#1 has been selected, would you like to\nA.Run an Example Program\nB.Input new parameters\nC.Select file\nD.Run file(multi-threaded)";

			//cout << " before loop" << endl;
			//for (int i = 0; i < 5; i++) {
			//	cout << "start thread i=" << i << endl;
			//	std::thread t(cpptest, 1, 2, 3,4,5);
			//	//
			//	t.join();
			//}
			//	std::cout << " ***END OF A PROGRAM***\n";
			
			
			cin >> input;
			if (toupper(input) == 'A') {
				test.IR1run(1000000, 0.04, 0.25, 0.15, 0.25, 3, 1000, "normal");
			}
				else if (toupper(input) == 'B'){
					double a, b, c, d, e, f, g;
					cout << "\nEnter the following info : \n\tNotational Value-(Total $value of a position's assets)\n\t(ex. 5000000) : "; cin >> a;
					cout << "\nEnter the following info : \n\tFixed Rate of IRS\n\t(ex. 0.05) : "; cin >> b;
					cout << "\nEnter the following info : \n\tDaycount Factor-(How interest accrues over time)\n\t(ex. 0.3) : "; cin >> c;
					cout << "\nEnter the following info : \n\tForward Volatility-(Measurement of future uncertainty)\n\t(ex. 0.2) : "; cin >> d;
					cout << "\nEnter the following info : \n\tDrift Time\n\t(ex. 0.2) : "; cin >> e;
					cout << "\nEnter the following info : \n\t# of Forward Rates\n\t(ex. 3) : "; cin >> f;
					cout << "\nEnter the following info : \n\t# of MonteCarlo Sims\n\t(>1000 at least) : "; cin >> g;
					test.IR1run(a, b, c, d, e, f, g, "normal");
				}
				else if (toupper(input) == 'C') {
					string file;
					cout << "Enter name of file to read (ex. readFile.txt): ";
					cin >> file;
					test.fileRead(1,file);
				}
				else if (toupper(input) == 'D') {
					string file;
					cout << "MultiThread TEST, Enter name of file to read (ex. readFile.txt): ";
					cin >> file;
					test.fileReadMultiThread(1, file);
					cout << "\nMulti-thread computation completed\n";
				}

				else cout << "\nInvalid input!\n";
				
		}
		else if ((input) == '2') {
			cout << "\n#2 has been selected, would you like to\nA.Run an Example Program\nB.Enter new variable parameters\nC.Select File\nD.Run file(multi-threaded)";
			cin >> input;
			if (toupper(input) == 'A') test.IR2run(0.05, 0.5, 0.15, 0.5, 4, 1000);
				else if (toupper(input) == 'B') {
					 double a,b,c,d,e,f;
					 cout << "\nEnter the following info : \n\tCap Value-(Floating interest hedge rate)\n\t(ex. 0.08) : "; cin >> a;
					 cout << "\nEnter the following info : \n\tDaycount Factor-(How interest accrues over time)\n\t(ex. 0.6) : "; cin >> b;
					 cout << "\nEnter the following info : \n\tForward Volatility-(Measurement of future uncertainty)\n\t(ex. 0.2) : "; cin >> c;
					 cout << "\nEnter the following info : \n\tDrift Time\n\t(ex. 0.6) : "; cin >> d;
					 cout << "\nEnter the following info : \n\t# of Forward Rates\n\t(ex. 5) : "; cin >> e;
					 cout << "\nEnter the following info : \n\t# of MonteCarlo Sims\n\t(>1000 at least) : "; cin >> f;
					 test.IR2run(a, b, c, d, e, f);
				}
				else if (toupper(input) == 'C') {
					string file;
					cout << "Enter name of file to read (ex. readFile2.txt): "; 
					cin >> file;
					//test.fileRead(2,"readFile2.txt");
					test.IR2run(0.05, 0.5, 0.15, 0.5, 4, 1000); cout << "\nRun #1 finished\n\n"; 
					system("pause");
				//	cout << "Run # 1\n";
					test.IR2run(0.05, 0.5, 0.15, 0.5, 4, 1000);
					cout << "\nRun #2 finished\n";
				}
				else if (toupper(input) == 'D') {
					string file;
					cout << "MultiThread test, Enter name of file to read (ex. readFile2.txt): ";
					cin >> file;
					test.fileReadMultiThread(2, file);
					cout << "\nMulti-thread computation completed\n";
				}
				else cout << "\nInvalid input!\n";;
		}
		else if (input == '3') {
			cout << "An interest rate swap is an agreement between two parties (known as counterparties) "<< 
			 "where one stream of future interest payments is exchanged for another based on a specified principal amount. " <<
				"Interest rate swaps often exchange a fixed payment for a floating payment that is linked to an interest rate." <<
				"\n \nAn interest rate cap is a derivative in which the buyer receives payments at the end of each period in which" <<
				"the interest rate exceeds the agreed strike price." ;
		}
		else if ((input) == '4') { break; }
		else { cout << "\nInvalid input!\n"; }

	} while (flag);
		 
		system("pause");
	return 0;
}