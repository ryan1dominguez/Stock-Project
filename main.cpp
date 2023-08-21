#include <iostream>
#include "library.h"
#include <fstream>
#include <iomanip>
using namespace std;
 

int main() {
 const int cap = 100;
  Stock all_stock[cap];
  string filename;
  ifstream file;
  Stock s;
  int size = 0, choice, pos_new, new_month = 0, pos = 0, num_month, remove_pos;
  string stock_symbol, company_name, month_name;
  double tally = 0.00, average, highest_price = 0, price_difference = 0;
  
  do{
    cout << "Enter the filename you want to use: ";
    cin >> filename;
    cin.ignore();
    file.open(filename);
    string credit;
    getline(file, credit);
    cout << credit << endl;
  } while(!file.is_open());
  do{
    collect_all(file, all_stock, size);
    cout << "\n";
    choice = menu();
    switch(choice){
    case 1:
      heading();
      display_all(all_stock, size);
      break;
    case 2:
      cout << "Enter the symbol of a stock: ";
      getline(cin, stock_symbol);
      pos = search(all_stock, stock_symbol,size);
      if(pos == -1){
        cout << "Sorry we don't have data for " << stock_symbol << endl;
      }else{
        heading();
        cout << left << setw(37) << all_stock[pos].company << setw(10) << all_stock[pos].symbol << setw(46);
        for(int i = 0; i < 6; i++){
          cout << setw(8) << all_stock[pos].price[i];
        }  
        cout << right << setw(11) << all_stock[pos].highest << setw(8) << all_stock[pos].lowest << endl;
      }
      break;
    case 3:
      cout << "Enter the stock symbol that you want to display the average price for: ";
      getline(cin, stock_symbol);
      pos = search(all_stock, stock_symbol,size);
      if(pos == -1){
        cout << "Sorry we don't have data for " << stock_symbol << endl;
      }else{
      average_for(average, all_stock, pos, tally);
        cout << "Average price for " << stock_symbol << " is " << fixed << setprecision(2) << average << endl; 
      }
      break;
    case 4:
      cout << "Enter the number of month (11 for November, 12 for December, .. 4 for April): ";
      cin >> num_month;
      highest_price = 0;
      if(num_month < 11 && num_month > 4 || num_month > 12 || num_month < 1){
        cout << "Sorry, we don't have data for that month." << endl;
      }else{
      if(num_month == 11){
        new_month = 0;
        month_name = "November";
      }if(num_month == 12){
        new_month = 1;
        month_name = "December";
      }if(num_month == 1){
        new_month = 2;
        month_name = "January";
      }if(num_month == 2){
        new_month = 3;
        month_name = "February";
      }if(num_month == 3){
        new_month = 4;
        month_name = "March";
      }if(num_month == 4){
        new_month =5;
        month_name = "April";
      }
      highest(highest_price, all_stock, size, pos_new, new_month);
      cout << all_stock[pos_new].company << " has the highest price in " << month_name << ", which is " << highest_price << endl;
      }
      break;
    case 5:
      cout << "Enter target price difference: ";
      cin >> price_difference;
      cout << "Prices for stocks with over a " << price_difference << " dollar price gap" << endl;
      heading();
      filter_difference(all_stock, size, price_difference);
    break;
    case 6:
      cout << "Stocks sorted by company name:" << endl;
      Sort_Name(all_stock, size);
      heading();
      display_all(all_stock, size);
    break; 
    case 7:
      cout << "Stocks sorted by the highest price of the last 6 months" << endl;
      Sort_Price(all_stock, size);
      heading();
      display_all(all_stock,size);
    break;
    case 8:
      cout << "Enter the stock symbol that you want to remove: ";
      getline(cin, company_name);
      remove_stock(all_stock, size, company_name);
      heading();
      display_all(all_stock, size);
      break;
    } 
  }while(choice != 9);
  cout << "Thank You for using the program";
}