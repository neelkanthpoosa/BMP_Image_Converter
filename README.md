# BMP Image Converter

- Tool to convert a given image to its negative.

------------------------------------------------------------------------
### Steps to Run the Tool:
------------------------------------------------------------------------
 Create execution file:

           gcc tool.c -o converter

    
   [USAGE]
       
            ./converter INPUT_IMAGE_NAME.BMP

   Details:
    
  - INPUT_IMAGE_NAME    -      NAME OF THE INPUT IMAGE
  - TYPE                -      .BMP
        
------------------------------------------------------------------------
### Input File Details ( You may add any other files )
------------------------------------------------------------------------
  1.  ex.bmp

  This is an ideal 24 bits per pixel .bmp image.

  2.  ex-compressed.bmp

  This is a compressed image file.

  3.  ex-err24.bmp

  This is a not a 24 bit per pixel image file.

  4.  ex-wrongfile.png

  Wrong file Format(.PNG)

------------------------------------------------------------------------
### Output File Details
------------------------------------------------------------------------
    1.  negative.bmp

  This is the result file, which has a negative image of the valid input image.

------------------------------------------------------------------------
### Execution File
------------------------------------------------------------------------
    - Alternatively, you can run the shell script to create C execution 
    file and execute the C program:

           sh run.sh


------------------------------------------------------------------------
### Assumptions:
------------------------------------------------------------------------
- Input file is of type .BMP

  - Errors are handled in any other case


- Image consists of 24 bits per pixel
  - Errors are handled in any other case


- Image is not Compressed
  - Errors are handled in any other case


- User runs the tool on one image at a time
  - Errors are handled if more aguments are passed

------------------------------------------------------------------------
### Limitations:
------------------------------------------------------------------------
- This tool only takes the input of two arguments:
   
1:  Execution file
              
              ./converter

2:  Input Image File or Help command

            ./converter input_file_name.bmp

            ./converter --help 
 
   Hence, the tool doesn't support serialized passing of input images.

  This implies, only one input can be passed per execution.
  And the corresponding output is seen as "negative.bmp" after successfully conversion.



------------------------------------------------------------------------
