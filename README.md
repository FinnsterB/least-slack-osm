# least-slack-osm
Working implementation of a least-slack scheduler in C++. Works for Jobs where the total duration of the longest job < unsigned long integer limit. Works for JobShops where the Job count < unsigned long integer limit. 

# Build using Eclipse C++:
Make new C/C++ Managed project. Put source files in the project directory. Right click the project and build it. After building you can run it by right clicking the project, and clicking "Run as"->"Local c++ application". 

# Usage:
Put the input file in the executable directory and run ./leastslackosm [filename]. Output will be on the std output.
