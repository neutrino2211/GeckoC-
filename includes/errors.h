#ifndef G_ERRORS_H
#define G_ERRORS_H

#include "lexer.h"

namespace Gecko {
    namespace Error {
        enum ExitCodes {
            CommandLineParseError = 40,
            SourceFileParsingError,
            KeywordValidationError
        };

        class Scope {
            const char* mScope = "";
            public:
            Scope(const char* scope);
            void raise(ExitCodes code, const char* message, const char* errorType);
            void raise(ExitCodes code, const char* message, const char* errorType, Gecko::lexer_node_t* node);
        };
    }
}

#endif