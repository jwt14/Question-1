#ifndef CLASS_TRIMATRIX
#define CLASS_TRIMATRIX

using namespace std;
class TriMatrix {
    public:
        // Custom constructor
        // No default constructor as size zero matrices make no sense
        TriMatrix(const unsigned int n);

        // Copy constructor is critical for the arithmetic operators below
        TriMatrix(const TriMatrix& pSrc);

        // Essential to deallocate the allocated memory
        ~TriMatrix();

        TriMatrix& operator=  (const TriMatrix& pSrc);
        double&    operator() (unsigned int pRow, unsigned int pCol);
        TriMatrix  operator+  (const TriMatrix& pSrc);
        TriMatrix  operator-  (const TriMatrix& pSrc);
        TriMatrix  operator*  (const double&    pVal);


        TriMatrix  operator/  (const double&    pVal);

        TriMatrix& operator+= (const TriMatrix&    pSrc);
        TriMatrix& operator-= (const TriMatrix&    pSrc);
        TriMatrix& operator*= (const double&    pVal);
        TriMatrix& operator/= (const double&    pVal);

        void print();

    private:
        unsigned int mSize;
        double* mDiag;
        double* mLower;
        double* mUpper;

        double  mZero;
};

#endif
