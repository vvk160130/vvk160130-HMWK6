/*
 * Name: Vishnu Kunadharaju 
 * Course Number: CS 3377
 * Section Number: 501
 * Homework Number: 6
 *
 */


/* Program Overview: 
 * 
 * This program uses binary file I/O techniques to open a supplied binary file. The file consists of a 
 * header record that is immediately followed by  a set of data records. We read and display 
 * the header record. Using information in the header record, we read the data records from 
 * the file. for each data record, we display the results in a CDK window. After displaying, 
 * the program waits for the user to type a character on the keyboard. When they do, the program will exit. 
 *
 * */

#include <iostream>
#include <cdk.h>
#include <stdint.h>
#include <fstream>
#include <stdio.h> 
#include <string.h> 
#include <string> 
//#include "cdk.h"


/* These values define the width and height of the matrix and 
   they also define the width of each field in the matrix. */

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;



/* BinaryFileHeader Class */

/* Our binary file has two sections:
 * 	1. header record 
 * 	2. data records
 *
 * We use the BinaryFileHeader class to extract
 * the header record data in the binary file. 
 * In a general overview we use the data in 
 * the header record to read the data records
 * from the file. 
 *
 * When we read the header record we get the following
 * information about the bin file. 
 * 	1. The magic number
 * 	2. The version number of the file
 * 	3. The number of data records found in the file
 *
 * We now know how many data records are in the file 
 * and then we loop through the rest of the file to 
 * print out all the records */

class BinaryFileHeader
{
 public: 

  uint32_t magicNumber;
  uint32_t versionNumber; 
  uint64_t numRecords;

};



/* BinaryFileRecord Class */

/* Our binary file has two sections: 
 * 	1. header record
 * 	2. data records
 *
 * We use the BinaryFileRecord class to 
 * read in the data records that the
 * binary file holds. Each data record
 * in the file is described by this class. 
 * This class has a char array with a
 * size of 25, and we can read these
 * many characters into the array 
 * for each data record from the file */


/* Records in the file have a fixed length buffer that will hold a 
 * C-style string. This is the size of the fixed length buffer. */

const int maxRecordStringLength = 25; 

class BinaryFileRecord
{
 public: 

  uint8_t strLength;
  char stringBuffer[maxRecordStringLength]; 

};




int main()
{

  char buffer[1024]; 

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // The matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
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






		  /*Binary File Operations Part 1 */

  /* Here we are creating a instance of the BinaryFileHeader class (pointer). 
   * We are also opening the binary file for reading */

  BinaryFileHeader *header = new BinaryFileHeader(); 

  ifstream binFile("cs3377.bin", ios::in | ios::binary);

  /* Below we are checking to see if the binary file opened properly.
   * We are exiting if the file failed to open */

  if(!binFile)
  {
	printf("Error in opening file \n");
	_exit(1); 
  }


  // We read in the header record 
  
  binFile.read((char *) header, sizeof(BinaryFileHeader));


  /*The sprintf function is used to generate a char* which 
   * holds the magic number and then we add it to the
   * setCDKMatrixCell() */

  sprintf(buffer, "Magic: 0x%X", header->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buffer); 


  /*The sprintf function is used to generate a char* which 
   * holds the version number and then we add it to the
   * setCDKMatrixCell() */

  sprintf(buffer, "Version: %d", header->versionNumber);  
  setCDKMatrixCell(myMatrix, 1, 2, buffer);


  /*The sprintf function is used to generate a char* which 
   * holds the number of records and then we add it to the
   * setCDKMatrixCell() */

  sprintf(buffer, "NumRecords: %lu", header->numRecords); 
  setCDKMatrixCell(myMatrix, 1, 3, buffer); 


 

 		/*Binary File Operations Part 2 */

  /*Below we are storing the number for the number of records
   *that exist in the binary file, and we created a instance
   of the BinaryFileRecord class. */

 unsigned long long recordNum = header->numRecords; 
 
 BinaryFileRecord *record = new BinaryFileRecord(); 


 string length = ""; 


 /*The following for loop, is used to read in the remaining data records. 
  * This loop only reads up to the first four records in the binary file. 
  * Within in the loop, we convert the length of the string to a char* 
  * and print it to the matrix and we also display the actual string itself
  * to the error */

 for(int x = 2; x <= int(recordNum) + 1; x++)
 {
	
 	binFile.read((char *) record, sizeof(BinaryFileRecord)); 

	length = "strlen: " + to_string(strlen(record->stringBuffer)); 

 	setCDKMatrixCell(myMatrix, x, 1, length.c_str()); 
	
  	sprintf(buffer, " %s", record->stringBuffer);

	
 	setCDKMatrixCell(myMatrix, x, 2, buffer); 


 }

 binFile.close(); 



  /*
   * Dipslay a message
   */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
