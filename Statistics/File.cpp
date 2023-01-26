#include "Glob.h"
#include "Code/SourceFile.h"
#include "File.h"

namespace code_learning {
	namespace statistics {
		File::File(const std::string &content, Glob &glob):
			Code(content, glob){
		}

		void File::Statistics(const code::Element &element) {
			Code::Statistics(element);
			const code::SourceFile &file = dynamic_cast<const code::SourceFile &>(element);
			m_glob.m_board.UpdateProcessing(file.m_file_name);
		}
	}
}