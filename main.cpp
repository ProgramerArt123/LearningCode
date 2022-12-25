
#include "CodeLearning.h"
#include "SourceFile.h"
#include "SourceFileBatch.hpp"

using namespace code_learning;

int main() {
	CodeLearning student;
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	SourceFileBatch samples("Adjacency.hpp", "Adjacencies.hpp", "Char.h", "Code.h",
		"CodeLearning.h", "Config.h", "CountAdjacency.hpp", "Description.h", "Descriptions.h",
		"Frequency.hpp", "Lexis.h", "SourceFile.h", "SourceFileBatch.hpp", "ListMap.hpp", "WordType.h",
		 "Char.cpp", "Code.cpp", "CodeLearning.cpp", "Config.cpp",
		"Description.cpp", "Descriptions.cpp", "Lexis.cpp",
		"main.cpp", "SourceFile.cpp");
	student.Learning(samples);
	student.Summary();
	getchar();
	return 0;
}