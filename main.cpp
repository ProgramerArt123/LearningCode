#include <boost/assert.hpp>
#include "Statistics/CodeLearning.h"
#include "Code/SourceFile.h"
#include "Code/SourceFileBatch.hpp"
#include "Code/SourcePath.h"
#include "Code/Code.h"
#include "Algorithm/Set.hpp"
#include "Algorithm/Event.h"
#include "Algorithm/Integer.h"
#include "Algorithm/Decimal.h"
#include "Algorithm/Series.hpp"

using namespace code_learning;

int main(int argc, char *argv[]) {
	{
#include "Algorithm/Probability.h"
		srand(time(0));
		const algorithm::SampleSpace S(10000);
		const algorithm::SampleSpace S2(10000);
		const algorithm::SampleSpace S3(10000);
		const algorithm::SampleSpace S4(10000);
		const algorithm::SampleSpace S5(10000);
		const algorithm::Event A(rand() % 10000 + 1, S);
		const algorithm::Event B(rand() % 10000 + 1, S);
		const algorithm::Event C(!B);
		const algorithm::Event D(rand() % 10000 + 1, S2);
		const algorithm::Event E(rand() % 10000 + 1, S3);
		const algorithm::Event F(rand() % 10000 + 1, S4);
		const algorithm::Event G(rand() % 10000 + 1, S5);
		const algorithm::Event K(rand() % 10000 + 1, S2);
		const algorithm::Event L(rand() % 10000 + 1, S3);

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

		const algorithm::Event &H = D & E;
		const algorithm::Event &I = F & G;
		const algorithm::Event &J = E & F;
		const algorithm::Event &M = K & L;
		
		BOOST_ASSERT(P(H) == 1 - P(!H) && "Composite Events--1");
		
		BOOST_ASSERT(P(A + A) == P(A) && "Composite Events--2");
		BOOST_ASSERT(P(H + H) == P(H) && "Composite Events--3");
		BOOST_ASSERT(P(A + H) == P(A)*P(H) && "Composite Events--4");
		BOOST_ASSERT(P(A + H) == P(A)*P(D)*P(E) && "Composite Events--5");
		BOOST_ASSERT(P(H + A) == P(A)*P(H) && "Composite Events--6");
		BOOST_ASSERT(P(H + A) == P(A)*P(D)*P(E) && "Composite Events--7");

		BOOST_ASSERT(P(A - A) == 0 && "Composite Events--8");
		BOOST_ASSERT(P(H - H) == 0 && "Composite Events--9");
		BOOST_ASSERT(P(H - D) == P(H) - P(D)*P(E) && "Composite Events--10");
		BOOST_ASSERT(P(H - D) == P(D - D)*P(E) && "Composite Events--11");
		BOOST_ASSERT(P(H - F) == P(H)*P(!F) && "Composite Events--12");
		BOOST_ASSERT(P(H - I) == P(H)*P(!F)*P(!G) && "Composite Events--13");
		BOOST_ASSERT(P(H - J) == 0 && "Composite Events--14");


		BOOST_ASSERT(P(A & A) == P(A) && "Composite Events--15");
		BOOST_ASSERT(P(H & H) == P(H) && "Composite Events--16");
		BOOST_ASSERT(P(H & D) == P(H) && "Composite Events--17");
		BOOST_ASSERT(P(H & F) == P(H)*P(F) && "Composite Events--18");
		BOOST_ASSERT(P(H & I) == P(H)*P(I) && "Composite Events--19");
		BOOST_ASSERT(P(H & J) == P(D)*P(E)*P(F) && "Composite Events--20");

		BOOST_ASSERT(P(A | A) == 1 && "Composite Events--21");
		BOOST_ASSERT(P(H | H) == 1 && "Composite Events--22");
		BOOST_ASSERT(P(H | M) == P(H&M) / P(M) && "Composite Events--23");
		
		std::cout << algorithm::Series<algorithm::Integer>(
			[](const uint64_t index) {
			return algorithm::Integer(index);
		}).Summation(100).GetString() << std::endl;

		std::cout << algorithm::Series<algorithm::Fraction>(
			[](const uint64_t index) {
			if (0 == index%2) {
				return algorithm::Fraction(algorithm::Integer(4,false), index * 2 - 1);
			}
			else {
				return algorithm::Fraction(4, index * 2 - 1);
			}
		}).Summation(20).GetMonomial().SetDecimal(true).GetString() << std::endl;

		std::cout << algorithm::Series<algorithm::Decimal>(
			[](const uint64_t index) {
			if (0 == index % 2) {
				return algorithm::Fraction(algorithm::Integer(4, false), index * 2 - 1);
			}
			else {
				return algorithm::Fraction(4, index * 2 - 1);
			}
		}).Summation(100).GetMonomial().GetString() << std::endl;

		std::cout << algorithm::Series<algorithm::Fraction>(
			[](const uint64_t index) {
			return algorithm::Fraction(1, !algorithm::Integer(index - 1));
		}).Summation(20).GetMonomial().SetDecimal(true).GetString() << std::endl;
	}
	statistics::CodeLearning student("CPP");
	student.SetSplits(' ', '\n', '\r', '\t', ';', ',');
	student.SetIgnores(' ', '\n', '\r', '\t');
	code::SourcePath samples(".");
	samples.AddSuffixNames(".h", ".hpp", ".cpp", ".cc", ".cxx", ".c++", ".cp", ".c");
	student.StartLearning(samples);
	code::Code code("int main(){return 0;}");
	student.StartLearning(code);
	
	student.Display(argc, argv);
	
	return 0;
}