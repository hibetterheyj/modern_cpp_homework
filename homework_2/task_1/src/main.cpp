#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;
int main() {
  // init a random seed
  std::random_device rd;
  std::mt19937 gen(rd());
  // generate random integer between 0 and 99
  std::uniform_int_distribution<> dis(0, 99);
  int random_number = dis(gen);
  bool guessed = false;
  while (guessed == false) {
    int input_arg;
    cout << "Input a random number (0~99): ";
    cin >> input_arg;
    if (!cin.fail()) {
      if (input_arg >= 0 && input_arg <= 99) {
        if (input_arg > random_number) {
          cout << "> Random" << endl;
        } else if (input_arg < random_number) {
          cout << "< Random" << endl;
        } else {
          guessed = true;
        }
      } else {
        cerr << "[WARNING] : Number must be between 0 and 99" << endl;
      }
    } else {
      // return 1;
      printf("Error encountered, exiting...\n");
      exit(EXIT_FAILURE);
    }
  }
  cout << "Random number is " << random_number << ". You are right!" << endl;
  // return 0;
  exit(EXIT_SUCCESS);
}