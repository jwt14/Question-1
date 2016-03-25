#include <iostream>
#include <math.h>
#include <limits>
#include <vector>

using namespace std;

void validating(double &vIn){
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"You have entered wrong input"<<endl;
            cin>>vIn;
        }
    if(!cin.fail())
        break;
    }
}

void validating(int &vIn){
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"You have entered wrong input"<<endl;
            cin>>vIn;
        }
    if(!cin.fail())
        break;
    }
}

int main() {

    double L, T;
    int N_x,N_t;

    cout << "\nLength of a domain = "; cin >> L; validating(L);
    cout << "\nNumber of grid points: "; cin >> N_x; validating(N_x);
    double del_x = L/(double(N_x));
    cout << "\nSpatial step size (del_x) = " << del_x << endl;
    cout << "\nTime of simulation = "; cin >> T; validating(T);
    cout << "\nNumber of time steps: "; cin >> N_t; validating(N_t);
    double del_t = T/(double(N_t));
    cout << "\nTime step size (del_x) = " << del_t << endl;

    double alpha;
    cout << "\nThermal conductivity (alpha) = "; cin >> alpha; validating(alpha);
    double nu = alpha*(del_t/pow(del_x,2));
    cout << "\nCourant number = " << nu << endl << endl;

    vector<double> u_0;
    for(int j=0; j<N_x+1; j++){
         u_0.push_back(j*del_x-pow(j*del_x,2));
     }

    return 0;
}
