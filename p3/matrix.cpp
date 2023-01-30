/*** PPC - HW03 ***/
/* Tento soubor se odevzdava. Zde implementujte vsechny potrebne funkce */

#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

Matrix temp(0,0);
Matrix temp2(0,0);
/*** CONSTRUCTORS & DESTRUCTOR ***/
Matrix::Matrix(int nrow, int ncol)
{
nrows = nrow;
ncols = ncol;
matSize = nrows*ncols;
if(nrows < 0 || ncols < 0) {
  throw matrix_negative_size();
  nrows = 0;
  ncols = 0;
}
data.resize(matSize);
fill(data.begin(), data.end(), 0);
}

Matrix::Matrix(int rowscols)
{
  nrows = rowscols;
  ncols = rowscols;
  matSize = nrows*ncols;
  if(nrows < 0 || ncols < 0) throw matrix_negative_size();
  data.resize(matSize);
  fill(data.begin(), data.end(), 0);
}

Matrix::Matrix(const Matrix &m)
{
  nrows = m.nrows;
  ncols = m.ncols;
  matSize = m.matSize;
  data = m.data;

}

Matrix::Matrix(const std::vector<value> &v)
{

}

Matrix::~Matrix()
{

}

/*** L1 Matrix:: FUNCTIONS ***/
void Matrix::zeros()
{
fill(data.begin(), data.end(), 0);
}

void Matrix::uniform(value element)
{
fill(data.begin(), data.end(), element);
}

void Matrix::eye()
{
  int colsIdx = 1;
  int colsCount = 1;
  int rowsIdx = 1;
  for(auto i = 0; i<matSize; i++){
      if(colsIdx == rowsIdx) data.at(i) = 1;
      else data.at(i) = 0;
      if(i+1 == colsCount*ncols){
        colsCount++;
        rowsIdx++;
        colsIdx = 0;
    }
    colsIdx++;
    }
}


void Matrix::bias(value b)
{
for(auto i = 0; i<matSize; i++) data.at(i) = data.at(i)+b;
}

/*** L2 Matrix:: FUNCTIONS ***/
void Matrix::scale(value s)
{
for(auto i = 0; i<matSize; i++) data.at(i) = data.at(i)*s;
}

void Matrix::transpose()
{
std::vector<value> tmp;
tmp.resize(matSize);
int a = 0;
for (auto i = 0; i < ncols; i++) {
  for (auto l = 0; l < nrows; l++) {
    /* code */
  tmp[a] = data[(l*ncols)+i];
  //std::cout << "tmp(" << a << ") = " << (l*nrows)+i << '\n';
  a++;
}
//  if((i*nrows)==(a*nrows)) a++;
}
int k;
k = nrows;
nrows = ncols;
ncols = k;
data = move(tmp);
}

/*** L3 Matrix:: FUNCTIONS ***/
void Matrix::changedim(int rows, int cols)
{

}

/*** L1 Matrix:: Operators ***/
value Matrix::operator () (int row, int col) const
{
  //std::cout << "row:" << row << "col:" << col << '\n';
  if (row > nrows-1 || (row < 0)) {throw std::out_of_range("Row index is out of range");}
if (col > ncols-1 || (col < 0)) {throw std::out_of_range("Column index is out of range");}
  return data.at((row)*ncols + (col));
}

value & Matrix::operator () (int row, int col)
{
//std::cout << "row:" << row << "col:" << col << '\n';
if (row > nrows-1 || (row < 0)) {throw std::out_of_range("Row index is out of range");}
if (col > ncols-1 || (col < 0)) {throw std::out_of_range("Column index is out of range");}
  return data[(row)*ncols + (col)];
}

bool Matrix::operator==(const Matrix &m)
{
if(ncols == m.ncols && nrows == m.nrows && data == m.data) return true;
else return false;

}

Matrix & Matrix::operator=(const Matrix &m)
{
ncols = m.ncols;
nrows = m.nrows;
matSize = m.matSize;
data.resize(matSize);
data = m.data;

return *this;
}

/*** L3 Matrix:: Operators ***/
std::vector<value> Matrix::operator () (void) const
{

return data;
}


/*** L1 NON-MEMBER FUNCTIONS/OPERATORS ***/
std::ostream & operator<<(std::ostream &os, const Matrix &m)
{
if (m.data.empty()) os << endl;
else{
int colsCount = 1;
for(auto i = 0; i<m.matSize; i++){
    os << setw(5) << right << m.data.at(i) << " ";
    if(i+1 == colsCount*m.ncols){
      os << endl;
      colsCount++;
  }
}
}
return os;
}

void loadMatrixFile(Matrix & m, string fname)
{
ifstream infile(fname);
if(!infile){throw cannot_open_file();}
string line;
std::getline(infile , line);
std::istringstream iss(line);
if(!(iss >> m.nrows >> m.ncols)){throw matrix_in_bad_header();}
else{
  int idx = 0;
  m.matSize = m.nrows*m.ncols;
  m.data.resize(m.matSize);
  for(auto i = 0; i <m.nrows; i++){
  getline(infile, line);
  std::istringstream iss2(line);
  for (auto l = 0; l < m.ncols; l++) {
    if(!(iss2 >> m(i , l))){throw matrix_in_bad_body();}
    idx++;
  }

  }
}

}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{

if((lhs.nrows == rhs.nrows) && (lhs.ncols == rhs.ncols)){
Matrix x(0,0);
temp = x;
temp.nrows = lhs.nrows;
temp.ncols = lhs.ncols;
temp.matSize = lhs.matSize;
temp.data.resize(temp.matSize);
for(auto i = 0; i<lhs.matSize; i++){
  //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  temp.data[i] = lhs.data[i] + rhs.data[i];
  //std::cout << temp.data[i] << '\n';
  //std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';
}


//lhs.data.swap(tmp);

}
else{throw matrix_bad_sizes();}
//std::cout << "/* message */" << endl << temp.data[0] << '\n';
return temp;
}

Matrix operator+(const value & lhs, const Matrix &rhs)
{
  Matrix x(0,0);
  temp = x;
  temp.nrows = rhs.nrows;
  temp.ncols = rhs.ncols;
  temp.matSize = rhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<temp.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = rhs.data[i] + lhs;
    //std::cout << temp.data[i] << '\n';
//std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  }

return temp;
}

Matrix operator+(const Matrix &lhs, const value & rhs)
{
return rhs+lhs;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{

  if((lhs.nrows == rhs.nrows) && (lhs.ncols == rhs.ncols)){
  Matrix x(0,0);
  temp = x;
  temp.nrows = lhs.nrows;
  temp.ncols = lhs.ncols;
  temp.matSize = lhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<lhs.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs.data[i] - rhs.data[i];
    //std::cout << temp.data[i] << '\n';
    //std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';
  }


  //lhs.data.swap(tmp);

  }
  else{throw matrix_bad_sizes();}
  //std::cout << "/* message */" << endl << temp.data[0] << '\n';
  return temp;
}

Matrix operator-(const value & lhs, const Matrix &rhs)
{
  Matrix x(0,0);
  temp = x;
  temp.nrows = rhs.nrows;
  temp.ncols = rhs.ncols;
  temp.matSize = rhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<temp.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs - rhs.data[i];
    //std::cout << temp.data[i] << '\n';
//std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  }

return temp;
}

Matrix operator-(const Matrix &lhs, const value & rhs)
{
  Matrix x(0,0);
  temp = x;
  temp.nrows = lhs.nrows;
  temp.ncols = lhs.ncols;
  temp.matSize = lhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<temp.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs.data[i] - rhs;
    //std::cout << temp.data[i] << '\n';
//std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  }

return temp;
}

/*** L2 NON-MEMBER FUNCTIONS/OPERATORS ***/

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
//std::cout << "/* message */" << '\n';
    if(lhs.ncols == rhs.nrows){
    Matrix x(0,0);
    temp = x;
    temp.ncols = rhs.ncols;
    temp.nrows = lhs.nrows;
    //std::cout << "/* message */1 " << lhs.ncols << lhs.nrows << rhs.ncols << rhs.nrows << '\n';
    //std::cout << "/* message */" << temp.nrows << temp.ncols << '\n';
    temp.matSize = temp.nrows * temp.ncols;
    temp.data.resize(temp.matSize);
    int ncolsCount = 0;
    int nrowsCount = 0;
    int a = 0;

    for(auto i = 0; i<temp.matSize; i++){
      //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';
      int b = 0;
      for (auto l = 0; l < lhs.ncols; l++) {
      //std::cout << "b+=" << "lhs("<< nrowsCount << ", " << l << ")" << '\n';
      //std::cout << "*" << "rhs(" << l << ", " << ncolsCount << ")" << '\n';
        b += lhs(nrowsCount, l) * rhs(l, ncolsCount);

      }
      //po ukoncini scitni do b
      temp.data[i] = b;
      //std::cout << temp << '\n';
      if(ncolsCount+1 != rhs.ncols) ncolsCount++;
      a++;
      if(a == rhs.ncols){
      ncolsCount = 0;
        if(nrowsCount+1 != lhs.nrows)  nrowsCount++;
        a = 0;
      }
      //std::cout << temp.data[i] << '\n';
      //std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';
    }


    //lhs.data.swap(tmp);

    }
    else{throw matrix_bad_sizes();}
    //std::cout << "/* message */" << endl << temp.data[0] << '\n';

    return temp;
}

Matrix operator*(const value & lhs, const Matrix &rhs)
{
  Matrix x(0,0);
  temp = x;
  temp.nrows = rhs.nrows;
  temp.ncols = rhs.ncols;
  temp.matSize = rhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<temp.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs * rhs.data[i];
    //std::cout << temp.data[i] << '\n';
  //std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  }

  return temp;
}

Matrix operator*(const Matrix &lhs, const value & rhs)
{
  Matrix x(0,0);
  temp = x;
  temp.nrows = lhs.nrows;
  temp.ncols = lhs.ncols;
  temp.matSize = lhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<temp.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs.data[i] * rhs;
    //std::cout << temp.data[i] << '\n';
//std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

  }

return temp;
}

Matrix hadamard(const Matrix &lhs, const Matrix &rhs)
{

  if((lhs.nrows == rhs.nrows) && (lhs.ncols == rhs.ncols)){
  Matrix x(0,0);
  temp = x;
  temp.nrows = lhs.nrows;
  temp.ncols = lhs.ncols;
  temp.matSize = lhs.matSize;
  temp.data.resize(temp.matSize);
  for(auto i = 0; i<lhs.matSize; i++){
    //std::cout << "test 1" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';

    temp.data[i] = lhs.data[i] * rhs.data[i];
    //std::cout << temp.data[i] << '\n';
    //std::cout << "test 2" << temp.data[i] << " = "<< lhs.data[i] << " + "<< rhs.data[i] << '\n';
  }


  //lhs.data.swap(tmp);

  }
  else{throw matrix_bad_sizes();}
  //std::cout << "/* message */" << endl << temp.data[0] << '\n';
  return temp;
}

Matrix power(const Matrix &m, unsigned int pow)
{
  //Matrix x(0,0);
  if(m.nrows == m.ncols){
  temp2 = m;
  if(pow == 0) temp2.eye();
  //std::cout << "before poer "<< temp << '\n';
  //std::cout << "m:" << '\n';
 //std::cout << "test 2" << endl << temp*m << '\n';
  if(pow != 1) {
    for (size_t i = 1; i < pow; i++) {
      temp2 = temp2*m;
      //std::cout << "test" << endl << temp << '\n';
    }
  }
}
else{throw matrix_bad_sizes();}

  return temp2;
}

/*** L3 NON-MEMBER FUNCTIONS/OPERATORS ***/
Matrix horzcat(const Matrix &lhs, const Matrix &rhs)
{

return rhs;
}

Matrix vertcat(const Matrix &top, const Matrix &bot)
{

return top;
}

Matrix blkdiag (const Matrix & lhs, const Matrix & rhs)
{

return rhs;
}

Matrix blkdiag (const value & lhs, const Matrix & rhs)
{

return rhs;
}

Matrix blkdiag (const Matrix & lhs, const value & rhs)
{

return rhs;
}

Matrix blkdiag (const value & lhs, const value & rhs)
{

return rhs;
}

Matrix kronecker(const Matrix &lhs, const Matrix &rhs)
{

return rhs;
}
