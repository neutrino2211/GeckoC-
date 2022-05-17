package main

/*
#include <stdio.h>
*/
import "C"
import (
	"strings"

	"github.com/alecthomas/participle"
	"github.com/alecthomas/participle/lexer"
	"github.com/alecthomas/participle/lexer/ebnf"
	"github.com/alecthomas/repr"
)

var graphQLLexer = lexer.Must(ebnf.New(`
Comment = "//"  { "\u0000"…"\uffff"-"\n" } .
CCode = "#"  { "\u0000"…"\uffff"-"\n" } .
Ident = (alpha | "_" | ".") { "_" | "." | alpha | digit } .
SingleQuoteString = "'" [ { "\u0000"…"\uffff"-"\""-"\\" | "\\" any } ] "'" .
String = "\"" [ { "\u0000"…"\uffff"-"\""-"\\" | "\\" any } ] "\"" .
Number = ( digit | "0x" | "." | "_" ) { digit | "." | "_" } .
Whitespace = " " | "\t" | "\n" | "\r" .
Digit = digit .
Punct = "!"…"/" | ":"…"@" | "["…` + "\"`\"" + ` | "{"…"~" .
alpha = "a"…"z" | "A"…"Z" .
digit = "0"…"9" .
EOL = ( "\n" | "\r" ) { "\n" | "\r" } .
any = "\u0000"…"\uffff" .
`))
var parser = participle.MustBuild(
	&Expression{},
	participle.UseLookahead(2),
	participle.Lexer(graphQLLexer),
	participle.Elide("Comment", "Whitespace"),
)

//export GoParser
func GoParser(in *C.char) {
	input := C.GoString(in)
	exp := &Expression{}
	parser.Parse(strings.NewReader(input), exp)

	repr.Println(exp)
	println("yo!!!!!!")
}

func main() {}
