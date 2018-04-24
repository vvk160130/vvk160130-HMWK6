/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <cdk.h>
#include <stdint.h>
#include <fstream>
#include <stdio.h> 
#include <string.h> 
#include <string> 
//#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


class BinaryFileHeader
{
 public: 

  uint32_t magicNumber;
  uint32_t versionNumber; 
  uint64_t numRecords;

};


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

  // Remember that matrix starts out at 1,1.
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


  /* Comment  */
  BinaryFileHeader *header = new BinaryFileHeader(); 

  ifstream binFile("cs3377.bin", ios::in | ios::binary);  

  if(!binFile)
  {
	printf("Error in opening file \n");
	_exit(1); 
  }

  binFile.read((char *) header, sizeof(BinaryFileHeader));


  sprintf(buffer, "Magic: 0x%X", header->magicNumber);

  setCDKMatrixCell(myMatrix, 1, 1, buffer); 

  sprintf(buffer, "Version: %d", header->versionNumber);  
	
  setCDKMatrixCell(myMatrix, 1, 2, buffer);

  sprintf(buffer, "NumRecords: %lu", header->numRecords); 

  setCDKMatrixCell(myMatrix, 1, 3, buffer); 


 

 /*Comment */


 unsigned long long recordNum = header->numRecords; 
 
 BinaryFileRecord *record = new BinaryFileRecord(); 



// string length = "strlen: " + to_string(strlen(record->stringBuffer));
 string length = ""; 


	
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
