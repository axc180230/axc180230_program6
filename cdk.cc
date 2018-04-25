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
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

/* Defining parameters for CDK window */
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 25;

using namespace std;

/* Class for Reading Binary File Header Records (default constructor) */
class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
}
;

/* Class for Reading Binary File Data Records (default constructor) */
class BinaryFileData
{
public:
  uint8_t strLength;
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
  BinaryFileData *myData = new BinaryFileData();
  /* Creating fstream for file */
  fstream binInfile;

  /* Opening file */
  binInfile.open("cs3377.bin", ios::in | ios::binary);
  /* Ensuring file opened, otherwise displaying error message. */
  if ( binInfile.is_open() )
    {
       binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

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

      /* Starting to read data records. Using array for loop. */
      string matrix_arr[3 * 4];
      char temp[1024];
      for (int i = 0; i < 4; i++)
	{ /* Reading data record string and length */
	  binInfile.read((char*)myData, sizeof(BinaryFileData));
	  sprintf(temp, "%d", myData->strLength);
	  matrix_arr[i] = "strlen: ";
	  matrix_arr[i] = matrix_arr[i] + temp;
	  
	  /* Reading dara record string */
	  sprintf(temp, "%s", myData->strBuffer);
	  matrix_arr[i+4] = temp;
	}
      
      /* Adding Data Records in matrix (from loop) */
      setCDKMatrixCell(myMatrix, 2, 1, matrix_arr[0].c_str());
      setCDKMatrixCell(myMatrix, 2, 2, matrix_arr[4].c_str());
      setCDKMatrixCell(myMatrix, 3, 1, matrix_arr[1].c_str());
      setCDKMatrixCell(myMatrix, 3, 2, matrix_arr[5].c_str());
      setCDKMatrixCell(myMatrix, 4, 1, matrix_arr[2].c_str());
      setCDKMatrixCell(myMatrix, 4, 2, matrix_arr[6].c_str());
      setCDKMatrixCell(myMatrix, 5, 1, matrix_arr[3].c_str());
      setCDKMatrixCell(myMatrix, 5, 2, matrix_arr[7].c_str());
      
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
