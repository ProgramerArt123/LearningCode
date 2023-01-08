
#include "CodeLearning.h"
#include "SourceFile.h"
#include "SourceFileBatch.hpp"

using namespace code_learning;

int main() {
	CodeLearning student;
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	SourceFileBatch samples("Adjacency.hpp", "Adjacencies.hpp", "Char.h", "Code/Code.h", "Code/Line.h", "Code/Region.h",
		"CodeLearning.h", "Config.h", "CountAdjacency.hpp", "Description.h", "Descriptions.h",
		"Frequency.hpp", "Code/Lexis.h", "SourceFile.h", "SourceFileBatch.hpp", "ListMap.hpp", "WordType.h",
		 "Char.cpp", "Code/Code.cpp", "Code/Line.cpp", "Code/Region.cpp", "Code/Composite.hpp", "CodeLearning.cpp", "Config.cpp",
		"Description.cpp", "Descriptions.cpp", "Code/Lexis.cpp",
		"main.cpp", "SourceFile.cpp");
	student.Learning(samples);
	student.Summary();
	getchar();
	return 0;
}