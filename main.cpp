#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

string toBinary(int value, int length) {
      string output = "";
      for(int i = length - 1; i >= 0; i--) {
        if((value >> i) & 1)
          output += "1";
        else
          output += "0";
      }
      return output;
}

int main() {
  int x, y = -1;
  int x_sign, x_exp, x_frac;
  int y_sign, y_exp, y_frac;
  float x_val, y_val;

  while(x < 0 || x > 255 || y < 0 || y > 255) {
    cout << "Input two integers (0-255): " << endl;
    cin >> x >> y;
  }

  cout << endl << "first value: " << x << endl;
  cout << "second value: " << y << endl << endl;
  cout << "encoding of first value: " << setw(14) << toBinary(x, 8) << endl;
  cout << "encoding of second value: " << setw(13) << toBinary(y, 8) << endl << endl;

  x_sign = (x >> 7) & 1;
  x_exp = (x >> 4) & 0x7;
  x_frac = x & 0xf;

  y_sign = (y >> 7) & 1;
  y_exp = (y >> 4) & 0x7;
  y_frac = y & 0xf;

  cout << "internal rep of first value: " << setw(3) << 1 << "." << toBinary(x_frac, 4)
       << " x 2^(";
  if((x_exp - 4) > 0) cout << "+";
  cout << x_exp - 4 << ")" << endl;

  cout << "internal rep of second value: " << setw(2) << 1 << "." << toBinary(y_frac, 4)
       << " x 2^(";
  if((y_exp - 4) > 0) cout << "+";
  cout << y_exp - 4 << ")" << endl;

  cout << "hidden bit---------------------^ ffff" << endl;
  cout << "4-bit fraction-------------------^^^^" << endl << endl;

  x_val = (1 + x_frac / 16.0) * pow(2, x_exp - 4);
  cout << "first value is: " << setw(2) << (!x_sign ? "+" : "-") << setw(6)
       << setfill('0') << left << 1 + x_frac / 16.0 << " x 2^("
       << (((x_exp - 4) > 0) ? "+" : "") << x_exp - 4 << ") = " << x_val << endl;

  y_val = (1 + y_frac / 16.0) * pow(2, y_exp - 4);
  cout << "second value is: " << setw(1) << (!y_sign ? "+" : "-") << setw(6)
       << setfill('0') << left << 1 + y_frac / 16.0 << " x 2^("
       << (((y_exp - 4) > 0) ? "+" : "") << y_exp - 4 << ") = " << y_val << endl;

  return 0;
}
