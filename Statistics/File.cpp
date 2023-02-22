#include "Glob.h"
#include "Code/SourceFile.h"
#include "File.h"

namespace code_learning {
	namespace statistics {
		File::File(const std::string &content, Glob &glob):
			Code(content, glob){
		}

		void File::Statistics(const code::Element &element) {
			const code::SourceFile &file = dynamic_cast<const code::SourceFile &>(element);
			if (m_glob.m_board) {
				m_glob.m_board->UpdateProcessingPath(file.m_parent);
				m_glob.m_board->UpdateProcessingCodes(file.m_file_name);
			}
			Code::Statistics(element);
		}
	}
}