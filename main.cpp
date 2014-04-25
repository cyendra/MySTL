#include "stl_vector.h"
#include <iostream>
//#include <vector>
using namespace std;
int main()
{
    vector<int> v1(111);
    vector<double> v2;
    v1[0] = 111;
    v1[1] = 222;
    for (int i=11;i<=123;i++) v2.push_back(0.123*i);
    for (int i=0;i<v2.size();i++) cout<<v2[i]<<endl;
    return 0;
}
