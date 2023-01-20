
#include "Statistics/CodeLearning.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"

using namespace code_learning;

int main() {
	statistics::CodeLearning student;
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	code::SourceFileBatch samples("Statistics/Adjacency.hpp", 
		"Statistics/CountAdjacencies.hpp", "Code/Char.h", "Code/Code.h",
		"Code/Line.h", "Code/Region.h", "Statistics/CodeLearning.h", 
		"Config.h", "Statistics/CountAdjacency.hpp",  "Statistics/Description.h", "Statistics/Descriptions.h",
		"Statistics/Frequency.hpp", "Code/Lexis.h", "Code/SourceFile.h", "Code/SourceFileBatch.hpp",
		"Statistics/ListMap.hpp", "Code/LexisType.h", "Code/Char.cpp", "Code/Code.cpp", "Code/Line.cpp", 
		"Code/Region.cpp", "Code/Composite.hpp", "Statistics/CodeLearning.cpp", "Config.cpp",
		"Statistics/Description.cpp", "Statistics/Descriptions.cpp", "Code/Lexis.cpp",
		"main.cpp", "Code/SourceFile.cpp");
	student.Learning(samples);
	student.Summary();
	getchar();
	return 0;
}