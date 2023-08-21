#include <iostream>
using namespace std;
struct Stock {
  string company;
  string symbol;
  double highest, lowest;
  double price[6];
};

void heading();
void collect_one(ifstream& input, Stock& s);
void display_one(Stock s);
void collect_all(ifstream& input, Stock arr[], int& size);
void display_all(const Stock arr[], int size);
int search(Stock arr[], string key, int size);
void Sort_Price(Stock arr[], int size);
void Sort_Name(Stock arr[], int size);
void average_for(double& average, Stock arr[], int pos, double& total);
void highest(double& highest_price, Stock arr[], int size, int& pos_new, int new_month);
void filter_difference(const Stock arr[], int size, double differnce);
int search_by_name(const Stock arr[], int size, string key);
void remove_stock(Stock arr[], int& size, string key);
int menu();
