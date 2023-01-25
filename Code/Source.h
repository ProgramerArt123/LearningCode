#ifndef __CODE_LEARNING_CODE_SOURCE_H__
#define __CODE_LEARNING_CODE_SOURCE_H__

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <functional>

#include "Region.h"

namespace code_learning {
	class Glob;
	namespace code {
		class Element;
		class Source {
		public:
			virtual uint64_t Scan(const Glob &glob) = 0;
			virtual void Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const = 0;

			uint64_t m_file_count = 0;
		};
	}
}

#endif