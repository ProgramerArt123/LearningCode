
#include "CodeLearning.h"
#include "SourceFile.h"
#include "SourceFileBatch.hpp"

using namespace code_learning;

int main() {
	CodeLearning student;
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	SourceFileBatch samples("AdjacencyWord.h", "AdjacencyWords.h", "Char.h", "Code.h",
		"CodeLearning.h", "Config.h", "CountAdjacencyWords.h", "Description.h", "Descriptions.h",
		"FrequencyWord.h", "Lexis.h", "SourceFile.h", "SourceFileBatch.hpp", "Words.hpp", "WordType.h",
		"AdjacencyWord.cpp", "AdjacencyWords.cpp", "Char.cpp", "Code.cpp", "CodeLearning.cpp", "Config.cpp",
		"CountAdjacencyWords.cpp", "Description.cpp", "Descriptions.cpp", "FrequencyWord.cpp", "Lexis.cpp",
		"main.cpp", "SourceFile.cpp");
	student.Learning(samples);
	student.Summary();
	getchar();
	return 0;
}