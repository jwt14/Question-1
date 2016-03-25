#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "TriMatrix.h"


TriMatrix::TriMatrix(const unsigned int pSize)
        : mSize(pSize),
          mZero(0.0) {
    if (pSize == 0) {
        cout << "Matrix size must be > 0" << endl;
        throw;
    }
    mDiag  = new double[mSize];
    mLower = new double[mSize - 1];
    mUpper = new double[mSize - 1];
}

TriMatrix::TriMatrix(const TriMatrix& pSrc)
        : mSize(pSrc.mSize),
          mZero(0.0) {
    mDiag  = new double[mSize];
    mLower = new double[mSize - 1];
    mUpper = new double[mSize - 1];
    memcpy(mDiag,  pSrc.mDiag,  sizeof(double) * mSize);
    memcpy(mLower, pSrc.mLower, sizeof(double) * (mSize - 1));
    memcpy(mUpper, pSrc.mUpper, sizeof(double) * (mSize - 1));
}

TriMatrix::~TriMatrix() {
    delete[] mDiag;
    delete[] mLower;
    delete[] mUpper;
}


TriMatrix& TriMatrix::operator=(const TriMatrix& pSrc) {
    if (mSize != pSrc.mSize) {
        mSize = pSrc.mSize;
        delete[] mDiag;
        delete[] mLower;
        delete[] mUpper;
        mDiag  = new double[mSize];
        mLower = new double[mSize - 1];
        mUpper = new double[mSize - 1];
    }

    memcpy(mDiag,  pSrc.mDiag,  sizeof(double) * mSize);
    memcpy(mLower, pSrc.mLower, sizeof(double) * (mSize - 1));
    memcpy(mUpper, pSrc.mUpper, sizeof(double) * (mSize - 1));
    return *this;
}

double& TriMatrix::operator() (unsigned int pRow, unsigned int pCol) {
    if (pRow >= mSize || pCol >= mSize) {
        cout << "Index out of range." << endl;
        throw;
    }
    else if (pRow == pCol) {
        return mDiag[pRow-1];
    }
    else if (pCol == pRow-1) {
        return mLower[pCol-1];
    }
    else if (pCol == pRow+1) {
        return mUpper[pCol-1];
    }
    else {
        mZero = 0;
        return mZero;
    }
}

TriMatrix TriMatrix::operator+(const TriMatrix& pSrc) {
    if (mSize != pSrc.mSize) {
        cout << "Matrices are of different sizes." << endl;
        throw;
    }
    TriMatrix result(*this);
    result += pSrc;
    return result;
}

TriMatrix TriMatrix::operator-(const TriMatrix& pSrc) {
    if (mSize != pSrc.mSize) {
        cout << "Matrices are of different sizes." << endl;
        throw;
    }
    TriMatrix result(*this);
    result -= pSrc;
    return result;
}

TriMatrix TriMatrix::operator*(const double& pVal) {
    TriMatrix result(*this);
    result *= pVal;
    return result;
}

TriMatrix TriMatrix::operator/(const double& pVal) {
    TriMatrix result(*this);
    result *= 1.0/pVal;
    return result;
}

TriMatrix& TriMatrix::operator+=(const TriMatrix& pSrc) {
    if (mSize != pSrc.mSize) {
        cout << "Matrices are of different sizes." << endl;
        throw;
    }
    for (unsigned int i = 0; i < mSize; ++i) {
        mDiag[i] += pSrc.mDiag[i];
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mLower[i] += pSrc.mLower[i];
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mUpper[i] += pSrc.mUpper[i];
    }
    return *this;
}

TriMatrix& TriMatrix::operator-=(const TriMatrix& pSrc) {
    if (mSize != pSrc.mSize) {
        cout << "Matrices are of different sizes." << endl;
        throw;
    }
    for (unsigned int i = 0; i < mSize; ++i) {
        mDiag[i] -= pSrc.mDiag[i];
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mLower[i] -= pSrc.mLower[i];
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mUpper[i] -= pSrc.mUpper[i];
    }
    return *this;
}

TriMatrix& TriMatrix::operator*=(const double& pVal) {
    for (unsigned int i = 0; i < mSize; ++i) {
        mDiag[i] *= pVal;
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mLower[i] *= pVal;
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mUpper[i] *= pVal;
    }
    return *this;
}

TriMatrix& TriMatrix::operator/=(const double& pVal) {
    double vTmp = 1.0/pVal;
    for (unsigned int i = 0; i < mSize; ++i) {
        mDiag[i] *= vTmp;
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mLower[i] *= vTmp;
    }
    for (unsigned int i = 0; i < mSize-1; ++i) {
        mUpper[i] *= vTmp;
    }
    return *this;
}

void TriMatrix::print() {
    for (unsigned int i = 1; i < mSize; ++i) {
        for (unsigned int j = 1; j < mSize; ++j) {
            cout << setprecision(3) << setw(5) << this->operator()(i,j);
        }
        cout << endl;
    }
    cout << endl;
}
