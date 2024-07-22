#include <iostream>
#include <vector>

using namespace std;

int main()
{
    using MyVector = vector<int>;

    MyVector vectorA( 1 );  
    cout << vectorA.size() << " " << vectorA[0] << std::endl;

    MyVector vectorB( 1, 10 );  
    cout << vectorB.size() << " " << vectorB[0] << std::endl;

    MyVector vectorC{ 1, 10 };  
    cout << vectorC.size() << " " << vectorC[0] << std::endl;

    initializer_list<int> initList{ 1, 10 };
    MyVector vectorD(initList);
    cout << vectorD.size() << " " << vectorD[0] << std::endl;

    return 0;
}