/*
 * New Author: Angel Castaneda
 * Email:  angel.castaneda@utdallas.edu
 * Usage of CDK Matrix
 * File Extracted: cs3377.bin
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>

/* Defining parameters for CDK window */
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 16;

using namespace std;

/* Class for Reading Binary File Header Records (default constructor) */
class BinaryFileHeader
{
public:
  int magicNumber;
  int versionNumber;
  long int numRecords;
}
;

/* Class for Reading Binary File Data Records (default constructor) */
class BinaryFileData
{
public:
  int strLength;
  char strBuffer[maxRecordStringLength];
}
;


int main()
{
  /* Setting up CDK variabls. */ 
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  /* Creating variables used later for column/row names and format */
  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /* Initialize the Cdk screen. Make sure the putty terminal is large enough. */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors (because we're fancy). */
  initCDKColor();

  /* Create the matrix.  Need to manually cast (const char**) to (char **) */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  /* Erroring out if there is an issue creating matrix */
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Displaying the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* Reading Header from Binary file using BinaryFileHeader class with default constructor */
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  /* Reading Data from Binary file using BinaryFileData class with defaul contructor */ 
  //BinaryFileData *myData = new BinaryFileData();

  /* Opening file */
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  /* Ensuring file opened, otherwise displaying error message. */
  if ( binInfile.is_open() )
    {
       binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
      //cout << "Magic Number was: " << hex << uppercase << myHeader->magicNumber << endl;
      //cout << "Version Number was: " << dec << myHeader->versionNumber << endl;
      //cout << "Number of Recs was: " << setprecision(10) << myHeader->numRecords << endl;
      
      /* Formatting Magic Number Header to display properly*/
      char mnum_arr[9];
      int mnum = myHeader->magicNumber;
      sprintf(mnum_arr, "%08X", mnum); 
      char * magicstr = "Magic: Ox";
      char mag_arr[19];
      strncpy(mag_arr, magicstr, 9);
      strcat(mag_arr, mnum_arr);
      /* Adding Magic Number in matrix */
      setCDKMatrixCell(myMatrix, 1, 1, mag_arr);
      
      /* Formatting Version Number Header to display properly*/
      char vnum_arr[9];
      int vnum = myHeader->versionNumber;
      sprintf(vnum_arr, "%d", vnum);
      char * versionstr = "Version: ";
      char ver_arr[19];
      strncpy(ver_arr, versionstr, 9);
      strcat(ver_arr, vnum_arr);
      /* Adding Version number in matrix */
      setCDKMatrixCell(myMatrix, 1, 2, ver_arr);

      /* Formatting Number of Records Header to display properly*/
      char rnum_arr[9];
      int rnum = myHeader->numRecords;
      sprintf(rnum_arr, "%d", rnum);
      char * numberrecordstr = "NumRecords: ";
      char recnum_arr[22];
      strncpy(recnum_arr, numberrecordstr, 12);
      strcat(recnum_arr, rnum_arr);
      /* Adding Number of Records in matrix */
      setCDKMatrixCell(myMatrix, 1, 3, recnum_arr);

      /* Starting to read data records. */
      /*binInfile.read((char *) myData, sizeof (BinaryFileData));
      string content = "";
      int i = 0;
      for (i=0; binInfile.eof()!=true; i++)
	{
	  //cout << "String Length was : " << dec << myHeader->versionNumber << endl;
	  //cout << "String (in buffer was) " << setprecision(10) << myHeader->numRecords << endl;
	  content += binInfile.get();
	  content += ",";
	}
      cout << content << endl;
      */
      
      /* Displaying Matrix*/
      drawCDKMatrix(myMatrix, true);    /* required  */

      /* closing binary file opened for reading header */
      binInfile.close();

      /* So we can see results, pause until a key is pressed. */
      unsigned char x;
      cin >> x;
    }
  else
    { /* Message incase binary file could not be opened. */
      cerr << "There was a problem opening the binary file." << endl;
      exit(1);
    }

  // Cleanup screen
  endCDK();

  return 0;
}
