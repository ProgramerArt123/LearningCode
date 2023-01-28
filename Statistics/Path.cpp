#include "Glob.h"
#include "Code/SourcePath.h"
#include "Path.h"

namespace code_learning {
	namespace statistics {
		Path::Path(const std::string &content, Glob &glob):
			File(content, glob){

		}
		void Path::Statistics(const code::Element &element) {
			Region::Statistics(element);
		}

		std::shared_ptr<statistics::Element> Path::CreateStatistic(const code::Element &element, Glob &glob) {
			switch (element.GetType())
			{
			case code::ELEMENT_TYPE_PATH:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Path>, "Path invalid");
				return std::shared_ptr<statistics::Element>(new statistics::Path(element.GetContent(), glob));
				break;
			case code::ELEMENT_TYPE_FILE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::File>, "File invalid");
				return std::shared_ptr<statistics::Element>(new statistics::File(element.GetContent(), glob));
				break;
			case code::ELEMENT_TYPE_CODE:
				static_assert(std::is_base_of_v<statistics::Element, statistics::Code>, "Code invalid");
				return std::shared_ptr<statistics::Element>(new statistics::Code(element.GetContent(), glob));
				break;
			default:
				throw "error source";
				break;
			}
		}
	}
}