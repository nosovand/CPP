

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int rangeError = 0;
int closeApp = 0;

vector<vector<int> > table;
vector<int> currentRow;

string currentParameter = " ";
string parametrValues[10];
int parameterIndex = 0;
int minimum = -99;
int maximum = 100;
int width = 3;
int alignP = 1;
int stretch = 0;
int header = 0;
int rowLength = 0;
int rowCount = 0;

void freeSapce(){
  for (int m = 0; m < (int)table.size(); m++) {
    //vector<int>().swap(table[m]);
    table[m].clear();
    table[m].shrink_to_fit();
  }
  //vector<vector<int>>().swap(table);
  table.clear();
  table.shrink_to_fit();
}

void getParameters (){
  while (currentParameter != "="){
    size_t found;
    cin >> currentParameter;
    found = currentParameter.find("min");
    if (found != string::npos){

      minimum = stoi(currentParameter.substr(found+4, 6));
      parameterIndex++;
    }

    found = currentParameter.find("max");
    if (found != string::npos){

      maximum = stoi(currentParameter.substr(found+4, 6));
      parameterIndex++;
    }

    found = currentParameter.find("width");
    if (found != string::npos){

      width = stoi(currentParameter.substr(found+6, 6));
      if(width<1){
        std::cerr << "Invalid configuration" << '\n';
        freeSapce();
        exit(102);
      }
      parameterIndex++;
    }

    found = currentParameter.find("align");
    if (found != string::npos){

    if(currentParameter.substr(found+6, 4) == "left"){
      alignP = 1;
    }
    if(currentParameter.substr(found+6, 5) == "right"){
      alignP = 2;
    }
      parameterIndex++;
    }

    found = currentParameter.find("stretch");
    if (found != string::npos){

    if(currentParameter.substr(found+8, 1) == "0"){
      stretch = 1;
    }
    if(currentParameter.substr(found+8, 1) == "1"){
      stretch = 2;
    }
      parameterIndex++;
    }

    found = currentParameter.find("header");
    if (found != string::npos){

    if(currentParameter.substr(found+7, 1) == "0"){
      header = 1;
    }
    if(currentParameter.substr(found+7, 1) == "1"){
      header = 2;
    }
      parameterIndex++;
    }

  }
  if(minimum>maximum){
    std::cerr << "Invalid configuration" << '\n';
    freeSapce();
    exit(102);
  }
}


string currentData;
string currentLine;
int startSum;
int endSum;
int sum = 0;
size_t found2;
int i = 0;


void checkData(int x){
  if (x<minimum || x>maximum){
    if(rangeError == 0){
    std::cerr << "Out of range" << '\n';
    freeSapce();
    exit(100);
  }
}
  string z = to_string(x);
  if(stretch == 0 && (int)z.length()>width){
    std::cerr << "Cell is too short" << '\n';
    freeSapce();
    exit(103);
  }
  if(stretch == 2 && (int)z.length()>width){
    width = z.length();
  }
}

void getData(){

  while (getline(cin, currentLine)){
    istringstream dataStream(currentLine);
  while (getline(dataStream, currentData, ';')){
      found2 = currentData.find("SUM");
      if (found2 != string::npos){
        startSum = (int)currentData[4]-65;
        endSum = (int)currentData[6]-65;
        rangeError = 1;
        for(int k = 0; k < (int)currentRow.size(); k++){
          sum += currentRow[k];
        }
        currentData = to_string(sum);
        sum = 0;
      }
     try {
       stoi(currentData);
     }
     catch (...) {

       freeSapce();
       closeApp = 1;
       return;
     }
     checkData(stoi(currentData));
     rangeError = 0;
     currentRow.push_back(stoi(currentData));

     i++;
    }
    table.push_back(currentRow);
    if(endSum>(int)currentRow.size()){
      freeSapce();
      closeApp = 1;
      return;
    }
    if ((int)currentRow.size()>(int)rowLength){
      rowLength = currentRow.size();
    }
    currentRow.clear();
    i = 0;
  }
}

void printParameter(){
  std::cout << "config.min=" << minimum << '\n';
  std::cout << "config.max=" << maximum << '\n';
  std::cout << "config.width=" << width << '\n';
  if(alignP == 2){
      std::cout << "config.align=right" << '\n';
  }
  else{
      std::cout << "config.align=left" << '\n';
  }

  switch (stretch) {
    case 1: std::cout << "config.stretch=0" << '\n';
    break;
    case 2: std::cout << "config.stretch=1" << '\n';
    break;
    default: ;
  }
  switch (header) {
    case 1: std::cout << "config.header=0" << '\n';
    break;
    case 2: std::cout << "config.header=1" << '\n';
    break;
    default: ;
  }

}

char cellName;
string lengthCheck;


void printTable(){



  if (header != 1){
    for (int l = 0; l <= rowLength; l++){ //tisk horni hranice
      if(header == 1 && l == 0) {
        l = 1;
      }
      std::cout << "+";
      for (int o = 0; o < width+2; o++) {
        std::cout << "-";
      }
    }
    std::cout << "+" << '\n';
                            //tisk nazvu
    for (int u = 0; u <= rowLength; u++) {
      std::cout << "|";
      if (u == 0){
        for (int t = 0; t < width+2; t++) {
          std::cout << " ";
      }
    }
      else{
      cellName = u+64;
        if(alignP != 2){
          std::cout << " " << cellName;
          for (int t = 0; t < width; t++) {
            std::cout << " ";
        }
      }
      else{
        for (int t = 0; t < width; t++) {
          std::cout << " ";
      }
        std::cout  << cellName << " ";
    }

  }
}
  std::cout << "|" << '\n';
}


for (int p = 1; p < (int)table.size(); p++) {

for (int l = 0; l <= rowLength; l++){ //tisk horni hranice
  if(header == 1 && l == 0) {
    l = 1;
  }
  std::cout << "+";
  for (int o = 0; o < width+2; o++) {
    std::cout << "-";
  }
}
std::cout << "+" << '\n';

  for (int u = 0; u <= rowLength; u++) { // tisk hodnot
    if(header == 1 && u == 0) {
      u = 1;
    }
    std::cout << "|";
    if(u == 0){                        //pro prvni bunku
      if(alignP != 2){//zarovnany doleva
            std::cout << " " << p;
        for (int t = 0; t < width; t++) {
          std::cout << " ";
      }
    }
    //zarovnany doprava
    else{
      for (int t = 0; t < width; t++) {
        std::cout << " ";
    }
      std::cout  << p << " ";
  }
}
  //pro ostatni bunky



    else{

if(u<=(int)table[p].size())lengthCheck = to_string(table[p][u-1]);

      if(stretch == 1 && (int)lengthCheck.length()>width && u <= (int)table[p].size()){
        std::cout << " ";
        for (int t = 0; t < width; t++) {
          std::cout << "#";
      }
        std::cout << " ";
      }
      else{

      if(alignP != 2){



        if(u <= (int)table[p].size()){



            std::cout << " " << table[p][u-1];

            for (int t = 0; t <= width-(int)lengthCheck.length(); t++) {
              std::cout << " ";
          }
        }

        else{
          for (int t = 0; t < width+2; t++) {
            std::cout << " ";
        }
        }

    }

    else{
      if(u <= (int)table[p].size()){
      for (int t = 0; t <= width-(int)lengthCheck.length(); t++) {
        std::cout << " ";
    }
      std::cout  << table[p][u-1] << " ";
  }

else{
  for (int t = 0; t < width+2; t++) {
    std::cout << " ";
}
}
}
}
}
}


    std::cout << "|" << '\n';
}
for (int l = 0; l <= rowLength; l++){ //tisk dolni hranice
  if(header == 1 && l == 0) {
    l = 1;
  }
  std::cout << "+";
  for (int o = 0; o < width+2; o++) {
    std::cout << "-";
  }
}
std::cout << "+" << '\n';
}

void testPrint(){
std::cout << "test" << table[2].size() << '\n';
}



int main(int argc, char const *argv[]) {
getParameters();
getData();
if (closeApp == 1) {
  freeSapce();
  std::cerr << "Invalid input" << '\n';
  return 101;
}
printParameter();
std::cout << '\n';
printTable();
freeSapce();


//testPrint();
  return 0;
}
