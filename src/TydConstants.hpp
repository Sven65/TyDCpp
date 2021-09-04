#ifndef H_TYD_CONSTANTS
#define H_TYD_CONSTANTS

#include <string>

namespace Tyd {
	namespace Constants {
		//Constants - public
		static std::string		TydFileExtension        = ".tyd";

		//Constants - internal
		const char     			CommentChar             = '#';
		const char     			RecordEndChar           = ';';

		const char     			AttributeStartChar      = '*';
		const std::string   	HandleAttributeName     = "handle";
		const std::string   	SourceAttributeName     = "source";
		const std::string   	AbstractAttributeName   = "abstract";
		const std::string   	NoInheritAttributeName  = "noinherit";

		const char     			TableStartChar          = '{';
		const char     			TableEndChar            = '}';
		const char     			ListStartChar           = '[';
		const char    			ListEndChar             = ']';
		
		const std::string   	SymbolChars             = "_-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		const std::string   	NullValueString         = "null";
	};
};

#endif
