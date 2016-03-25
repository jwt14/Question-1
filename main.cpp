#include <iostream>
#include <math.h>

using namespace std;

int main() {

    double L, T;
    int N_x,N_t;

    cout << "\nLength of a domain = "; cin >> L;
    cout << "\nNumber of grid points: "; cin >> N_x;
    double del_x = L/(double(N_x));
    cout << "\nSpatial step size (del_x) = " << del_x << endl;
    cout << "\nTime of simulation = "; cin >> T;
    cout << "\nNumber of time steps: "; cin >> N_t;
    double del_t = T/(double(N_t));
    cout << "\nTime step size (del_x) = " << del_t << endl;

    double alpha;
    cout << "\nThermal conductivity (alpha) = "; cin >> alpha;
    double nu = alpha*(del_t/pow(del_x,2));
    cout << "\nCourant number = " << nu << endl << endl;
    return 0;
}
