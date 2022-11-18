#include <iostream>
using namespace std;

class myMatrix {
private:
  int rows;
  int cols;
  int **pData;

  void allocateMemory();
  void deleteMemory();
  void errorMessage(string msg) const;
public:
  myMatrix(int nRows = 1, int nCols = 1, int initValue = 0);
  myMatrix(int nRows, int nCols, int *data);
  myMatrix(int nRows, int nCols, int **data);
  myMatrix(const myMatrix& mat);
  ~myMatrix();

  int getRows() const;
  int getCols() const;
  int* operator[](int i) const;
  int& operator()(int i, int j) const;

  myMatrix& operator =(const myMatrix& mat);
  myMatrix& operator +=(const myMatrix& mat);
  myMatrix& operator -=(const myMatrix& mat);
  myMatrix& operator *=(const myMatrix& mat);
  myMatrix& operator *=(int value);

friend bool operator==(const myMatrix& a, const myMatrix& b);

  myMatrix operator -() const;
  myMatrix& transpose();

friend myMatrix operator+(myMatrix lhs, const myMatrix& mat);
friend myMatrix operator-(myMatrix lhs, const myMatrix& mat);
friend myMatrix operator*(myMatrix lhs, const myMatrix& mat);
friend myMatrix operator*(myMatrix lhs, int value);
friend myMatrix operator*(int value, myMatrix rhs);

friend ostream& operator<<(ostream &outStream, const myMatrix& mat);
friend istream& operator>>(istream &inStream, myMatrix& mat);
};

myMatrix::myMatrix(int nRows, int nCols, int initValue) : rows(nRows), cols(nCols), pData(nullptr){
  allocateMemory();
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] = initValue;
}
myMatrix::myMatrix(int nRows, int nCols, int *data) : rows(nRows), cols(nCols), pData(nullptr){
  allocateMemory();
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] = data[i*cols+j];
}
myMatrix::myMatrix(int nRows, int nCols, int **data) : rows(nRows), cols(nCols), pData(nullptr){
  allocateMemory();
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] = data[i][j];
}
myMatrix::~myMatrix(){
  if (pData != nullptr)
    deleteMemory();
}
// Copy constructor
myMatrix::myMatrix(const myMatrix& mat):
rows(mat.rows), cols(mat.cols), pData(nullptr){
  allocateMemory();
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] = mat.pData[i][j];
}
// Accessor functions
int myMatrix::getRows() const { return rows; }
int myMatrix::getCols() const { return cols; }
int* myMatrix::operator[](int i) const {
  if((i < 0) || (i >= rows))
    errorMessage("Accessing out-of-bound value of a matrix");
  return pData[i];
}
int& myMatrix::operator()(int i, int j) const {
  if((i < 0) || (i >= rows) || (j < 0) || (j >= cols))
    errorMessage("Accessing out-of-bound value of a matrix");
  return pData[i][j];
}
// Overloaded operators
myMatrix& myMatrix::operator+=(const myMatrix& mat){
  if((rows != mat.rows) || (cols != mat.cols))
    errorMessage("cannot add two matrices of different size");

  // fill in
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] += mat.pData[i][j];

  return *this;
}
myMatrix& myMatrix::operator-=(const myMatrix& mat){
  if((rows != mat.rows) || (cols != mat.cols))
    errorMessage("cannot do subtraction between two matrices of different size");

  //fill in
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] -= mat.pData[i][j];

  return *this;
}
myMatrix& myMatrix::operator*=(const myMatrix& mat){
  if(cols != mat.rows)
    errorMessage("cannot do multiplication between the given two matrices");

  //filll in
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[j][i] *= mat.pData[i][j];
  return *this;
}

myMatrix& myMatrix::operator*=(int value){

  //fill in
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] *= value;

  return *this;
}

// Assignment operators
myMatrix& myMatrix::operator=(const myMatrix& mat){
  if(&mat == this)
    return *this;

  // fill in
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      pData[i][j] = mat.pData[i][j];

  return *this;
}
// Overloaded binary operators : fill in the body
myMatrix operator+(myMatrix lhs, const myMatrix& mat){
  if((lhs.getRows() != mat.getRows()) || (lhs.getCols() != mat.getCols()))
    lhs.errorMessage("cannot add two matrices of different size");

  myMatrix result(lhs.rows, lhs.cols);

  for(int i = 0; i < lhs.rows; i++)
    for(int j = 0; j < lhs.cols; j++)
      result.pData[i][j] = lhs.pData[i][j] + mat.pData[i][j];

  return result;
}
myMatrix operator-(myMatrix lhs, const myMatrix& mat){
  if((lhs.rows != mat.rows) || (lhs.cols != mat.cols))
    lhs.errorMessage("cannot add two matrices of different size");

  myMatrix result(lhs.rows, lhs.cols);

  for(int i = 0; i < lhs.rows; i++)
    for(int j = 0; j < lhs.cols; j++)
      result.pData[i][j] = lhs.pData[i][j] - mat.pData[i][j];

  return result;
}
myMatrix operator*(myMatrix lhs, const myMatrix& mat){
  if((lhs.rows != mat.rows) || (lhs.cols != mat.cols))
    lhs.errorMessage("cannot add two matrices of different size");

  myMatrix result(lhs.rows, lhs.cols);

  for(int i = 0; i < lhs.rows; i++)
    for(int j = 0; j < lhs.cols; j++)
      result.pData[i][j] = lhs.pData[i][j] * mat.pData[i][j];

  return result;
}
myMatrix operator*(myMatrix lhs, int value){
  for(int i = 0; i < lhs.rows; i++)
    for(int j = 0; j < lhs.cols; j++)
      lhs.pData[i][j] = lhs.pData[i][j] * value;

  return lhs;
}
myMatrix operator*(int value, myMatrix rhs){
  for(int i = 0; i < rhs.rows; i++)
    for(int j = 0; j < rhs.cols; j++)
      rhs.pData[i][j] = value * rhs.pData[i][j];

  return rhs;
}

// Overloaded relational operators
bool operator==(const myMatrix& a, const myMatrix& b){
  if((a.rows != b.rows) || (a.cols != b.cols))
    return false;
  // fill in
  for(int i = 0; i < a.rows; i++)
    for(int j = 0; j < a.cols; j++)
      if(a.pData[i][j] != b.pData[i][j])
        return false;
  return true;
}

bool operator !=(const myMatrix& a, const myMatrix& b){
  return !(a == b);
}

// Overloaded unary operators
myMatrix myMatrix::operator-() const {
  // fill in
  myMatrix result(rows, cols);
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      result.pData[i][j] = -pData[i][j];
  return result;
}

// transpose the matrix
myMatrix& myMatrix::transpose(){
  // fill in
  myMatrix result(cols, rows);
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++){
      int tmp = 0;
      result.pData[j][i] = pData[i][j];
    }
  return result;
}

// private functions
void myMatrix::allocateMemory(){
  if(pData != nullptr)
    deleteMemory();

  pData = new int *[rows];
  if(pData == nullptr)
    errorMessage("Memory allocation error");

  pData[0] = new int[rows*cols];
  if(pData[0] == nullptr){
    delete [] pData;
    errorMessage("Memory allocation error");
  }

  for(int i = 0; i < rows; i++)
    pData[i] = pData[0] + i * cols;
}

void myMatrix::deleteMemory(){
  delete [] pData[0];
  delete [] pData;

  pData = nullptr;
}

void myMatrix::errorMessage(string str) const{
  cout << "Error: " << str << endl;
  exit(1);
}

// friend functions
ostream& operator<<(ostream &outStream, const myMatrix& mat){
  outStream << mat.rows << "*" << mat.cols << endl;

  for(int i = 0; i < mat.rows; i++){
    for(int j = 0; j < mat.cols; j++)
      outStream << mat[i][j] << " ";
    outStream << endl;
  }
  return outStream;
}

istream& operator>>(istream &inStream, const myMatrix& mat){
  mat.deleteMemory();
  inStream >> mat.rows >> mat.cols;
  mat.allocateMemory();

  for(int i = 0; i < mat.rows; i++)
    for(int j = 0; j < mat.cols; j++)
      inStream >> mat[i][j];
  return inStream;
}

void testSimpleCase();
void testDataFromFile();
myMatrix readMatrix();

int main(void){
  testSimpleCase();
  testDataFromFile();
}

void testSimpleCase(){
  int testData1[6] = {1, 2, 3, 4, 5, 6};
  int testData2[6] = {6, 5, 4, 3, 2, 1};

  myMatrix m1(2, 2, 1);
  myMatrix m2(2, 3, testData1);
  myMatrix m3(3, 2, testData2);
  myMatrix m4(m3);
  myMatrix m5, m6(2, 3, 1), m7(3, 4, 1), m8(4, 2, 1), m9;

  cout << m1.getRows() << " " << m1.getCols() << endl;
  m4(0, 0) = 1;
  m4(0, 1) = 2;
  cout << m4[0][0] << " " << m4[0][1] << endl;
  cout << m4(1, 0) << " " << m4(1, 1) << endl;
  cout << m4[2][0] << " " << m4(2, 1) << endl;

  m3 = m3;
  cout << m3;

  m5 = m3 + m4;
  cout << m5;

  cout << (m4 == m3) << " " << (m4 != m3) << endl;
  m4 = m5 - m4;
  cout << (m4 == m3) << " " << (m4 != m3) << endl;

  m9 = m6 * m7 * m8 + m1;
  cout << m9;
  m8 = m7 = m6 = m5;
  cout << m8;

  m4 = m4 * 2;
  cout << m4;

  m4 = 2 * m4;
  cout << m4;

  m5 = m2 * m3;
  cout << m5;

  m2 *= m3;
  cout << m2;

  m2 += m1;
  cout << m2;

  m2 -= m1;
  cout << m2;

  m2 = -m1 + 2 * m2;
  cout << m2;

  m7 = m4;
  m8 = m7 * m4.transpose();
  cout << m8;
}

void testDataFromFile(){
  myMatrix m[4], m0;

  for(int j = 0; j < 4; j++)
    m[j] = readMatrix();

  m0 = m[0] * m[1] * m[2] + m[3];

  cout << m0;
  cout << m0[0][0] << " " << m0[m0.getRows()-1][m0.getCols()-1] << endl;
}

myMatrix readMatrix(){
  int *data;
  int row, col;

  cin >> row >> col;
  data = new int[row*col];
  for(int i = 0; i < row*col; i++)
    cin >> data[i];

  myMatrix m(row, col, data);
  delete[] data;
  return m;
}
