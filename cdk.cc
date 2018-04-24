/*
 * Usage of CDK Matrix
 *
 * File: cs3377.bin
 * New Author: Angel Castaneda
 * Email:  angel.castaneda@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

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

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  /* Reading Header from Binary file using BinaryFileHeader class with defaul constructer */
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  //cout << "Magic Number was: " << hex << uppercase << myHeader->magicNumber << endl;
  //cout << "Version Number was: " << dec << myHeader->versionNumber << endl;
  //cout << "Number of Recs was: " << setprecision(10) << myHeader->numRecords << endl;
  
  /* Formatting Magic Number Header to display properly*/
  char mnum_arr[15];
  int mnum = myHeader->magicNumber;
  sprintf(mnum_arr, "%08X", mnum); 
  char * magicstr = "Magic: Ox";
  char mag_arr[50];
  strncpy(mag_arr, magicstr, 9);
  strcat(mag_arr, mnum_arr);
  /* Adding Magic Number in matrix */
  setCDKMatrixCell(myMatrix, 1, 1, mag_arr);

  /* Formatting Version Number Header to display properly*/
  char vnum_arr[10];
  int vnum = myHeader->versionNumber;
  sprintf(vnum_arr, "%d", vnum);
  char * versionstr = "Version: ";
  char ver_arr[40];
  strncpy(ver_arr, versionstr, 9);
  strcat(ver_arr, vnum_arr);
  /* Adding Version number in matrix */
  setCDKMatrixCell(myMatrix, 1, 2, ver_arr);

  /* Formatting Number of Records Header to display properly*/
  char rnum_arr[10];
  int rnum = myHeader->numRecords;
  sprintf(rnum_arr, "%d", rnum);
  char * numberrecordstr = "NumRecords: ";
  char recnum_arr[40];
  strncpy(recnum_arr, numberrecordstr, 12);
  strcat(recnum_arr, rnum_arr);
  /* Adding Number of Records in matrix */
  setCDKMatrixCell(myMatrix, 1, 3, recnum_arr);


  
  /* Displaying Matrix*/
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* closing binary file opened for reading header */
  binInfile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
