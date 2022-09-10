#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
class wow {
  public:
    T variable;
};

int main(int argc, char *argv[]) {
    wow<int> f;
    vector<int> myVector;
    myVector.push_back(33);
    myVector.push_back(44);
    string myString = "Hello";
    cout << myVector[0] << myString << endl;
    return 0;
}
