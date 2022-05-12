#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


/*---------------------------------------------------------------
    FUNCTION DECLARATIONS
---------------------------------------------------------------*/
void convertToNegative(char *input_file, char *output_file);
void helper();
void errorCheck(char str[]);
void driver(int argc,char *argv[],char* input_file,char *output_file);
/*---------------------------------------------------------------*/


/*---------------------------------------------------------------
    MAIN PROGRAM
---------------------------------------------------------------*/
int main(int argc, char *argv[]) 
{
  char *input_file = argv[argc -1];
  char *output_file;
  // Drives The Tool Pipepline
  driver(argc,argv,input_file,output_file);
  return 0;
}
/*---------------------------------------------------------------*/



/*---------------------------------------------------------------
    FUNCTION DEFINITIONS
---------------------------------------------------------------*/

 /*--------------------------------------------------
        Drives the Tool
   --------------------------------------------------*/
void driver(int argc,char *argv[],char* input_file,char *output_file)
  {
     if(argc == 2)
      {
        if (strcmp(argv[1],"--help") == 0)
        {
          // Helper Guide called
          helper();
        }
        else
        {      
          
            // Default Filename
            output_file = "negative.bmp";

          // Conversion Called
          convertToNegative(input_file,output_file);
        }
      }
     else if(argc>2)
        {
          errorCheck("Too many arguments passed, check out './converter --help' for the usage.");
        }
     else
          errorCheck("Too few arguments passed, check out './converter --help' for the usage.");

  }

 /*--------------------------------------------------
        Converts the Input Image to its Negative
   --------------------------------------------------*/

void convertToNegative(char *input_file, char *output_file)
{

  int startOfPixelArray=54;
  //ASCII values of B,M
  int B=66,M=77;

  unsigned char *input_data, *output_data;
  size_t imageSize;
  
  int padding;
  // data for source file
  int sourceFileDescriptor = open(input_file,O_RDONLY);
  
  //File doesn't Exist/Error Reading Input File
  if (sourceFileDescriptor == -1)
    errorCheck("Oops! the file doesn't exist. Use './converter --help' to check correct usage.");

  imageSize = lseek(sourceFileDescriptor, 0, SEEK_END);

  input_data = mmap(NULL,imageSize,PROT_READ,MAP_PRIVATE,sourceFileDescriptor,0);
  if(input_data == MAP_FAILED) errorCheck("MMAP Problem");
  
  
  // Type Checking
  //Value for BMP File Header at 0 and 1 are "B" and "M" respectively. This signifies  24 bit BMP image.
  if((input_data[0]) == B && (input_data[1] == M))
    {
      
      //Compression Check (30 to 33 bytes ~ 4 bytes)
      int c= input_data[30] | (input_data[31]<<8) |(input_data[32]<<16) | (input_data[33]<<24);
      if(c!=0) errorCheck("This file is compressed, try with another file.\n");

      //Number of bits per pixel-> from 28th and 29th bytes (2 bytes)
      int bits=input_data[28] | (input_data[29]<<8);
      
      if(bits!=24) 
      {
        printf("Number of bits per pixel:%d\n",bits);
        errorCheck("Sorry, the file is not of 24 bits/pixel.\n");
      }

      printf("Number of bits per pixel:%d\n",bits);

      //Image Width starts from 18th byte to 21st byte(4 bytes)
      int w = input_data[18] | (input_data[19]<<8) |(input_data[20]<<16) | (input_data[21]<<24);

      //Image Height starts from 22nd byte to 25th byte(4 bytes)
      int h = input_data[22] | (input_data[23]<<8) |(input_data[24]<<16) | (input_data[25]<<24);

      //Padding consists of 4 bytes alignment with 3 bytes(24bits) per pixel
      padding = (4 - ((w * 3) % 4)) % 4;
      
      
      if(c==0)
      {
        printf("Not Compressed");
      }
    
      printf("\nHeight of the Image: %d\nWidth of the Image: %d \n\n", h,w);


        // Creating Output File with input image size provided
        int outputFileDescriptor = open(output_file, O_RDWR | O_CREAT, 0666);
        ftruncate(outputFileDescriptor, imageSize);
        output_data = mmap(NULL, imageSize, PROT_READ | PROT_WRITE, MAP_SHARED, outputFileDescriptor, 0);
        
        // Providing a deepcopy of the source data to the output file
        memcpy(output_data, input_data, imageSize);

        // last pixel in the row of pixels
        int lastPixel = (w * 3) ;

        for(int i = startOfPixelArray; i < (h * w * 3) + (padding * h); i += 3)
        {
          // Padding Checked and Skipped Bytes Accordingly
          if(padding)
            {
              if(i == lastPixel + startOfPixelArray)
              {
                lastPixel = (lastPixel+padding) + (w * 3);
                i += (padding);
              }
            }

          // Inverting the color of each pixel and Writing data into output file
          int color=2;//0-Indexed BLUE GREEN RED Colors
          while(color>=0)
            {
              
              output_data[i+color] = 255 - input_data[i+color];
              color--;

            }

        }
        // Unmap the Memory
        munmap(output_data, imageSize);
        // Close the Output File
        close(outputFileDescriptor);
        printf("Successfully converted!\n");
    }
  else
    {
      errorCheck("Wrong file format, only .BMP files are allowed!");
    }

  }


 /*--------------------------------------------------
        Help Guide Definition froom helper.txt
   --------------------------------------------------*/
 void helper()
 {
    int c;
    FILE *file;
    file = fopen("help/helper.txt", "r");
    if (file)
    {
        c = getc(file);
        while (!feof(file))
        {
          putchar(c);
          c = getc(file);

        }
        int key = fgetc(stdin);
        if(key==10)
        {
          system("clear");
        }
            fclose(file);
        }

  }
 /*--------------------------------------------------
        Checks Errors and Terminates
   --------------------------------------------------*/
  void errorCheck(char str[])
  {
     printf ("Error : %s\n",str);
     exit(1);
  }
 
 /* ----------------------------------------------------------------------*/