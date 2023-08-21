#include <iostream>
#include "library.h"
#include <fstream>
#include <iomanip>
using namespace std;


void heading(){
  cout << left << setw(37) << "COMPANY" << setw(10) << "STOCK" << setw(50) <<"MONTHLY PRICE" << right << setw(9) << "HIGHEST" << right << setw(8) << "LOWEST" << endl;
}

void collect_one(ifstream& input, Stock& s){
  int highest = 0, lowest = 9999;
  getline(input, s.company, ',');
  getline(input, s.symbol);
  for(int i = 0; i < 6; i++){
    input >> s.price[i];
    if(highest < s.price[i]){
      highest = s.price[i];
      s.highest = s.price[i];
    }if(lowest > s.price[i]){
      lowest = s.price[i];
      s.lowest = s.price[i];
    }    
  }
  input.ignore();
}

void display_one(Stock s){
  cout << left << setw(37) << s.company << setw(10) << s.symbol << setw(46);
  for(int i = 0; i < 6; i++){
    cout << setw(8) << s.price[i];
  }
  cout << right << setw(11) << s.highest << setw(8) << s.lowest << endl;
}

void collect_all(ifstream& input, Stock arr[], int& size){
  while(!input.eof()){
    collect_one(input, arr[size]);
    size++;
  }
}

void display_all(const Stock arr[], int size){
  for(int i = 0; i < size; i++){
    display_one(arr[i]);
  }
}

int menu(){
  int choice = -1;
  do{
  cout << "Choose from the following options:" << endl;
  cout << "1. Display all stock data" << endl;
  cout << "2. Display data for one stock symbol" << endl;
  cout << "3. Average price for a given stock" << endl;
  cout << "4. Highest price on a given month" << endl;
  cout << "5. Show stocks of target difference gap" << endl;
  cout << "6. Sort by company name" << endl;
  cout << "7. Sort by highest price" << endl;
  cout << "8. Remove a stock" << endl;
  cout << "9. Exit the program" << endl;
  cin >> choice;
  cin.ignore();
  } while(choice < 1 || choice > 9);
  return choice;
}

int search(Stock arr[], string symbol,int size){
  for(int i = 0; i < size; i++){
    if(arr[i].symbol == symbol){
      return i;
    }
  }
  return -1;
}
void Sort_Price(Stock arr[], int size){
  Stock temp;
  bool flag = true;
  do{
    flag = false; 
    for(int i = 0; i < size - 1; i++){
	    if(arr[i].highest < arr[i+1].highest){
	      temp = arr[i];
	      arr[i] = arr[i+1];
	      arr[i+1] = temp;
	      flag = true;
	    } 
    } 
  }while(flag == true); 
}

void Sort_Name(Stock arr[], int size){
  Stock temp;
  bool flag = true;
  do{
    flag = false;
    for(int i = 0; i < size - 1; i++){
      if(arr[i].company > arr[i+1].company){
        temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
        flag = true;
      }
    }
    
  }while(flag == true);
}

void average_for(double& average, Stock arr[], int pos, double& total){
  for(int i = 0; i < 6; i++){
    total+= arr[pos].price[i];
  }
  average = total / 6;
}

void filter_difference(const Stock arr[], int size, double difference){
  for(int i = 0; i < size; i++){
    if(arr[i].highest - arr[i].lowest >= difference){
      display_one(arr[i]);
    }
  }
}

void highest(double& highest_price, Stock arr[], int size, int& pos_new, int new_month){
  for(int i = 0; i < size; i++){
        if(highest_price < arr[i].price[new_month]){
          highest_price = arr[i].price[new_month];
          pos_new = i; 
        }
      }
}

int search_by_name(const Stock arr[], int size, string key){
  int pos = -1;
  for(int i = 0; i < size && pos == -1; i++) {
    if(arr[i].symbol == key){
      pos = i;
    }
  }
  return pos;
}

void remove_stock(Stock arr[], int& size, string key){
  int loc = search_by_name(arr, size, key);
  if(loc != -1){
    for(int i = loc; i < size - 1; i++){
      arr[i] = arr[i+1];
    }
    size--;
  }else{
    cout << key << "not found\n";
  }
}