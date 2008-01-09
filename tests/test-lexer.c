
#include <st-lexer.h>

#include <glib.h>
#include <stdio.h>
#include <stdbool.h>

static const char * const token_names[] =
{
	"TOKEN_INVALID",
	"TOKEN_LPAREN",
	"TOKEN_RPAREN",
	"TOKEN_BLOCK_BEGIN",
	"TOKEN_BLOCK_END",
	"TOKEN_COMMA",
	"TOKEN_SEMICOLON",
	"TOKEN_PERIOD",
	"TOKEN_RETURN",
	"TOKEN_COLON",
	"TOKEN_ASSIGN",
	"TOKEN_ARRAY_BEGIN",
	"TOKEN_IDENTIFIER",
	"TOKEN_CHAR_CONST", 
	"TOKEN_STRING_CONST",
	"TOKEN_NUMBER_CONST",
	"TOKEN_SYMBOL_CONST",
	"TOKEN_COMMENT",
	"TOKEN_BINARY_SELECTOR",
	"TOKEN_KEYWORD_SELECTOR",
	"TOKEN_EOF",
};

static void
print_token (GooLexer *lexer, GooLexerToken *token)
{
	GooTokenType type;
	
	char *string;

	GooLexerError *error;
	type = st_lexer_token_type (token);

	switch (type) {


	// tokens string values	
	case ST_TOKEN_COMMENT:
	case ST_TOKEN_IDENTIFIER:
	case ST_TOKEN_STRING_CONST:	
	case ST_TOKEN_SYMBOL_CONST:
	case ST_TOKEN_NUMBER_CONST:
	case ST_TOKEN_KEYWORD_SELECTOR:
	case ST_TOKEN_BINARY_SELECTOR:
	case ST_TOKEN_CHAR_CONST:

		string =  st_lexer_token_text (token);
		
		printf ("%s (%i:%i: \"%s\")\n", token_names[type],
			st_lexer_token_line (token),
			st_lexer_token_column (token),
			string);			 
		break;
		
	// Invalid Token;
	case ST_TOKEN_INVALID:
	
		error = st_lexer_last_error (lexer);
		
		printf ("%s\n", st_lexer_error_create_message (error));
		break;
		
		
	default:
		printf ("%s (%i:%i)\n", token_names[type],
			st_lexer_token_line (token),
			st_lexer_token_column (token));
		break;
	}
}


#define BUF_SIZE 20480

int
main (int argc, char *argv[])
{
	GooLexer      *lexer;
	GooLexerToken *token;
	
	/* read input from stdin */
	char buffer[BUF_SIZE];
	char c;
	int i=0;
	while ((c = getchar()) != EOF && i < (BUF_SIZE-1))
		buffer[i++] = c;
	buffer[i] = '\0';
	
	lexer = st_lexer_new (buffer);
	
	GooTokenType type;
			
	do {
	
		token = st_lexer_next_token (lexer);
		type = st_lexer_token_type (token);
		
		print_token (lexer, token);
	
	} while (type != ST_TOKEN_EOF);
	
	return 0;
}

