#include <iostream>
#include <math.h>
#include <limits>
#include <vector>
#include <fstream>
#include "TriMatrix.h"
#include <iterator>
using namespace std;

TriMatrix MakeIdentityMatrix(int N_x)
{
     TriMatrix Identity(N_x+2);
     for (int i=2; i <=N_x;i++){
                    Identity(i,i) = 1;
                    Identity(i,i-1) = 0;
                    Identity(i,i+1) = 0;
    }
    Identity(1,1) = 1;
    Identity(N_x+1,N_x+1) = 1;
    Identity(1,2) = 0;
    Identity(N_x+1,N_x) = 0;
    return Identity;
}

TriMatrix MakeSpatialOpMatrix(int N_x, double nu)
{
     TriMatrix Spatial(N_x+2);
     for (int i=2; i <=N_x;i++){
                    Spatial(i,i) = -2*nu;
                    Spatial(i,i-1) = nu;
                    Spatial(i,i+1) = nu;
    }
    Spatial(1,1) = 0;
    Spatial(N_x+1,N_x+1) = 0;
    Spatial(1,2) = 0;
    Spatial(N_x+1,N_x) = 0;

    return Spatial;
}

void print_vector(vector<double> U, char vector_filename[128]){
	    ofstream output_file(vector_filename);
        ostream_iterator<double> output_iterator(output_file, "\n");
        copy(U.begin(), U.end(), output_iterator);
}

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

    if (nu >= 0.5){
        cout << "\nCourant number is " << nu << " and scheme is unstable!" << endl << endl;
    }
    else{
        cout << "\nCourant number is " << nu << " and scheme is stable!" << endl << endl;
    }

    vector<double> u_0, u;
    for(int j=0; j<N_x+1; j++){
         u_0.push_back(j*del_x-pow(j*del_x,2));
     }

    TriMatrix I(N_x+2);
    TriMatrix l(N_x+2);
    TriMatrix A(N_x+2);

    l = MakeSpatialOpMatrix(N_x, nu);
    I = MakeIdentityMatrix(N_x);
    A = I+l;

    for(double k=0;k<N_t;++k){
        u = A * u_0;
        u_0 = u;
    }
    print_vector(u,"FEsolution.dat");

    return 0;
}
