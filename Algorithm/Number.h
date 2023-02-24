#ifndef __CODE_LEARNING_ALGORITHM_NUMBER_H__
#define __CODE_LEARNING_ALGORITHM_NUMBER_H__

#include <string>

namespace code_learning {

	namespace algorithm {

		class Number {
		public:
			virtual const std::string GetString() = 0;
		};

	}

}

#endif