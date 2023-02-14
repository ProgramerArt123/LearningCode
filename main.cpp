#include <boost/assert.hpp>
#include "Statistics/CodeLearning.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Code/SourcePath.h"
#include "Code/Code.h"
#include "Algorithm/Set.hpp"
#include "Algorithm/Event.h"

using namespace code_learning;

int main() {
	{
#include "Algorithm/Probability.h"
		srand(time(0));
		const algorithm::SampleSpace S(10000);
		const algorithm::SampleSpace S2(10000);
		const algorithm::SampleSpace S3(10000);
		const algorithm::SampleSpace S4(10000);
		const algorithm::Event A(rand() % 10000 + 1, S);
		const algorithm::Event B(rand() % 10000 + 1, S);
		const algorithm::Event C(!B);
		algorithm::Event D(rand() % 10000 + 1, S2);
		algorithm::Event E(rand() % 10000 + 1, S3);
		algorithm::Event F(rand() % 10000 + 1, S4);

		const algorithm::Probability P;

		BOOST_ASSERT(P(A) == 1 - P(!A) && "Complementary Events--1");
		BOOST_ASSERT(1 == P(A) + P(!A) && "Complementary Events--2");
		BOOST_ASSERT(1 - P(A) == P(!A) && "Complementary Events--3");

		BOOST_ASSERT(P(A - B) == P(A) - P(A&B) && "Difference Events--1");
		BOOST_ASSERT(P(A) - P(A - B) == P(B&A) && "Difference Events--2");

		BOOST_ASSERT(P(A + B) == P(A) + P(B) - P(B&A) && "Unions Events--1");
		BOOST_ASSERT(P(B + A) + P(A&B) == P(B) + P(A) && "Unions Events--2");

		BOOST_ASSERT(P(B + C) == P(B) + P(C) && "Disjoint Events--1");
		BOOST_ASSERT(P(C + B) - P(B) == P(C) && "Disjoint Events--2");

		BOOST_ASSERT(P(D&E) == P(D)*P(E) && "Independent Events--1");
		BOOST_ASSERT(P(D&E&F) == P(D)*P(E)*P(F) && "Independent Events--2");
		BOOST_ASSERT(P(D&(E&F)) == P(D)*P(E)*P(F) && "Independent Events--3");

		BOOST_ASSERT(P(B | A) == P(A&B) / P(A) && "Conditional Events--1");
		BOOST_ASSERT(P(A | B)*P(B) == P(B&A) && "Conditional Events--2");

		const algorithm::Event &G = D & E;
		BOOST_ASSERT(P(G & G) == P(G) && "Composite Events--1");
		BOOST_ASSERT(P(G + G) == P(G) && "Composite Events--2");
		BOOST_ASSERT(P(G - G) == 0 && "Composite Events--3");
		BOOST_ASSERT(P(G - D) == P(G) - P(D)*P(E) && "Composite Events--4");
		BOOST_ASSERT(P(G - F) == P(G)*P(!F) && "Composite Events--5");
	}
	statistics::CodeLearning student("CPP");
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	code::SourcePath samples(".");
	samples.AddSuffixNames(".h", ".hpp", ".cpp", ".cc", ".cxx", ".c++", ".cp", ".c");
	student.Learning(samples);
	code::Code code("int main(){return 0;}");
	student.Learning(code);
	getchar();
	return 0;
}