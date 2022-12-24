#ifndef __CODE_LEARNING_WORD_H__
#define __CODE_LEARNING_WORD_H__

#include <string>
#include "WordType.h"

namespace code_learning {

	class Config;

	class Word {
	public:
		explicit Word(const std::string &content, const Config &cfg);
		const std::string &GetContent()const;
		WORD_TYPE GetType() const;
		virtual void Sort();
		static WORD_TYPE JudgeWordType(const std::string &content);
	protected:
		const std::string m_content;
		WORD_TYPE m_type = WORD_TYPE_NONE;
	};

}

#endif