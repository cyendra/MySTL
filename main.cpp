
#include "stl_algo.h"
#include <iostream>

//using namespace std;

/*****
The function to test vector
#include "stl_vector.h"
void test_vector() {
    int i;

    vector<int> iv(2,9);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    iv.push_back(1);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    iv.push_back(2);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    iv.push_back(3);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    iv.push_back(4);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;
    for (i=0;i<iv.size();++i) cout<<iv[i]<<" ";
    cout<<endl;

    iv.push_back(5);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;
    for (i=0;i<iv.size();++i) cout<<iv[i]<<" ";
    cout<<endl;

    iv.pop_back();
    iv.pop_back();
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    iv.pop_back();
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;

    vector<int>::iterator ivite = find(iv.begin(),iv.end(),1);
    if (ivite != iv.end()) iv.erase(ivite);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;
    for (i=0;i<iv.size();++i) cout<<iv[i]<<" ";
    cout<<endl;

    ivite = find(iv.begin(),iv.end(),2);
    if (ivite != iv.end()) iv.insert(ivite,3,7);
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;
    for (i=0;i<iv.size();++i) cout<<iv[i]<<" ";
    cout<<endl;

    iv.clear();
    cout<<"size="<<iv.size()<<endl;
    cout<<"capacity="<<iv.capacity()<<endl;
}
*****/

#include "stl_list.h"
void test_list() {
    list<int> ilist;
    std::cout<<"size="<<ilist.size()<<std::endl;

    ilist.push_back(0);
    ilist.push_back(1);
    ilist.push_back(2);
    ilist.push_back(3);
    ilist.push_back(4);
    std::cout<<"size="<<ilist.size()<<std::endl;

    list<int>::iterator ite;
    for (ite = ilist.begin(); ite != ilist.end(); ++ite) { std::cout<< *ite << " "; } std::cout<<std::endl;

    ite = find(ilist.begin(), ilist.end(), 3);
    if (ite != ilist.end()) ilist.insert(ite, 99);

    std::cout<<"size="<<ilist.size()<<std::endl;
    std::cout<< *ite <<std::endl;
    for (ite = ilist.begin(); ite != ilist.end(); ++ite) { std::cout<< *ite << " "; } std::cout<<std::endl;

    ite = find(ilist.begin(), ilist.end(), 1);
    if (ite != ilist.end()) std::cout << *(ilist.erase(ite)) <<std::endl;

    for (ite = ilist.begin(); ite != ilist.end(); ++ite) { std::cout<< *ite << " "; } std::cout<<std::endl;
}

int main()
{

    test_list();

    return 0;
}
