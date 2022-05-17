// Package tokens contains the definitions for all gecko symbols/tokens
package main

import (
	"github.com/alecthomas/participle/lexer"
)

type baseToken struct {
	Pos   lexer.Position
	RefID string
}

// File tokens

type File struct {
	PackageName string   `parser:"['package' @Ident]"`
	Entries     []*Entry `parser:"@@*"`
	Imports     []*File
	Name        string
}

type Entry struct {
	baseToken
	CCode      string      `parser:"@CCode"`
	Return     *Literal    `parser:"| 'return' @@"`
	Assignment *Assignment `parser:"| @@"`
	ElseIf     *ElseIf     `parser:"| @@"`
	Else       *Else       `parser:"| @@"`
	If         *If         `parser:"| @@"`
	FuncCall   *FuncCall   `parser:"| @@"`
	Method     *Method     `parser:"| @@"`
	Class      *Class      `parser:"| @@"`
	Type       *Type       `parser:"| @@"`
	Schema     *Schema     `parser:"| @@"`
	Enum       *Enum       `parser:"| @@"`
	Field      *Field      `parser:"| @@"`
	Loop       *Loop       `parser:"| @@"`
	Import     string      `parser:"| 'import' @Ident"`
}

// Class tokens

type Class struct {
	baseToken
	Visibility string             `parser:"[ @'private' | @'public' | @'protected' ]"`
	Name       string             `parser:"'class' @Ident"`
	Extends    []string           `parser:"[ 'extends' @Ident { ',' @Ident } ]"`
	Fields     []*ClassBlockField `parser:"'{' { @@ } '}'"`
}

type ClassBlockField struct {
	baseToken
	Method *Method `parser:"@@"`
	Field  *Field  `parser:"| @@"`
}

type ClassField struct {
	baseToken
	Field
}

type ClassMethod struct {
	baseToken
	Method
}

// Conditionals

type If struct {
	baseToken
	Expression *Expression `parser:"'if' '(' @@ ')'"`
	Value      []*Entry    `parser:"'{' { @@ } '}'"`
}

type ElseIf struct {
	baseToken
	Expression *Expression `parser:"'elif' '(' @@ ')'"`
	Value      []*Entry    `parser:"'{' { @@ } '}'"`
}

type Else struct {
	baseToken
	Value []*Entry `parser:"'else' '{' { @@ } '}'"`
}

// Expressions

type Expression struct {
	baseToken
	Equality *Equality `parser:"@@"`
}

type Equality struct {
	baseToken
	Comparison *Comparison `parser:"@@"`
	Op         string      `parser:"[ @( '!' '=' | '=' '=' )"`
	Next       *Equality   `parser:"  @@ ]"`
}

type Comparison struct {
	baseToken
	Addition *Addition   `parser:"@@"`
	Op       string      `parser:"[ @( '>' | '>' '=' | '<' | '<' '=' )"`
	Next     *Comparison `parser:"  @@ ]"`
}

type Addition struct {
	baseToken
	Multiplication *Multiplication `parser:"@@"`
	Op             string          `parser:"[ @( '-' | '+' )"`
	Next           *Addition       `parser:"  @@ ]"`
}

type Multiplication struct {
	baseToken
	Unary *Unary          `parser:"@@"`
	Op    string          `parser:"[ @( '/' | '*' )"`
	Next  *Multiplication `parser:"  @@ ]"`
}

type Unary struct {
	baseToken
	Op      string   `parser:"  ( @( '!' | '-' | '+' )"`
	Unary   *Unary   `parser:"    @@ )"`
	Primary *Primary `parser:"| @@"`
}

type Primary struct {
	baseToken
	FuncCall      *FuncCall   `parser:"@@"`
	Bool          string      `parser:"| ( @'true' | @'false' )"`
	Nil           *bool       `parser:"| @'nil'"`
	String        string      `parser:"| @String"`
	Symbol        string      `parser:"| @Ident"`
	Number        string      `parser:"| @Number"`
	SubExpression *Expression `parser:"| '(' @@ ')'"`
}

// Misc TODO: Sort

type Enum struct {
	baseToken
	Name  string   `parser:"'enum' @Ident"`
	Cases []string `parser:"'{' { @Ident } '}'"`
}

type Schema struct {
	baseToken
	Fields []*Field `parser:"'schema' '{' { @@ } '}'"`
}

type Type struct {
	baseToken
	Visibility string       `parser:"[ @'private' | @'public' | @'protected' ]"`
	Name       string       `parser:"'type' @Ident"`
	Implements string       `parser:"[ 'implements' @Ident ]"`
	Fields     []*TypeField `parser:"'{' { @@ } '}'"`
}

type Field struct {
	baseToken
	Visibility string   `parser:"[ @'private' | @'public' | @'protected' | @'external' ]"`
	Name       string   `parser:"@Ident"`
	Type       *TypeRef `parser:"':' @@"`
	Value      *Literal `parser:"[ '=' @@ ]"`
}

type Assignment struct {
	baseToken
	Name  string   `parser:"@Ident"`
	Value *Literal `parser:"'=' @@"`
}

type TypeField struct {
	baseToken
	Name      string   `parser:"@Ident"`
	Arguments []*Value `parser:"[ '(' [ @@ { ',' @@ } ] ')' ]"`
	Type      *TypeRef `parser:"':' @@"`
	Value     *Literal `parser:"[ '=' @@ ]"`
}

type Method struct {
	baseToken
	Visibility string   `parser:"[ @'private' | @'public' | @'protected' | @'external' ]"`
	Name       string   `parser:"'func' @Ident"`
	Arguments  []*Value `parser:"'(' [ @@ { ',' @@ } ] ')'"`
	Type       *TypeRef `parser:"[ ':' @@ ]"`
	Value      []*Entry `parser:"[ '{' @@* '}' ]"`
}

type Value struct {
	baseToken
	External bool     `parser:"[ @'external' ]"`
	Name     string   `parser:"@Ident"`
	Type     *TypeRef `parser:"':' @@"`
	Default  *Literal `parser:"[ '=' @@ ]"`
}

type Argument struct {
	baseToken
	Name  string   `parser:"[ @Ident ':' ]"`
	Value *Literal `parser:"@@"`
}

type TypeRef struct {
	baseToken
	Array       *TypeRef `parser:"(   '[' @@ ']'"`
	Type        string   `parser:"  | @Ident )"`
	NonNullable bool     `parser:"[ @'!' ]"`
	Pointer     bool     `parser:"[ @'*']"`
}

type Literal struct {
	baseToken
	FuncCall   *FuncCall         `parser:"( @@"`
	Bool       string            `parser:" | @( 'true' | 'false' )"`
	Nil        *bool             `parser:" | @'nil'"`
	Expression *Expression       `parser:" | @@"`
	String     string            `parser:" | @String"`
	Symbol     string            `parser:" | @Ident"`
	Number     string            `parser:" | @Number"`
	Object     []*ObjectKeyValue `parser:" | '{' [ @@ { ',' @@ } ] '}'"`
	Array      []*Literal        `parser:" | '[' [ @@ { ',' @@ } ] ']' )"`
	ArrayIndex *Literal          `parser:"[ '[' @@ ']' ]"`
}

type FuncCall struct {
	baseToken
	Function  string      `parser:"@Ident"`
	Arguments []*Argument `parser:"'(' [ @@ { ',' @@ } ] ')'"`
}

type Object struct {
	baseToken
}

type ObjectKeyValue struct {
	baseToken
	Key   string   `parser:"@Ident ':'"`
	Value *Literal `parser:"@@"`
}

type Loop struct {
	baseToken
	For           string      `parser:"'for'"`
	ForOf         *ForOfLoop  `parser:"( @@"`
	ForIn         *ForInLoop  `parser:" | @@"`
	ForExpression *Expression `parser:" | @@ )"`
	Value         []*Entry    `parser:" '{' @@* '}' "`
}

type ForOfLoop struct {
	baseToken
	Variable    *Field   `parser:"@@ 'of'"`
	SourceArray *Literal `parser:"@@"`
}

type ForInLoop struct {
	baseToken
	Variable    *Field   `parser:"@@ 'in'"`
	SourceArray *Literal `parser:"@@"`
}
