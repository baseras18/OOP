#include <iostream>
#include "stdlib.h"
using namespace std;

class SafeArray {
  private:
    int N;
    int *arr;

    void put(int i, int val) {  // bu fonksiyona sadece SafeArray class ı tarafından erişilebilir
      arr[i] = val;
    }

  public:
    SafeArray() {
      N = 0;
      arr = NULL;
    }

    SafeArray(int SIZE, int FILL = 0) {   //// Fill=0 demek array tablosu 0 ile doldurulacak demek.
      if (SIZE != 0) {                    //// Fill != 0 demek array tablosu bilgisayar tarafından seçilen rastgele sayılarla doldurulacak demek.
        N = SIZE;
        arr = new int[SIZE];
        if (FILL == 0) {
          for (int i = 0; i < SIZE; i++) arr[i] = 0; 
        } else {
          unsigned int t = static_cast<unsigned int>(time(NULL));  // kod her execute edildiğinde array tablosuna verilen rastgele sayılar değişiyor
          srand(t);                                                // 
          for (int i = 0; i < SIZE; i++) arr[i] = rand()%FILL;  /* Fill != 0 ve bilgisayara verilen rastgele sayı seçme komudu tek seferlik
                                                                   eğer  unsigned int t = static_cast<unsigned int>(time(NULL)) ve srand(t) olmasa,
                                                                   program her execute edildiğinde aynı rastgele seçilmiş sayılar ekrana gelir  */
        }
      }   
    }

    int at(int i) {
      if (i < N && i >= 0) {
        return arr[i];
      } else {
        cout << "out of bound !!!" << endl;
        return 0;
      }
    }

    SafeArray operator + (SafeArray &other) {
      SafeArray tmp(N);
      for (int i = 0; i < N; i++) {
        //tmp.put(i, arr[i]+other.arr[i]);
        tmp.arr[i] = arr[i]+other.arr[i];
      }
      return tmp;
    }
    int operator [] (unsigned int i){  // ben yazdım internetten bakarak bu member function ı.
        return (*this).arr[i];
    }
};

int main(){
  // test default constructor
  SafeArray sa0;

  // test overloaded constructor
  SafeArray sa1(10, 100);   // Safearray sa(10); diye girseydim de FILL=0 olarak algılanırdı kod tarafından.
  SafeArray sa2(10, 5);

  // perform arithmetic operation
  SafeArray sa3 = sa1+sa2;
  cout<<"sa3.at(i=5) = "<<sa3.at(5)<<endl;
  cout<<"sa3[5]="<<sa3[5]<<endl;

  // print content
  for (int i = 0; i < 10; i++){
    cout << sa1.at(i) << "+" << sa2.at(i) << " = " << sa3.at(i) << endl;
    //cout << sa1[i] << "+" << sa2[i] << " = " << sa3[i] << endl;
  }
  
  cout<<"ya da"<<endl;
  for (int i = 0; i < 10; i++){
 //   cout << sa1.at(i) << "+" << sa2.at(i) << " = " << sa3.at(i) << endl;
    cout << sa1[i] << "+" << sa2[i] << " = " << sa3[i] << endl;
  }
 return 0;
}
