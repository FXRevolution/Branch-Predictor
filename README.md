# Branch-Predictor
gShare or gSelect branch predictor

Use the following instructions to run the simulator on your system.

•	Using a Windows or Linux command line terminal, change directory to the folder containing the executable file BranchPredictionSim.exe (i.e. “.../BranchPredictionSim/Debug/”)

•	Once in the folder execute the program in the following format:

o	./BranchPredictionSim.exe Gshare  <M> <N> <Trace_File path>

•	The Trace File Path can be the file’s full path with the file name as shown below:

*NOTE Please use \\ instead of \ because the string will not ignore escape characters*

•	If the trace file is in the same folder as the executable the file path can be just the filename and extension.

•	The trace file must contain input lines in the following format

  o	Address	Taken/Not Taken

  o	 0x123456789abcdef 	t

  o	0xfedcba987654321 	n

•	The program was created using Visual Studios and the solution can be viewed on the platform with minimal configuration.

•	To view the code in Visual Studios go to the project folder “BranchPredictionSim” and open the solution file “BranchPredictionSim.sln” using VS 2017

The Simulator outputs the following values to the console:

M	N	Miss Percentage
