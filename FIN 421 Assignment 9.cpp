#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


//Global Variables

char stock[100] = {0};

//Equation Term Vars
float ebit, depreciation, capEX, nwc, debt,
sharesOutstanding, taxRate, hGrowth, regGrowth,
costDebt, beta, sharePrice, rfRate, mrp;

//core variables

float fcff;
double sumPresentValue = 0.00, equity, capm, valWACC, leverage;
int hGrowthPeriods;

//Function declarations

void dcfFCFF();
void prompts();
void debug();
//main function

int main () {
system("Color 06");

prompts();

dcfFCFF();

debug();

return 0;

}

//Function Expositions

void dcfFCFF() { //WACC function

equity = (sharesOutstanding * sharePrice);
capm = rfRate + beta * mrp;
leverage = debt / (debt + equity);

valWACC = leverage * costDebt * (1 - taxRate) +
(equity / (debt + equity)) * capm;

//Calculation of first FCFF prior to growth
fcff = ebit * (1 - taxRate) + depreciation - capEX - nwc;

//Growth

for (int i = 1; i <= hGrowthPeriods; i++) {
        double cashFlow = fcff * pow(1 + hGrowth, i);
        double presentValue = cashFlow / pow (1 + valWACC, i);
        sumPresentValue += presentValue;
        cout << "Year " << i << ": FCFF = " << cashFlow << ", PV = " << presentValue << endl;
}

//Calc Terminal Value at end of high growth period
double finalYearCF = fcff * pow(1 + hGrowth, hGrowthPeriods);
double fcffPerpetuity = finalYearCF * (1 + regGrowth);
double terminalValue = fcffPerpetuity / (valWACC - regGrowth);
double presentValTerminal = terminalValue / pow(1 + valWACC, hGrowthPeriods);
double intrinsicVal = presentValTerminal + sumPresentValue;

//Adding PV of terminal val to sum of discounted FCFF's
sumPresentValue += presentValTerminal;
double intrinsicValShare = ((sumPresentValue - debt) / sharesOutstanding);

cout << "\n\nTerminal Value at the end of Year " << hGrowthPeriods << ": " << terminalValue << endl;
cout << "Present Value of Terminal Value: " << presentValTerminal << endl;
cout << "Total Intrinsic Value of the Stock: " << sumPresentValue << endl;
cout << "Intrinsic Value per share: " << intrinsicValShare << endl;

//Debug
cout << "<DEBUG> | Cash flow in year " << hGrowthPeriods << ": " << finalYearCF << endl;

cout << "<DEBUG> | Equity is: " << equity <<endl;

cout << "<DEBUG> | CAPM is : " << capm << endl;

cout << "<DEBUG> | WACC is :" <<valWACC << endl;

cout << "<DEBUG> | Free Cash Flows to the Firm at time t :" << fcff << endl
<< "<DEBUG> | Leverage is: " <<leverage<< endl;

}//End of function

void debug() {


}

void prompts() {

cout << "Enter company EBIT: ";
cin >> ebit;

cout << "Enter depreciattion: ";
cin >> depreciation;

cout << "Enter in capital expenditures: ";
cin >> capEX;

cout << "Enter in the change in net working capital ";
cin >> nwc;

cout << "Enter in total debt: ";
cin >> debt;

cout << "Enter in total shares outstanding (in billions): ";
cin >> sharesOutstanding;

cout << "Enter in the tax rate: ";
cin >> taxRate;

cout << "How long is the high growth rate period?: ";
cin >> hGrowthPeriods;

cout << "Enter in the growth rate for this period: ";
cin >> hGrowth;

cout << "After this period, what will be the growth rate?: ";
cin >> regGrowth;

cout << "Enter in the cost of debt: ";
cin >> costDebt;

cout << "Enter in the company's beta: ";
cin >> beta;

cout << "Enter in the current share price: ";
cin >> sharePrice;

cout << "Enter in the current risk free rate: ";
cin >> rfRate;

cout << "Enter market risk-premium: ";
cin >> mrp;
cout << "\n\n";

}
