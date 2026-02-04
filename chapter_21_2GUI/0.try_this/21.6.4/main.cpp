

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <unordered_map>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Извлечение значений и перемножение
double weighted_value(const pair<string, double>& a, const pair<string, double>& b)
	{ return a.second * b.second; }

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			//Индекс Доу-Джонса NYSE 02.10.2022
			
			//Аббревиатура и цена
			unordered_map<string, double> dow_price = {
				{"MMM",		110.50},
				{"AXP",		134.91},
				{"AMGN",	225.40},
				{"AAPL",	138.20},
				{"BA",		121.08},
				{"CAT",		164.08},
				{"CVX",		143.67},
				{"CSCO",	40.00},
				{"KO",		56.02},
				{"DOW",		43.93},
				{"GS",		293.05},
				{"HD",		275.94},
				{"HON",		166.97},
				{"IBM",		118.81},
				{"INTC",	25.77},
				{"JNJ",		163.36},
				{"JPM",		104.50},
				{"MCD",		230.74},
				{"MRK",		86.12},
				{"MSFT",	232.90},
				{"NKE",		83.12},
				{"PG",		126.25},
				{"CRM",		143.84},
				{"TRV",		153.20},
				{"UNH",		505.04},
				{"VZ",		37.97},
				{"V",		177.65},
				{"WMT",		129.70},
				{"WBA",		31.40},
				{"DIS",		94.33}
			};
			
			//Аббревиатура и вес (beta)
			unordered_map<string, double> dow_weight = {
				{"MMM",		0.9935},
				{"AXP",		1.139},
				{"AMGN",	0.5623},
				{"AAPL",	1.2296},
				{"BA",		1.3532},
				{"CAT",		1.0256},
				{"CVX",		1.1466},
				{"CSCO",	0.9586},
				{"KO",		0.539},
				{"DOW",		1.3448},
				{"GS",		1.3565},
				{"HD",		0.9861},
				{"HON",		1.0602},
				{"IBM",		0.8409},
				{"INTC",	0.6474},
				{"JNJ",		0.6053},
				{"JPM",		1.0999},
				{"MCD",		0.5659},
				{"MRK",		0.3293},
				{"MSFT",	0.9421},
				{"NKE",		1.0284},
				{"PG",		0.3547},
				{"CRM",		1.1231},
				{"TRV",		0.6062},
				{"UNH",		0.7641},
				{"VZ",		0.356},
				{"V",		0.902},
				{"WMT",		0.5216},
				{"WBA",		0.6205},
				{"DIS",		1.2006}
			};
			
			//Аббревиатура и название
			unordered_map<string, string> dow_name = {
				{"MMM",		"3M Co."},
				{"AXP",		"American Express Co."},
				{"AMGN",	"Amgen"},
				{"AAPL",	"Apple Inc."},
				{"BA",		"Boeing Co."},
				{"CAT",		"Caterpillar, Inc."},
				{"CVX",		"Chevron Corp."},
				{"CSCO",	"Cisco Systems"},
				{"KO",		"Coca-Cola Co."},
				{"DOW",		"Dow Inc."},
				{"GS",		"The Goldman Sachs Group, Inc."},
				{"HD",		"Home Depot, Inc."},
				{"HON",		"Honeywell"},
				{"IBM",		"International Business Machines Corp."},
				{"INTC",	"Intel Corp."},
				{"JNJ",		"Johnson & Johnson Inc."},
				{"JPM",		"JPMorgan Chase and Co."},
				{"MCD",		"McDonald’s Corp."},
				{"MRK",		"Merck & Co., Inc."},
				{"MSFT",	"Microsoft Corp."},
				{"NKE",		"Nike Inc."},
				{"PG",		"Procter & Gamble Co."},
				{"CRM",		"Salesforce"},
				{"TRV",		"Travelers"},
				{"UNH",		"UnitedHealth Group Inc"},
				{"VZ",		"Verizon Communications"},
				{"V",		"Visa, Inc."},
				{"WMT",		"Walmart, Inc."},
				{"WBA",		"Walgreens Boots Alliance, Inc."},
				{"DIS",		"Walt Disney Co., The"}
			};
			
			//--------------------------------------------------------------------------
			
			//Вывод цен акций каждой компании в индексе Доу Джонса
			for(const auto& p : dow_price) {
				const string& symbol = p.first; //Аббревиатура
				cout << symbol << '\t' << p.second << '\t' << dow_name[symbol] << endl;
			}
			
			//--------------------------------------------------------------------------
			
			double dji_index = inner_product(dow_price.begin(), dow_price.end(), dow_weight.begin(),
											 0.0, plus<double>(), weighted_value);
			
			cout << "\n\ndji_index: " << dji_index << endl;
			
			keep_window_open("~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}