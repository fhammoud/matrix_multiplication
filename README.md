# Multithreaded Matrix Multiplication

This was a senior year Operating Systems project that was about determining the turnaround time of mulitplying two matrices
using various numbers of threads.

The program takes in a text file containing a matrix of numbers and the number of threads to use as parameters,
then (for simplicity) it multiplies the matrix by itself dividing up the work between the number of threads specified.
Finally it will log the execution time to the console.

#### To test
##### Must be executed on Linux
* Clone the project and move to its directory
* Run `make` to build the executable
* Run `./main.out resources/<matrix_file> <output file> <threads(1,4,16,64 or 256)>`
* e.g. `./main.out resources/matrix16.txt output.txt 4`
* Take note of execution time and try other matrices and thread counts

##### Visual Studio and Windows Subsystem for Linux (WSL)
If you want to use Visual Studio and have WSL installed and configured correctly to be used with Visual Studio:
* Clone the project
* Open the solution file in Visual Studio
* Configure a connection to your WSL installation
* Run the program
* You can change input parameters from `Debug > matrix_multiplication Properties > Debugging > Program Arguments`