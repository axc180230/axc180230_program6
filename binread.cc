#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BinaryFileHeader
{
public:
  int magicNumber;
  int versionNumber;
  long int numRecords;
}
;

int main()
{
  BinaryFileHeader *myHeader = new BinaryFileHeader();  
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  cout << "Magic Number was: " << hex << uppercase << myHeader->magicNumber << endl;
  cout << "Version Number was: " << dec << myHeader->versionNumber << endl;
  cout << "Number of Recs was: " << setprecision(10) << myHeader->numRecords << endl;
  
  binInfile.close();
  return 0;
}
;
