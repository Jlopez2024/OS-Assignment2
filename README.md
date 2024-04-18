The banker file is the already compiled code for bankers_algorithm.cpp. You can either execute that or recompile the source code. 

The inpupt.txt file is where the allocation and max matrices are stored along with the array of available resources. The fstream library is used to open and read the data from the file. The white-space lines between the matrices in the input file are purely for organizational purposes.

Within the directory of these files, to recompile the source code enter the command:

`g++ bankers_algorithm.cpp -o banker`

And to execute the banker file, type:

`./banker`
