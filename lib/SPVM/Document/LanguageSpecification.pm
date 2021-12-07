=encoding utf8

=head1 NAME

SPVM::Document::LanguageSpecification - SPVM Language Specification

=head1 DESCRIPTION

SPVM Language Specification.

=head1 SPVM LANGUAGE SPECIFICATION

=begin html

<ul>
  <li><a href="#language-c99">C99 Compliant</a></li>
  <li><a href="#language-token">Tokenizing</a></li>
  <li><a href="#language-parsing">Syntax Parsing</a></li>
  <li><a href="#language-comment">Comment</a></li>
  <li><a href="#language-pod">POD</a></li>
  <li><a href="#language-class">Class</a></li>
  <li><a href="#language-module">Module</a></li>
  <li><a href="#language-class-var">Class Variable</a></li>
  <li><a href="#language-field">Field</a></li>
  <li><a href="#language-method">Method</a></li>
  <li><a href="#language-enum">Enumeration</a></li>
  <li><a href="#language-begin-block">INIT Block</a></li>
  <li><a href="#language-local-var">Local Variable</a></li>
  <li><a href="#language-scope">Scope</a></li>
  <li><a href="#language-literal">Literal</a></li>
  <li><a href="#language-string">String</a></li>
  <li><a href="#language-undef">Undefined Value</a></li>
  <li><a href="#language-array">Array</a></li>
  <li><a href="#language-mulnum">Multi Numeric Value</a></li>
  <li><a href="#language-mulnum-array">Multi Numeric Array</a></li>
  <li><a href="#language-ref">Reference</a></li>
  <li><a href="#language-expression">Expression</a></li>
  <li><a href="#language-operator">Operator</a></li>
  <li><a href="#language-statement">Statement</a></li>
  <li><a href="#language-type">Type</a></li>
  <li><a href="#language-type-inference">Type Inference</a></li>
  <li><a href="#language-type-compatible">Type Compatibility</a></li>
  <li><a href="#language-type-convertion">Type Conversion</a></li>
  <li><a href="#language-exception">Exception</a></li>
  <li><a href="#language-garbage-collection">Garbage Collection</a></li>
  <li><a href="#language-callback">Callback</a></li>
  <li><a href="#language-weak-ref">Weaken Reference</a></li>
  <li><a href="#language-default-loaded-modules">Default loaded modules</a></li>
</ul>

<h2 id="language-c99">C99 Compliant</h2><!-- 2019/2/27 almost ok-->
<ul>
  <li><a href="#language-c99-spec">C99 Compliant compiler and runtime</a>
  <li><a href="#language-c99-type">SPVM types correspondence with C99 Types</a>
</ul>

<h3 id="language-c99-spec">C99 Compliant compiler and runtime</h3><!-- 2021-02-08 updated -->

The source code of the SPVM compiler and SPVM runtime is written in C99.

Note that this does not mean that SPVM cannot bind the functions of C specific versions(C11, GUN99, GNU11, etc.) or bind the functions of specific C++ versions.

SPVM can bind any functions of C specific versions or C++ specific versions, and even can bind the functions of CUDA/GPGPU nvcc.

This means that SPVM compiler and runtime must be C99 compliant.

<h3 id="language-c99-type">SPVM Types correspondence with C99 Types</h3><!-- 2019/2/27 almost ok-->

the following SPVM Types are exactly same as the following C99 Types:

<table>
  <tr>
    <th>
      <b>SPVM Type</b>
    </ th>
    <th>
      <b>C99 Type</b>
    </ th>
    <th>
      <b>Description</b>
    </ th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      int8_t
    </td>
    <td>
      SPVM <a href="#language-type-byte">byte Type</a> is same as C99 int8_t Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      int16_t
    </td>
    <td>
      SPVM <a href="#language-type-short">short Type</a> is same as the C99 int16_t Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      int32_t
    </td>
    <td>
      SPVM <a href="#language-type-int">int Type</a> is same as the C99 int32_t Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      int64_t
    </td>
    <td>
      SPVM <a href="#language-type-long">long Type</a> is same as C99 int64_t Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      float
    </td>
    <td>
      SPVM <a href="#language-Type-float">float Type</a> is same as the C99 float Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      double
    </td>
    <td>
      SPVM <a href="#language-Type-double">double Type</a> is same as C99 double Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>Object Type</b>
    </td>
    <td>
      void*
    </td>
    <td>
      SPVM <a href="#language-Type-object">Object Type</a> is same as the C99 void* Type.
    </td>
  </tr>        
  <tr>
    <td>
      <b>Multiple Numeric Type</b>
    </td>
    <td>
      Numeric Array Type that is same as the Type and length in SPVM multiple Numeric Type fields
    </td>
    <td>
      <p>
        For example, if SPVM <a href="#language-Type-multi-numeric">multiple Numeric Type</a>
      </p>
      <p>
        <b>class Point_2i: mulnum_t {has x: int; has y: int;}</b>
      </p>
      <p>
        matches the Type declared in C99
      </p>
      <p>
        <b>int32_t var[2];</b>
      </p>
    </td>
  </tr>
</table>

<h2 id="language-token">Tokenizing</h2>

This topic specifies the Tokenizing of the SPVM language.

<ul>
  <li><a href="#language-token-lalr">LALR(1)</a>
  <li><a href="#language-token-charset">Character Set</a>
  <li><a href="#language-token-component">Component</a>
  <li><a href="#language-token-line-terminator">Line Terminater</a>
  <li><a href="#language-token-space-character">Space Character</a>
  <li><a href="#language-token-identifier">Identifiers</a>
  <li><a href="#language-token-separator">Separator</a></li>
  <li><a href="#language-token-separator-fat-comma">Fat Comma</a></li>
  <li><a href="#language-token-operator">Operator</a>
  <li><a href="#language-token-syntax-definition">Syntax Definition</a></li>
</ul>

<h3 id="language-token-lalr">LALR(1)</h3><!-- 2019/2/27 almost ok-->

SPVM language can be analyzed by the LALR(1). It can be parsed by the parser generator generated by yacc/bison.

<h3 id="language-token-lalr">Character Set</h3>

SPVM programs are written in UTF-8.

<h3 id="language-token-component">Component</h3><!-- 2019/2/27 almost ok-->

Component in SPVM is <a href="#language-token-space-character">Space Character</a>,<a href="#language-comment">Comment</a>, <a href="#language-pod">POD</a>, <a href="#language-literal">Literal</a>, <a href="#language-token-identifier">Identifier</a>, <a href="#language-token-keyword">Keyword</a>, <a href="#language-token-separator">Separator</a>, or <a href="#language-token-operator">Operator</a>.

<h3 id="language-token-line-terminator">Line Terminator</h3><!-- 2019/7/1 check-->

Line Terminator in SPVM are ASCII Code "LF", "CR", "CRLF".

When a line terminator appears, the line number is incremented.Line Terminator in a program is converted to ASCII Code "LF".

<h3 id="language-token-space-character">Space Character</h3><!-- 2019/2/27 almost ok-->

Space Character in SPVM is ASCII Code "SP", "HT", "FF" or <a href="#language-token-line-terminator">Line Terminator</a>.

Space Character has no meaning in the program execution.

<h3 id="language-token-identifier">Identifiers</h3><!-- 2019/2/27 maybe ok-->

Identifiers in SPVM are <a href="#language-token-identifier-class-name">Class Name</a>, <a href="#language-token-identifier-sub-name">Method Name</a>, <a href="#language-token-identifier-field-name">Field Name</a>, <a href="#language-token-identifier-class-var-name">Class Variable Name</a>, and <a href="#language-token-identifier-local-var-name">Local Variable Name</a>.

<h3 id="language-token-identifier-class-name">Class Name</h3><!-- 2021-02-08 updated -->

Class Name is one or more alphabet(a-zA-Z), number(0-9), underscore(_) or "::" of ASCII Code.

The part name of Class name must start uppercase letter. Part name of Class name means "Foo", "Bar", "Baz" in Class Name "Foo:Bar::Baz".

"::" cannot be continued twice. Last characters cannot end with "::".

Underscore "_" cannot be continued twice.

Class Name must be corresponding to the relative name of module file. If Class Name is "Foo::Bar::Baz", the relative name of module file must be "SPVM/Foo/Bar/Baz.spvm".

If Class Name is invalid, Compile Error occurs.

<b>Valid Class Name Examples</b>

<pre>
Foo
Foo::Bar
Foo::Bar::Baz3
Foo::bar
Foo_Bar::Baz_Baz
</pre>

<b>Invalid Class Name Examples</b>

<pre>
Foo
Foo::::Bar
Foo::Bar::
Foo__Bar
Foo::bar
</pre>

<h3 id="language-token-identifier-sub-name">Method Name</h3><!-- 2019/2/27 almost ok-->

Method Name is one or more alphabet(a-zA-Z), number(0-9), or underscore(_) of ASCII Code.

First character must not number character.

Underscore cannot be continued twice.

<pre>
# Valid Method Name
FOO
FOO_BAR3
foo
foo_bar
_foo
_foo_bar_

# Invalid Method Name
foo__bar
</pre>

<h3 id="language-token-identifier-field-name">Field Name</h3><!-- 2019/2/27 almost ok-->

Field Name is one or more alphabet(a-zA-Z), number(0-9), or underscore(_) of ASCII Code.

First character must not number character.
  
Underscore cannot be continued twice.

<pre>
# Valid Field Name
FOO
FOO_BAR3
foo
foo_bar
_foo
_foo_bar_

# Invalid Field Name
3foo
foo__bar
</pre>

<h3 id="language-token-identifier-class-var-name">Class Variable Name</h3><!-- 2019/2/27 maybe ok-->

Class Variable Name starts with "$", followed more alphabet(a-zA-Z), number(0-9), underscore(_) or "::" of ASCII Code.

Followed character must not start with number.

"::" cannot be continued twice. Last characters cannot end with "::".

Underscore cannot be continued twice.

<pre>
# Valid Class Variable Name
$FOO::BAR
$Foo::Bar3
$FOO
$FOO_BAR
$foo

# Invalid Class Variable Name
$FOO__BAR
$3FOO
</pre>

<h3 id="language-token-identifier-local-var-name">Local Variable Name</h3><!-- 2019/2/27 maybe ok-->

Local Variable Name starts with "$", followed more alphabet characters of ASCII Code.

Followed character must not start with number.

Underscore cannot be continued twice.

<pre>
# Valid Local Variable Name
$foo
$foo_bar3
$_foo
$FOO

# Invalid Local Variable Name
$foo__bar
$3foo
</pre>

<h3 id="language-token-keyword">Keywords</h3><!-- 2019/2/27 maybe ok-->

Keywords in SPVM are the followings.

<pre>
allow byte INIT case die warn print default double elsif else enum eq
eval for float gt ge has if callback_t isa int last break length
lt le long my native ne next new our object class private
public precompile pointer_t return require rw ro switch
sub string short scalar undef unless use void mulnum_t while
weaken wo __END__ __CLASS__ __FILE__ __LINE__
</pre>

<h3 id="language-token-separator">Separators</h3><!-- 2019/2/27 almost ok-->

Separators in SPVM are the followings.

<pre>
( ) { } [ ] ; , ->=>
</pre>

<h3 id="language-token-separator-fat-comma">Fat Comma</h3>

Fat Comma is a <a href="#language-token-separator">Separator</a> represented by "<b>=></b>".

<pre>
=>
</pre>

Fat Comma is an alias for Comma "<b>,</b>". Wherever you can use "<b>,</b>" you can use Fat Comma instead.

<pre>
# Comma
["a", "b", "c", "d"]

# Use Fat Comma instead of Comma
["a" => "b", "c" => "d"]
</pre>


Identifiers other than <a href="#language-token-identifier-class-var-name">Class Variable Name</a> and <a href="#language-token-identifier-local-var-name">Local Variable Name</a> placed on the Left of Fat Comma are treated as <a href="#language-literal-string">String Literal</a>.

<pre>
# Identifiers placed on the Left of Fat Comma are treated as String Literal
# a is "a", c is "c"
[a => "b", c => "d"]
</pre>

<h3 id="language-token-operator">Operators</h3>

Operators in SPVM are the followings.

<pre>
=   >   <   !   ~
==  <=  >=  !=  <=> &&  || ++ --
+   -   *   /   &   |   ^   %   <<   >>   >>>
+=  -=  *=  /=  &=  |=  ^=  %=  <<=  >>=  >>>=
\   $  @   .   .=
cmp length isa ref
</pre>

<h2 id="language-parsing">Syntax Parsing</h2>

<h3 id="language-parsing-syntax-definition">Syntax Parsing Definition</h3><!-- 2019/2/27 not ok-->

The following is Syntax Parsing Definition in SPVM, using the syntax in yacc/bison. 

<pre>
%token <opval> CLASS HAS METHOD OUR ENUM MY USE REQUIRE ALLOW
%token <opval> DESCRIPTOR
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
%token <opval> NAME VAR_NAME CONSTANT EXCEPTION_VAR
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE
%token <opval> DOT3 FATCAMMA RW RO WO INIT NEW
%token <opval> RETURN WEAKEN DIE WARN CURRENT_CLASS UNWEAKEN '[' '{' '('

%type <opval> grammar
%type <opval> opt_classes classes class class_block
%type <opval> opt_declarations declarations declaration
%type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
%type <opval> sub cb_obj opt_args args arg has use require our
%type <opval> opt_descriptors descriptors method_names opt_method_names
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement switch_statement case_statement default_statement
%type <opval> block eval_block begin_block switch_block if_require_statement
%type <opval> unary_op binary_op comparison_op isa logical_op  expression_or_logical_op
%type <opval> call_method opt_vaarg
%type <opval> array_access field_access weaken_field unweaken_field isweak_field convert array_length
%type <opval> assign inc dec allow
%type <opval> new array_init
%type <opval> my_var var
%type <opval> expression opt_expressions expressions opt_expression case_statements
%type <opval> field_name method_name
%type <opval> type basic_type array_type array_type_with_length ref_type type_or_void

%right <opval> ASSIGN SPECIAL_ASSIGN
%left <opval> LOGICAL_OR
%left <opval> LOGICAL_AND
%left <opval> BIT_OR BIT_XOR
%left <opval> '&'
%nonassoc <opval> NUMEQ NUMNE STREQ STRNE
%nonassoc <opval> NUMGT NUMGE NUMLT NUMLE STRGT STRGE STRLT STRLE ISA NUMERIC_CMP STRING_CMP
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> MULTIPLY DIVIDE REMAINDER
%right <opval> LOGICAL_NOT BIT_NOT '@' REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT REFOP DUMP
%nonassoc <opval> INC DEC
%left <opval> ARROW

%%

grammar
  : opt_classes

opt_classes
  : /* Empty */
  | classes

classes
  : classes class
  | class

class
  : CLASS basic_type class_block
  | CLASS basic_type ':' opt_descriptors class_block
  | CLASS basic_type ';'
  | CLASS basic_type ':' opt_descriptors ';'

class_block
  : '{' opt_declarations '}'

opt_declarations
  : /* Empty */
  | declarations

declarations
  : declarations declaration
  | declaration

declaration
  : has
  | sub
  | enumeration
  | our ';'
  | use
  | allow
  | begin_block

begin_block
  : INIT block

use
  : USE basic_type ';'
  | USE basic_type '(' opt_method_names ')' ';'

require
  : REQUIRE basic_type

allow
  : ALLOW basic_type ';'

enumeration
  : opt_descriptors ENUM enumeration_block

enumeration_block 
  : '{' opt_enumeration_values '}'

opt_enumeration_values
  : /* Empty */
  | enumeration_values

enumeration_values
  : enumeration_values ',' enumeration_value 
  | enumeration_values ','
  | enumeration_value

enumeration_value
  : method_name
  | method_name ASSIGN CONSTANT

our
  : OUR CLASS_VAR_NAME ':' opt_descriptors type

has
  : HAS field_name ':' opt_descriptors type ';'

sub
  : opt_descriptors METHOD method_name ':' type_or_void '(' opt_args opt_vaarg')' block
  | opt_descriptors METHOD method_name ':' type_or_void '(' opt_args opt_vaarg')' ';'

cb_obj
  : opt_descriptors METHOD ':' type_or_void '(' opt_args opt_vaarg')' block
  | '[' args ']' opt_descriptors METHOD ':' type_or_void '(' opt_args opt_vaarg')' block

opt_args
  : /* Empty */
  | args

args
  : args ',' arg
  | args ','
  | arg

arg
  : var ':' type

opt_vaarg
  : /* Empty */
  | DOT3

opt_descriptors
  : /* Empty */
  | descriptors

descriptors
  : descriptors DESCRIPTOR
  | DESCRIPTOR

opt_statements
  : /* Empty */
  | statements

statements
  : statements statement 
  | statement

statement
  : if_statement
  | for_statement
  | while_statement
  | block
  | switch_statement
  | case_statement
  | default_statement
  | eval_block
  | if_require_statement
  | expression ';'
  | LAST ';'
  | NEXT ';'
  | RETURN ';'
  | RETURN expression ';'
  | DIE ';'
  | DIE expression ';'
  | WARN ';'
  | WARN expression ';'
  | PRINT expression ';'
  | weaken_field ';'
  | unweaken_field ';'
  | ';'

for_statement
  : FOR '(' opt_expression ';' expression_or_logical_op ';' opt_expression ')' block

while_statement
  : WHILE '(' expression_or_logical_op ')' block

switch_statement
  : SWITCH '(' expression ')' switch_block

switch_block
  : '{' case_statements '}'
  | '{' case_statements default_statement '}'

case_statements
  : case_statements case_statement
  | case_statement

case_statement
  : CASE expression ':' block
  | CASE expression ':'

default_statement
  : DEFAULT ':' block
  | DEFAULT ':'

if_require_statement
  : IF '(' require ')' block
  | IF '(' require ')' block ELSE block

if_statement
  : IF '(' expression_or_logical_op ')' block else_statement
  | UNLESS '(' expression_or_logical_op ')' block else_statement

else_statement
  : /* NULL */
  | ELSE block
  | ELSIF '(' expression_or_logical_op ')' block else_statement

block 
  : '{' opt_statements '}'

eval_block
  : EVAL block ';'

opt_expressions
  : /* Empty */
  | expressions

opt_expression
  : /* Empty */
  | expression

expression_or_logical_op
  : expression
  | logical_op

expression
  : var
  | EXCEPTION_VAR
  | class_var_access
  | CONSTANT
  | UNDEF
  | call_method
  | field_access
  | array_access
  | convert
  | new
  | array_init
  | array_length
  | my_var
  | binary_op
  | unary_op
  | assign
  | inc
  | dec
  | '(' expressions ')'
  | CURRENT_CLASS
  | isweak_field
  | comparison_op
  | isa
  | TRUE
  | FALSE

expressions
  : expressions ',' expression
  | expressions ','
  | expression

unary_op
  : '+' expression %prec PLUS
  | '-' expression %prec MINUS
  | BIT_NOT expression
  | REFCNT var
  | REFOP expression
  | STRING_LENGTH expression
  | DUMP expression
  | DEREF var
  | REF var

inc
  : INC expression
  | expression INC

dec
  : DEC expression
  | expression DEC

binary_op
  : expression '+' expression
  | expression '-' expression
  | expression MULTIPLY expression
  | expression DIVIDE expression
  | expression REMAINDER expression
  | expression BIT_XOR expression
  | expression '&' expression
  | expression BIT_OR expression
  | expression SHIFT expression
  | expression '.' expression

comparison_op
  : expression NUMEQ expression
  | expression NUMNE expression
  | expression NUMGT expression
  | expression NUMGE expression
  | expression NUMLT expression
  | expression NUMLE expression
  | expression NUMERIC_CMP expression
  | expression STREQ expression
  | expression STRNE expression
  | expression STRGT expression
  | expression STRGE expression
  | expression STRLT expression
  | expression STRLE expression
  | expression STRING_CMP expression

isa
  : expression ISA type

logical_op
  : expression_or_logical_op LOGICAL_OR expression_or_logical_op
  | expression_or_logical_op LOGICAL_AND expression_or_logical_op
  | LOGICAL_NOT expression_or_logical_op
  | '(' logical_op ')'

assign
  : expression ASSIGN expression
  | expression SPECIAL_ASSIGN expression

new
  : NEW basic_type
  | NEW array_type_with_length
  | cb_obj

array_init
  : '[' opt_expressions ']'
  | '{' expressions '}'
  | '{' '}'

convert
  : '(' type ')' expression %prec CONVERT

array_access
  : expression ARROW '[' expression ']'
  | array_access '[' expression ']'
  | field_access '[' expression ']'

call_method
  : NAME '(' opt_expressions  ')'
  | basic_type ARROW method_name '(' opt_expressions  ')'
  | basic_type ARROW method_name
  | expression ARROW method_name '(' opt_expressions ')'
  | expression ARROW method_name
  | expression ARROW '(' opt_expressions ')'

field_access
: expression ARROW '{' field_name '}'
| field_access '{' field_name '}'
| array_access '{' field_name '}'

weaken_field
  : WEAKEN var ARROW '{' field_name '}'

unweaken_field
  : UNWEAKEN var ARROW '{' field_name '}'

isweak_field
  : ISWEAK var ARROW '{' field_name '}'

array_length
  : '@' expression
  | '@' '{' expression '}'
  | SCALAR '@' expression
  | SCALAR '@' '{' expression '}'

my_var
  : MY var ':' type
  | MY var

var
  : VAR_NAME

class_var_access
  : CLASS_VAR_NAME

type
  : basic_type
  | array_type
  | ref_type

basic_type
  : NAME
  | BYTE
  | SHORT
  | INT
  | LONG
  | FLOAT
  | DOUBLE
  | OBJECT
  | STRING

ref_type
  : basic_type '&'

array_type
  : basic_type '[' ']'
  | array_type '[' ']'

array_type_with_length
  : basic_type '[' expression ']'
  | array_type '[' expression ']'

type_or_void
  : type
  | VOID

field_name
  : NAME

method_name
  : NAME

opt_method_names
  : /* Empty */
  | method_names

method_names
  : method_names ',' method_name
  | method_names ','
  | method_name
%%
</pre>

The following is a correspondence table between tokens in yacc/bison and keywords and operators in SPVM.

<table>
  <tr>
    <th>Tokens in yacc/bison</th><th>Keywords and Operators in SPVM</th>
  </tr>
  <tr>
    <td>CLASS</td><td>class</td>
  </tr>
  <tr>
    <td>METHOD</td><td>sub</td>
  </tr>
  <tr>
    <td>OUR</td><td>our</td>
  </tr>
  <tr>
    <td>ENUM</td><td>enum</td>
  </tr>
  <tr>
    <td>MY</td><td>my</td>
  </tr>
  <tr>
    <td>SELF</td><td>self</td>
  </tr>
  <tr>
    <td>USE</td><td>use</td>
  </tr>
  <tr>
    <td>REQUIRE</td><td>require</td>
  </tr>
  <tr>
    <td>ALLOW</td><td>allow</td>
  </tr>
  <tr>
    <td>DESCRIPTOR</td><td>descriptor</td>
  </tr>
  <tr>
    <td>IF</td><td>if</td>
  </tr>
  <tr>
    <td>UNLESS</td><td>unless</td>
  </tr>
  <tr>
    <td>ELSIF</td><td>elsif</td>
  </tr>
  <tr>
    <td>ELSE</td><td>else</td>
  </tr>
  <tr>
    <td>FOR</td><td>for</td>
  </tr>
  <tr>
    <td>WHILE</td><td>while</td>
  </tr>
  <tr>
    <td>LAST</td><td>last</td>
  </tr>
  <tr>
    <td>BREAK</td><td>break</td>
  </tr>
  <tr>
    <td>NEXT</td><td>next</td>
  </tr>
  <tr>
    <td>SWITCH</td><td>switch</td>
  </tr>
  <tr>
    <td>CASE</td><td>case</td>
  </tr>
  <tr>
    <td>DEFAULT</td><td>default</td>
  </tr>
  <tr>
    <td>EVAL</td><td>eval</td>
  </tr>
  <tr>
    <td>NAME</td><td>name</td>
  </tr>
  <tr>
    <td>VAR</td><td>var</td>
  </tr>
  <tr>
    <td>CONSTANT</td><td>Literal</td>
  </tr>
  <tr>
    <td>CLASS_VAR_NAME</td><td>Class Variable Name</td>
  </tr>
  <tr>
    <td>EXCEPTION_VAR</td><td>$@</td>
  </tr>
  <tr>
    <td>UNDEF</td><td>undef</td>
  </tr>
  <tr>
    <td>VOID</td><td>void</td>
  </tr>
  <tr>
    <td>BYTE</td><td>byte</td>
  </tr>
  <tr>
    <td>SHORT</td><td>short</td>
  </tr>
  <tr>
    <td>INT</td><td>int</td>
  </tr>
  <tr>
    <td>LONG</td><td>long</td>
  </tr>
  <tr>
    <td>FLOAT</td><td>float</td>
  </tr>
  <tr>
    <td>DOUBLE</td><td>double</td>
  </tr>
  <tr>
    <td>STRING</td><td>string</td>
  </tr>
  <tr>
    <td>OBJECT</td><td>object</td>
  </tr>
  <tr>
    <td>DOT3</td><td>...</td>
  </tr>
  <tr>
    <td>FATCAMMA</td><td>=></td>
  </tr>
  <tr>
    <td>RW</td><td>rw</td>
  </tr>
  <tr>
    <td>RO</td><td>ro</td>
  </tr>
  <tr>
    <td>WO</td><td>wo</td>
  </tr>
  <tr>
    <td>INIT</td><td>INIT</td>
  </tr>
  <tr>
    <td>NEW</td><td>new</td>
  </tr>
  <tr>
    <td>RETURN</td><td>return</td>
  </tr>
  <tr>
    <td>WEAKEN</td><td>weaken</td>
  </tr>
  <tr>
    <td>DIE</td><td>die</td>
  </tr>
  <tr>
    <td>WARN</td><td>warn</td>
  </tr>
  <tr>
    <td>PRINT</td><td>print</td>
  </tr>
  <tr>
    <td>CURRENT_CLASS</td><td>__CLASS__</td>
  </tr>
  <tr>
    <td>UNWEAKEN</td><td>unweaken</td>
  </tr>
  <tr>
    <td>ASSIGN</td><td>=</td>
  </tr>
  <tr>
    <td>SPECIAL_ASSIGN</td><td>+=  -=  *=  /=  &=  |=  ^=  %=  &lt;&lt;=  &gt;&gt;=  &gt;&gt;&gt;= .=</td>
  </tr>
  <tr>
    <td>LOGICAL_OR</td><td>||</td>
  </tr>
  <tr>
    <td>LOGICAL_AND</td><td>&&</td>
  </tr>
  <tr>
    <td>BIT_OR</td><td>|</td>
  </tr>
  <tr>
    <td>BIT_XOR</td><td>&</td>
  </tr>
  <tr>
    <td>NUMEQ</td><td>==</td>
  </tr>
  <tr>
    <td>NUMNE</td><td>!=</td>
  </tr>
  <tr>
    <td>NUMGT</td><td>&gt;</td>
  </tr>
  <tr>
    <td>NUMGE</td><td>&gt;=</td>
  </tr>
  <tr>
    <td>NUMLT</td><td>&lt;</td>
  </tr>
  <tr>
    <td>NUMLE</td><td>&lt;=</td>
  </tr>
  <tr>
    <td>NUMERIC_CMP</td><td>&lt;=&gt;</td>
  </tr>
  <tr>
    <td>STREQ</td><td>eq</td>
  </tr>
  <tr>
    <td>STRNE</td><td>ne</td>
  </tr>
  <tr>
    <td>STRGT</td><td>gt</td>
  </tr>
  <tr>
    <td>STRGE</td><td>ge</td>
  </tr>
  <tr>
    <td>STRLT</td><td>lt</td>
  </tr>
  <tr>
    <td>STRLE</td><td>le</td>
  </tr>
  <tr>
    <td>SRING_CMP</td><td>cmp</td>
  </tr>
  <tr>
    <td>ISA</td><td>isa</td>
  </tr>
  <tr>
    <td>SHIFT</td><td>&lt;&lt;  &gt;&gt;  &gt;&gt;&gt;</td>
  </tr>
  <tr>
    <td>MULTIPLY</td><td>*</td>
  </tr>
  <tr>
    <td>DIVIDE</td><td>/</td>
  </tr>
  <tr>
    <td>REMAINDER</td><td>%</td>
  </tr>
  <tr>
    <td>LOGICAL_NOT</td><td>!</td>
  </tr>
  <tr>
    <td>BIT_NOT</td><td>~</td>
  </tr>
  <tr>
    <td>REF</td><td>\</td>
  </tr>
  <tr>
    <td>DEREF</td><td>$</td>
  </tr>
  <tr>
    <td>PLUS</td><td>+</td>
  </tr>
  <tr>
    <td>MINUS</td><td>-</td>
  </tr>
  <tr>
    <td>CONVERT</td><td>(TypeName)</td>
  </tr>
  <tr>
    <td>SCALAR</td><td>scalar</td>
  </tr>
  <tr>
    <td>LENGTH</td><td>length</td>
  </tr>
  <tr>
    <td>ISWEAK</td><td>isweak</td>
  </tr>
  <tr>
    <td>REFCNT</td><td>refcnt</td>
  </tr>
  <tr>
    <td>REFOP</td><td>ref</td>
  </tr>
  <tr>
    <td>DUMP</td><td>dump</td>
  </tr>
  <tr>
    <td>INC</td><td>++</td>
  </tr>
  <tr>
    <td>DEC</td><td>--</td>
  </tr>
  <tr>
    <td>ARROW</td><td>-></td>
  </tr>
</table>

<h2 id="language-comment">Comment</h2>

Comment begins with "#" and ends with <a href="#language-token-line-terminator">Line Terminator</a>.

<pre>
# Comment
</pre>

Comment has no meaning in the program execution.

<h2 id="language-pod">POD</h2>

POD(Plain Old Document) is a syntax to write documents easily.

You can use POD as Multi-Line comments.

POD starts from the line beginning with "=", followed by any character string of one or more characters, and ending with <a href="#language-token-line-terminator">Line Terminator</a>.

POD ends from the line beginning with "=cut", and ending with <a href="#language-token-line-terminator">Line Terminator</a>.

<b>POD Example:</b>

=end html

  =pod

  Multi-Line
  Comment

  =cut

  =head1

  Multi-Line
  Comment

  =cut

=begin html

POD has no meaning in the program execution.

<h2 id="language-class">Class</h2>
<ul>
  <li><a href="#language-class-definition">Class Definition</a></li>
  <li><a href="#language-class-descriptor">Class Descriptor</a></li>
  <li><a href="#language-class-destructor">Destructor</a></li>
  <li><a href="#language-class-allow-class-access">Allow Class Access</a></li>
</ul>

<h3 id="language-class-definition">Class Definition</h3>

<b>Class Definition</b> is the following syntax.

<pre>
class PACAKGE_NAME {

}
</pre>

PACAKGE_NAME must follow the rule for <a href="#language-token-identifier-class-name">Class Name</a>.

<a href="#language-class-descriptor">Class Descriptor</a> can be specified by the following syntax.

<pre>
class PACAKGE_NAME : PACAKGE_DESCRIPTOR {

}

class PACAKGE_NAME : PACAKGE_DESCRIPTOR1 PACAKGE_DESCRIPTOR2 PACAKGE_DESCRIPTORN {

}
</pre>

<b>Class Definition Example:</b>

<pre>
# Class Name
class Point {

}
</pre>

<pre>
# Class Name and Class Descriptor
class Point : public {

}
</pre>

In direct children of the class block, <a href="#language-module-use">use</a>, <a href="#language-class-var-definition">our</a>, <a href="#language-field-definition">has</a>, <a href="#language-enum-definition">enum</a>, <a href="#language-method-definition">sub</a> can be defined.

<pre>
class Foo {
  # use
  use Point;

  # Class Variable Definition
  our $VAR int;

  # Field Defintion
  has var : int;

  # Enumeration Definition
  enum {
    CONST_VAL1,
    CONST_VAL2,
  }

  # Method Definition
  static method foo : int ($num : int) {

  }
}
</pre>

If more than one class with the same name is defined, Compile Error occurs.

<h3 id="language-class-descriptor">Class Descriptor</h3>

The descriptions of Class Descriptors.

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Meaning
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This class is public. Other classes can <a href="#language-expression-new">new</a> this class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This class is private. Other classes can't <a href="#language-expression-new">new</a> this class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>callback_t</b>
    </td>
    <td>
      This class is <a href="#language-type-callback">Callback Type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>mulnum_t</b>
    </td>
    <td>
      This class is <a href="#language-type-multi-numeric">Multi Numeric Type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>pointer_t</b>
    </td>
    <td>
      This class is <a href="#language-type-pointer">Pointer Type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>precompile</b>
    </td>
    <td>
      Do precompile all methods in this class, except for accessor, and enum. 
    </td>
  </tr>
</table>

If both "public" and "private" are specifed, Compile Error occurs.

If more than one of "callback_t", "mulnum_t", "pointer_t" are specified, Compile Error occurs.

<h3 id="language-class-destructor">Destructor</h3>

If the class is <a href="#language-type-class">Class Type</a>, the class defined a destructor.

Destructor is a special <a href="#language-method">Method</a> called when the object of this class is freed.

Destructor name must be "DESTROY".

Destructor Retrun Value must be <a href="#language-type-void">void Type</a>, otherwise Compile Error occurs.

Destructor arguments must be one and the type must be <a href="#language-type-self">self Type</a>, otherwise Compile Error occurs.

<pre>
method DESTROY : void () {

}
</pre>

If a <a href="#language-exception-occur">Exception</a> occurs in Destructor, the program don't exit, print the message of the exception to STDERR.

<b>Destructor Example:</b>

<pre>
class Foo {
  static method new : Foo {
    return new Foo;
  }

  method DESTROY : void () {
    print "DESTROY";
  }
}
</pre>

<h3 id="language-class-allow-class-access">Allow Class Access</h3>

By default, private Methods, Fields, and Class Variables cannot be accessed from outside the Class.

Also, Private Class cannot <a href="#language-expression-new">Create Object</a> from outside of Class.

If the class allow other class, the other class can access private Methods, Fields, and Class Variables, and can <a href="#language-expression-new">Create Object</a> of the class.

<pre>
allow CLASS_NAME;
</pre>

allow must be defined directory under <a href="#language-class-definition">Class Definition</a>.

<pre>
class Foo {
  allow Bar;
}
</pre>

In this example, Bar can access the private Method, Field, and Class Variable of Foo can be accessed and can Create Object of Foo.

Specifying the module of <b>allow</b> also loads the module by <a href="#language-module-use">use</a> at the same time.


<h2 id="language-module">Module</h2>
<ul>
  <li><a href="#language-module-summary">Module Summary</a></li>
  <li><a href="#language-module-file-name">Module File Name</a></li>
  <li><a href="#language-module-use">Load Module</a></li>
  <li><a href="#language-module-auto-loaded-module">Automatically Loaded Module</a></li>
  <li><a href="#language-module-if-require">Selective Load Module</a></li>
</ul>

<h3 id="language-module-summary">Module Summary</h3>

Module is a single file that can be read as SPVM source code.

<pre>
# lib/path/SPVM/Foo/Bar.spvm
class Foo::Bar {

}
</pre>


Module can contain multiple Classes.

<pre>
# lib/path/SPVM/Foo/Bar.spvm
class Foo::Bar {

}

class Foo::Bar::Baz {

}
</pre>

<h3 id="language-module-file-name">Module File Name</h3>

Modules must be placed in the module loading path with the following File Name.

Change "::" to "/". Add ".spvm" at the end.

<pre>
SPVM/Foo.spvm
SPVM/Foo/Bar.spvm
SPVM/Foo/Bar/Baz.spvm
</pre>

<h3 id="language-module-use">Load Module</h3>

Use <b>use</b> keyword to load a Module.

<pre>
use Foo;
use Foo::Bar;
</pre>

Modules are loaded at compile-time.

If the Module does not exist, Compile Error will occur.

use Keyword must be defined directly under <a href="#language-class-definition">Class Definition</a>.

<pre>
class Foo {
  use Foo;
}
</pre>

<h3 id="language-module-auto-loaded-module">Automatically Loaded Module</h3>

The followings are Automatically Loaded Modules. They can be used without <a href="#language-module-use">use</a>.

<ul>
  <li>Byte</li>
  <li>Short</li>
  <li>Int</li>
  <li>Long</li>
  <li>Float</li>
  <li>Double</li>
</ul>

<h3 id="language-module-if-require">Load Module Selective</h3>

In SPVM, there is an if require Statement that loads a Module only if it exists in the module path, and if it does not exist, the block does not exist.

It was designed to implement a part of features of "#ifdef" in C language.

<pre>
if (require Foo) {

}
</pre>

if require Statement can be followed by else Statement. 

<pre>
if (require Foo) {

}
else {

}
</pre>

Note that elsif Statement cannot be followed.

Let's look at an example. if Foo does not exist, no Compile Error occurs and it is assumed that there is no if block

Therefore, "$foo = new Foo;" does not result in Compile Error because it is assumed that there is no if block.

In the other hand, the else block exists, so a warning is issued.

<pre>
my $foo : object;
if (require Foo) {
  $foo = new Foo;
}
else {
  warn "Warning: Can't load Foo";
}
</pre>

<h3 id="language-module-function-import">Function Import</h3>

The Method which is defined as Class Method is imported as Function using <a href="#language-module-use">use Statement</a>.

<pre>
use Foo(method1, method2);
</pre>

This function is called by <a href="language-expression-callsub-function-call">Function Call</a>

<h2 id="language-class-var">Class Variable</h2>
<ul>
  <li><a href="#language-class-var-definition">Class Variable Definition</a></li>
  <li><a href="#language-class-var-descriptor">Class Variable Descriptor</a></li>
  <li><a href="#language-class-var-initial-value">Class Variable Initial Value</a></li>
  <li><a href="#language-class-var-access">Class Variable Access</a></li>
</ul>

<h3 id="language-class-var-definition">Class Variable Definition</h3>

<b>Class Variable</b> is a global variable that belongs to <a href="#language-class">Class</a> and exists from the start to the end of the program execution.

"our" Keyword defines a Class Variable.

<pre>
our CLASS_VARIABLE_NAME : TYPE;
</pre>

Class Variable must be defined directly under <a href="#language-class-definition">Class Definition</a>.

Class Variable Definition must specify <a href="#language-type">Type</a>. The Type must be <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-object">Object Type</a>.

Class Variable Name must follows the rule specified in <a href="#language-token-identifier-class-var-name">Class Variable Name</a>, and must not contain "::", otherwise Compile Error occurs.

If more than one Class Variable with the same name is defined, Compile Error occurs.

Class Variable Descriptor can be specified together in Class Variable definition.

<pre>
our CLASS_VARIABLE_NAME : DESCRIPTOR TYPE;
our CLASS_VARIABLE_NAME : DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN TYPE;
</pre>

<h3 id="language-class-var-descriptor">Class Variable Descriptor</h3>

List of Class Variable Descriptors.

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This Class Variable is public. This Class Variable can be accessed from other class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This Class Variable is private. This Class Variable can't be accessed from other class. This is default setting of Class Variable.
    </td>
  </tr>
  <tr>
    <td>
      <b>ro</b>
    </td>
    <td>
      This Class Variable has Read Accessor. Read Accessor name is the same as Class Variable Name except removing "$". For example, If the Class Variable Name is "$FOO", Read Accessor name is "FOO".
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This Class Variable has Write Accessor. Write Accessor name is the same as Class Variable Name except removing "$" and adding "SET_" to top. For example, If the Class Variable Name is "$FOO", Read Accessor name is "SET_FOO".
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      This Class Variable has Read accessor and Write Accessor.
    </td>
  </tr>
</table>

If both "public" and "private" Descriptors are specified, Compile Error occurs.

If more than one of "ro", "wo", and "rw" are specified at the same time, Compile Error occurs

Read Accessor of Class Variable has no arguments and the return type is same as the type of Class Variable.

Write Acessor of Class Variable has one argument and the type is same as the type of Class Variable. The type of return value is <a href="#language-type-void">void Type</a>.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Class Variable Accessors.

<b>Class Variable Definition Example:</b>

<pre>
class Foo {
  our $NUM1 : byte;
  our $NUM2 : short;
  our $NUM3 : int;
  our $NUM4 : long;
  our $NUM5 : float;
  our $NUM6 : double;

  our $NUM_PUBLIC : public int;
  our $NUM_RO : ro int;
  our $NUM_WO : wo int;
  our $NUM_RW : rw int;
}
</pre>

<h3 id="language-class-var-initial-value">Class Variable Initial Value</h3>

Class Variable is initialized with <a href="#language-type-initial-value">Type Initial Value</a> after compilation and before execution.

This initial value can be changed by using <a href="#language-begin-block">INIT Block</a>.

<pre>
class Foo {
  our $VAR : int;

  INIT {
    $VAR = 3;
  }
}
</pre>

<h3 id="language-class-var-access">Class Variable Access</h3>

Class Variable Access is an operation to access Class Variable to get or set a value.

See <a href="#language-expression-get-class-var">Get Class Variable Value</a> for how to get the value of Class Variable.

See <a href="#language-expression-set-class-var">Set Class Variable Value</a> for the setting of the value of Class Variable.

<h2 id="language-field">Field</h2>
<ul>
  <li><a href="#language-field-definition">Field Definition</a></li>
  <li><a href="#language-field-descriptor">Field Descriptor</a></li>
  <li><a href="#language-field-access">Field Access</a></li>
</ul>
<h3 id="language-field-definition">Field Definition</h3>

Field is a data area in a <a href="#language-expression-new">object created using new keyword</a>

"has" Keyword defines a Field.

<pre>
has FIELD_NAME : TYPE;
</pre>

Field must be defined directly under <a href="#language-class-definition">Class Definition</a>.

Field Definition must be specify <a href="#language-type">Type</a>. The Type must be <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-object">Object Type</a>.

Field Name must follows the rule specified in <a href="#language-token-identifier-field-name">Field Name</a>.

Field Name is allowed as same as <a href="#language-token-keyword">Keyword</a>.

Field Type must be <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.

If more than one Field Name Variable with the same name is defined, Compile Error occurs.

Field Descriptor can be specified together in Field Definition.

<pre>
has FIELD_NAME : DESCRIPTOR TYPE_NAME;
has FIELD_NAME : DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN TYPE_NAME;
</pre>

<h3 id="language-field-descriptor">Field Descriptor</h3>

List of Field Descriptors.

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This field is public. This field can be accessed from other class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This field is private. This field can't be accessed from other class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>ro</b>
    </td>
    <td>
      This Field has Read Accessor. Read Accessor name is the same as Field Name. For example, If the Field Name is "foo", Read Accessor name is "foo".
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This Field has Write Accessor. Write Accessor name is the same as Field Name adding "set_" to top. For example, If the Field Name is "foo", Read Accessor name is "set_foo".
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      This Field has Read Accessor and Write Accessor.
    </td>
  </tr>
</table>

If both "public" and "private" Descriptors are specified, Compile Error occurs.

If more than one of "ro", "wo", and "rw" are specified at the same time, Compile Error occurs

Read Accessor of Field has one argument that is <a href="#language-type-self">self Type</a> and the Return Type is same as the type of Field.

Write Acessor of Class Variable has two arguments. First argument is <a href="#language-type-self">self Type</a> and second argument is same as the type of Field. The type of return value is <a href="#language-type-void">void Type</a>.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Field Accessors.

<b>Field Definition Example:</b>

<pre>
class Foo {
  has num1 : byte;
  has num2 : short;
  has num3 : int;
  has num4 : long;
  has num5 : float;
  has num6 : double;

  has num_public : public int;
  has num_ro : ro int;
  has num_wo : wo int;
  has num_rw : rw int;
}
</pre>

<h3 id="language-field-access">Field Access</h3>

Field Access is an operation to access Field to get or set a value.

<pre>
EXPRESSION->{FIELD_NAME}
</pre>

Field Access has three different meanings.

<b>1. Class Based Object Field Access</b>

Class Based Object Field Access is Field Access from object which is create by <a href="#language-expression-new">new</a> keyword.

<pre>
my $point = new Point;
$point->{x} = 1;
</pre>

See <a href="#language-expression-get-field">Get Field Value</a> to get field of Class Based Object.

See <a href="#language-expression-set-field">Set Field Value</a> to set field of Class Based Object.

<b>2. Multi Numeric Field Access</b>

Multi Numeric Field Access is Field Access from the value of <a href="#language-type-multi-numeric">Multi Numeric Type</a>. The value of <a href="#language-type-multi-numeric">Multi Numeric Type</a> is allocated Callstack of Method.

<pre>
my $z : Complex_2d;
$z->{x} = 1;
$z->{y} = 3;
</pre>

See <a href="#language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</a> to get field of the value of <a href="#language-type-multi-numeric">Multi Numeric Type</a>.

See <a href="#language-expression-set-field-multi-numeric">Set Multi Numeric Field Value</a> to set field of the value of <a href="#language-type-multi-numeric">Multi Numeric Type</a>.

<b>3. Dereference Multi Numeric Field</b>

Dereference Multi Numeric Field is Field access from Reference of the value of <a href="#language-type-multi-numeric">Multi Numeric Type</a>.

<pre>
my $z : Complex_2d;
my $z_ref = \$z;
$z_ref->{x} = 1;
$z_ref->{y} = 3;
</pre>

See <a href="#language-expression-get-field-multi-numeric-deref">Get Multi Numeric Field Value via Dereference</a> to get Multi Numeric Field via Dereference.

See <a href="#language-expression-set-field-multi-numeric-deref">Set Multi Numeric Field Value via Dereference</a> to set Multi Numeric Field via Dereference.

<h2 id="language-method">Method</h2>
<ul>
  <li><a href="#language-method-definition">Method Definition</a></li>
  <li><a href="#language-method-descriptor">Method Descriptor</a></li>
  <li><a href="#language-method-native">Native Method</a></li>
  <li><a href="#language-method-precompiled">Precompiled Method</a></li>
  <li><a href="#language-method-constant">Constant Method</a></li>
  <li><a href="#language-method-method">Method</a></li>
  <li><a href="#language-method-signature">Signature</a></li>
  <li><a href="#language-method-stack">Method Callstack</a></li>
</ul>

<h3 id="language-method-definition">Method Definition</h3>

"sub" Keyword defines Method.

<pre>
static method METHOD_NAME : RETURN_VALUE_TYPE_NAME () {

}
static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2, ARGUMENT_NAMEN : ARGUMENT_TYPE_NAMEN) {

}
</pre>

Method must be defined directly under <a href="#language-class-definition">Class Definition</a>.

Method name must be follow the rule of <a href="#language-token-identifier-sub-name">Method Name</a>.

Method Name is allowed as same as <a href="#language-token-keyword">Keyword</a>. 

Type of Return Value must be <a href="#language-type-void">void Type</a>, <a href="#language-type-numeric">Numeric Type</a>, or <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.

Argument name must be follow the rule of <a href="#language-token-identifier-local-var-name">Local Variable Name</a>.

Minimal Argument Count is 0. Max Argument Count is 255.

Type of Argument must be <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-object">Object Type</a>, or <a href="#language-type-reference">Reference Type</a>, otherwise Compile Error occurs.

The defined Method can be called. See <a href="#language-expression-callsub">Method Call</a> about calling Method, .

<a href="#language-scope-block-statement-sub">Method Block</a> can have zero or more Statements.

Method Definition can have <a href="#language-method-descriptor">Method Descriptor</a>.

<pre>
DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN static method METHOD_NAME : RETURN_VALUE_TYPE_NAME () {

}
DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2, ARGUMENT_NAMEN : ARGUMENT_TYPE_NAMEN) {

}
</pre>


If "..." follows Type of Argument, the Argument becomes Variable Length Argument. Only the last Argument can be Variable Length Argument.

The Type must be <a href="#language-type-array">Array Type</a>.

<pre>
static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2...) {

}
</pre>

Variable Length Argument can recieve multi values.

<pre>
# Variable Length Argument Definition
static method sprintf : string ($format : string, $values : object[]...) {

}

# Call Variable Length Argument Method with multi values.
sprintf("Value %d %f", 1, 2.0);
</pre>

Variable Length Argument can recieve Array.

<pre>
# Call Variable Length Argument Method with Array.
sprintf("Value  %d %f", [(object)1, 2.0]);
</pre>

If you want to treat the value of Array as an individual element of the variable length argument, cast it to Type other than Array Type.

<pre>
sprintf("aaa %p", (object)[(object)1, 2.0]);
</pre>

<h3 id="language-method-descriptor">Method Descriptor</h3>

List of Method Descriptor.

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>native</b>
    </td>
    <td>
      This Method is <a href="#language-method-native">Native Method</a>. 
    </td>
  </tr>
</table>

<h3 id="language-method-native">Native Method</h3>

Native Method is Method that call function written in Native Language(C, C++, etc).

See <a href="/native-api.html">SPVM Native API</a> Native Method.

<h3 id="language-method-precompiled">Precompiled Method</h3>

If the Class has "precompile" descriptor, the methods of the class become Precompiled Method.

Precompiled Method is translated into C99 Compliant source code and converted into machine code.

The precompiled methods are C code, so you can get performance of C language.

Precompiled Method needs Build Directory described in <a href="/native-api.html">SPVM Native API</a>

<h3 id="language-method-constant">Constant Method</h3>

Constant Method is a Method that Return Type is <a href="#language-type-numeric">Numeric Type</a> and returns Constant Value.

<pre>
static method foo : int () { return 5; }
static method foo : long () { return 5L; }
static method foo : float () { return 5.0f; }
static method foo : double () { return 5.0; }
</pre>

Inline Expansion optimization is performed to Constant Method.

Note that SPVM does not perform constant convolution optimization, so if a constant is calculated, it will not performe Inline Expansion.

<pre>
# This is not Constant Method.  Inline Expansion is not performed
static method foo : int () { return 5 + 3; }
</pre>

<h3 id="language-method-method">Method</h3>

Method is Method that has <a href="#language-type-self">self Type</a> as its first argument.

<pre>
method METHOD_NAME : TYPE  (ARGUMENT2 : TYPE2, ARGUMENT3 : TYPE3, ARGUMENTN : TYPEn) {

}
</pre>

<a href="#language-type-self">self Type</a> must be first argument.

Method can be called from the object created by <a href="#language-expression-new">new</a>. See <a href="#language-expression-callsub">Method Call</a> for Method Call.

$self is called Invocant.

<h3 id="language-method-signature">Signature</h3>

Signature is a string that follow the following rule sequence of Method Retrun Value and arguments arranged according to the following rules. Arguments do not need to exist. There cannot be spaces between them.

1. RETURN_VALUE_TYPE

2. (

3. ARGUMENT_TYPE1,ARGUMENT_TYPE2,ARGUMENT_TYPE3

4. )

<b>Signature Example:</b>

<pre>
# Method Definition
static method foo : int ($num1 : double, $num2 : long[])

# Signature
int(double,long[])

# Method Definition
static method foo : void ()

# Signature
void()
</pre>

Signature is not used in SPVM programs. Signature is used when calling the SPVM Method from <a href="/native-api.html">SPVM Native API</a>.

<h3 id="language-method-stack">Method Callstack</h3>

Method Callstack is memory area allocated in each method call.


<p>
  Method Callstack save the folloing information.
</p>
<p>
  1. Memroy area for <a href="#language-local-var">Local Variable</a>
</p>
<p>
  2. The places of Mortal Local Variable
</p>

<h2 id="language-enum">Enumeration</h2>

<ul>
  <li>
    <a href="#language-enum-definition">Enumeration Definition</a>
 </li>
  <li>
    <a href="#language-enum-descriptor">Enumeration Descriptor</a>
 </li>
  <li>
    <a href="#language-enum-call">Enumeration Call</a>
 </li>
</ul>

<h3 id="language-enum-definition">Enumeration Definition</h3>

Enumeration Definition is a syntax to define multiple <a href="#language-method-constant">Constant Methods</a> easily.

<pre>
# Enumeration Definition
enum {
  FLAG1,
  FLAG2,
  FLAG3
}
</pre>

Enumeration must be defined directly under <a href="#language-class-definition">Class Definition</a>.

<pre>
class Foo {
  enum {
    FLAG1,
    FLAG2,
    FLAG3
  }
}
</pre>

The first value starts with "0". The value is incremented by "1". In this example, "FLAG1" is "0", "FALG2" is "1", and "FLAG3" is "2".

"," can be added after the last element of Enumeration.

<pre>
enum {
  FLAG1,
  FLAG2,
  FLAG3,
}
</pre>

Enumeration is an alias for <a href="#language-method-constant">Constant Method</a> that Return Type is <a href="#language-type-int">int Type</a>. It is equivalent to the following Method Definition:

<pre>
static method FLAG1 : int () { return 0; }
static method FLAG2 : int () { return 1; }
static method FLAG3 : int () { return 2; }
</pre>

The value of <a href="#language-type-int">int Type</a> can be set in the enum element.

<pre>
enum {
  FLAG1,
  FLAG2 = 4,
  FLAG3,
}
</pre>


In the above case, "FLAG1" is "0", "FALG2" is "4", and "FLAG3" is "5".

If Enum Definition is invalid, Compile Error occurs.

<h3 id="language-enum-descriptor">Enumeration Descriptor</h3>

Descriptor can be specified for Enumeration.

<pre>
private enum {
  FLAG1,
  FLAG2 = 4,
  FLAG3,
}
</pre>

List of Enumeration Descriptor

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This Enumeration is public. This Enumeration can be accessed from other Class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This Enumeration is private. This Enumeration can not be accessed from other Class.
    </td>
  </tr>
</table>

If both "public" and "private" Descriptors are specified, Compile Error occurs.

<h3 id="language-enum-call">Enumeration Call</h3>

Enumeration is an alias for <a href="#language-method-constant">Constant Method</a>, so it can be called in exactly the same way as Method call.

<pre>
my $flag1 = Foo->FLAG1;
my $flag2 = Foo->FLAG2;
my $flag3 = Foo->FLAG3;
</pre>

<p>
  In special case, Enumeration Call can be used in <a href="#language-statement-case">case Statement</a> of <a href="#language-statement-switch">switch Statement</a>.
</p>

<pre>
switch ($num) {
  case Foo->FLAG1: {

    break;
  }
  case Foo->FLAG2: {

    break:
  }
  case Foo->FLAG3: {

    break:
  }
  default: {

  }
}
</pre>

<h2 id="language-begin-block">INIT Block</h2>

<b>INIT Block</b> is a block that is executed immediately after the compilation of program.

INIT Keyword defines INIT Block.

<pre>
INIT {

}
</pre>

INIT Block must be defined directly under <a href="#language-class-definition">Class Definition</a>.

<pre>
class Foo {
  INIT {

  }
}
</pre>

Zero or more <a href="#language-statement">Statements</a> can be written in INIT Block.

<pre>
INIT {
  my $foo = 1 + 1;
  my $bar;
}
</pre>

<a href="#language-statement-return">return Statement</a> cannot be written in INIT Block.

Internally, INIT Block is a <a href="#language-method">Method</a> that Return Type is <a href="#language-type-void">void Type</a> and has no arguments.

You can define multiple INIT Blocks.

The execution order of INIT Block is not guaranteed. If ohter INIT Block is defined in ohter Class, do not assume that INIT Block of the current class will be executed first.

A common use of INIT Block is to initialize <a href="#language-class-var">Class Variable</a>.

<pre>
class Foo {
  use Point;
  
  our $NUM : int;
  our $POINT : Point;
  INIT {
    $NUM = 3;
    $POINT = Point->new;
  }
}
</pre>

<h2 id="language-local-var">Local Variable</h2>

<ul>
  <li><a href="#language-local-var-declaration">Local Variable Declaration</a></li>
  <li><a href="#language-local-var-initial-value">Local Variable Initial Value</a></li>
  <li><a href="#language-local-var-access">Local Variable Access</a></li>
</ul>

<h3 id="language-local-var-declaration">Local Variable Declaration</h3>

<b>Local Variable</b> is a variable that is declared in <a href="#language-scope-scope-block">Scope Block</a>.  Local Variable has <a href="#language-scope">Scope</a>. This is same as Local Variable in C Language.

Local Variable is declared using <b>my</b> <a href="#language-token-keyword">Keyword</a>.

<pre>
my LEXICAL_VARIABLE_NAME : TYPE;
</pre>

Lexical variable name must be follow the rule of <a href="#language-token-identifier-local-var-name">Local Variable Name</a>.

<a href="#language-type">Type</a> must be specified. Type must be <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-object">Object Type</a>, <a href="#language-type-multi-numeric">Multi Numeric Type</a>, or <a href="#language-type-ref">Reference Type</a>.

<pre>
# Local Variable Declaration Examples
my $var : int;
my $var : Point;
my $var : Complex_2d;
my $var : int&;
</pre>

Local Variable is initialized by <a href="#language-local-var-initial-value">Local Variable Initial Value</a>.

<pre>
# Initialized by 0
my $num : int;

# Initialized by 0
my $num : double;

# Initialized by undef
my $point : Point;

# x is initialized by 0. y is initialized by 0.
my $z : Complex_2d;
</pre>


Initialization can be done at the same time as Local Variable Declaration.

<pre>
# Initialized by 1
my $num : int = 1;

# Initialized by 2.5
my $num : double = 2.5;

# Initialized by Point object
my $point : Point = new Point;
</pre>

Using <a href="#language-type-inference">Type Inference</a>, you omit <a href="#language-type">Type</a> in Local Variable Declaration.

<pre>
# int
my $num = 1;

# double
my $num = 1.0;
</pre>

Local Variable Declaration returns the value of Local Variable. This is a <a href="#language-expression">Expression</a>.

<pre>
my $ppp = my $bar = 4;

if (my $bar = 1) {

}

while (my $bar = 1) {

}
</pre>

See <a href="#language-scope">Scope</a> about Local Variable Scope.

<h3 id="language-local-var-initial-value">Local Variable Initial Value</h3>

Local Variable is initialized by <a href="#language-type-initial-value">Type Initial Value</a>.

<h3 id="language-local-var-access">Local Variable Access</h3>

Local Variable Access is an operation to access Local Variable to get or set the value.

See <a href="#language-expression-get-local-var">Get Local Variable Value</a> to get Local Variable value.

<a href="#language-expression-set-local-var">Set Local Variable Value</a> to get Local Variable value.

If <a href="#language-class-var">Class Variable</a> with the same name as the Local Variable exists, Program uses the variable as Local Variable, not <a href="#language-class-var">Class Variable</a>.

<h2 id="language-scope">Scope</h2>
<ul>
  <li><a href="#language-scope-summary">Scope Summary</a>
  <li><a href="#language-scope-block">Block</a></li>
  <li><a href="#language-scope-scope-block">Scope Block</a>
</ul>

<h3 id="language-scope-summary">Scope Summary</h3>

<b>Scope</b> is a range surrounded by <a href="#language-scope-scope-block">Scope Block</a>.

<pre>
# Scope Block 
{
  # Start of Scope
  
  # ...
  
  # End of Scope
}
</pre>

Local Variable Declaration registers the Local Variable that is <a href="#language-type-object">Object Type</a> with Mortal Variable in run-time. 

If the object is not <a href="#language-undef">undef</a>, The Reference Count is added by 1.

<pre>
{
  # $num become Mortal Variable in run-time
  my $num = new Foo;
}
</pre>

At the end of Scope, the object that is registered as Mortal Variable, Reference Count is reduced by 1 except the object is not <a href="#language-undef">undef</a>.

If the Reference Count become 0, the object released.

<h3 id="language-scope-block">Block</h3>

The part enclosed by "{" and "}" is called <b>Block</b>.

<pre>
# Block 
{

}
</pre>

There are <a href="#language-scope-scope-block">Scope Block</a> that creates a scope and Non Scope Block that does not create a scope.

<h3 id="language-scope-scope-block">Scope Block</h3>

<b>Scope Block</b> is a block that creates a Scope. Zero or more <a href="#language-statement">Statement</a> can be written in Scope Block.

<b>List of Scope Blocks</b>

<ul>
  <li><a href="#language-scope-block-statement-simple">Simple Block</a></li>
  <li><a href="#language-scope-block-statement-sub">Method Block</a></li>
  <li><a href="#language-scope-block-statement-eval">eval Block</a></li>
  <li><a href="#language-scope-block-statement-if">if Block</a></li>
  <li><a href="#language-scope-block-statement-elsif">elsif Block</a></li>
  <li><a href="#language-scope-block-statement-else">else Block</a></li>
  <li><a href="#language-scope-block-statement-for">for Block</a></li>
  <li><a href="#language-scope-block-statement-while">while Block</a></li>
  <li><a href="#language-scope-block-statement-switch">switch Block</a></li>
</ul>

<h3 id="language-scope-block-statement-simple">Simple Block</h3>

Simple Block is a scope block.

<pre>
# Simple Block
{

}
</pre>

<h3 id="language-scope-block-statement-sub">Method Block</h3>

Method Block is a scope block.

<pre>
# Method Block
static method foo : int () {

}
</pre>

<h3 id="language-scope-block-statement-eval">eval Block</h3>

eval Block is a scope block.

<pre>
# eval Block
eval {

}
</pre>

<h3 id="language-scope-block-statement-if">if Block</h3>

if Block is a scope block.

<pre>
# if Block
if (EXPRESSION) {

}
</pre>

<h3 id="language-scope-block-statement-elsif">elsif Block</h3>

elsif Block is a scope block.

<pre>
#elsif Block
elsif (EXPRESSION) {

}
</pre>

<h3 id="language-scope-block-statement-else">else Block</h3>

else Block is a scope block.

<pre>
# else Block
else {

}
</pre>

<h3 id="language-scope-block-statement-for">for Block</h3>

for Block is a scope block.

<pre>
# for Block 
for (my $i = 0; $i < 3; $i++) {

}
</pre>

<h3 id="language-scope-block-statement-while">while Block</h3>

while Block is a scope block.

<pre>
# while Block
while (EXPRESSION) {

}
</pre>

<h3 id="language-scope-block-statement-switch">switch Block</h3>

switch Block is a scope block.

<pre>
switch (EXPRESSION) {

}
</pre>

<h2 id="language-literal">Literal</h2>

<ul>
  <li><a href="#language-literal-summary">Literal Summary</a></li>
  <li><a href="#language-literal-integer">Integer Literal</a></li>
  <li><a href="#language-literal-floating-point">Floating Point Literal</a></li>
  <li><a href="#language-literal-character">Charater Literal</a></li>
  <li><a href="#language-literal-string">String Literal</a></li>
  <li><a href="#language-literal-string-variable-expansion">Variable Expansion</a></li>
</ul>

<h3 id="language-literal-summary">Literal Summary</h3>

<b>Literal</b> is a <a href="#language-expression">Expression</a> that represents Constant Value.

<h3 id="language-literal-integer">Integer Literal</h3>

<h4>Decimal Representation of Integer Literal</h4>

Decimal Representation of Integer Literal is represented by one or more consecutive characters from "0" to "9".

Can be prefixed with "+" or "-".

<a href="#language-type">Type</a> of Integer Literal is <a href="#language-type-int">int Type</a> by default.

If Integer Literal exceeds the range of numbers that can be represented by <a href="#language-type-int">int Type</a>, Compile Error occurs.

By suffixing "L" or "l" at the end, that represents <a href="#language-type-long">long Type</a> Integer Literal.

If <a href="#language-type-long">long Type</a> Integer Literal  exceeds the range of numbers that can be represented by <a href="#language-type-long">long Type</a>,  If it exceeds the range, Compile Error occurs.

"_" can be used as a Separator. Separator has no meaning.

If Integer Literal is assigned to a <a href="#language-type-byte">byte Type</a> variable or passed to <a href="#language-type-byte">byte Type</a> Method Argument, and does not exceed the range of numbers that can be represented by <a href="#language-type-byte">byte Type</a>, <a href = "#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a> is applied and the value converted to <a href="#language-type-byte">byte Type</a> value. If it exceeds the range, Compile Error will occur.

If Integer Literal is assigned to a <a href="#language-type-short">short Type</a> variable or passed to <a href="#language-type-short">short Type</a> Method Argument, and does not exceed the range of numbers that can be represented by <a href="#language-type-short">short Type</a>, <a href = "#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a> is applied and the value converted to <a href="#language-type-short">short Type</a> value. If it exceeds the range, Compile Error will occur.

<b>Integer Literal Example:</b>

<pre>
123
+123
-123
123L
123l
123_456_789
-123_456_789L
</pre>

<h4>Hexadecimal Representation of Integer Literal</h4>

Hexadecimal Representation of Integer Literal is represented by the following rule.

Hexadecimal Representation of Integer Literal starts with "0x" or "0X".

It is followed by one or more consecutive characters "0" to "9", "a" to "f", or "A" to "F"..

Other rules are same as Decimal Representation of Integer Literal

<b>Hexadecimal Representation of Integer Literal Example:</b>

<pre>
0x3b4f
-0x3F1A
0xDeL
0xFFFFFFFF_FFFFFFFF
</pre>

<h4>Octal Representation of Integer Literal</h4>

Octal Representation of Integer Literal is represented by the following rule.

Octal Representation of Integer Literal starts with "0".

It is followed by one or more consecutive characters "0" to "7".

Other rules are same as Decimal Representation of Integer Literal

<b>Octal Representation of Integer Literal Example:</b>

<pre>
0755
-0644
0666L
0655_755
</pre>

<h4>Binary Representation of Integer Literal</h4>

Binary Representation of Integer Literal is represented by the following rule.

Binary Representation of Integer Literal starts with "0b" or "0B".

It is followed by one or more consecutive characters "0" or "1".

<b>Binary Representation of Integer Literal Example:</b>

<pre>
0b0101
-0b1010
0b110000L
0b10101010_10101010
</pre>

<h3 id="language-literal-floating-point">Floating Point Literal</h3>

Floating Point Literal consists of <b>Sign Part</b>, <b>Numeric Part</b>, <b>Exponent Part</b> and <b>Suffix</b>.

<pre>
# Floating Point Literal
[Sign Part][Numeric Part][Exponent Part][Suffix Part]
</pre>

Floating Point Literal is <b>Decimal Floating Point Literal</b> or <b>Hexadecimal Floating Point Literal</b>.

<b>Sign Part</b> is represented by "+" or "-". Sign Part is optional.

Numeric Part of Decimal Floating Point Literal starts one or more "0" to "9".

Numeric Part of Hexadecimal Floating Point Literal starts "0x" or "0X", and is followed by "0" to "9", "a" to "f", or "A" to "F".

For that the Literal is Floating Point Literal, Numeric Part contains "." or, The Literal have Exponent Part, or have Suffix Part.


Numeric part can contain "_". This is just a Numeric Separator and is ignored.

Hexadecimal Floating Point Literal needs Exponent Part.

<b>Exponent Part</b> is consist of <b>Exponential Notation</b> and <b>Signed Decimal Integer</b>.

<pre>
# Exponent Part
[Exponential Notation][Signed Decimal Integer]
</pre>

Exponential Notation is "e" or "E" for Decimal Floating Point Literal, and "p" or "P" for Hexadecimal Floating Point Literal.

The meaning of Exponent Part is decimal shift for Decimal Floating Point Literal, or binary shift for Hexadecimal Floating Point Literal.

If Suffix Part is "f" or "F", the <a href="#language-type">Type</a> of Floating Point Literal is <a href="#language-type-float">float Type</a>.

If Suffix Part is "d" or "D", the <a href="#language-type">Type</a> of Floating Point Literal is <a href="#language-type-double">double Type</a>.

If Suffix Part is omitted, the <a href="#language-type">Type</a> of Floating Point Literal is <a href="#language-type-double">double Type</a>.

If Floating Point Literal is <a href="#language-type-float">float Type</a>, the Floating Point Literal is converted to float value using C standard "strtof" function. If the conversion fails, Compile Error occurs.

If Floating Point Literal is <a href="#language-type-double">double Type</a>, the Floating Point Literal is converted to double value using C standard "strtod" function. If the conversion fails, Compile Error occurs.

<b>Floating Point Literal Example:</b>

<pre>
1.32
-1.32
1.32f
1.32F
1.32e3
1.32e-3
1.32E+3
1.32E-3
0x3d3d.edp0
0x3d3d.edp3
0x3d3d.edP3
0x3d3d.edP-3f
</pre>

<h3 id="language-literal-character">Charater Literal</h3>

<b>Charater Literal</b> represents one character of ASCII code.

Character Literal is enclosed in single quotes "'".

Content of Character Literal is one printable ASCII character or one Escape Character of Character Literal.

Charater Literal Type is "<a href="#language-type-byte">byte Type</a>"

<a href="#language-type">Type</a> of Charater Literal is <a href="#language-type-byte">byte Type</a>.

<table class="toc">
  <tr>
    <th>
      Escape Characters of Character Literal
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>\0</b>
    </td>
    <td>
      ASCII Code 0 NUL
    </td>
  </tr>
  <tr>
    <td>
      <b>\a</b>
    </td>
    <td>
      ASCII Code 7 BEL
    </td>
  </tr>
  <tr>
    <td>
      <b>\b</b>
    </td>
    <td>
      ASCII Code 8 BS
    </td>
  </tr>
  <tr>
    <td>
      <b>\t</b>
    </td>
    <td>
      ASCII Code 9 HT
    </td>
  </tr>
  <tr>
    <td>
      <b>\n</b>
    </td>
    <td>
      ASCII Code 10 LF
    </td>
  </tr>
  <tr>
    <td>
      <b>\f</b>
    </td>
    <td>
      ASCII Code 12 "FF"
    </td>
  </tr>
  <tr>
    <td>
      <b>\r</b>
    </td>
    <td>
      ASCII Code 13 CR
    </td>
  </tr>
  <tr>
    <td>
      <b>\"</b>
    </td>
    <td>
      ASCII Code 34 "
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII Code 39 '
    </td>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII Code 92 \
    </td>
  </tr>
  <tr>
    <td>
      <b>\x + tow hexadecimal numbers</b>
    </td>
    <td>
      Specify ASCII code by hexadecimal. Hexadecimal numbers are "0" to "9", "a" to "z", "A" to "Z".
    </td>
  </tr>
</table>

<b>Charater Literal Example:</b>

<b>Charater Literal</b> represents one character of ASCII code.

<pre>
# Charater Literal 
'a'
'x'

# Charater Literal using Escape Character
'\a'
'\b'
'\t'
'\n'
'\f'
'\r'
'\"'
'\''
'\\'
'\x0D'
'\x0A'
</pre>

<h3 id="language-literal-string">String Literal</h3>

<b>String Literal</b> represents String.

String Literal is enclosed in double quotes '"'. String Literal return the value of string type.

The content of String Literal is zero or more ASCII printable Characters or Escape Characters of String Literal".

<h4>Escape charaters of String Literal</h4>

<table class="toc">
  <tr>
    <th>
      Escape Character of String Literal
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>\0</b>
    </td>
    <td>
      ASCII Code 0 NUL
    </td>
  </tr>
  <tr>
    <td>
      <b>\a</b>
    </td>
    <td>
      ASCII Code 7 BEL
    </td>
  </tr>
  <tr>
    <td>
      <b>\b</b>
    </td>
    <td>
      ASCII Code 8 BS
    </td>
  </tr>
  <tr>
    <td>
      <b>\t</b>
    </td>
    <td>
      ASCII Code 9 HT
    </td>
  </tr>
  <tr>
    <td>
      <b>\n</b>
    </td>
    <td>
      ASCII Code 10 LF
    </td>
  </tr>
  <tr>
    <td>
      <b>\f</b>
    </td>
    <td>
      ASCII Code 12 FF
    </td>
  </tr>
  <tr>
    <td>
      <b>\r</b>
    </td>
    <td>
      ASCII Code 13 CR
    </td>
  </tr>
  <tr>
    <td>
      <b>\"</b>
    </td>
    <td>
      ASCII Code 34 "
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII Code 39 '
    </td>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII Code 92 \
    </td>
  </tr>
  <tr>
    <td>
      <b>\x + two hexadecimal numbers</b>
    </td>
    <td>
      Specify ASCII code by hexadecimal. Hexadecimal numbers are "0" to "9", "a" to "z", "A" to "Z". <br>For example, \x0D.
    </td>
  </tr>
  <tr>
    <td>
      <b>\N{U+} + hexadecimal numbers after U+</b>
    </td>
    <td>
      Specify the Unicode code point in hexadecimal. Hexadecimal numbers are expressed as "0" to "9", "a" to "f", "A" to "F".<br>For example, \N{U+3046}.<br>The code point is converted to UTF-8. 
    </td>
  </tr>
  <tr>
    <td>
      <b>Raw escape character</b><br>(For example, \s is become \s. This represents a sequence of two characters in a character literal '\\' 's')</b>
    </td>
    <td>
      \s \S \d \D \w \W \p \P \X \g \k \K \v \V \h \H \R \b \B \A \Z \z \G \N<br>
      \1 \2 \3 \4 \5 \6 \7 \8 \9 <br>
      \! \# \@ \% \& \( \) \* \+ \- \. \/ \: \; \< \= \> \? \[ \] \^ \_ \` \{ \| \} \~ \,
    </td>
  </tr>
</table>

If the espape characters which is not included avobe is used, a compiler error occurs.<br>

<b>String Literal Example:</b>

<pre>
# String Literal 
"abc"
"あいう"

# Escape Character of String Literal 
"abc\tdef\n"
"\x0D\x0A"
"\N{U+3042}\N{U+3044}\N{U+3046}"
</pre>

<h3 id="language-literal-string-variable-expansion">Variable Expansion</h3>

<b>Variable Expansion</b> applys <a href="#language-local-var">Local Variable</a>, <a href="#language-class-var">Class Variable</a>, <a href="#language-ref-deref">Dereference</a>, <a href="#language-field-access">Field Access</a>, <a href="#language-array-access">Array Access</a>, <a href="#language-exception-var">Exception Variable</a> in String Literal.

<pre>
"AAA $foo BBB"
"AAA $FOO BBB"
"AAA $$foo BBB"
"AAA $foo->{x} BBB"
"AAA $foo->[3] BBB"
"AAA $foo->{x}[3] BBB"
"AAA $@ BBB"
</pre>

The above is expanded as the following.

<pre>
"AAA" . $foo . "BBB"
"AAA" . $FOO . "BBB"
"AAA" . $$foo . "BBB"
"AAA" . $foo->{x} . "BBB"
"AAA" . $foo->[3] . "BBB"
"AAA" . $foo->{x}[3] . "BBB"
"AAA" . $@ . "BBB"
</pre>

The variable name can besurround with "{" and "}" to indicate the end of the variable name.

<pre>
"AAA ${foo}_ccc BBB"
</pre>
<p>

The above is expanded as the following.

</p>
<pre>
"AAA " . ${foo} . "_ccc BBB"
</pre>

If there is no enclosing "{" and "}", up to the valid part as a variable name is interpreted as a Variable. Dereference interpreting is same as this.

If "->" follows the variable name, it is interpreted as <a href="#language-field-access">Field Access</a> or <a href="#language-array-access">Array Access</a>.

[1] If the following Characters are "a-z" "A-Z" "0-9" "_" "{" "[", proceed with the interpretation.

[2] If the Character following [1] is "}", or "]", then if the next Character is "->", "{", or "[", proceed with the interpretation and return back to [1], otherwise stop interpreting.

The trailing $is not treated as the start of Variable Expansion. It is treated as "$".

<pre>
"AAA$"
</pre>

<h2 id="language-string">String</h2>

SPVM has <b>String Type</b>. String is created by <a href="#language-literal-string">String Literal</a> or Type Convertion from <a href="#language-type-array-byte">byte[] Type</a>.

String is immutable and you can't change the each character. You can only get the each character. 

<pre>
# String is Array of byte Type
my $string : string = "Hello";
my $char0 = $string->[0];
my $char1 = $string->[1];
my $char2 = $string->[2];

# Compile Error because String Type is immutable.
$string_const->[0] = 'd';

# Create new String using Type Convertion;
my $bytes = new byte[3];
$bytes->[0] = 'a';
$bytes->[1] = 'b';
$bytes->[2] = 'c';
my $string = (string)$bytes;
</pre>

<h2 id="language-undef">Undefined Value</h2>

Undefined Value is "undef"

<pre>
undef
</pre>

Undefined Value can be assigned to all <a href="#language-type-object">Object Type</a> variable.

Undefined Value can be compared with the value of Object Type using "==" Operator or "!=" Operator. Undefined Value is guaranteed not to be equal to the created object.

If Undefined Value is used in the Condition Part, it will be false.

<h2 id="language-array">Array</h2>

<ul>
  <li><a href="#language-array-summary">Array Summary</a></li>
  <li><a href="#language-array-new">Create Array</a></li>
  <li><a href="#language-array-access">Array Access</a></li>
</ul>
<h3 id="language-array-summary">Array Summary</h3>

Array is a data structure for continuous multiple values.

There are the following types of Array.

<ul>
  <li>
    Numeric Type Array
 </li>
  <li>
    Object Type Array
 </li>
  <li>
    Multi Numeric Type Array
 </li>
</ul>

Numeric Type Array is Array that element type is <a href="#language-type-numeric">Numeric Type</a>.

Numeric Type Array is Array that element type is <a href="#language-type-object">Object Type</a>.

Numeric Type Array is Array that element type is <a href="#language-type-multi-numeric">Multi Numeric Type</a>.

<h3 id="language-array-summary">Create Array</h3>

See <a href="#language-expression-new-array">Create Array</a> to create Array.

<h3 id="language-array-access">Array Access</h3>

Array Access is an operation to access the element of Array to get or set the value.

<pre>
ARRAY->[INDEX]
</pre>

See <a href="#language-expression-get-array-element">Get Array Element Value</a> to get the element value of Array.

See <a href="#language-expression-set-array-element">Set Array Element Value</a> to set the element value of Array.

<h2 id="language-mulnum">Multi Numeric Value</h2>

<ul>
  <li><a href="#language-mulnum-definition">Multi Numeric Type Definition</a></li>
  <li><a href="#language-mulnum-definition">Multi Numeric Type Suffix</a></li>
  <li><a href="#language-mulnum-usage">Multi Numeric Type Usage</a></li>
  <li><a href="#language-mulnum-access">Multi Numeric Type Field Access</a></li>
</ul>

<h3 id="language-mulnum-definition">Multi Numeric Type Definition</h3>

Multi Numeric type represents continuous numeric values. For example, there are three consecutive 32-bit signed integers, two consecutive double-precision floating point numbers. It isplaned to use 3D points, complex numbers, quaternions, etc.

Multi Numeric Type is defined by specifying mulnum_t <a href="#language-class-descriptor">Class Descriptor</a> in <a href="#language-class-definition">Class Definition</a>.

<pre>
# Three consecutive 32bit signed integers
class Point_3i : mulnum_t {
  has x : int;
  has y : int;
  has z : int;
}

# Tow consecutive 64bit floating point numbers
class Complex_2d : mulnum_t {
  x : double;
  y : double;
}
</pre>

Multi Numeric Type must end with "_", Number of Fields, <a href="#language-mulnum-definition">Multi Numeric Type Suffix</a>.

The suffix must correspond to <a href="#language-type-numeric">Numeric Type</a>.

All Fields must be the same <a href="#language-type-numeric">Numeric Type</a>.

The maximum number of Fields is 255.

Multi Numeric Type can be used as <a href="#language-type">Type</a> of <a href="#language-local-var-declaration">Local Variable Declaration</a>.

Multi Numeric Type can be used as an argument <a href="#language-type">Type</a> in <a href="#language-method-definition">Method Definition</a> .

Multi Numeric Type can be used as <a href="#language-type">Type</a> of Return Value in <a href="#language-method-definition">Method Definition</a>.

Multi Numeric Type can be used as <a href="#language-type-basic">Basic Type</a> of <a href="#language-type-array">Array Type</a> .

<pre>
my $points = new Point_3i[5];
</pre>

Reference can be created for Multi Numeric Type value.

<pre>
my $point : Point_3i;
my $point_ref = \$point;
</pre>

<a href="#language-undef">Undefined Value</a> cannot be assigned to Multi Numeric Type value.

See <a href="#language-mulnum-access">Multi Numeric Type Field Access</a> to get and set the value of field of Multi Numeric Type Value.

<h3>Multi Numeric Type Suffix</h3>

List of Multi Numeric Type Suffix.

<table>
  <tr>
    <th>
      <b>Numeric Type</b>
   </th>
    <th>
      Multi Numeric Type Suffix
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      b
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      s
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      i
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      l
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      f
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      d
    </td>
  </tr>
</table>

<h3 id="language-mulnum-usage">Multi Numeric Type Usage</h3>

To use Multi Numeric Type, load a Module using <a href="#language-module-use">use Statement</a>.

<pre>
use Point_3i;
use Complex_2d;
</pre>


Next is <a href="#language-local-var-declaration">Local Variable Declaration</a>. Local Variable Declaration create continuous area for fields of Multi Numeric Type Value on <a href="#language-method-stack">Method Callstack</a>. All fields of of Multi Numeric Type Value are initialized by <a href="#language-type-initial-value">Type Initial Value</a>.

<pre>
my $point : Point_3i;
my $z : Complex_2d;
</pre>

Note that Multi Numeric Type value are not object, so cannot create a Object by <a href="#language-expression-new">new</a> syntax.

<h3 id="language-mulnum-access">Multi Numeric Type Field Access</h2>

<b>Multi Numeric Type Field Access</b> is an operation to access Multi Numeric Type Field to get or set a value.

<pre>
MULTI_NUMERIC_TYPE_VALUE->{FIELD_NAME}
</pre>

See <a href="#language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</a> to get Multi Numeric Type Field Value.

See <a href="#language-expression-set-field-multi-numeric">Set Multi Numeric Field Value</a> to set Multi Numeric Type Field Value.

<h2 id="language-mulnum-array">Multi Numeric Array</h2>
<ul>
  <li><a href="#language-mulnum-array-summary">Multi Numeric Array Summary</a></li>
  <li><a href="#language-mulnum-array-access">Multi Numeric Array Access</a></li>
</ul>

<h3 id="language-mulnum-array-summary">Multi Numeric Array Summary</h3>

<a href="#language-mulnum">Multi Numeric Value</a> can be an element of <a href="#language-array">Array</a>.

<pre>
my $points = new Point_3i[5];

my $zs = new Complex_2d[5];
</pre>

Multi Numeric Array has continuous Multi Numeric Values.

The Element Type is <a href="#language-type-multi-numeric">Multi Numeric Type</a>, not <a href="#language-type-object">Object Type</a>.

For example, Point_3i[5] is continuous 15 (= 3 * 5) count <a href="#language-type-int">int Type</a> Value.

<a href="#language-type">Type</a> of Multi Numeric Array is <a href="#language-type-array">Array Type</a>.

<h3 id="language-mulnum-array-access">Multi Numeric Array Access</h3>

Multi Numeric Array Access is an operation to access Multi Numeric Array to get and set the element value.

<pre>
Array->[INDEX]
</pre>

See <a href="#language-expression-get-array-element">Get Array Element Value</a> to get Array Element Value.

See <a href="#language-expression-set-array-element">Set Array Element Value</a> to get Array Element Value.

<h2 id="language-ref">Reference</h2>
<ul>
  <li><a href="#language-ref-summary">Reference Summary</a></li>
  <li><a href="#language-ref-deref">Dereference</a></li>
</ul>

<h3 id="language-ref">Reference Summary</h3>

Reference is data that indicates the location of <a href="#language-local-var">Local Variable</a> in the memory. Reference is a feature corresponding to Pointer in C language.

You can get Reference of Local Variable using <a href="#language-operator-ref">Reference Operator</a>.

<a href="#language-type-ref">Reference Type</a> is represented by <a href="#language-type-numeric">Numeric Type</a> "&" or <a href="#language-type-multi-numeric ">Multi Numeric Type</a> followed by "&".
Reference types are represented by appending an & after <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-multi-numeric ">Multi Numeric Type</a>.

<pre>
# Numeric Type Reference
my $num : int;
my $num_ref : int& = \$num;

# Multi Numeric Type Reference
my $point : Point_3d;
my $point_ref : Point_3d& = \$point;
</pre>

Target of Reference Operator is Variable of <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-multi-numeric">Multi Numeric Type</a>. <a href="#language-type-object">Object Type</a> Variable or <a href="#language-literal">Literal</a> can't be target of Reference Operator.

<a href="#language-type-ref">Reference Type</a> can be used in Method Argument.

<pre>
# Method Definition
static method sum : void ($out_ref : int&, $in1 : int, $in2 : int) {
  $$out_ref = $in1 + $in2;
}

# Method Call
my $num1 = 1;
my $num2 = 2;
my $out : int;
my $out_ref = \$out;
sum($out_ref, $num1, $num2);
</pre>

<h3 id="language-ref-deref">Dereference</h3>

Dereference is an operation to get and set the value pointed by Reference.

<pre>
# Dereference Numeric Type Reference to get the pointed value
my $num2 = $$num_ref;

# Dereference Numeric Type Reference to set the pointed value
$$num_ref = 3;

# Dereference Mutil Numeric Type Reference to get the pointed value
my $point2 = $$point_ref;

# Dereference Mutil Numeric Type Reference to set the pointed value
$$point_ref = $point2;
</pre>

If the target of Reference Type is <a href="#language-type-multi-numeric">Multi Numeric Type</a>, the setting and getting of Multi Numeric Type Field Value can be done by Arrow Operator.

<pre>
# If the target of Reference Type is Multi Numeric Type, get Multi Numeric Type Field Value
my $x = $point_ref->{x};

# If the Target of Reference Type is Multi Numeric Type, set Multi Numeric Type Field Value
$point_ref->{x} = 1;
</pre>

<h2 id="language-expression">Expression</h2>

<ul>
  <li><a href="#language-expression-summary">Expression Summary</a></li>
  <li><a href="#language-expression-operator">Operator</a></li>
  <li><a href="#language-expression-literal">Literal</a></li>
  <li><a href="#language-expression-undef">Undefined Value</a></li>
  <li><a href="#language-expression-get-local-var">Get Local Variable Value</a></li>
  <li><a href="#language-expression-set-local-var">Set Local Variable Value</a></li>
  <li><a href="#language-expression-set-class-var">Get Class Variable Value</a></li>
  <li><a href="#language-expression-get-class-var">Set Class Variable Value</a></li>
  <li><a href="#language-expression-get-exception-var">Get Exception Variable Value</a></li>
  <li><a href="#language-expression-set-exception-var">Set Exception Variable Value</a></li>
  <li><a href="#language-expression-get-field">Get Field Value</a></li>
  <li><a href="#language-expression-set-field">Set Field Value</a></li>
  <li><a href="#language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</a></li>
  <li><a href="#language-expression-set-field-multi-numeric">Set Multi Numeric Field Value</a></li>
  <li><a href="#language-expression-get-field-multi-numeric-deref">Get Multi Numeric Field Value via Dereference</a></li>
  <li><a href="#language-expression-set-field-multi-numeric-deref">Set Multi Numeric Field Value via Dereference</a></li>
  <li><a href="#language-expression-get-array-element">Get Array Element Value</a></li>
  <li><a href="#language-expression-set-array-element">Set Array Element Value</a></li>
  <li><a href="#language-expression-new">Create Object</a></li>
  <li><a href="#language-expression-new-array">Create Array</a></li>
  <li><a href="#language-expression-array-init">Array Initialization</a></li>
  <li><a href="#language-expression-callsub">Method Call</a></li>
  <li><a href="#language-expression-callsub-class-method-call">Class Method Call</a></li>
  <li><a href="#language-expression-callsub-method-call">Method Call</a></li>
  <li><a href="#language-expression-callsub-function-call">Function Call</a></li>
  <li><a href="#language-expression-current-class">Get Current Class Name</a></li>
  <li><a href="#language-expression-current-file">Get Current File Name</a></li>
  <li><a href="#language-expression-current-line">Get Current Line Number</a></li>
  <li><a href="#language-expression-typecast">Type Cast</a></li>
  <li>(EXPRESSION)</li>
  <li><a href="#language-operator-precedence">Operator Precidence</a></li>
</ul>

<h3 id="language-expression-summary">Expression Summary</h3>

Expression is a syntax component that can be evaluated as a value.

<h3 id="language-expression-operator">Operator</h3>

<a href="#language-operator">Operator</a> is a Expression.

<h3 id="language-expression-literal">Undefined Value</h3>

<a href="#language-undef">Undefined Value</a> is a Expression.

<h3 id="language-expression-undef">Literal</h3>

<a href="#language-literal">Literal</a> is a Expression.

<h3 id="language-expression-get-local-var">Get Local Variable Value</h3>

<b>Get Local Variable Value</b> is a Expression to get <a href="#language-local-var">Local Variable</a> Value.

<pre>
$var
</pre>

<h3 id="language-expression-set-local-var">Set Local Variable Value</h3>

<b>Set Local Variable Value Expression</b> is a Expression to set <a href="#language-local-var">Local Variable</a> Value using <a href="#language-operator-assign">Assignment Operator</a>.

<pre>
$var = RIGHT_EXPRESSION
</pre>

The Assignment must satisfy <a href="#language-type-compatible">Type Compatibility</a>.

Set Local Variable Value Expression returns the value after setting.

If Right Expression is <a href="#language-type-object">Object Type</a>, Reference Count of the object is incremented by 1.

If an object has already been assigned to $var before the assignment, the Reference Count of that object is decremented by 1.

See <a href="#language-scope">Scope</a> to know Garbage Collection of Local Variable.

<h3 id="language-expression-get-class-var">Get Class Variable Value</h3>

<b>Get Class Variable Value Expression</b> is a Expression to get <a href="#language-class-var">Class Variable</a> Value.

<pre>
$CLASS_NAME::CLASS_VARIABLE_NAME
</pre>

"CLASS_NAME::" can be omitted when the Class Variable belongs to own <a href="#language-class">Class</a>.

<pre>
$CLASS_VARIABLE_NAME
</pre>

If you try to get the value of a Class Variable that is not defined, Compile Error occurs.

If you try to access a private Class Variable from outside the Class, Compile Error occurs.

<b>Get Class Variable Value Example:</b>

<pre>
class Foo {
  our $VAR : int;

  static method bar : int () {
    my $var1 = $Foo::VAR;
    my $var2 = $VAR;
  }
}
</pre>

<h3 id="language-expression-set-class-var">Set Class Variable Value</h3>

<b>Set Class Variable Value Expression</b> is a Expression to set <a href="#language-class-var">Class Variable</a> Value using <a href="#language-operator-assign">Assignment Operator</a>.
.

<pre>
$CLASS_NAME::CLASS_VARIABLE_NAME = RIGHT_EXPRESSION
</pre>

"CLASS_NAME::" can be omitted when the Class Variable belongs to own <a href="#language-class">Class</a>.

<pre>
$CLASS_VARIABLE_NAME = RIGHT_EXPRESSION
</pre>

If the assignment does not satisfy <a href="#language-type-compatible">Type Compatibility</a>, Compile Error occurs.

Set Class Variable Value Expression returns the value after setting.

If you try to get the value of a Class Variable that is not defined, Compile Error occurs.

If you try to access a private Class Variable from outside the Class, Compile Error occurs.

If Right Expression is <a href="#language-type-object">Object Type</a>, Reference Count of the object is incremented by 1.

If an object has already been assigned to Class Variable before the assignment, the Reference Count of that object is decremented by 1.

<b>Set Class Variable Value Example:</b>

<pre>
class Foo {
  our $VAR : int;

  static method bar : int () {
    $Foo::VAR = 1;
    $VAR = 3;
  }
}
</pre>

<h3 id="language-expression-get-exception-var">Get Exception Variable Value</h3>

<b>Get Exception Variable Value Expression</b> is a Expression to get the value of <a href="#language-exception-var">Exception Variable</a>.

<pre>
$@
</pre>

Get Exception Variable Value Expression returns the value of <a href="#language-type-string">String Type</a>.

<b>Get Exception Variable Value Example:</b>

<pre>
eval {
  foo();
};

if (my $message = $@) {

}
</pre>

<h3 id="language-expression-set-exception-var">Set Exception Variable Value</h3>

<b>Set Exception Variable Value Expression</b> is a Expression to set the value of <a href="#language-exception-var">Exception Variable</a> using <a href="#language-operator-assign">Assignment Operator</a>.

<pre>
$@ = RIGHT_EXPRESSION
</pre>

Right Expression must be <a href="#language-type-string">String Type</a>.

Returns the value of Exception Variable after setting. This is <a href="#language-type-string">String Type</a>.

The Reference Count of Right Expression is incremented by 1.

If an object has already been assigned to Exception Variable before the assignment, the Reference Count of that object is decremented by 1.

<b>Set Exception Variable Value Example:</b>

<pre>
$@ = "Error";
</pre>

<h3 id="language-expression-get-field">Get Field Value</h3>

<b>Get Field Value Expression</b> is a Expression to get <a href="#language-field">Field</a> Value.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME}
</pre>

Invocant Expression is <a href="#language-type-class">Class Type</a>. If Expression is <a href="#language-type-multi-numeric">Multi Numeric Type</a> Value, The Field Access is <a href="#language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</a>. If Expression is <a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a> Value, The Field Access is ,<a href="#language-expression-get-field-multi-numeric-deref">, otherwise Compile Error occurs.

If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs

Get Field Value Expression returns the value of the Field stored in the object.

Retrun Type is The <a href="#language-type">Type</a> of the Field.

<b>Get Field Value Example:</b>

<pre>
my $point = Point->new;
my $x = $point->{x};
</pre>

<h3 id="language-expression-set-field">Set Field Value</h3>

<b>Set Field Value Expression</b> is a Expression to set <a href="#language-field">Field</a> Value.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_EXPRESSION
</pre>

Invocant Expression is <a href="#language-type-class">Class Type</a>. If Invocant Expression is <a href="#language-type-multi-numeric">Multi Numeric Type</a>, the Field Access is ,<a href="#language-expression-get-field-multi-numeric">Set Multi Numeric Field Value</a>. If Invocant Expression is <a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a>, the Field Access is <a href="#language-expression-get-field-multi-numeric-deref">Set Multi Numeric Field Value via Dereference</a>, otherwise Compile Error occurs.

If the assignment does not satisfy <a href="#language-type-compatible">Type Compatibility</a> of the Type of Field, Compile Error occurs.

If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs.

Set Field Value Expression returns the value of Field after setting. 

Return Value Type is the Type of Field.

If Right Expression is <a href="#language-type-object">Object Type</a>, Reference Count of the object is incremented by 1.

If an object has already been assigned to Field before the assignment, the Reference Count of that object is decremented by 1.

<b>Set Field Value Example:</b>

<pre>
my $point = Point->new;
$point->{x} = 1;
</pre>

<h3 id="language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</h3>

<b>Get Multi Numeric Field Value Expression</b> is a Expression to get Field Value of <a href="#language-mulnum">Multi Numeric Value</a>.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME}
</pre>
<p>
  Invocant Expression is <a href="#language-type-class">Multi Numeric Type</a>. If Invocant Expression is <a href="#language-type-class">Class Type</a>, the Field Access is <a href="#language-expression-get-field">. If Invocant Expression <a href="#language-type-ref-multi-numeric">is Multi Numeric Reference Type</a>, the Field Access is <a href="#language-expression-get-field-multi-numeric-deref">Get Multi Numeric Field Value via Dereference</a>, otherwise Compile Error occurs.
  
If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs

Get Multi Numeric Field Value Expression returns the field value in the Multi Numeric Value.

Retrun Type is The <a href="#language-type">Type</a> of the Field.

<b>Get Multi Numeric Field Value Example:</b>

<pre>
my $z : Complex_2d;
my $re = $z->{x};
</pre>

<h3 id="language-expression-set-field-multi-numeric">Set Multi Numeric Field Value</h3>

Set Multi Numeric Field Value Expression is a Expression to set Field Value of <a href="#language-mulnum">Multi Numeric Value</a> using <a href="#language-operator-assign">Assignment Operator</a>.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_EXPRESSION
</pre>
<

Invocant Expression is <a href="#language-type-class">Multi Numeric Type</a>. If Invocant Expression is <a href="#language-type-class">Class Type</a>, the Field Access is <a href="#language-expression-set-field">Set Field Value</a>. Invocant Expression is <a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a>, <a href="#language-expression-set-field-multi-numeric-deref">Set Multi Numeric Field Value via Dereference</a>, otherwise Compile Error occurs.

If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs.

Set Multi Numeric Field Value Expression returns the value of Field after setting. 

The Assignment must satisfy <a href="#language-type-compatible">Type Compatibility</a>.

Return Value Type is the Type of Field.

<b>Set Multi Numeric Field Value Example:</b>

<pre>
my $z : Complex_2d;
$z->{x} = 2.5;
</pre>

<h3 id="language-expression-get-field-multi-numeric-deref">Get Multi Numeric Field Value via Dereference</h3>

<b>Get Multi Numeric Field Value via Dereference Expression</b> is a Expression to get Field Value of <a href="#language-mulnum">Multi Numeric Value</a> via <a href="#language-deref">Dereference</a>.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME}
</pre>

Invocant Expression is <a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a>. If Invocant Expression is <a href="#language-type-class">Class Type</a>, the Field Access is , <a href="#language-expression-get-field">Get Field Value</a>. If Invocant Expression is <a href="#language-type-multi-numeric">Multi Numeric Type</a>, the Field Access is <a href="#language-expression-get-field-multi-numeric">Get Multi Numeric Field Value</a>, otherwise Compile Error occurs.

If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs

Get Multi Numeric Field Value via Dereference Expression returns the field value in the Multi Numeric Value.

Retrun Type is The <a href="#language-type">Type</a> of the Field.

<b>Get Multi Numeric Field Value via Dereference Example:</b>

<pre>
my $z : Complex_2d;
my $z_ref = \$z;
my $re = $z_ref->{x};
</pre>

<h3 id="language-expression-set-field-multi-numeric-deref">Set Multi Numeric Field Value via Dereference</h3>

Set Multi Numeric Field Value Expression via Dereference is a Expression to set Field Value of <a href="#language-mulnum">Multi Numeric Value</a> via <a href="#language-deref">Dereference</a> using <a href="#language-operator-assign">Assignment Operator</a>.

<pre>
INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_EXPRESSION
</pre>

Invocant Expression is <a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a>. If Invocant Expression is <a href="#language-type-class">Class Type</a>, <a href="#language-expression-set-field">Set Field Value</a>. If Invocant Expression is <a href="#language-type-multi-numeric">Multi Numeric Type</a>, <a href="#language-expression-set-field-multi-numeric">Set Multi Numeric Field Value</a>, otherwise Compile Error occurs.

If the Field Name does not found in the <a href="#language-class">Class</a>, Compile Error occurs

Set Multi Numeric Field Value via Dereference Expression returns the value of Field after setting.

The Assignment must satisfy <a href="#language-type-compatible">Type Compatibility</a>.

Return Value Type is the Type of Field.

<b>Set Multi Numeric Field Value via Dereference Example:</b>

<pre>
my $z : Complex_2d;
my $z_ref = \$z;
$z_ref->{x} = 2.5;
</pre>

<h3 id="language-expression-get-array-element">Get Array Element Value</h3>

<b>Get Array Element Value Expression</b> is a Expression to get a Element Value of <a href="#language-array">Array</a>.

<pre>
ARRAY_EXPRESSION->[INDEX_EXPRESSION]
</pre>

Array Expression must be <a href="#language-type-array">Array Type</a>.

Index Expression must be <a href="#language-type-int">int Type</a> or the Type that become <a href="#language-type-int">int Type</a> by <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a>.

Get Array Element Value Expression returns the Element Value of the Index.

If Array Expression is <a href="#language-undef">Undefined Value</a>, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

<b>Get Array Element Value Example:</b>

<pre>
my $nums = new int[3];
my $num = $nums->[1];

my $points = new Point[3];
my $point = $points->[1];

my $objects : oarray = $points;
my $object = (Point)$objects->[1];
</pre>

<h3 id="language-expression-set-array-element">Set Array Element Value</h3>

Set Array Element Value Expression is a Expression to set a Element Value of a Array using <a href="#language-operator-assign">Assignment Operator</a>.

<pre>
ARRAY_EXPRESSION->[INDEX_EXPRESSION] = RIGHT_EXPRESSION
</pre>

Array Expression must be <a href="#language-type-array">Array Type</a>.

Index Expression must be <a href="#language-type-int">int Type</a> or the Type that become <a href="#language-type-int">int Type</a> by <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a>.

The Assignment must satisfy <a href="#language-type-compatible">Type Compatibility</a>.

Set Array Element Value Expression returns the value of the element after setting.

If Array Expression is <a href="#language-undef">Undefined Value</a>, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

If Right Expression is <a href="#language-type-object">Object Type</a>, Reference Count of the object is incremented by 1.

If an object has already been assigned to Field before the assignment, the Reference Count of that object is decremented by 1.

<b>Set Array Element Value Example:</b>

<pre>
my $nums = new int[3];
$nums->[1] = 3;

my $points = new Point[3];
$points->[1] = Point->new(1, 2);

my $objects : oarray = $points;
$objects->[2] = Point->new(3, 5);
</pre>

<h3 id="language-expression-new">Create Object</h3>

<b>Create Object Expression</b> is a Expression to create Object using <b>new</b> keyword.

<pre>
my $object = new CLASS_NAME;
</pre>

<a href="#language-class">Class</a> that is specified by <a href="#language-token-identifier-class-name">Class Name</a> must be <a href="#language-type-class">Class Type</a>.

Fields of the Object are initialized by <a href="#language-type-initial-value">Type Initial Value</a>.

Created Object Reference count is 0 at first. If the Object is assigned to some Variable by <a href="#language-operator-assign">Assignment Operator</a>, The Reference Count is incremented by 1. If implicite assignment is not done, Temporary Variable is created, the object is assigned to the Temporary Variable.

<b>Create Object Example:</b>

<pre>
my $object = new Foo;
</pre>

Create Object has the following information.

<ul>
  <li>Reference Count</li>
  <li>Back references of <a href="#language-weak-ref">Weaken Reference</a></li>
  <li>Basic Type ID</li>
  <li>Type Dimension(Always 0)</li>
</ul>

<h3 id="language-expression-new-array">Create Array</h3>

<b>Create Array Expression</b> is a Expression to create Array with <b>new</b> Keyword.

<pre>
new Type[ELEMENTS_COUNT_EXPRESSION]
</pre>

Type must be <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-object">Object Type</a>, <a href="#language-type-multi-numeric">Multi Numeric Type</a>.

Elements Count Expression must be <a href="#language-type-int">int Type</a> or the Type that become <a href="#language-type-int">int Type</a> by <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a>.

If Index Expression is lower than 0, a Runtime Exception occurs.

Created Array Length is the value of Elements Count Expression.

All Array Element is initialized by <a href="#language-type-initial-value">Type Initial Value</a>.

All Element is gurantied to be continued on Memory.

Array is <a href="#language-type-array">Array Type</a>. This is also <a href="#language-type-object">Object Type</a>.

<b>Create Array Example:</b>

<pre>
my $nums = new int[3];
my $objects = new Foo[3];
my $objects = new object[3];
my $values = new Complex_2d[3]
</pre>

Created Array has the following information.

<ul>
  <li>Reference Count</li>
  <li>Basic Type ID</li>
  <li>Type Dimension(the value is 1)</li>
  <li>Array Length</li>
</ul>

Multi-Dimention Array is created by the following syntax.

<pre>
# 2 Dimention Array (3 elements of int[] Type)
my $nums = new int[][3];

# 3 Dimention Array (3 elements of int[][] Type)
my $nums = new int[][][3];
</pre>

The max of Dimention of Multi-Dimention Array is 255.

<h3 id="language-expression-array-init">Array Initialization</h3>
<p>
  SPVM has a syntax for Array Initialization to simplify Create Array. Expression is not required.
</p>
<pre>
[]
[Expression1, Expression2, Expression3]
</pre>
<p>
  Array Initialization returns an Array that has the length of the number of elements of Expression.
</p>
<p>
  The type of Array is the type of Expression1 converted to Array Type. If no element is specified, it will be an Array Type of <a href="#language-type-any-object">Any Object Type</a>.
</p>
<p>
  If Expression2 or later does not satisfy <a href="#language-type-compatible">Type Compatibility</a>, a Compile Error will occur.
</p>

<b>Examples:</b>

<pre>
# int array
my $nums = [1, 2, 3];

# double array
my $nums = [1.5, 2.6, 3.7];

# string array
my $strings = ["foo", "bar", "baz"];
</pre>

Array Initialization has another syntax. This is same as above array init syntax, but always the generated object type is Array Type of <a href="#language-type-any-object">Any Object Type</a>. And if count of expression is odd number, a compile error occurs.

<pre>
{}
{Expression1, Expression2, Expression3, Expression4}
</pre>

<b>Examples:</b>

<pre>
# Key values empty
my $key_values = {};

# Key values
my $key_values = {foo => 1, bar => "Hello"};
</pre>

<h3 id="language-expression-callsub">Method Call</h3>

Methods defined by <a href="#language-method-definition">Method Definition</a> can be called from program. There are three types of method calls. <b>Class Method Call</b> and <b>Instance Method Call</b>.

Defined method can be called by Class Method Call except a case that the first argument is <a href="#language-type-self">self Type</a>.

<pre>
ClassName->MethodName(ARGS1, ARGS2, ARGS3, ..., ARGSn);
</pre>

The arguments max count is 255.

If the number of arguments does not match the number of arguments defined in the Method Definition, Compile Error occurs The Type of each argument and the type of the argument defined in Method Definition and <a href = "#language-type-compatible">Type Compatibility</a>, Compile Error occurs.

<b>Class Method Call Example</b>

<pre>
my $ret = Foo->bar(1, 2, 3);
</pre>

<h3 id="language-expression-callsub-function-call">Function Call</h3>

Method which is defined as Class Method is imported as Function using <a href="#language-module-use">use Statement</a>.

<pre>
use Foo(MethodName);
</pre>

<pre>
MethodName(ARGS1, ARGS2, ARGS3, ..., ARGSn);
</pre>

Function Call is <a href="#language-expression">Expression</a>.

<b>Function Call Example</b>

<pre>
class Foo {
  use Fn (copy_string);
  
  static method test : void () {
    my $ret = copy_string("hello");
  }
}
</pre>

<h3 id="language-expression-callsub-method">Instance Method Call</h3>
<p>
  Instance Method Call is a method to call Method which is <a href="#language-method-method">Method</a>. In <a href="#language-method-definition">Method Definition</a>, the first argument is <a href="#language-type-self">self Type</a> If the argument of> is specified, it becomes Method.
</p>
<p>
  Instance Method Call can be done with the following syntax using the object created by <a href="#language-expression-new">Create Object</a>.
</p>
<pre>
OBJECT_EXPRESSION->METHOD_NAME(ARGS1, ARGS2, ARGS3, ..., ARGSn);
</pre>
<p>
  Instance Method Call takes arguments. If the number of arguments does not match the number of arguments defined in the Method Definition, Compile Error occurs The Type of each argument and the type of the argument defined in Method Definition and <a href = "#language-type-compatible">Type Compatibility</a>, Compile Error occurs
</p>
<p>
  Instance Method Call returns Return Value if Return Value is other than <a href="#language-type-void">void Type</a>.
</p>
<p>
  Instance Method Call is <a href="#language-expression">Expression</a>.
<p>
<p>
  <b>Instance Method Call Example</b>
</p>
<pre>
my $point = new Point;
$point->set_x(3);
</pre>
<p>
  Since the object created by <a href="#language-method-new-callback-object">Create Callback Object</a> is a normal object, you can call Method.
</p>
<pre>
OBJECT_EXPRESSION->(ARGS1, ARGS2, ARGS3, ..., ARGSn);
</pre>

<p>
  <b>Example that calls Method from the object created with Create Callback Object</b>
</p>
<p>
  An Example that calls a Method from the object created by Create Callback Object.
</p>
<pre>
my $cb_obj = method : int ($num1 : int, $num2 : int) {
  return $num1 + $num2;
};

my $ret = $cb_obj->(1, 2);
</pre>

<h3 id="language-operator-deref-get">Get value by Dereference</h3>
<p>
  Obtaining a value by Dereference is an operation to obtain the actual value from Reference. It was designed to realize the C joint operator "*".
</p>
<pre>
$VARIABLE
</pre>
<p>
  The variable Type must be Reference Type, otherwise Compile Error occurs.
</p>
<p>
  The value obtained by Dereference returns <a href="#language-expression">Expression</a>.
</p>
<pre>
  <b>Example of getting value by Dereference</b>
</pre>
<pre>
my $num : int;
my $num_ref : int& = \$num;
my $num_deref : int = $$num_ref;

my $z : Complex_2d;
my $z_ref : Complex_2d& = \$z;
my $z_deref : Complex_2d = $$z_ref;
</pre>

<h3 id="language-operator-deref-set">Setting the value with Dereference</h3>
<p>
  Setting a value with Dereference is an operation to set the actual value from Reference. It was designed to realize the C joint operator "*".
</p>
<pre>
$VARIABLE = Expression
</pre>
<p>
  The variable Type must be Reference Type, otherwise Compile Error occurs.
</p>
<p>
  The Type of Expression must match the Type of the variable when dereferenced, otherwise Compile Error occurs.
</p>
<p>
  Setting a value with Dereference returns the set value. This is <a href="#language-expression">Expression</a>.
</p>
<pre>
  <b>Example of setting values ​​with Dereference</b>
</pre>
<pre>
my $num : int;
my $num_ref : int& = \$num;
$$num_ref = 1;

my $z : Complex_2d;
my $z_ref : Complex_2d& = \$z;

my $z2 : Complex_2d;

$$z_ref = $z2;
</pre>

<h3 id="language-expression-current-class">Get Current Class Name</h3>

<b>Get Current Class Name</b> is a Expression to get the current class name by __CLASS__ <a href="#language-token-keyword">Keyword</a>.

<pre>
__CLASS__
</pre>

<p>
  <b>Get Current Class Name Example:</b>
</p>
<pre>
class Foo::Bar {
  static method baz : void () {
    # Foo::Bar
    my $class_name == __CLASS__;
  }
}
</pre>

<h3 id="language-expression-current-class">Get Current File Name</h3>

<b>Get Current File Name</b> is a Expression to get the current file name by __LINE__ <a href="#language-token-keyword">Keyword</a>.

<pre>
__FILE__
</pre>

Current File Name means the relative path from the base path of the module file. For example, if the Module Loaded Path is "/mypath" and the Module name is "Foo::Bar", the absolute path is "/mypath/SPVM/Foo/Bar.spvm" and the relative path is "SPVM/Foo/Bar.spvm". "SPVM/Foo/Bar.spvm" is Current File Name.

<b>Get Current File Name Example:</b>

<pre>
# SPVM/Foo/Bar.spvm
class Foo::Bar {
  static method baz : void () {
    # SPVM/Foo/Bar.spvm
    my $file_name == __FILE__;
  }
}
class Foo::Bar2 {
  static method baz : void () {
    # SPVM/Foo/Bar.spvm
    my $file_name == __FILE__;
  }
}
</pre>

<h3 id="language-expression-current-class">Get Current Line Number</h3>

<b>Get Current Line Number</b> is a Expression to get the current line number of the current file by __LINE__ <a href="#language-token-keyword">Keyword</a>.

<pre>
__LINE__
</pre>

<p>
  <b>Get Current Line Number Example:</b>
</p>
<pre>
class Foo::Bar {
  static method baz : void () {
    # 4
    my $line = __LINE__;
  }
}
</pre>

<h2 id="language-operator">Operator</h2>
<ul>
  <li><a href="#language-operator-summary">Operator</a></li>
  <li><a href="#language-operator-unary">Unary Operator</a></li>
  <li><a href="#language-operator-binary">Binary Operator</a></li>
  <li><a href="#language-operator-sequential">Sequential Operator</a></li>
  <li><a href="#language-operator-arithmetic">Arithmetic Operator</a></li>
  <li><a href="#language-operator-unary-plus">Unary Plus Operator</a></li>
  <li><a href="#language-operator-unary-minus">Unary Minus Operator</a></li>
  <li><a href="#language-operator-add">Addition Operator</a></li>
  <li><a href="#language-operator-subtract">Subtraction Operator</a></li>
  <li><a href="#language-operator-multiply">Multiplication Operator</a></li>
  <li><a href="#language-operator-divide">Division Operator</a></li>
  <li><a href="#language-operator-remainder">Remainder Operator</a></li>
  <li><a href="#language-operator-inc">Increment Operator</a></li>
  <li><a href="#language-operator-dec">Decrement Operator</a></li>
  <li><a href="#language-operator-bit">Bit Operator</a></li>
  <li><a href="#language-operator-bit-and">Bit AND Operator</a></li>
  <li><a href="#language-operator-bit-or">Bit OR Operator</a></li>
  <li><a href="#language-operator-bit-not">Bit NOT Operator</a></li>
  <li><a href="#language-operator-shift">Shift Operator</a></li>
  <li><a href="#language-operator-left-shift">Left Shift Operator</a></li>
  <li><a href="#language-operator-arithmetic-right-shift">Arithmetic Right Shift Operator</a></li>
  <li><a href="#language-operator-logical-right-shift">Logical Right Shift Operator</a></li>
  <li><a href="#language-operator-comparison">Comparison Operator</a></li>
  <li><a href="#language-operator-comparison-numeric">Numeric Comparison Operator</a></li>
  <li><a href="#language-operator-comparison-string">String Comparison Operator</a></li>
  <li><a href="#language-operator-isa">isa Operator</a></li>
  <li><a href="#language-operator-refop">ref Operator</a></li>
  <li><a href="#language-operator-dump">dump Operator</a></li>
  <li><a href="#language-operator-logical">Logical Operator</a></li>
  <li><a href="#language-operator-logical-and">Logical AND Operator</a></li>
  <li><a href="#language-operator-logical-or">Logical OR Operator</a></li>
  <li><a href="#language-operator-logical-not">Logical NOT Operator</a></li>
  <li><a href="#language-operator-concat">String Concatenation Operator</a></li>
  <li><a href="#language-operator-assign">Assignment Operator</a></li>
  <li><a href="#language-operator-assign-special">Special Assignment Operator</a></li>
  <li><a href="#language-operator-ref">Reference Operator</a></li>
  <li><a href="#language-operator-array-length">Array Length Operator</a></li>
  <li><a href="#language-operator-string-length">String Length Operator</a></li>
  <li><a href="#language-operator-scalar">Scalar Operator</a></li>
  <li><a href="#language-operator-isweak">isweak Operator</a></li>
</ul>

<h3 id="language-operator-summary">Operator</h3>

<b>Operator</b> is a <a href="#language-expression">Expression</a> to culcurate number mainly.

<b>Operators</b> are <a href="#language-operator-unary">Unary Operator</a>, <a href="#language-operator-binary">Binary Operator</a>, <a href="#language-operator-inc">Increment Operator</a>, <a href="#language-operator-dec">Decrement Operator</a>, <a href="#language-operator-comparison">Comparison Operator</a>, <a href="#language-operator-logical">Logical Operator</a>, and <a href="#language-operator-assign">Assignment Operator</a>.

<h3 id="language-operator-unary">Unary Operator</h3>

Unary Operator is an Operator placed before <a href="#language-expression">Expression</a>.

<pre>
UNARY_OPERATOR EXPRESSION
</pre>

Unary Operators are <a href="#language-operator-unary-plus">Unary Plus Operator</a>, <a href="#language-operator-unary-minus">Unary Minus Operator</a>, <a href="#language-operator-bit-not">Bit NOT Operator</a>, <a href="#language-operator-logical-not">Logical NOT Operator</a>, <a href="#language-operator-array-length">Array Length Operator</a>, and <a href="#language-operator-string-length">String Length Operator</a>.

Note that <a href="#language-operator-inc">Increment Operator</a> and <a href="#language-operator-dec">Decrement Operator</a> is not Unary Operator.

<h3 id="language-operator-binary">Binary Operator</h3>

Binary Operator is a Operator placed between Left <a href="#language-expresssion">Expression</a> and Right <a href="#language-expresssion">Expression</a>.

<pre>
LEFT_EXPRESSION BINARY_OPERATOR RIGHT_EXPRESSION
</pre>

Binary Operators are <a href="#language-operator-add">Addition Operator</a>, <a href="#language-operator-subtract">Subtraction Operator</a>, <a href="#language-operator-multiply">Multiplication Operator</a>, <a href="#language-operator-divide">Division Operator</a>, <a href="#language-operator-remainder">Remainder Operator</a>, <a href="#language-operator-bit-and">Bit AND Operator</a>, <a href="#language-operator-bit-or">Bit OR Operator</a>, <a href="#language-operator-logical-and">Logical AND Operator</a>, <a href="#language-operator-logical-or">Logical OR Operator</a>, <a href="#language-operator-shift">Shift Operator</a>, and <a href="#language-operator-concat">String Concatenation Operator</a>.

<h3 id="language-operator-sequential">Sequential Operator</h3>

Sequential Operator is an Operator that join "," with multiple <a href="#language-expression">Expressions</a> and return the last Expression.

<pre>
(EXPRESSION1, EXPRESSION2, EXPRESSION3)
</pre>

Expression is executed from Left to Right and the last Expression is return.

<b>Sequential Operator Example:</b>

<pre>
# 3 is assigned to $foo
my $foo = (1, 2, 3);

# $x is 3, $ret is 5
my $x = 1;
my $y = 2;
my $ret = ($x += 2, $x + $y);
</pre>

<h3 id="language-operator-arithmetic">Arithmetic Operator</h3>

<b>Arithmetic Operator</b> is an <a href="#language-operator-summary">Operator</a> that performs arithmetic.

<b>Arithmetic Operators</b> are <a href="#language-operator-add">Addition Operator</a>, <a href="#language-operator-subtract">Subtraction Operator</a>, <a href="#language-operator-multiply">Multiplication Operator</a>, <a href="#language-operator-divide">Division Operator</a>, <a href="#language-operator-remainder">Remainder Operator</a>, <a href="#language-operator-unary-plus">Unary Plus Operator</a>, <a href="#language-operator-unary-minus">Unary Minus Operator</a>, <a href="#language-operator-inc">Increment Operator</a>, and <a href="#language-operator-dec">Decrement Operator</a>.

<h3 id="language-operator-unary-plus">Unary Plus Operator</h3>

Unary Plus Operator is a <a href="#language-operator-unary">Unary Operator</a> represented by "+".

<pre>
+Expression
</pre>

Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> applys to Expression.

After that, returns the value copied from the avobe value.

Return Type of Unary Plus Operator is the Type after <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> is applied.

Unary Plus Operator does not throw <a href="#language-exception">Exception</a>.

<b>Unary Plus Operator Example:</b>

<pre>
my $num = +10;
</pre>

<h3 id="language-operator-unary-minus">Unary Minus Operator</h3>

Unary Minus Operator is a <a href="#language-operator-unary">Unary Operator</a> represented by "-".

<pre>
-Expression
</pre>

Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> applys to Expression.

After that, Unary Minus Operator performs an operation that exactly matches the following operation in C99.

<pre>
-x
</pre>

<a href="#language-type-int">int Type</a> Operation, <a href="#language-type-long">long Type</a> Operation, <a href="#language-type-float">float Type</a> Operation, and <a href="#language-type-double">double Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

Return Type of Unary Minus Operator is the Type after <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> is applied.

Unary Minus Operator does not throw <a href="#language-exception">Exception</a>.

<b>Unary Minus Operator Example:</b>

<pre>
my $num = -10;
</pre>

<h3 id="language-operator-add">Addition Operator</h3>

<b>Addition Operator</b> is a <a href="#language-operator-binary">Binary Operator</a> represtented by "+" to perform addition.

<pre>
LEFT_EXPRESSION + RIGHT_EXPRESSION
</pre>

Left Expression and Right Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied to Left Expression and Right Expression.

After that, Addition Operator performs an operation that exactly matches the following operation in C99.

<pre>
x + y;
</pre>

<a href="#language-type-int">int Type</a> Operation, <a href="#language-type-long">long Type</a> Operation, <a href="#language-type-float">float Type</a> Operation, and <a href="#language-type-double">double Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

Return Type of Addition Operator is the Type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied.

Addition Operator does not throw <a href="#language-exception">Exception</a>.

<h3 id="language-operator-subtract">Subtraction Operator</h3>

<b>Subtraction Operator</b> is a <a href="#language-operator-binary">Binary Operator</a> represtented by "-" to perform Subtraction.

<pre>
LEFT_EXPRESSION - RIGHT_EXPRESSION
</pre>

Left Expression and Right Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied to Left Expression and Right Expression.

After that, Subtraction Operator performs an operation that exactly matches the following operation in C99.

<pre>
x - y;
</pre>

Return Type of Subtraction Operator is the Type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied.

Subtraction Operator does not throw <a href="#language-exception">Exception</a>.

<h3 id="language-operator-multiply">Multiplication Operator</h3>

<b>Multiplication Operator</b> is a <a href="#language-operator-binary">Binary Operator</a> represtented by "*" to perform Multiplication.

<pre>
LEFT_EXPRESSION * RIGHT_EXPRESSION
</pre>

Left Expression and Right Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied to Left Expression and Right Expression.

After that, Multiplication Operator performs an operation that exactly matches the following operation in C99.

<pre>
x * y;
</pre>

<a href="#language-type-int">int Type</a> Operation, <a href="#language-type-long">long Type</a> Operation, <a href="#language-type-float">float Type</a> Operation, and <a href="#language-type-double">double Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

Return Type of Multiplication Operator is the Type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied.

Multiplication Operator does not throw <a href="#language-exception">Exception</a>.

<h3 id="language-operator-divide">Division Operator</h3>

<b>Division Operator</b> is a <a href="#language-operator-binary">Binary Operator</a> represtented by "/" to perform Division.

<pre>
LEFT_EXPRESSION / RIGHT_EXPRESSION
</pre>

Left Expression and Right Expression must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied to Left Expression and Right Expression.

After that, Division Operator performs an operation that exactly matches the following operation in C99.

<pre>
x / y;
</pre>

<a href="#language-type-int">int Type</a> Operation, <a href="#language-type-long">long Type</a> Operation, <a href="#language-type-float">float Type</a> Operation, and <a href="#language-type-double">double Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

Return Type of Division Operator is the Type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied.

In the operation to <a href="#language-type-integral">Integral Type</a>, Division Operator throw <a href="#language-exception">Exception</a> if Right Expression is 0.

In the operation to <a href="#language-type-floating-point">Floating Point Type</a>, Division Operator dose not throw <a href="#language-exception">Exception</a>.

<h3 id="language-operator-remainder">Remainder Operator</h3>

<b>Remainder Operator</b> is a <a href="#language-operator-binary">Binary Operator</a> represtented by "%" to perform Division.

<pre>
LEFT_EXPRESSION % RIGHT_EXPRESSION
</pre>

Left Expression and Right Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.

<a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied to Left Expression and Right Expression.

After that, Remainder Operator performs an operation that exactly matches the following operation in C99.

<pre>
x % y;
</pre>

<a href="#language-type-int">int Type</a> Operation, and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

Return Type of Remainder Operator is the Type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is applied.

Remainder Operator throw <a href="#language-exception">Exception</a> if Right Expression is 0.

<h3 id="language-operator-inc">Increment Operator</h3>

<p>
  <b>Increment Operator</b> is an Operator that adds 1 to the value. the meaning of Increment Operator is different depending on whether the Increment Operator is placed Pre or Post.
</p>
<pre>
# Pre Increment Operator
++LEXICAL_VARIABLE
++CLASS_VARIABLE
++FIELD_ACCESS
++ARRAY_ACCESS
++DEREFERENCE

# Post Increment Operator
LEXICAL_VARIABLE++
CLASS_VARIABLE++
FIELD_ACCESS++
ARRAY_ACCESS++
DEREFERENCE++
</pre>
<p>
  The operand of Increment Operator must <a href="#language-local-var">Local Variable</a>, <a href="#language-class-var">Class Variable</a>, <a href = "#language-field-access">Field Access</a>, <a href="#language-array-access">Array Access</a>, <a href="#language-deref">Dereference</a>, otherwise Compile Error occurs.
</p>
<p>
  The Type of operand of Increment Operator must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error will occur.
</p>

<h4>Pre Increment Operator</h4>

<p>
  Pre Increment Operator adds 1 to the operand and returns the value after increment.
</p>
<p>
  Pre Increment Operator is equivalent to the following Expression. After 1 is added to the operand, <a href="#language-type-convertion-typecast">Type Cast</a> is performed with the operand Type and the value is assinged to original operand.
</p>

<pre>
(OPERAND_EXPRESSION = (TYPE)(OPERAND_EXPRESSION + 1))
</pre>
<p>
  For example, Pre Increment of <a href="#language-type-byte">byte Type</a> value is equivalent to the following Expression:
</p>

<pre>
($num = (byte)($num + 1))
</pre>

<h4>Post Increment Operator</h4>

<p>
  Post Increment Operator add 1 to the operand and returns the value before Increment.
</p>
<p>
  Post Increment Operator is equivalent to the following Expression using <a href="#language-operator-sequential">Sequential Operator</a>. The value of operand is saved in a temporary variable, 1 is added to the operand, <a href="#language-type-convertion-typecast">Type Cast</a> is performed with the operand Type, and the value is assinged to original operand. Then the temporary variable is returned.
</p>
<pre>
(my TMP_VARIABLE = OPERAND_EXPRESSION, OPERAND_EXPRESSION = (TYPE)(OPERAND_EXPRESSION + 1), TMP_VARIABLE)
</pre>

<p>
  For example, Post Increment of <a href="#language-type-byte">byte Type</a> value is equivalent to the following Expression.
</p>

<pre>
(my $tmp = $num, $num = (byte)($num + 1), $tmp)
</pre>

<h3 id="language-operator-dec">Decrement Operator</h3>

<p>
  <b>Decrement Operator</b> is an Operator that subtracts 1 to the value. the meaning of Decrement Operator is different depending on whether the Decrement Operator is placed Pre or Post.
</p>
<pre>
# Pre Decrement Operator
--LEXICAL_VARIABLE
--CLASS_VARIABLE
--FIELD_ACCESS
--ARRAY_ACCESS
--DEREFERENCE

# Post Decrement Operator
LEXICAL_VARIABLE--
CLASS_VARIABLE--
FIELD_ACCESS--
ARRAY_ACCESS--
DEREFERENCE--
</pre>
<p>
  The operand of Decrement Operator must <a href="#language-local-var">Local Variable</a>, <a href="#language-class-var">Class Variable</a>, <a href = "#language-field-access">Field Access</a>, <a href="#language-array-access">Array Access</a>, <a href="#language-deref">Dereference</a>, otherwise Compile Error occurs.
</p>
<p>
  The Type of operand of Decrement Operator must be <a href="#language-type-numeric">Numeric Type</a>, otherwise Compile Error will occur.
</p>

<h4>Pre Decrement Operator</h4>

<p>
  Pre Decrement Operator subtracts 1 to the operand and returns the value after decrement.
</p>
<p>
  Pre Decrement Operator is equivalent to the following Expression. After 1 is subtracted to the operand, <a href="#language-type-convertion-typecast">Type Cast</a> is performed with the operand Type and the value is assinged to original operand.
</p>

<pre>
(OPERAND_EXPRESSION = (TYPE)(OPERAND_EXPRESSION - 1))
</pre>
<p>
  For example, Pre Decrement of <a href="#language-type-byte">byte Type</a> value is equivalent to the following Expression:
</p>

<pre>
($num = (byte)($num - 1))
</pre>

<h4>Post Decrement Operator</h4>

<p>
  Post Decrement Operator subtract 1 to the operand and returns the value before Decrement.
</p>
<p>
  Post Decrement Operator is equivalent to the following Expression using <a href="#language-operator-sequential">Sequential Operator</a>. The value of operand is saved in a temporary variable, 1 is subtracted to the operand, <a href="#language-type-convertion-typecast">Type Cast</a> is performed with the operand Type, and the value is assinged to original operand. Then the temporary variable is returned.
</p>
<pre>
(my TMP_VARIABLE = OPERAND_EXPRESSION, OPERAND_EXPRESSION = (TYPE)(OPERAND_EXPRESSION - 1), TMP_VARIABLE)
</pre>

<p>
  For example, Post Decrement of <a href="#language-type-byte">byte Type</a> value is equivalent to the following Expression.
</p>

<pre>
(my $tmp = $num, $num = (byte)($num - 1), $tmp)
</pre>

<h3 id="language-operator-bit">Bit Operator</h3>
<p>
  Bit Operator is an Operator that performs Bit operation. <a href="#language-operator-bit-and">Bit AND Operator</a>, <a href = "#language-operator-bit-or">Bit OR Operator</a>, <a href="#language-operator-bit-not">Bit NOT Operator</a>.
</p>

<h3 id="language-operator-bit-and">Bit AND Operator</h3>
<p>
  Bit AND is <a href="#language-operator-binary">Binary Operator</a> represented by "&".
</p>
<pre>
LEFT_EXPRESSION & RIGHT_EXPRESSION
</pre>
<p>
  Left Expression and Right Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
<p>
<p>
  <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is performed on Left Expression and Right Expression.
</p>
<p>
  After that, the operation result of Bit AND Operator performs the operation that exactly matches the following operation in C99

</p>
<pre>
x & y;
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

<p>
  The Type of Return Value of Bit AND Operator is the type after <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type</a> is performed.
</p>
<p>
  Bit AND Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-bit-or">Bit OR Operator</h3>
<p>
  Bit OR is <a href="#language-operator-binary">Binary Operator</a> represented by "|".
</p>
<pre>
LEFT_EXPRESSION | RIGHT_EXPRESSION
</pre>
<p>
  Left Expression and Right Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
<p>
<p>
  <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is performed on Left Expression and Right Expression.
</p>
<p>
  After that, the operation result of Bit OR Operator performs the operation that exactly matches the following operation in C99.
</p>

<pre>
x | y;
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

<p>
  The Type of Return Value of Bit OR Operator is the type that is <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Converted</a>.
</p>
<p>
  Bit OR Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-bit-not">Bit NOT Operator</h3>
<p>
  Bit NOT Operator is <a href="#language-operator-unary">Unary Operator</a> represented by "~".
</p>
<pre>
~EXPRESSION
</pre>
<p>
  Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
</p>
<p>
  <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> is performed to Expression before Operation.
</p>
<p>
  After that, the operation result of Bit NOT Operator performs the operation that exactly matches the following operation in C99.
</p>
<pre>
~x
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

<p>
  The Type of Return Value of Bit NOT Operator is the type after <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a>
</p>
<p>
  Bit NOT Operator does not throw <a href="#language-exception">Exception</a>.
</p>
<p>
  <b>Bit NOT Operator Example</b>
</p>
<pre>
my $num = ~0xFF0A;
</pre>

<h3 id="language-operator-shift">Shift Operator</h3>
<p>
  Shift Operator is an operator that performs Bit shift. <a href="#language-operator-left-shift">Left Shift Operator</a>, <a href = "#language-operator-arithmetic-right-shift" > Arithmetic Right Shift Operator</a>, <a href="#language-operator-logical-right-shift">Logical Right Shift Operator</a>.
</p>
<h3 id="language-operator-left-shift">Left Shift Operator</h3>
<p>
  The Left shift is <a href="#language-operator-binary">Binary Operator</a> represented by "<<".
</p>
<pre>
LEFT_EXPRESSION << RIGHT_EXPRESSION
</pre>
<p>
  Left Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
<p>
<p>
  Right Expression must be <a href="#language-type-int">int Type</a>, otherwise Compile Error occurs.
<p>
<p>
  The calculation result of Left Shift Operator is the same as the following calculation in C99.
</p>
<pre>
x << y;
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>

<p>
  Left Shift Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-arithmetic-right-shift">Arithmetic Right Shift Operator</h3>
<p>
  Arithmetic Right Shift Operator is <a href="#language-operator-binary">Binary Operator</a> represented by ">>".
</p>
<pre>
LEFT_EXPRESSION >> RIGHT_EXPRESSION
</pre>
<p>
  Left Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
<p>
<p>
  First, for <a href="#language-expression">Left Expression</a>, <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> is performed.
</p>
<p>
  Right Expression must be <a href="#language-type-int">int Type</a>, otherwise Compile Error occurs.
<p>
<p>
  The operation result of Arithmetic Right Shift Operator is the operation that exactly matches the following operation in C99.
</p>
<pre>
x >> y;
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>
 
<p>
  Arithmetic Right Shift Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-logical-right-shift">Logical Right Shift Operator</h3>
<p>
  Logical Right Shift Operator is <a href="#language-operator-binary">Binary Operator</a> represented by ">>>".
</p>
<pre>
LEFT_EXPRESSION >>> RIGHT_EXPRESSION
</pre>
<p>
  Left Expression must be <a href="#language-type-integral">Integral Type</a>, otherwise Compile Error occurs.
</p>
<p>
  Right Expression must be <a href="#language-type-int">int Type</a>, otherwise Compile Error occurs.
<p>
<p>
  The calculation result of Logical Right Shift Operator is the same as the following calculation in C99.
</p>
<pre>
(SIGNED_INTEGRAL_TYPE_CAST)((UNSINGED_INTEGRAL_TYPE_CAST)x >> y);
</pre>

<a href="#language-type-int">int Type</a> Operation and <a href="#language-type-long">long Type</a> Operation are defined corresponding to <a href="#language-c99-type">C99 Type</a>
 
<p>
  Logical Right Shift Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-comparison">Comparison Operator</h3>
<p>
  Comparison Operator is an Operator that is placed between Left Expression and Right Expression to compare the size, and return True/False Value.
</p>
<pre>
LEFT_EXPRESSION COMPARISON_OPERATOR RIGHT_EXPRESSION
</pre>
<p>
  Comparison Operators are <a href="#language-operator-comparison-numeric">Numeric Comparison Operator</a>, <a href="#language-operator-comparison-string">String Comparison Operator</a>, and <a href="#language-operator-isa">isa Operator</a>.
</p>

<h3 id="language-operator-comparison-numeric">Numeric Comparison Operator</h3>
<p>
  <b>Numeric Comparison Operator</b> is a <a href="#language-operator-comparison">Comparison Operator</a> that is placed between Left Expression and Right Expression to compare the size of number or check the equqlity of objects.
</p>
<pre>
LEFT_EXPRESSION NUMERIC_COMPARISON_OPERATOR RIGHT_EXPRESSION
</pre>
<p>
  A list of Numeric Comparison Operators.
</p>
<table>
  <tr>
    <th>Operator</th>
    <th>Comparable Type</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION == RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type, Left Expression and Right Expression are Object Type (including Undefined Value)
    </td>
    <td>
      Left Expression and Right Expression are equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION != RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type, Left Expression and Right Expression are Object Type (including Undefined Value)
    </td>
    <td>
      Left Expression and Right Expression are not equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION > RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type
    </td>
    <td>
      Left Expression is greater than Right Expression
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION >= RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type
    </td>
    <td>
      Left Expression is greater than or equal to Right Expression
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION < RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type
    </td>
    <td>
      Left Expression is less than Right Expression
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION <= RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type
    </td>
    <td>
      Left Expression is less than or equal to Right Expression
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION <=> RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are Numeric Type
    </td>
    <td>
      If Left Expression is greater than Right expression, return 1. If Left Expression is lower than Right expression, return -1. If Left Expression is equals to Right expression, return 0.
    </td>
  </tr>
</table>
<p>
  The Types of Left Expression and Right Expression Comparable Types, otherwise Compile Error occurs.
</p>
<p>
  In Numeric Type Comparison, <a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a> is performed for Left Expression and Right Expression.
</p>
<p>
  After that, the Numeric Comparison Operation is performed that exactly matches the following operation in C99.
</p>
<pre>
# Numeric Type Comparison, Object Type Comparison
(int32_t)(x == y);
(int32_t)(x != y);

# Numeric Type Comparison
(int32_t)(x > y);
(int32_t)(x >= y);
(int32_t)(x < y);
(int32_t)(x <= y);
(int32_t)(x > y ? 1 : x < y ? -1 : 0);
</pre>

For Numeric Type Operation(==, !=, >, >=, <, <=), <a href="#language-type-int">int Type</a> Operation, <a href="#language-type-long">long Type</a> Operation, <a href="#language-type-float">float Type</a> Operation, <a href="#language-type-double">double Type</a> Operation is defined.

And Object Type Operation(==, !=) is defined.

<p>
  The Type of Return Value of the Numeric Comparison Operator is <a href="#language-type-int">int Type</a>.
</p>

<p>
  Numeric Comparison Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-comparison-string">String Comparison Operator</h3>
<p>
  <b>String Comparison Operator</b> is a <a href="#language-operator-comparison">Comparison Operator</a> that is placed between Left Expression and Right Expression to compare String Size in dictionary order.
</p>
<pre>
LEFT_EXPRESSION STRING_COMPARISON_OPERATOR RIGHT_EXPRESSION
</pre>
<p>
  Left Expression and Right Expression must be <a href="#language-type-string">String Type</a>.
</p>
<p>
  A list of String Comparison Operators.
</p>
<table>
  <tr>
    <th>Operator</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION eq RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION ne RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression and Right Expression are not equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION gt RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression is greater than Right Expression in dictionary Expression order.
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION ge RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression is greater than or equal to Right Expression compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION lt RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression is smaller than Right Expression when compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION le RIGHT_EXPRESSION
    </td>
    <td>
      Left Expression is less than or equal to Right Expression compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_EXPRESSION cmp RIGHT_EXPRESSION
    </td>
    <td>
      If Left Expression is greater than Right expression, return 1. If Left Expression is lower than Right expression, return -1. If Left Expression is equals to Right expression, return 0.
    </td>
  </tr>
</table>
<p>
  The Type of Return Value of the String Comparison Operator is <a href="#language-type-int">int Type</a>. If the condition is met, returns 1, otherwise 0.
</p>

<h3 id="language-operator-isa">isa Operator</h3>
<p>
  <b>isa Operator</b> is a <a href="#language-operator-comparison">Comparison Operator</a> to check whether Left Expression satisfies Right Type.
</p>

<pre>
LEFT_EXPRESSION isa RIGHT_TYPE
</pre>
<p>
  isa Operator has three behaviors, depending on Right Type.
</p>
<p>
  1. If Right Type is <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-multi-numeric">Multi Numeric Type</a>, <a href="#language-type-any-object">Any Object Type</a>, <a href="#language-type-ref">Reference Type</a>, isa operator checks whether the Type of Left Expression is same as Right Type. This check is done at compile time and isa operator is replaced by <a href="#language-type-int">int Type</a> value. If their types is same, replaced by 1, otherwise by 0.
</p>
<p>
  2. If the Right Type is <a href="#language-type-class">Class Type</a>, isa operator checks whether the Type of Left Expression is same as Right Type at Run Time. If their types are same, <a href="#language-type-int">int Type</a> 1 is return, otherwise 0. The Type of Left Expression must be <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.
</p>
<p>
  3. If the Right Type is <a href="#language-type-callback">Callback Type</a>, isa Operator checks whether the Type of Left Expression satisfy the Callback Type at Run Time. If Left Expression satisfies the Callback Type, returns <a href="#language-type-int">int Type</a> 1, otherwise 0. The Type of Left Expression must be <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.
</p>

<h3 id="language-operator-refop">ref Operator</h3>

<b>ref Operator</b> is a Operator to get type name of the object.

<pre>
ref EXPRESSION
</pre>

ref Operator return type name if the object defined. Otherwise return undef.

If EXPRESSION is not a object type, a compile error occurs.

<h3 id="language-operator-dump">dump Operator</h3>

<b>dump Operator</b> is a Operator to dump object value.

<pre>
dump EXPRESSION
</pre>

dump Operator return the dump string.

If EXPRESSION is not a object type, a compile error occurs.

The contents of the dumped string may vary from SPVM version to version. Please use dump operator only for viewing the content of object data.

<h3 id="language-operator-logical">Logical Operator</h3>
<p>
  Logical Operator is an Operator that performs logical operations,<a href="#language-operator-logical-and">Logical AND Operator</a><a href="#language-operator-logical-or"_or Logical Operator</a><a href="#language-operator-logical-not">Logical NOT Operator</a>
</p>
<p>
  Logical Operator returns <a href="#language-expression">Expression</a>
</p>

<h3 id="language-operator-logical-and">Logical AND Operator</h3>
<p>
  Logical AND Operator is a <a href="#language-expresssion"=Expression</a><a href="#language-operator-binary">Binary Operator</a>
</p>
<pre>
LEFT_EXPRESSION && RIGHT_EXPRESSION
</pre>
<p>
  Logical AND Operator のReturn ValueのTypeは,<a href="#language-type-int">int Type</a>.
</p>
<p>
  Logical AND Operator behaves as follows:
</p>
<p>
  1. Run the <a href="#language-type-convertion-bool">Bool Type Conversion</a> to Left Expression.
</p>
<p>
  2. If the value of Left Expression is non-zero, execute the <a href="#language-type-convertion-bool" <#language-type-convertion-bool" for the Right Expression, execute the</a> and return that value.
</p>
<p>
  3. If the value of Left Expression is 0, it returns that value.
</p>
<p>
  Logical AND Operator returns <a href="#language-expression">Expression</a>
</p>
<p>
  Logical AND Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-logical-or">Logical OR Operator</h3>
<p>
  Logical OR Operator is a logical OR operation that is "<a href="#language-expresssion">Expression</a> is an operand of <a href="#language-operator-binary">Binary Operator</a>
</p>
<pre>
LEFT_EXPRESSION || RIGHT_EXPRESSION
</pre>
<p>
  Logical OR Operator behaves as follows:
</p>
<p>
  Logical OR Operator のReturn ValueのTypeは,<a href="#language-type-int">int Type</a>.
</p>
<p>
  1. Run the <a href="#language-type-convertion-bool">Bool Type Conversion</a> to Left Expression.
</p>
<p>
  2. If the value of Left Expression is 0, the <a href="#language-type-convertion-bool"</a> and returns that value for Right Expression.
</p>
<p>
  3. If the value of Left Expression is non-zero, it returns that value.
</p>
<p>
  Logical OR Operator は<a href="#language-expression">Expression</a>を返します。
</p>
<p>
  Logical OR Operator returns <a href="#language-expression">Expression</a>
</p>

<h3 id="language-operator-logical-not">Logical NOT Operator</h3>
<p>
  Logical NOT Operator is an operator to the Left of expression to perform logical NOT operations,<a href="#language-expression"_Expression</a> returning <a href="#language-operator-binary">Unary Operator</a> For more information about Expression, see <a href="#language-expresssion">Expression</a>.
</p>
<pre>
!EXPRESSION
</pre>
<p>
  Logical NOT Operator のReturn ValueのTypeは,<a href="#language-type-int">int Type</a>.
</p>
<p>
  Logical NOT Operator executes <a href="#language-type-convertion-bool"</a>=$Bool Type Conversion for Expression, returns 1 if its value is 0, and 0 if it is not 0.
</p>
<p>
  Logical NOT Operator returns <a href="#language-expression">Expression</a>
</p>
<p>
  Logical NOT Operator does not throw <a href="#language-exception">Exception</a>.
</p>

<h3 id="language-operator-concat">String Concatenation Operator</h3>
<p>
  String StringOn Operator is a <a href="#language-operator-binary">Binary Operator</a>.
</p>
<pre>
LEFT_EXPRESSION . RIGHT_EXPRESSION
</pre>
<p>
  If the Left Expression or Right Expression was</a><a href="#language-type-numeric">Numeric Type=<a href="#language-type-convertion-numeric-to-string=numeric>to-string</a> href="#language-String Type-</a>=>stringtype</a> convertion</a> converts it to a String.
</p>
</p>
<p>
  Both Left Expression and Right Expression must be <a href="#language-type-string">String Type</a> There is an otherwise Compile Error. </p>
</p>
<p>
  String Concatenation Operator concatenates the <a href="#language-string">String</a> represented by Left Expression and Right Expression and returns a new String.
</p>
<p>
  String Concatenation Operator retruns <a href="#language-expression">Expression</a>, The Type is <a href="#language-type-string">String Type</a>.
</p>
<p>
  If both Left Expression and Right Expression were <a href="#language-literal-string">String Literal</a>, a string Literal concatenated at compile time is generated. You can concatenate String Literal with string Concatenation Operator without being aware of the cost of performance.
</p>
<p>
  If Left expression or Right Expression is <a href="#language-undef">Undefined Value</a> <a href="#language-exception">Exception</a> occurs at Run Time.
</p>
<p>
  <b>String Concatenation Operator Example</b>
</p>
<pre>
my $str = "abc" . "def";
my $str = "def" . 34;
my $str = 123 . 456;
</pre>
<h3 id="language-operator-assign">Assignment Operator</h3>
<p>
  Assignment Operator is a <a href="#language-operator-binary">Binary Operator</a> for assignment, expressed in "=".
</p>
<pre>
LEFT_EXPRESSION = RIGHTH_EXPRESSION
</pre>
<p>
  Assignment Operator has multiple meanings depending on the Right and Left sides. Please refer to each item.
</p>
<p>
  In Assignment Operator, the Left Expression is evaluated after the Right Expression is evaluated. This is with the exception of expression being executed from Left to Right as a rule.
</p>

<ul>
  <li><a href="#language-expression-set-local-var">Set Local Variable Value</a></li>
</ul>

<h3 id="language-operator-assign-special">Special Assignment Operator</h3>
<p>
  Special Assignment Operator is a <a href="#language-operator-binary"_binary operator</a> and <a href="#language-operator-assign">Assignment Operator</a><a href="#language-operator-binary</a></a>.
</p>
<pre>
LEFT_EXPRESSION SPECIAL_ASSIGNMENT_OPERATOR  RIGHT_EXPRESSION
</pre>
<p>
  Left ExpressionとRight Expressionが<a href="#language-type-compatible">Type Compatibility</a>を満たさない場合は,Compile Error occurs
</p>
<p>
  <b>List of Special Assignment Operators</b>
</p>
<p>
  List of Special Assignment Operators
</p>
<table>
  <tr>
    <td>Addition Assignment Operator </td>
    <td>+=</td>
  </tr>
  <tr>
    <td>Subtraction Assignment Operator </td>
    <td>-=</td>
  </tr>
  <tr>
    <td>Multiplication Assignment Operator </td>
    <td>*=</td>
  </tr>
  <tr>
    <td>Division Assignment Operator </td>
    <td>/=</td>
  </tr>
  <tr>
    <td>Remainder Assignment Operator </td>
    <td>%=</td>
  </tr>
  <tr>
    <td>Bit AND Assignment Operator </td>
    <td>&=</td>
  </tr>
  <tr>
    <td>Bit OR Assignment Operator </td>
    <td>|=</td>
  </tr>
  <tr>
    <td>Left Shift Assignment Operator </td>
    <td><<=</td>
  </tr>
  <tr>
    <td>Arithmetic Right Shift Assignment Operator </td>
    <td>>>=</td>
  </tr>
  <tr>
    <td>Logical Right Shift Operator</td>
    <td>>>>=</td>
  </tr>
</table>
<p>
  The Special Assignment Operator is deployed as follows:
</p>
<pre>
# Before unexpanding
LEFT_EXPRESSION SPECIAL_ASSIGNMENT_OPERATOR RIGHT_EXPRESSION

# After unwinding
LEFT_EXPRESSION ASSIGNMENT_OPERATOR (LEFT EXPRESSION TYPE CAST)(LEFT_EXPRESSION SPECIFIC_OPERATOR RIGHT_EXPRESSION)
</pre>
<p>
  For example, for add assignment Operator, it is expanded as follows:
</p>
<pre>
# Before unexpanding x is <a href="#language-type-byte">byte Type</a>
$x += 1;

# After unwinding
$x = (byte)($x + 1)
</pre>
<p>
  <b>Special Assignment Operator Example</b>
</p>
<p>
  Special Assignment Operator Example
</p>
<pre>
$x += 1;
$x -= 1;
$x *= 1;
$x /= 1;
$x &= 1;
$x |= 1;
$x ^= 1;
$x %= 1;
$x <<= 1;
$x >>= 1;
$x >>>= 1;
</pre>

<h3 id="language-operator-ref">Reference Operator</h3>
<p>
  The Reference Operator is an Operator that retrieves the address of a variable for <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-multi-numeric">Multi Numeric Type</a>. Designed to achieve c address Operator "&".
</p>
<pre>
\VARIABLE
</pre>
<p>
  If the variable is not numeric type or Multi Numeric Type, Compile Error occurs
</p>
<p>
  Reference Operator returns expression. The type returned is <a href="#language-type-ref">Reference Type</a>.
</p>
<pre>
  <b>Reference Operator Example</b>
</pre>
<pre>
my $num : int;
my $num_ref : int& = \$num;

my $z : Complex_2d;
my $z_ref : Complex_2d& = \$z;
</pre>
<p>
  For a detailed description of Reference, see <a href="#language-ref">Reference</a>.
</p>

<h3 id="language-operator-array-length">Array Length Operator</h3>
<p>
  Array Length Operator is a <a href="#language-array">Array</a></a><a href="#language-operator-binary">Unary Operator</a>
</p>
<pre>
@RIGHT EXPRESSION
</pre>
<p>
  Right Expression must be an Array Type, otherwise Compile Error occurs.
</p>
<p>
  Array Length Operator returns array length for <a href="#language-type-int">int Type</a> value.
</p>
<p>
  Array Length Operator returns <a href="#language-expression">Expression</a>
</p>
<p>
  <b>Array Length Operator Example</b>
</p>
<p>
  Array Length Operator Example
</p>
<pre>
my $nums = new byte[10];
my $length = @$nums;
</pre>
<p>
  Note that SPVM does not have the idea of a context in Perl, and array length operators always return Array Length.
</p>

<h3 id="language-operator-string-length">String Length Operator</h3>
<p>
  String Length Operator is a <a href="#language-string">String</a></a> <a href="#language-operator-binary">Unary Operator</a>
</p>
<pre>
length RIGHT_EXPRESSION
</pre>
<p>
  Right Expression must be <a href="#language-type-string">String Type</a>, otherwise Compile Error occurs.
</p>
<p>
  The String Length Operator returns the length of the String as a <a href="#language-type-int">int Type</a> value. String Length The length of the String returned by the Operator is the length when viewed as a byte string.
</p>
<p>
  String Length Operator returns the <a href="#language-expression">Expression</a>
</p>
<p>
  <b>String Length Operator Example</b>
</p>
<p>
  String Length Operator Exampleです。
</p>
<pre>
my $nums = "abcde";
my $length = length $nums;
</pre>

<h3 id="language-operator-scalar">Scalar Operator</h3>
<p>
  Scalar Operator is an Operator that returns the given value itself without doing anything. It is provided only to clarify the meaning of <a href="#language-operator-array-length">Array Length Operator operator</a>
</p>
<pre>
scalar RIGHT_EXPRESSION
</pre>
<p>
  Right Expressionは<a href="#language-operator-array-length">Array Length Operator</a>でなければなりません。 otherwise Compile Error occurs.
</p>
<p>
  Scalar Operator returns Expression.
</p>
<p>
  <b>Scalar Operator Example</b>
</p>
<p>
  Scalar Operator Example
</p>
<pre>
my $nums = new int[3];
foo(scalar @$nums);
</pre>

<h3 id="language-operator-isweak">isweak Operator</h3>
<p>
  isweak Operator is an Operator that checks whether Field is</a><a href="#language-weak-ref">Weaken Reference.</a>
</p>
<pre>
isweak VARIABLE->{FIELD_NAME};
</pre>
<p>
  The Type of object Expression must be</a><a href="#language-type-class">Class Type.< otherwise Compile Error occurs.
</p>
<p>
  Field Name must be a existed Field Name, otherwise Compile Error occurs.
</p>
<p>
  The Type of the value stored in field must be <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.
</p>
<p>
  If the value stored in field at Run Time is</a> <a href="#language-undef">Undefined Value, it returns false. This is <a href="#language-expression">Expression</a>
</p>
<p>
  isweak Operator returns <a href="#language-type-int" <</a></a> if Field is weaken reference, or 0. This is <a href="#language-expression">Expression</a>
</p>

<h3 id="language-operator-operator-precedence">Precidence</h3>
<p>
  Operator Precidence is the following street. The lower you go, the higher your priority.
</p>
<table>
  <tr>
    <th> join direction</th>
    <th> Operator</th>
  </tr>
  <tr>
    <td>
      Right Join
    </td>
    <td>
      <ul>
      Assignment Operator"=" <br>
      Add Assignment Operator"+=" <br>
      Subtraction Assignment Operator "-="<br>
      Multiply Assignment Operator "*=" <br>
      Division Assignment Operator "/=" <br>
      Remainder Assignment Operator "%=" <br>
      Bit ANDAssignment Operator "&=" <br>
      Bit ORAssignment Operator "|=" <br>
      Bit Exclusive ORAssignment Operator "^=" <br>
      Left Shift Assignment Operator"<</<br>
      Arithmetic Right Shift Assignment Operator ">>=" <br>
      Logical Right Shift Operator ">>>="<br>
      String Join Assignment Operator ".="
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Logical OR Operator "| | "
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Logical AND Operator "&&"
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Bit OR Operator "|"<br>
      Bit XOR Operator "^"
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Bit AND Operator "&"
    </td>
  </tr>
  <tr>
    <td>
      Non Associative
    </td>
    <td>
      Numerical Equivalence Operator"==" <br>
      Numeric inequality Operator "!=" <br>
      String Equivalent Operator "eq"<br>
      String Inequality Operator"ne"<br>
    </td>
  </tr>
  <tr>
    <td>
      Non Associative
    </td>
    <td>
      Numerical value operator ">" <br>
      Number less Operator"""<br>
      Numerical equivalent Operator ">=" <br>
      Numerical or equivalent Operator "<="<br>
      String Large Operator"gt"<br>
      String-large or equivalent Operator"ge"<br>
      String less Operator"lt"<br>
      String less or equivalent Operator"le"<br>
      isa Operator"isa"
    </td>
  </tr>
  <tr>
    <td>
      Left Join 
    </td>
    <td>
      Left Shift Operator"<<br>
      Signed Right Shift Operator ">>" <br>
      Unsigned Right Shift Operator ">>>"
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Addition Operator"+"<br>
      Subtraction Operator"-" <br>
      String StringOn Operator "."
    </td>
  </tr>
  <tr>
    <td>
      Left Join
    </td>
    <td>
      Sand Operator"*" <br>
      Division Operator "/" <br>
      Remainder Operator"%"
    </td>
  </tr>
  <tr>
    <td>
      Right Join
    </td>
    <td>
      Logical NOT Operator "!"<br>
      Bit NOT Operator "~"<br>
      Reference Operator  "\"<br>
      Unary Plus Operator "+"<br>
      Unary Minus Operator "-"<br>
      Array Length Operator "@"<br>
      Dereference Operator "$"<br>
      Type Cast"(TypeName)"
      Scalar Operator "scalar"<br>
      String Length Operator "length"<br>
      require keyword "require"<br>
    </td>
  </tr>
  <tr>
    <td>
      Non Associative
    </td>
    <td>
      Pre Increment Operator "++"<br>
      Post Increment Operator "++"<br>
      Pre Decrement Operator "--"<br>
      Post Decrement Operator "--"
    </td>
  </tr>
  <tr>
    <td>
      Right Join
    </td>
    <td>
      Arrow Operator "->"<br>
    </td>
  </tr>
</table>
<p>
  Operator Precidence can be a top priority by using "()".
</p>
<pre>
#  a * b is the first
a * b + c

# b + c is the first
a * (b + c)
</pre>
<h2 id="language-statement">Statement</h2>
<p>
  Statement can be written more than one in <a href="#language-scope-scope-block">Scope Block</a> for a single process. <a href="#language-expression">Expression</a> is not evaluated as a value.
</p>
<p>
  <b>List of Statements</b>
</p>
<p>
  List of Statements
</p>
<ul>
  <li><a href="#language-statement-if">if Statement</a></li>
  <li><a href="#language-statement-switch">switch Statement</a></li>
  <li><a href="#language-statement-case">case Statement</a></li>
  <li><a href="#language-statement-while">while Statement</a></li>
  <li><a href="#language-statement-for">for Statement</a></li>
  <li><a href="#language-statement-default">default Statement</a></li>
  <li><a href="#language-statement-block-simple">Simple Block</a></li>
  <li><a href="#language-statement-eval">eval Statement</a></li>
  <li><a href="#language-statement-ifrequire">if requireStatement</a></li>
  <li><a href="#language-statement-next">next Statement</a></li>
  <li><a href="#language-statement-last">last Statement</a></li>
  <li><a href="#language-statement-break">break Statement</a></li>
  <li><a href="#language-statement-return">return Statement</a></li>
  <li><a href="#language-statement-die">die Statement</a></li>
  <li><a href="#language-statement-weaken">weaken Statement</a></li>
  <li><a href="#language-statement-unweaken">unweaken Statement</a></li>
  <li><a href="#language-statement-expression">expression Statement</a></li>
  <li><a href="#language-statement-print">print Statement</a></li>
  <li><a href="#language-statement-warn">warn Statement</a></li>
  <li><a href="#language-statement-empty">empty Statement</a></li>
</ul>
<h3 id="language-statement-if">if Statement</h3>
<p>
  If Statement is a statement for conditional branching.
</p>
<pre>
if (EXPRESSION) {

}
</pre>
<p>
  Expression <a href="#language-type-convertion-bool">Bool Type Conversion</a> is executed and Block is executed if the value is non-zero.
</p>
<p>
  If you want to write more than one condition, you can continue with "elsif Statement". The condition determination is performed from above, and each Expression is <a href="#language-type-convertion-bool">Bool Type Conversion</a> is executed, and a corresponding Block is executed if the value is non-zero.
</p>
<pre>
if (EXPRESSION) {

}
elsif(EXPRESSION) {

}
</pre>

<p>
  You can use "elseStatement" to describe what happens if or if the elsif Statement does not meet the criteria. If the if statement and elsif statement condition determination are all false, the statement inside the elseBlock is executed. Elsif Statement does not have to be.
</p>

<pre>
if (EXPRESSION) {

}
elsif (EXPRESSION) {

}
else {

}
</pre>
<p>
  <b>if Statement Example</b>
</p>
<p>
  An example of if Statement.
</p>
<pre>
my $flag = 1;

if ($flag == 1) {
  print "One \ n";
}
elsif ($flag == 2) {
  print "Tow \ n";
}
else {
  print "Other";
}
</pre>
<p>
  The if Statement is internally surrounded by an invisible Simple Block.
</p>
<pre>
{
  if (EXPRESSION) {

  }
}
</pre>
<p>
  elsif is internally expanded into if Statement and else Statement.
</p>
<pre>
#Before deployment
if (EXPRESSION1) {

}
elsif (EXPRESSION2) {

}
else {

}

#After deployment
if (EXPRESSION1) {
}
else {
  if (EXPRESSION2) {

  }
  else {

  }
}
</pre>
<p>
  When a variable is declared in the conditional part of if Statement, it must be surrounded by invisible <a href="#language-scope-block-statement-simple">Simple Block</a>. Be aware that elsif is internally expanded into if Statement and else Statement.
</p>
<pre>
#Before deployment
my $num = 1;
if (my $num = 2) {

}
elsif (my $num = 3) {

}
else {

}

#After deployment
my $num = 1;
{
  if (my $num = 2) {

  }
  else {
    {
      if (my $num = 3) {
        
      }
      else {
        
      }
    }
  }
}
</pre>

<h3 id = "language-statement-switch">switch Statement</h3>
<p>
  The switch statement is a statement for conditional branching with an integer of <a href="#language-type-int">int Type</a> as a condition. Faster than if Statement if the condition is an integer of <a href="#language-type-int">int Type</a> and there are many branches.
</p>
<pre>
switch (CONDITION_EXPRESSION) {
  case constant 1: (

    break;
  }
  case constant 2: {

    break;
  }
  case constant n: {
    break;
  }
  default: {

  }
}
</pre>
<p>
  As the condition Expression, <a href="#language-expression">Expression</a> can be specified. <a href="#language-type-convertion-bool">Bool Type Conversion</a> is executed for the condition Expression.
</p>
<p>
  The constants specified in case Statement are <a href="#language-type-byte">byte Type</a> or <a href="#language-type-int">int Type</a> constants. must be. For a constant of <a href="#language-type-byte">byte Type</a>, type conversion to <a href="#language-type-int">int Type</a> at compile time. Will be done. The value of enumType and Constant Method of <a href="#language-type-int">int Type</a> are constants of <a href="#language-type-int">int Type</a>. As it is expanded at the time of syntax analysis, it can be used.
</p>
<p>
  The constants specified in the case statement must not overlap. If there are duplicates, Compile Error occurs
</p>
<p>
  If the value specified in the condition Expression matches the value specified in the case statement, jump to the position of that case statement.
</p>
<p>
  If there is no match and a default statement is specified, jump to the default statement position. If no default statement is specified, switch block will not be executed.
</p>
<p>
  A switch statement requires at least one case statement, otherwise Compile Error will occur.
</p>
<p>
  The default Statement is optional.
</p>
<p>
  Only case statement and default statement can be described directly under switch block.
</p>
<p>
  The case and default Blocks can be omitted.
</p>
<pre>
switch (CONDITION_EXPRESSION) {
  case constant 1:
  case constant 2:
  {
    break;
  }
  default:
}
</pre>
<p>
  If you use break Statement, you can exit from the switch block.
</p>

<pre>
switch (CONDITION_EXPRESSION) {
  case constant 1: (
    break;
  }
  case constant 2: {
    break;
  }
  case constant n: {
    break;
  }
  default: {

  }
}
</pre>
<p>
  If a case Block exists, the last Statement must be a break Statement or a returnl Statement, otherwise Compile Error will occur.
</p>

<p>
  <b>Switch Statement Example</b>
</p>
<p>
  An example of a switch statement.
</p>
<pre>
my $code = 2;
switch ($code) {
  case 1: {
    print "1 \ n";
    break;
  }
  case 2: {
    print "2 \ n";
    break;
  }
  case 3: {
    print "3 \ n";
    break;
  }
  case 4:
  case 5:
  {
    print "4 or 5 \ n"; {
    break;
  }
  default: {
    print "Other \ n";
  }
}
</pre>

<h3 id = "language-statement-switch">case Statement</h3>
<p>
  A case statement is a Statement that can be used in a switch block to specify conditions. For more information on case statements, see the <a href="#language-statement-switch">switch Statement</a> description.
</p>

<h3 id = "language-statement-switch">default Statement</h3>
<p>
  The default Statement is a Statement that can be used in the switch block to specify the default condition. For more information on the default Statement, see the <a href="#language-statement-switch">switch Statement</a> description.
</p>

<h3 id = "language-statement-while">while Statement</h3>
<p>
  while Statement is a Statement for repeating.
</p>
<pre>
while (CONDITION_EXPRESSION) {

}
</pre>
<p>
  <a href="#language-expresssion">Expression</a> can be described in the condition Expression. <a href="#language-type-convertion-bool">Bool Type Conversion</a> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise Block.
</p>
<p>
  <b>While Statement Example</b>
</p>
<p>
  An example of a while Statement.
</p>
<pre>
my $i = 0;
while ($i <5) {

  print "$i \ n";

  $i++;
}
</pre>
<p>
  Inside the while block, you can leave the while block by using <a href="#language-statement-last">last Statement</a>.
</p>
<pre>
while (1) {
  last;
}
</pre>

<p>
  Inside a while block, you can use <a href="#language-statement-next">next Statement</a> to move to the condition immediately before the next condition Expression.
</p>
<pre>
my $i = 0;
while ($i <5) {

  if ($i == 3) {
    $i++;
    next;
  }

  print "$i \ n";
  $i++;
}
</pre>

<p>
  The while Statement is internally enclosed by an invisible <a href="#language-scope-block-statement-simple">Simple Block</a>.
</p>
<pre>
{
  while (CONDITION_EXPRESSION) {
  $i++;
}

# 展開後
my $num = 5;
{
  while (my $num = 3) {

    $i++;
  }
}
</pre>

<h3 id = "language-statement-for">for Statement</h3>
<p>
  for Statement is a Statement for repeating.
</p>
<pre>
for (INITIALIZATION_EXPRESSION; CONDITIONAL_EXPRESSION; INCREMENT_EXPRESSION) {

}
</pre>
<p>
  <a href="#language-expression">Expression</a> can be described in the initialization Expression. Generally, write Expression such as initialization of loop variable. Initialization Expression can be omitted.
</p>
<p>
  Condition Expression, <a href="#language-expresssion">Expression</a> can be described. <a href="#language-type-convertion-bool">Bool Type Conversion</a> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise block.
</p>
<p>
  <a href="#language-expression">Expression</a> can be described in INCREMENT_EXPRESSION. Generally, Expression of Increment of loop variable is described. INCREMENT_EXPRESSION can be omitted.
</p>
<p>
  for Statement has the same meaning as the following while Statement. INCREMENT_EXPRESSION is executed at the end of Block. Initialization Expression is enclosed in <a href="#language-scope-block-statement-simple">Simple Block</a>.
</p>
<pre>
{
  INITIALIZATION_EXPRESSION;
  while (CONDITION_EXPRESSION) {


    INCREMENT_EXPRESSION;
  }
}
</pre>
<p>
  <b>for Statement Example</b>
</p>
<p>
  An example of for Statement.
</p>
<pre>
for (my $i = 0; $i <5; $i++) {

  print "$i \ n";
}
</pre>
<p>
  Inside the for Block, you can exit the for Block using <a href="#language-statement-last">last Statement</a>.
</p>

<pre>
for (INITIALIZATION_EXPRESSION; CONDITIONAL_EXPRESSION; INCREMENT_EXPRESSION) {

}
</pre>

<p>
  Inside the for Block, you can use <a href="#language-statement-next">next Statement</a> to move immediately before the next INCREMENT_EXPRESSION to be executed.
</p>
<pre>
for (my $i = 0; $i <5; $i++) {

  if ($i == 3) {
    next;
  }
}
</pre>

<h3 id = "language-statement-return">returnl Statement</h3>
<p>
  Use the returnl Statement to get out of the Method. The object assigned to the mortal variable is automatically released.
</p>
<pre>
return;
</pre>
<p>
  If there is a Return Value, <a href="#language-expression">Expression</a> can be specified.
</p>
<pre>
return EXPRESSION;
</pre>
<p>
  If the Return Value Type in <a href="#language-method-definition">Method Definition</a> is <a href="#language-type-void">void Type</a>, Expression Must not exist, otherwise Compile Error occurs.
</p>
<p>
  <a href="#language-method-definition">Method Definition</a>, if the Return Value Type is other than <a href="#language-type-void">void Type</a>, Expression Must match the Type of, otherwise Compile Error occurs.
</p>

<h3 id = "language-statement-die">die Statement</h3>
<p>
  die Statement is a Statement for raising <a href="#language-exception">Exception</a>.
</p>
<pre>
die EXPRESSION;
</pre>
<p>
  Expression must be a String Type.
</p>
<p>
  See <a href="#language-exception">Exception</a> for a detailed explanation of the die statement.</p>
<h3 id = "language-statement-weaken">weaken Statement</h3>
<p>
  A weaken Statement is a Statement that sets <a href="#language-weak-ref">Weaken Reference</a> for the Field.
</p>
<pre>
weaken VARIABLE->{FIELD_NAME};
</pre>
<p>
  The Type of the object Expression must be <a href="#language-type-class">Class Type</a>, otherwise Compile Error occurs.
</p>
<p>
  Field Name must be an existing Field Name, otherwise Compile Error occurs.
</p>
<p>
  The Type of the value saved in Field must be <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.
</p>
<p>
  If the value stored in the Field at execution time is <a href="#language-undef">Undefined Value</a>, the weak Statement does nothing.
</p>
<p>
  If the value stored in the Field at runtime is not <a href="#language-undef">Undefined Value</a>, then the following is done:
</p>
<p>
  1. Decrement the Reference Count of the object stored in Field by 1.
</p>
<p>
  2. Set the Weaken Reference flag in Field.
</p>
<p>
  3. Add Field to the back reference of the object saved in Field.
</p>
<p>
  Note that the Weaken Reference flag is set on the Field itself, not on the object stored in the Field.
</p>
<p>
  If the Reference Count of the object saved in Field becomes 0, the Weaken Reference is not created and the object saved in Field is released.
</p>
<p>
  Back Reference is the data of the object saved in Field, and is added to know the Field with the Weaken Reference flag set. There may be more than one.
</p>
<pre>
# There are multiple back references
my $foo = new Foo;
my $bar = new Bar;
my $baz = new Baz;

$foo->{bar} = $bar;
$foo->{baz} = $baz;

$bar->{foo} = $foo;
$baz->{foo} = $foo;

weaken $bar->{foo};
weaken $baz->{foo};
</pre>
<p>
  In the above example, "$bar->{foo}" and "$baz->{foo}" have the Weaken Reference flag set. The object represented by $foo has the back References "$bar->{foo}" and "$baz->{foo}".
</p>
<p>
  The information of the back Reference is necessary because when the <a href="#language-garbage-collection">Garbage Collection</a> is performed, it is necessary to assign the Undefined Value to the Field pointed to by the back Reference.
</p>

<h3 id = "language-statement-unweaken">unweaken Statement</h3>
<p>
  unweaken Statement is a Statement that cancels <a href="#language-weak-ref">Weaken Reference</a> for Field.
</p>
<pre>
unweaken VARIABLE->{FIELD_NAME};
</pre>
<p>
  The Type of the object Expression must be <a href="#language-type-class">Class Type</a>, otherwise Compile Error occurs.
</p>
<p>
  Field Name must be an existing Field Name, otherwise Compile Error occurs.
</p>
<p>
  The Type of the value saved in Field must be <a href="#language-type-object">Object Type</a>, otherwise Compile Error occurs.
</p>
<p>
  If the value stored in the Field at execution time is <a href="#language-undef">Undefined Value</a>, the unweaken Statement does nothing.
</p>
<p>
  If the value stored in the Field at runtime is not <a href="#language-undef">Undefined Value</a>, then the following is done:
</p>
<p>
  1. Increase the Reference Count of the object stored in the Field by 1.
</p>
<p>
  2. Clear the Weaken Reference flag of Field.
</p>
<p>
  3. Delete the Field from the back reference of the object stored in the Field.
</p>

<h3 id = "language-statement-next">next Statement</h3>
<p>
  "next Statement" is a Statement to move to the beginning of the next loop. in <a href="#language-scope-block-statement-while">while Block</a>, <a href="#language-scope-block-statement-for">for Block</a> You can use it.
</p>
<pre>
next;
</pre>
<p>
  Please see the explanation of <a href="#language-statement-while">while Statement</a>, <a href="#language-statement-for">for Statement</a> for the actual operation. ..
</p>

<h3 id = "language-statement-last">last Statement</h3>
<p>
  "last Statement" is a Statement to break the loop. in <a href="#language-scope-block-statement-while">while Block</a>, <a href="#language-scope-block-statement-for">for Block</a> You can use it.
</p>
<p>
  Please see the explanation of <a href="#language-statement-while">while Statement</a>, <a href="#language-statement-for">for Statement</a> for the actual operation. ..
</p>
<pre>
last;
</pre>

<h3 id = "language-statement-break">break Statement</h3>
<p>
  "break Statement" is a Statement to escape the switch block. It can be used in <a href="#language-scope-block-statement-switch">switch Block</a>.
</p>
<p>
  See <a href="#language-statement-switch">switch Statement</a> for the actual operation.
</p>
<pre>
break;
</pre>

<h3 id = "language-statement-warn">warn Statement</h3>

<p>
  Use warnStatement to throw a warning.
</p>
<pre>
warn Expression;
</pre>
<p>
  Expression must be <a href="#language-type-string">String Type</a>.
</p>
<p>
  If the end is a line feed Character "\ n", the String specified in Expression is output to the standard error output.
</p>
<p>
  If the end is not a line feed character, File Name and line number are added to the end, and standard error is output.
</p>
<p>
  If the length of String specified in Expression is 0 or Undefined Value, the specified message behaves as "Warning: something's wrong".
</p>
<p>
  The standard error output buffer is flushed.
</p>

<h3 id = "language-statement-print">print Statement</h3>
<p>
  Use print Statement to print a String to standard output.
</p>
<pre>
print Expression;
</pre>
<p>
  Expression must be <a href="#language-type-string">String Type</a>.
</p>
<p>
  If Expression is Undefined Value, do nothing.
</p>

<h3 id = "language-statement-expression">expression Statement</h3>
<p>
  The expression Statement is a Statement consisting of <a href="#language-expression">Expression</a> and ";".
</p>
<pre>
Expression;
</pre>

<p>
  An example of an expression statement.
</p>
<pre>
1;
$var;
1 + 2;
foo ();
my $num = 1 + 2;
</pre>

<h3 id = "language-statement-empty">empty Statement</h3>
<p>
  An empty statement is a statement that ends with just ";".
</p>
<pre>
;
</pre>

<h2 id = "language-type">Type</h2>
<ul class = "list">
  <li><a href="#language-type-summary">Type Summary</a></li>
  <li><a href="#language-type-initial-value">Type Initial Value</a></li>
  <li><a href="#language-type-void">void Type</a></li>
  <li><a href="#language-type-numeric">Numeric Type</a></li>
  <li><a href="#language-type-integral">Integral Type</a></li>  <li><a href="#language-type-byte">byte Type</a></li>
  <li><a href="#language-type-short">short Type</a></li>
  <li><a href="#language-type-int"><a href="#language-type-int">int Type</a></a></li>
  <li><a href="#language-type-long">long Type</a></li>
  <li><a href="#language-type-floating-point">Floating Point Type</a></li>
  <li><a href="#language-type-float">float Type</a></li>
  <li><a href="#language-type-double">double Type</a></li>
  <li><a href="#language-type-class">Class Type</a></li>
  <li><a href="#language-type-object">Object Type</a></li>
  <li><a href="#language-type-numeric-object">Numeric Object Type</a></li>
  <li><a href="#language-type-undef">Undefined Type</a></li>
  <li><a href="#language-type-class">Class Type</a></li>
  <li><a href="#language-type-callback">Callback Type</a></li>
  <li><a href="#language-type-any-object">Any Object Type</a></li>
  <li><a href="#language-type-self">self Type</a></li>
  <li><a href="#language-type-array">Array Type</a></li>
  <li><a href="#language-type-array-numeric">Numeric Array Type</a></li>
  <li><a href="#language-type-array-byte">byte[] Type</a></li>
  <li><a href="#language-type-array-object">Object Array Type</a></li>
  <li><a href="#language-type-array-mulnum">Multi Numeric Array Type</a></li>
  <li><a href="#language-type-any-object-array">Any Object Array Type</a></li>
  <li><a href="#language-type-string">String Type</a></li>
  <li><a href="#language-type-string">String Type</a></li>
  <li><a href="#language-type-multi-numeric">Multi Numeric Type</a></li>
  <li><a href="#language-type-ref">Reference Type</a></li>
  <li><a href="#language-type-ref-numeric">Numeric Reference Type</a></li>
  <li><a href="#language-type-ref-multi-numeric">Multi Numeric Reference Type</a></li>
</ul>
<h3 id="language-type-summary">Type Summary</h3>

SPVM is a static type language. All data has a static type.

<p>
  <a href="#language-local-var-declaration">Local Variable Declaration</a>, <a href="#language-field-definition">Field Definition</a>, <a href="#language-class-var-definition">Class Variable Definition</a>, and <b>Arguments</b> and <b>Return Value</b> of <a href="#language-method-definition">Method Definition</a> must specify <b>Type</b>.
</p>

In <a href="#language-local-var-declaration">Local Variable Declaration</a>, <a href="#language-type-inference">Type Inference</a> can be used.

<h3 id="language-type-initial-value">Type Initial Value</h3>
<p>
  Local Variable Initial Value,<a href="#language-class-var-initial-value">Class Variable Initial Value</a>,Create ObjectにおけるFieldの初期値は,Type Initial Valueによって決まります。
</p>
<p>
  A list of Type Initial Value. All Bit columns in the data are set to 0.
</p>
</p>
<table>
  <tr>
    <th>
      <b>Type Name</b>
   </th>
    <th>
      Initial Value
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>Object Type</b>
    </td>
    <td>
      undef
    </td>
  </tr>
  <tr>
    <td>
      <b>Multi Numeric Type</b>
    </td>
    <td>
      All Field is 0
    </td>
  </tr>
</table>

<h3 id="language-type-numeric">Numeric Type</h3>

Numeric Type is <a href="#language-type-integral">Integral Type</a> or <a href="#language-type-floating-point">Floating Point Type</a>.

<h3 id="language-type-integral">Integral Type</h3>

Integral Type are the following four types.

<table>
  <tr>
    <th>
      <b>Type</b>
   </th>
    <th>
      Description
   </th>
    <th>
      Size
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      signed 8-bit integer type
    </td>
    <td>
      1 byte
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      signed 16-bit integer type
    </td>
    <td>
      2 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      signed 32-bit integer type
    </td>
    <td>
      4 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      signed 64-bit integer type
    </td>
    <td>
      8 bytes
    </td>
  </tr>
</table>

See <a href="#language-operator-arithmetic">Arithmetic Operator</a> for integer calculation rules.

Note that SPVM has only <b>singed</b> Integral Type, and don't has <b>unsigned</b> Integral Type.

<h3 id = "language-type-byte">byte Type</h3>
<p>
   <a href="#language-type-byte">byte Type</a> is <a href="#language-type-integral">Integral Type</a> that represents a signed 8-bit integer. It is the same Type as int8_tType of C99.
</p>
<h3 id = "language-type-short">short Type</h3>
<p>
   <a href="#language-type-byte">byte Type</a> is <a href="#language-type-integral">Integral Type</a> that represents a signed 16-bit integer. It is the same Type as int16_tType of C99.
</p>

<h3 id="language-type-int">int Type</h3>
<h3 id = "language-type-int">int Type</h3>
<b>int Type</b> is a type that represents signed 32-bit integer.

This is same as <b>C99 int32_t Type</b>.

This is a <a href="#language-type-integral">Integral Type</a>.

<h3 id = "language-type-long">long Type</h3>
<p>
  <a href="#language-type-long">long Type</a> is <a href="#language-type-integral">Integral Type</a> that represents a signed 64-bit integer. It is the same Type as int64_tType of C99.
</p>

<h3 id = "language-type-floating-point">Floating Point Type</h3>

<b>Floating Point Type</b> are the following two.

<table>
  <tr>
    <th>
      <b>Type</b>
    </ th>
    <th>
      Description
    </ th>
    <th>
      Size
    </ th>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      Single precision (32bit) floating po <a href="#language-type-int">int Type</a>
    </td>
    <td>
      4 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      Double precision (64bit) floating po <a href="#language-type-int">int Type</a>
    </td>
    <td>
      8 bytes
    </td>
  </tr>
</table>

See <a href="#language-operator-arithmetic">Arithmetic Operator</a> for floating-point calculation rules.

<h3 id = "language-type-float">float Type</h3>
<p>
  <a href="#language-type-floating-point">Floating Point Type <a represents a single precision floating point (32bit). / a> It is the same Type as <a href="#language-type-float">float Type</a> of C99.
</p>

<h3 id = "language-type-double">double Type</h3>
<p>
  <b>double Type</b> represents a double precision floating point (64bit) <a href="#language-type-floating-point">Floating Point Type</a> It is the same Type as <a href="#language-type-double">double Type</a> of C99.
</p>

<h3 id = "language-type-class">Class Type</h3>
<p>
  Class Type is the Type defined by <a href="#language-class-definition">Class Definition</a>.
</p>
<pre>
class Foo {

}
</pre>
<p>
  Class Type is <a href="#language-type-class">Class Type</a> <a href="#language-type-callback">Callback Type</a> <a href = "#language-type It consists of -multi-numeric ">Multi Numeric Type</a>.
</p>
<pre>
# Class Type
class Foo {

}

# Callback Type
class Foo: callback_t {

}

# Multi Numeric Type
class Foo: mulnum_t {

}
</pre>
<p>
  <a href="#language-type-pointer">Pointer Type</a> is also Class Type, so Pointer Type will also be Class Type.
</p>
<pre>
# Pointer Type
class Foo: pointer_t {

}
</pre>
<h3 id = "language-type-object">Object Type</h3>
<p>
What is Object Type <a href="#language-type-class">Class Type</a> <a href="#language-type-callback">Callback Type</a> <a href = "#language- type-array ">Array Type</a> <a href="#language-type-string">String Type</a> <a href="#language-type-any-object">Any Object Type</a> It is a combination of a>. "Multi Numeric Type" and "Reference Type" are not included.
</p>
<p>
The Object Type value can be assigned to "Any Object Type".
</p>
<pre>
my $object: object = new Foo;
my $object: object = new Foo [];
my $object: object = "abc";
</pre>
<p>
The size of Object Type must match the value of "sizeof (void *)" in C99.
</p>

<h3 id = "language-type-numeric-object">Numeric Object Type</h3>
<p>
<b>Numeric Object Type</b> are the following six.
</p>
<table>
  <tr>
    <th>
      <b>Type</b>
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      Byte
    </td>
    <td>
      Numeric Object Type with <a href="#language-type-byte">byte Type</a> data
    </td>
  </tr>
  <tr>
    <td>
      Short
    </td>
    <td>
      Numeric Object Type with <a href="#language-type-short">short Type</a> data
    </td>
  </tr>
  <tr>
    <td>
      Int
    </td>
    <td>
      Numeric Object Type with <a href="#language-type-int"><a href="#language-type-int">int Type</a></a> data
    </td>
  </tr>
  <tr>
    <td>
      Long
    </td>
    <td>
      Numeric Object Type with <a href="#language-type-long">long Type</a> data
    </td>
  </tr>
  <tr>
    <td>
      Float
    </td>
    <td>
      Numeric Object Type with <a href="#language-type-float">float Type</a> data
    </td>
  </tr>
  <tr>
    <td>
      Double
    </td>
    <td>
    Numeric Object Type with <a href="#language-type-double">double Type</a> data
    </td>
  </tr>
</table>

For the conversion between <a href="#language-type-numeric">Numeric Type</a> and <b>Numeric Object Type</b>, see <a href="#language-type-convertion">Type Conversion</a>.

<h3 id = "language-type-undef">Undefined Type</h3>
<p>
Undefined Type is the Type that <a href="#language-undef">Undefined Value</a> has. It cannot be used explicitly.
</p>
<p>
The only Undefined Type value is <a href="#language-undef">Undefined Value</a>.
</p>
<p>
The value of Undefined Type can be assigned to Object Type.If you assign to another Type, Compile Error occurs
</p>

<h3 id = "language-type-class">Class Type</h3>
<p>
Class Type is the Type defined by <a href="#language-class-definition">Class Definition</a> and is not "Multi Numeric Type" "Callback Type".
</p>
<pre>
packag Foo {

}
</pre>
<p>
  Class Type can create objects by new Operator.
</p>
<pre>
my $foo = new Foo;
</pre>
<p>
  Class Type is a <a href="#language-type-object">Object Type</a>.
</p>
<p>
  Class Type is a <a href="#language-type-class">Class Type</a>.
</p>
<p>
  <a href="#language-type-pointer">Pointer Type</a> is the Class Type.
</p>

<h3 id = "language-type-pointer">Pointer Type</h3>
<p>
  Pointer Type is the one that "pointer_t Descriptor" is specified in <a href="#language-class-definition">Class Definition</a>.
</p>
<pre>
class Foo: pointer_t {

}
</pre>
<p>
  Pointer Type is a type of Class Type.
</p>
<p>
  Pointer type data can store C language pointers.
</p>
<p>
  Field cannot be defined for Pointer Type. If it is defined, Compile Error occurs
</p>

<h3 id = "language-type-callback">Callback Type</h3>

Callback Type is a <a href="#language-type-class">Class Type</a> with <a href="#language-class-descriptor">Class Descriptor</a> "callback_t".

<pre>
class Comparator: callback_t {
  method: int ($x1: object, $x2: object);
}
</pre>

Callback Type is designed to provide a feature corresponding to Function Pointer in C language.

Callback Type must have only one <a href="#language-method-definition">Method Definition</a>. Method must be <a href="#language-method-method">Method</a>.

Method Name of Callback Type must be anonymouse.

Callback Type must not have any <a href="#language-field-definition">Field Definition</a> and <a href="#language-class-var-definition">Class Variable Definition</a>.

Callback Type is a <a href="#language-type-object">Object Type</a>.

Callback Type cannot be the operand of <a href="#language-expression-new">new Statement</a>.

The variable of Callback Type can be assigned a <a href="#language-type-class">Class Type</a> object that matches the Callback Type. "Matches the Callback Type" means the following two cases.

1. Class Type object with anonimouse name and the <a href="#language-method-signature">Signature</a> is same as Callback Type

<pre>
# Callback Type Definition
class Comparator: callback_t {
  method: int ($x1: object, $x2: object);
}

# Class Definition
class SomeComparator {
  static method new: int () {
    return new SomeComparator;
  }

  method: int ($x1: object, $x2: object) {

  }
}

# The object can be assign to the variable of Callback Type
my $comparator: Comparator = SomeComparator->new;
</pre>

2. Class Type object which is created by <a href="#language-method-new-callback-object">Create Callback Object</a> and the <a href="#language-method-signature">Signature</a> is same as Callback Type.

<pre>
Definition of #Callback Type
class Comparator: callback_t {
  method: int ($x1: object, $x2: object);
}

# The object which is created by Create Callback Object can be assign to the variable of Callback Type
my $comparator : Comparator = method: int ($x1: object, $x2: object) {

}
</pre>

<h3 id = "language-type-any-object">Any Object Type</h3>
<p>
  Any Object Type is represented by "object". Designed to represent the "void *" Type in C.
</p><pre>
my $object: object;
</pre>
<p>
  You can methodstitute the value of "Object Type" for Any Object Type.
</p>
<pre>
my $object: object = new Foo;
my $object: object = "abc";
my $object: object = new Foo [3];
</pre>

<h3 id = "language-type-self">self Type</h3>
<p>
  self Type represents the Class Type to which it belongs, and indicates that the argument is Invocant.
</p>

<pre>
self
</pre>

<p>
  It can only be used as the Type of the first argument in <a href="#language-method-definition">Method Definition</a>.
</p>

<h3 id = "language-type-void">void Type</h3>

<b>void Type</b> is a special Type that can only be used in Return Type of <a href="#language-method-definition">Method Definition</a> and indicates the Method has no Return Value.

<pre>
void
</pre>

<h3 id = "language-type-basic">Basic Type</h3>
<p>
  A Type that does not have dimensions is called a Basic Type. <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-class">Class Type </ a>, <a href = "#language-type- any-object ">Any Object Type</a>, <a href="#language-type-string">String Type</a> is a Basic Type.
</p>

<h3 id = "language-type-array">Array Type</h3>
<p>
  Array Type represents multiple continuous data areas. <a href="#language-type-basic">Basic Type</a> can be an Array.
</p>
<pre>
int[]
double[]
Point[]
object[]
string []
</pre>
<p>
  Array has dimensions and can express up to 255 dimensions.
</p>
<pre>
# Two dimensions
int[] []

# Three-dimensional
int[] [] []
</pre>
<p>
  Array Type is <a href="#language-type-object">Object Type</a>.
</p>
<p>
  Use new Operator to create an Array. In the following example, <a href="#language-type-int">int Type</a> Array with 3 elements is created.
</p>
<p>
my $nums = new int [3];
</p>
<p>
  You also use new Operator when creating a multidimensional Array.The following example creates an Array of int[] Type with 3 elements.
</p>
<p>
my $nums = new int[] [3];
</p>
<h3 id = "language-type-array-numeric">Numeric Array Type</h3>
<p>
  Numeric Array Type means <a href="#language-type-numeric">Numeric Type</a> with the element <a href="#language-type-array">Array Type</a> It is.
</p>
<p>
  <b>Numeric Array Type list</b>
</p>
<ul class = "list">
  <li>
    byte[]
  </li>
  <li>
    short[]
  </li>
  <li>
    int[]
  </li>
  <li>
    long[]
  </li>
  <li>
    float[]
  </li>
  <li>
    double[]
  </li>
</ul>
<p>
  Data represented by Numeric Array Type must have elements whose size is <a href="#language-type-numeric">Numeric Type</a>, and must be consecutive by the number of Array Length.
</p>
<p>
  All elements of Numeric Array Type are initialized by <a href="#language-type-initial-value">Type Initial Value</a> when Create Array is performed.
</p>
<h3 id = "language-type-array-byte">byte[] Type</h3>
<p>
  In SPVM, the <a href="#language-type-array-byte">byte[] Type</a> is a special Type in that it is <a href="#language-type-string">String Type</a>.
</p>
<pre>
byte[]
</pre>
<p>
  <a href="#language-type-string">String Type</a> is treated as <a href="#language-type-string">String Type</a> at compile time, but at runtime It will be <a href="#language-type-array-byte">byte[] Type</a>.
</p>

<h3 id="language-type-array-object">Object Array Type</h3>
<p>
  Object Array Type is <a href="#language-type-array">Array Type</a> that has the value of <a href="#language-type-object">Object Type</a> as an element. It is.
</p>
<p>
  <b>Object Array TypeのExample</b>
</p>
<ul>
  <li>
    Foo[]
 </li>
  <li>
    Foo[][]
 </li>
  <li>
    Comparable[]
 </li>
  <li>
    object[]
 </li>
</ul>
<p>
  The data represented by Object Array Type must have elements of size of <a href="#language-type-object">Object Type</a> and consecutive by the number of Array Length.
</p>
<p>
  All elements of Object Array Type are initialized by <a href="#language-type-initial-value">Type Initial Value</a> when Create Array is performed.
</p>

<h3 id="language-type-array-mulnum">Multi Numeric Array Type</h3>
<p>
  Multi Numeric Array Type means <a href="#language-type-array">Array Type that has the value of <a href="#language-type-multi-numeric">Multi Numeric Type</a> as an element.</a>.
</p>
<p>
  <b>Multi Numeric Array Type Example</b>
</p>
<ul>
  <li>
    Complex_2d[]
 </li>
  <li>
    Complex_2f[]
 </li>
</ul>
<p>
  Data represented by Multi Numeric Array Type must have elements whose size is <a href="#language-type-numeric">Multi Numeric Type</a> and must be contiguous with the number of Array Length ..
</p>
<p>
  All elements of Multi Numeric Array Type are initialized by <a href="#language-type-initial-value">Type Initial Value</a> when Create Array is performed.
</p>

<h3 id="language-type-any-object-array">Any Object Array Type</h3>
<p>
  Any Object Array Type is an arbitrary <a href="#language-type- that has the value of <a href="#language-type-object">Object Type</a> expressed as an oarray as an element. A Type that can be assigned the value of array ">Array Type</a>. Any Array Type can be cast to void * Type and passed to the first argument of the C language qsort function, but Any Object Array Type is not designed to realize the function corresponding to this. It was
</p>
<pre>
my $array : oarray = new Point[3];
my $array : oarray = new object[3];
</pre>
<p>
  If a value with a Type other than Object Type is assigned, Compile Error occurs
</p>
<p>
  Note that "oarrayType" is a different Type than "object[] Type". While oarrayType is a Type that can be methodstituted with an arbitrary Array Type value that has an Object Type value as an element, "object[] Type" is a Type that represents an "Array that has an objectType value as an element". Therefore, the value of arbitrary Array Type cannot be assigned.
</p>
<p>
  Any Object Array Type is <a href="#language-type-array">Array Type</a>. <a href="#language-operator-array-length">Array Length Operator</a> to get length, <a href="#language-expression-set-array-element">Set Array Element You can use Value</a>, <a href="#language-expression-get-array-element">Get Array Element Value</a>.
</p>
<pre>
my $array : oarray = new Int[3];

# Get the length of the element of Any Object Array Type
my $length = @$array;

# Get the value of any object array type element
my $num = (Int)$array->[0];

# Setting the value of the element of Any Object Array Type
$array->[0] = Int->new(5);
</pre>
<p>
  When setting the value of the element of Any Object Array Type, a check is made at runtime whether the Type of the element is smaller than the Type Dimension of Array by 1. If the check fails, <a href="#language-exception">Exception</a> will occur. Any Object Array Type guarantees runtime Type safety.
</p>

<h3 id="language-type-string">String Type</h3>
<p>
  <a href="#language-type-string">String Type</a> is a Type that represents a String. Expressed by string. Designed to represent C "const char *".
</p>
<pre>
my $str : string;
</pre>
<p>
  String Literal allows you to assign the generated String object.
</p>
<pre>
my $str : string = "abc";
</pre>
<p>
  SPVM String is an Array of bytes whose elements cannot be changed. You can get the Character by accessing the Array.
</p>
<pre>
# Acquisition of Character
my $ch = $str->[1];
</pre>
<p>
  If you try to change the element, Compile Error occurs
</p>
<pre>
# Compile Error when changing element
$str->[1] = 'd';
</pre>
<p>
  <a href="#language-type-string">String Type</a> will be exactly the same as the Array of bytes Type after compilation. For example, the first expression is treated as the second expression.
</p>
<pre>
# isa String Type
if ($str isa string) {

}

# isa <a href="#language-type-array-byte">byte[] Type</a>
if ($str isa byte[]) {

}
</pre>
<p>
  Note that SPVM Strings are immutable, but this is a compile-time check.
</p>
<p>
  <a href="#language-type-string">String Type</a> can be cast to <a href="#language-type-array-byte">byte[] Type</a>, and the String can be changed at runtime.
</p>
<pre>
my $bytes = (byte[])$str;
$bytes->[1] = 'd';
</pre>
<p>
  Treat String as if you can always change it.
</p>

<h3 id="language-type-string">String Type</h3>
<p>
  String Type is a combination of <a href="#language-type-string">String Type</a> and <a href="#language-type-array-byte">byte[] Type</a>. Say that.
</p>
<p>
  When a String Type value is generated, it is guaranteed that the last one after the last memory area reserved for the value will be "\ 0". (For example, if it is "abc", "c" is followed by "\ 0".) From the SPVM language, this "\ 0" has no meaning, but when using the native API, String Type is It can be handled as a C language String.
</p>

<h3 id="language-type-multi-numeric">Multi Numeric Type</h3>
<p>
  Multi Numeric Type is a type that can represent continuous numerical values.
</p>
<p>
  Multi Numeric Type can be defined by specifying "mulnum_t" Descriptor in <a href="#language-class-definition">Class Definition</a>.
</p>
<pre>
class Point_3i : mulnum_t {
  has x : int;
  has y : int;
  has z : int;
}
</pre>
<p>
  See <a href="#language-mulnum">Values ​​</a> for a detailed explanation of Multi Numeric Type.
</p>

<h3 id="language-type-ref">Reference Type</h3>
<p>
  Reference Type is a Type that can store the address of a variable. Add "&" after <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-multi-numeric">Multi Numeric Type</a> You can define it.
</p>
<pre>
my $num : int;
my $num_ref : int& = \$num;

my $point : Point_3i;
my $point_ref : Point_3i& = \$point;
</pre>
<p>
  Only the address of the Local Variable acquired by <a href="#language-operator-ref">Reference Operator</a> can be assigned to the value of Reference Type.
</p>
<p>
  If only Local Variable Declaration of Reference Type is performed, Compile Error occurs
</p>
<p>
  Reference Type can be used as Type of <a href="#language-local-var-declaration">Local Variable Declaration</a>. The address of the Local Variable must be stored by the Reference Operator. In case of only Local Variable Declaration, Compile Error occurs
</p>
<p>
  Reference Type can be used as Type of argument in <a href="#language-method-definition">Method Definition</a>.
</p>
<p>
  Reference Type cannot be used as Return Value Type in <a href="#language-method-definition">Method Definition</a>.
</p>
<p>
  Reference Type cannot be used as the Type of Field in <a href="#language-class-definition">Class Definition</a>.
</p>
<p>
  Reference Type cannot be used as the Type of Class Variable in <a href="#language-class-definition">Class Definition</a>.
</p>
<p>
  If the Reference Type is used at an Invalid location, Compile Error occurs
</p>
<p>
  See <a href="#language-ref">Reference</a> for a detailed explanation of Reference.
</p>

<h3 id="language-type-ref-numeric">Numeric Reference Type</h3>

<p>
  Numeric Reference Type means <a href="#language-type-numeric">Numeric Type</a> for <a href="#language-type-ref">Reference Type</a>. Says.
</p>

<h3 id="language-type-ref-multi-numeric">Multi Numeric Reference Type</h3>

<p>
  Multi Numeric Reference Type means <a href="#language-type-ref">Reference Type</a> for <a href="#language-type-multi-numeric">Multi Numeric Type</a> variables. > Means.
</p>

<h2 id="language-type-inference">Type Inference</h2>
<p>
  Omitting <a href="#language-type">Type</a> when <a href="#language-local-var-declaration">Local Variable Declaration</a> by Type Inference can. Type Inference is always performed by the Type on the Right side of Assignment Operator.
</p>
<pre>
# int
my $num = 1;

# double
my $num = 1.0;

# Foo
my $foo = new Foo;
</pre>
<h2 id="language-type-compatible">Type Compatibility</h2>
<p>
  Type compatibility means that the value can be moved without performing <a href="#language-expression-typecast">Type Cast</a>.
</p>
<p>
  Types are compatible in the following cases.
</p>
<p>
  <b>When the source and destination types are the same</b>
</p>
<p>
  If the source and destination types are the same, there is Type Compatibility.
</p>
<pre>
my $num1 : int;
my $num2 : int;
$num1 = $num2;
</pre>
<p>
  <b>When the source Type is <a href="#language-type-array-byte">byte[] Type</a> and the destination Type is <a href="#language-type-string">String Type</a></b>
</p>
<p>
  If the source Type is <a href="#language-type-array-byte">byte[] Type</a> and the destination Type is <a href="#language-type-string">String Type</a>, there is Type Compatibility.
</p>
<pre>
my $bytes = new byte[3];
my $str : string;
$str = $bytes;
</pre>
<p>
  <b>When the source Type is Object Type and the destination Type is Any Object Type</b>
</p>
<pre>
my $foo : Foo = new Foo;
my $object : object;
$object = $foo;
</pre>
<p>
  <b>When the source Type and destination Type are Any Object Type or Any Object Type Array and the source Type Dimension count is greater than or equal to the destination Type Dimension count</b>
</p>
<pre>
my $objects_dim2_src : object[];
my $objects_dim1_dist : object;
$objects_dim1_dist = $objects_dim2_src;
</pre>
<p>
  Note that the general object Array and the Basic Type Array are not compatible.
</p>
<pre>
# Compilation error
my $objets : object[] = new int[3];
</pre>
<p>
  If the types are not compatible, <a href="#language-type-convertion-implicite">implicit Type Conversion</a> is tried. If the implicit Type Conversion fails, Compile Error occurs
</p>

<h2 id="language-type-convertion">Type Conversion</h2>
<ul>
  <li><a href="#language-type-convertion-typecast">Type Cast</a></li>
  <li><a href="#language-type-convertion-implicite">Implicit Type Conversion</a></li>
  <li><a href="#language-type-convertion-typecast">Numeric Type Conversion</a></li>
  <li><a href="#language-type-convertion-numeric-type-order">Numeric Type Order</a></li>
  <li><a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a></li>
  <li><a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a></li>
  <li><a href="#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a></li>
  <li><a href="#language-type-convertion-numeric-widening">Numeric Widening Type Conversion</a></li>
  <li><a href="#language-type-convertion-numeric-to-string">Numeric-to-String Type Conversion</a></li>
  <li><a href="#language-type-convertion-string-to-byte-array">String-to-byte[] Type Conversion</a></li>
  <li><a href="#language-type-convertion-byte-array-to-string">byte[]-to-String Type Conversion</a></li>
  <li><a href="#language-type-convertion-boxing">Boxing Type Conversion</a></li>
  <li><a href="#language-type-convertion-unboxing">Unboxing Type Conversion</a></li>
  <li><a href="#language-type-convertion-bool">Bool Type Conversion</a></li>
</ul>

<h3 id="language-type-convertion-typecast">Type Cast</h3>
<p>
  Type Cast is Type Conversion that is explicitly described.
</p>
<pre>
# Type Cast
(TYPE)EXPRESSION
</pre>
<p>
  <a href="#language-type-int">int Type</a> value is converted to <a href="#language-type-long">long Type</a> Become.
</p>
<pre>
my $num = (long)3;
</pre>
<p>
  ype Cast returns <a href="#language-expression">Expression</a>.
</p>
<p>
  If the source Type and the specified Type are the same, the value is simply copied.
</p>
<pre>
my $num : int = (int)4;
</pre>
<p>
  <b>List of Type Conversion in Type Cast</b>
</p>
<p>
  It is a list of Type Conversion in Type Cast. If a Type Cast not listed in this table is performed, Compile Error occurs.
</p>
<table>
  <tr>
    <th>
      <b>The specified Type</b>
   </th>
    <th>
      <b>Source type</b>
   </th>
    <th>
      Content of conversion
   </th>
  </tr>
  <tr>
    <td>
      <b>byte[]</b>
    </td>
    <td>
      <b>string</b>
    </td>
    <td>
      The address value is copied.
    </td>
  </tr>
  <tr>
    <td>
      <b>string</b>
    </td>
    <td>
      <b>byte[]</b>
    </td>
    <td>
      The address value is copied.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <a href="#language-type-convertion-numeric-widening">Numeric Type Conversion</a> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Object Type</b>
    </td>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <a href="#language-type-convertion-boxing">Boxing Type Conversion</a> is performed. Numeric Type represented by Numeric Type and Numeric Object Type must be the same. For example, if Numeric Type is int, Numeric Object Type must be Int Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>Any Object Type</b>
    </td>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <a href="#language-type-convertion-boxing">Boxing Type Conversion</a> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <b>Numeric Object Type</b>
    </td>
    <td>
      <a href="#language-type-convertion-unboxing">Unboxing Type Conversion</a> is performed. Numeric Type represented by Numeric Type and Numeric Object Type must be the same. For example, if Numeric Type is int, Numeric Object Type must be Int Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      <b>Any Object Type</b>
    </td>
    <td>
      <a href="#language-type-convertion-unboxing">Unboxing Type Conversion</a> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b><a href="#language-type-string">String Type</a></b>
    </td>
    <td>
      <b>Numeric Type</b>
    </td>
    <td>
      The number is converted to a string using the "%g" format of the C standard sprintf function.
    </td>
  </tr>
</table>

<h3 id="language-type-convertion-implicite">Implicit Type Conversion</h3>
<p>
  Implicit type conversion is automatic type conversion performed by SPVM. The following are the places where implicit Type Conversion may occur.
</p>
<ul>
  <li>When assigning to a different Type</li>
  <li>When passing to Method Arguments of different Type</li>
  <li>When returning a Type different from Return Value</li>
</ul>
<p>
  Implicit Type Conversion occurs when:
</p>
<p>
  If both the source and destination Type are Numeric Type and the destination Type is greater than the source Type, <a href="#language-type-convertion-numeric-widening">Numeric Widening Type Conversion</a> is done.
</p>
<pre>
# Implicit Widening Type Conversion
my $num : long = 123;
my $num : double = 12.5f;
</pre>

<p>
  Both the source and destination Type are Numeric Type, and the destination Type is smaller than the source Type, and the source value can be expressed in the range of Integer Literal and destination Type value. <a href="#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a> is performed.
</p>

<pre>
# Implicit Narrowing Type Conversion
my $num : byte = 123;
my $num : short = 134;
</pre>

<p>
  If the source Type is Numeric Type and the destination Type is Any Object Type, <a href="#language-type-convertion-boxing">Boxing Type Conversion</a> to the corresponding Numeric Object Type Is done. In the following case, the converted Int Type object is assigned to the generic object.
</p>

<pre>
# Implicit Boxing Type Conversion to objectType
my $num = 123;
my $object : object = $num;
</pre>
<p>
  When the source Type is Numeric Type and the destination Type is the corresponding Numeric Object Type, <a href="#language-type-convertion-boxing">Boxing Type Conversion</a> to the corresponding Numeric Object Type a> is done.
</p>
<pre>
# Implicit Boxing Type Conversion to object Type
my $num = 123;
my $object : Int = $num;
</pre>

<p>
  When the source Type is Any Object Type and the destination Type is Numeric Type, <a href="#language-type-convertion-unboxing">Unboxing Type Conversion</a> in the corresponding Numeric Type is displayed. Will be opened. In the following case, an attempt is made to convert the Int Type object to <a href="#language-type-int">int Type</a>.
</p>

<pre>
# Implicit Unboxing Type Conversion from objectType-
my $object : object;
my $num : int = $object;
</pre>
<p>
  
If the source Type is Numeric Object Type and the destination Type is the corresponding Numeric Type, <a href="#language-type-convertion-unboxing">Unboxing Type Conversion</a> in the corresponding Numeric Type Is done.
</p>

<pre>
# Implicit Unboxing Type Conversion from Numeric Object Type
my $num_obj = Int->new(3);
my $num : int = $num_obj;
</pre>

<p>
  If the source Type is Numeric Type and the destination Type is <a href="#language-type-string">String Type</a>, <a href = "#language-type-convertion-numeric-to-string ">Numeric-to-String Type Conversion</a> is performed. In the following case, the numerical value "123" is converted to String "" 123 "" and assigned.
</p>

<pre>
# mplicit Boxing Type Conversion to String Type
my $num = 123;
my $str : string = $num;
</pre>

<h3 id="language-type-convertion-numeric">Numeric Type Conversion</h3>

Numeric Type Conversion is the conversion from <a href="#language-type-numeric">Numeric Type</a> to <a href="#language-type-numeric">Numeric Type</a>.

Numeric Type Conversion performs exactly the same processing as Numeric Type Conversion in the corresponding C language. For example, Type Conversion from int to long in SPVM is the same as the type conversion from int32_t Type to int64_t Type in C language.

<pre>
# SPVM conversion
my $src : int = 5;
my $dist = (long)$src;

# Correspondence in C language
int32_t src = 5;
int64_t dist = (int64_t)src;
</pre>

See also <a href="#language-c99-type">Corresponding Type with C99</a>.

SPVM has two Numeric Type Convertions.

<ul>
  <li><a href="#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a></li>
  <li><a href="#language-type-convertion-numeric-widening">Numeric Widening Type Conversion</a></li>
</ul>

There are some rules for automatic type conversion of Numeric Type.

<ul>
  <li><a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a></li>
  <li><a href="#language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</a></li>
</ul>

Numeric types have an order.

<ul>
  <li><a href="#language-type-convertion-numeric-type-order">Numeric Type Order</a></li>
</ul>

<h3 id="language-type-convertion-numeric-type-order">Numeric Type Order</h3>
<p>
  <a href="#language-type-numeric">Numeric Type</a> has the order of Type. The order of Type is "byte", "short", "int", "long", "float", "double" from the smallest.
</p>
<h3 id="language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</h3>
<p>
  Unary Numeric Widening Type Conversion means that <a href="#language-expression">Expression</a> is <a href="#language-type-byte">byte Type</a> or short Type. In this case, perform <a href="#language-type-convertion-numeric-widening">Numeric Widening Type Conversion</a> to <a href="#language-type-int">int Type</a> I say that.
</p>
<p>
  Unary Numeric Widening Type Conversion is performed in the following cases.
</p>
<ul>
  <li>Array Index</li>
  <li>Dimension when creating Array</li>
  <li>Unary Plus Operator operands</li>
  <li>Unary Minus Operator operands</li>
  <li>Left and Right operands of Shift Operator "<<" ">>" ">>>"</li>
</ul>
<h3 id="language-type-convertion-binary-numeric-widening">Binary Numeric Widening Type Conversion</h3>
<p>
  Binary Numeric Widening Type Conversion is applied to Left Expression and Right Expression in Binary Operator that takes Numeric Type on the Left and Right sides. <a href="#language-type-convertion-numeric-widening">Numeric Widening Type Conversion</a>.
</p>
<p>
  The following rules apply.
</p>
<p>
  1. When one Expression is <a href="#language-type-double">double Type</a>, the other Type is <a href="#language-type-double">double Type</a> Is converted to>.
</p>
<p>
  2. If one Expression is <a href="#language-type-float">float Type</a>, the other Type is <a href="#language-type-float">float Type</a> Is converted to>.
</p>
<p>
  3. When one Expression is <a href="#language-type-long">long Type</a>, the other Type is <a href="#language-type-long">long Type</a> Is converted to>.
</p>
<p>
  4, otherwise, it will be converted to <a href="#language-type-int">int Type</a>.
</p>
<p>
  Binary Numeric Widening Type Conversion is performed in the following cases.
</p>
<ul>
  <li><a href="#language-operator-add">Addition Operator</a></li>
  <li><a href="#language-operator-subtract">Subtraction Operator</a></li>
  <li><a href="#language-operator-multiply">Multiplication Operator</a></li>
  <li><a href="#language-operator-divide">Division Operator</a></li>
  <li><a href="#language-operator-remainder">Remainder Operator</a></li>
  <li><a href="#language-operator-bit-and">Bit AND Operator</a></li>
  <li><a href="#language-operator-bit-or">Bit OR Operator</a></li>
  <li><a href="#language-operator-comparison-numeric">Numeric Comparison Operator</a></li>
</ul>

<h3 id="language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</h3>
<p>
  Numeric Narrowing Type Conversion is a conversion rule applied when converting from a large type to a small type in <a href="#language-type-numeric">Numeric Type</a>.
</p>

<h3 id="language-type-convertion-numeric-widening">Numeric Widening Type Conversion</h3>

<p>
  Numeric Widening Type Conversion is a conversion rule applied when converting from a small type to a large type in <a href="#language-type-numeric">Numeric Type</a>.
</p>

<h3 id="language-type-convertion-string-to-byte-array">String-to-byte[] Type Conversion</h3>

<b>String-to-byte[] Type Conversion</b> is the Type Conversion from <a href="#language-type-string">String Type</a> to <a href="#language-type-array-byte">byte[] Type</a>.

<pre>
# String-to-byte[] Type Conversion
my $string : string = "Hello";
my $bytes : byte[] = (byte[])$string;
</pre>

A new byte[] Type object is created and all characters in string are copied to the elements of byte[] Type.

<h3 id="language-type-convertion-byte-array-to-string">byte[]-to-String Type Conversion</h3>

<b>byte[]-to-String Type Conversion</b> is the Type Conversion from <a href="#language-type-array-byte">byte[] Type</a> to <a href="#language-type-string">String Type</a>.

<pre>
# byte[]-to-String Type Conversion
my $bytes : byte[] = new byte[3];
$bytes->[0] = 'a';
$bytes->[1] = 'b';
$bytes->[2] = 'c';
my $string : string = (string)$bytes;
</pre>

A new String Type object is created and all elements in byte[] are copied to the characters of String Type.

<h3 id="language-type-convertion-boxing">Boxing Type Conversion</h3>
<p>
  Boxing Type Conversion is the operation to convert the value of Numeric Type to Numeric Object Type.
</p>

<h3 id="language-type-convertion-unboxing">Unboxing Type Conversion</h3>

<p>
  Unboxing Type Conversion is an operation to convert the value of Numeric Object Type to the corresponding value of Numeric Type.
</p>

<h3 id="language-type-convertion-bool">Bool Type Conversion</h3>

<p>
  Bool Type Conversion is a conversion applied in the conditional part of if Statement, etc. for True/False Value judgment.
</p>
<p>
  <b>Where Bool Type Conversion takes place</b>
</p>
<p>
  <b>Inside the if statement braces</b>
</p>
<pre>
if (CONDITION) {

}
</pre>
<p>
  <b>In unless statement brackets</b>
</p>
<pre>
unless (CONDITION) {

}
</pre>
<p>
  <b>The second in the parentheses for</b>
</p>
<pre>
for (INITIALIZEATION;CONDITION;NEXT_VALUE;) {

}
</pre>
<p>
  <b>in parentheses while</b>
</p>
<pre>
while (CONDITION) {

}
</pre>
<p>
  <b>Left and Right of Logical AND Operator</b>
</p>
<pre>
CONDITION && CONDITION
</pre>
<p>
  <b>Left and Right of Logical OR Operator</b>
</p>
<pre>
CONDITION || CONDITION
</pre>
<p>
  <b>Right side of Logical NOT Operator</b>
</p>
<pre>
!CONDITION
</pre>
<p>
  Expression specified by Bool Type Conversion is <a href="#language-type-numeric">Numeric Type</a> or <a href="#language-type-object">Object Type</a> or It must be <a href="#language-type-undef">Undefined Type</a>, otherwise Compile Error occurs.
</p>
<p>
  Return Value of Bool Type Conversion is Expression of <a href="#language-type-int">int Type</a>.
</p>
<p>
  If Expression is <a href="#language-undef">Undefined Value</a>, 0 is returned.
</p>
<p>
  If Expression is Bool->FALSE, 0 is returned. This is special case of the object of Bool class. false keywords means Bool->FALSE.
</p>
<p>
  If Expression is Bool->TRUE, 1 is returned.  This is special case of the object of Bool class. true keywords means Bool->TRUE.
</p>
<p>
  When Expression is <a href="#language-type-numeric">Numeric Type</a>, <a href="#language-type-convertion-unary-numeric-widening">Unary Numeric Widening Type Conversion</a> is done.
</p>
<p>
  If Expression is <a href="#language-type-int">int Type</a>, that value is returned.
</p>
<p>
  Expression is <a href="#language-type-long">long Type</a>, <a href="#language-type-float">float Type</a>, <a href = "#language- If it is type-double ">double Type</a>, Object Type, the operation that exactly matches the following operation in C99 is performed and the result is returned.
</p>
<pre>
!!x
</pre>
<p>
  If Expression is Object Type, 0 is returned if it is Undefined Value, 1 otherwise.
</p>

<b>Bool Type Conversion Examples</b>

<pre>
if (1) {
  # run
}

if (0) {
  # not run
}

if (1.5) {
  # run
}

if (0.0) {
  # not run
}

if (true) {
  # run
}

if (Bool->TRUE) {
  # run
}

if (false) {
  # not run
}

if (Bool->FALSE) {
  # not run
}

my $object = SPVM::Int->new(1);

if ($object) {
  # run
}

if (undef) {
  # not run
}
</pre>

<h2 id="language-exception">Exception</h2>

<ul>
  <li><a href="#language-exception-summary">Exception overview</a></li>
  <li><a href="#language-exception-occur">Throw Exception</a></li>
  <li><a href="#language-exception-catch">Catch Exception</a></li>
  <li><a href="#language-exception-var">Exception Variable</a></li>
</ul>

<h3 id="language-exception-summary">Exception overview</h3>
<p>
  SPVM has a mechanism of Exception. Exception consists of raising <a href="#language-exception">Exception</a> and catching the exception.
</p>

<h3 id="language-exception-occur">Throw Exception</h3>
<p>
  Use die Statement to throw <a href="#language-exception">Exception</a>.
</p>
<pre>
die EXPRESSION;
</pre>
<p>
  Expression must be <a href="#language-type-string">String Type</a>.
</p>
<p>
  When the die statement is executed, the stack trace and the String specified by Expression are displayed, and the program ends. The stack trace includes Class Name, Method Name, File Name and line number. File Name is a relative File Name from the path where Module is loaded.
</p>
<pre>
Error
from TestCase::Minimal->sum2 at SPVM/TestCase/Minimal.spvm line 1640
from TestCase->main at SPVM/TestCase.spvm line 1198
</pre>

<h3 id="language-exception-occur">Catch Exception</h3>
<p>
  Exception catching is a function that can stop the program from ending and get an error message when <a href="#language-exception">Exception</a> is thrown.
</p>
<p>
  Exceptions are caught using eval Block Statement. Please note that the eval Block Statement requires a semicolon at the end.
</p>
<pre>
eval {
  # Processing that may throw <a href="#language-exception">Exception</a>
};
</pre>
<p>
  When <a href="#language-exception">Exception</a> is caught by the eval Block, the program termination is stopped and <a href="#language-exception-occur">is added to <a href="#language-exception-var">Exception Variable</a>. The message specified in Exception is thrown</a> is methodstituted.
</p>

<h3 id="language-exception-var">Exception Variable</h3>

<b>Exception Variable</b> is a global variable that is represented by "<b>$@</b>"

<pre>
$@
</pre>

See <a href="#language-expression-get-exception-var">Get Exception Variable Value</a> to get Exception Variable Value.

See <a href="#language-expression-set-exception-var">Set Exception Variable Value</a> to set Exception Variable Value.

<h2 id="language-garbage-collection">Garbage Collection</h2>
<p>
  The object is released from memory when the Reference Count reaches 0.
</p>
<p>
  If the object is an Array that has Object Type values ​​as elements, the Reference Count of all Array elements that are not Undefined Value is decremented by 1 before Garbage Collection
</p>
<p>
  When an object is a Class Type and has a Field of Object Type, the Reference Count of the objects owned by all Fields of Object Type that are not Undefined Value is decremented by 1 before Garbage Collection. If Weaken Reference is set to the object saved in Field, Weaken Reference is released before Reference Count is decremented by 1.
</p>
<p>
  When the object has Back references of Weaken Reference, Undefined Value is assigned to all Fields registered as back References and all back References are deleted.
</p>
<p>
  The above process is done recursively.
</p>

<h2 id="language-callback">Callback</h2>

<ul>
  <li><a href="#language-method-new-callback-object">Create Callback Object</a></li>
  <li><a href="#language-method-capture">Capture</a></li>
</ul>

<p>
  Callback Type in SPVM is a Class Type in which only one unnamed Method with no implementation is defined. If callback_tDescriptor is specified in <a href="#language-class-definition">Class Definition</a>, it becomes Callback Type.
</p>
<p>
  The purpose of Callback Type is to provide a Type that can be assigned to different objects when they have the same MethodDefinition. Consider that the function corresponding to the C function pointer is realized in SPVM.
</p>
<pre>
class Foo1 {
  static method new : Foo1 () {
    new Foo1;
  }
  method : int ($num : int) {
    return 1 + $num;
  }
}

class Foo2 {
  static method new : Foo2 () {
    new Foo2;
  }
  method : int ($num : int) {
    return 2 + $num;
  }
}

class FooCallback : callback_t {
method : int ($num : int);
}
</pre>

<p>
  Foo1 and Foo2 have the same MethodDefinition "method: int ($num: int)". Now suppose you want to selectively call the Foo1 or :Foo2 Method.
</p>
<p>
  In this case, if you define a Callback Type FooCallback with the same MethodDefinition, you can assign either object to this Type. Then you can call Method from this object.
</p>
<pre>
my $foo1 = Foo1->new;
my $foo2 = Foo2->new;

my $foo : FooCallback;

my $flag = 1;
if ($flag) {
  $foo = $foo1;
}
else {
  $foo = $foo2;
}

my $ret = $foo->(5);
</pre>
<p>
  If $flag is 1, the anonymous Method of Foo1 is called, otherwise the anonymous Method of Foo2 is called.
</p>
<p>
  For more information on Callback Type, see <a href="#language-type-callback">Callback Type</a>.
</p>

<h3 id="language-method-new-callback-object">Create Callback Object</h3>

<p>
  Create Callback Object is a Syntax that creates an object that conforms to Callback Type by using a special syntax for the purpose of Callback.
</p>

<pre>
method : TYPE_NAME  (ARGS1 : TYPE1, ARGS2 : TYPE2, ARGSN : TYPEn) {

}
</pre>

<p>
  When Create Callback Object is performed, <a href="#language-class-definition">Class Definition</a> is performed internally, an object based on that Class is generated, and <a href = " Returned as # language-expression ">Expression</a>. It is possible to assign to a variable like the following.
</p>

<pre>
my $cb_obj = method : TYPE (ARGS1 : TYPE1, ARGS2 : TYPE2, ..., ARGSn : TYPEn) {

};
</pre>

<p>
  Method defined by Create Callback Object must be <a href="#language-method-method">Method</a>. It must also be a Method with no name.
</p>

<p>
  <b>Create Callback Object Example</b>
</p>

<pre>
my $comparator = method : int ($x1 : object, $x2 : object) {

}
</pre>

<p>
  You can call Method because the object created by Create Callback Object is a normal object. For the call to Create Callback Object, see <a href="#language-expression-callsub">Method Call</a>.
<p>

<h3 id="language-method-capture">Capture</h3>
<p>
  In Create Callback Object, you can use the syntax called Capture to use the variables defined outside the Method defined by Create Callback Object inside the Method defined by Create Callback Object.
</p>
<pre>
# Capture
[VariableName1 : Type1, VariableName2 : Type2] method Method Name : int ($x1 : object, $x2 : object) {

};
</pre>

Capture Example.

<pre>
my $foo = 1;
my $bar = 5L;

my $comparator = [$foo : int, $bar : long] method : int ($x1 : object, $x2 : object) {

  print "$foo\n";
  print "$bar\n";
}
</pre>
<p>
  The variable name used in Capture must be the one with "$" added at the beginning of <a href="#language-token-identifier-field-name">Field Name</a>.
</p>
<p>
  The Capture is actually defined as a Field of Class. Capture is a field definition and value setting syntax sugar.
</p>
<p>
  If <a href="#language-local-var">Local Variable</a> with the same name as the Capture variable exists in the Scope, access the Local Variable.
</p>
<p>
  If there is a <a href="#language-class-var">Class Variable</a> with the same name as the Capture variable, access the Capture variable.
</p>
<p>
  If you write Create Callback Object and Capture without using syntax sugar, it will be as follows.
</p>

<pre>
class ComapartorImpl {
  has foo : int;
  has bar : long;

  method : int ($x1 : object, $x2 : object) {
    print $self->{foo} . "\n";
    print $self->{bar} . "\n";
  }
}
</pre>

<pre>
my $foo = 1;
my $bar = 5L;

my $comparator = new ComparatorImpl;

$comparator->{foo} = $foo;
$comparator->{bar} = $bar;
</pre>

Capture is a syntax for writing such a long description short.

<h2 id="language-weak-ref">Weaken Reference</h2>
<p>
  Weaken Reference is a reference that does not increase the Reference Count. Weaken Reference can be used to solve the problem of circular references.
</p>
<p>
  SPVM has GC of Reference Count Type. In the GC of Reference Count Type, the object is automatically released when the Reference Count becomes 0, but when the circular reference occurs, the Reference Count does not become 0 and the object is automatically released. not.
</p>
<p>
  This is an Example when the Field of the object is circularly referenced.
</p>
<pre>
{
  my $foo = new Foo;
  my $bar = new Bar;

  $foo->{bar} = $bar;
  $bar->{foo} = $foo;
}
</pre>
<p>
  In this case, both objects are not released when the Scope ends. This is because a circular reference has occurred and the Reference Count does not become 0.
</p>
<p>
  Weaken Reference is a function to correctly destroy objects when a circular reference occurs in a programming language that has a Reference Count GC.
</p>
<p>
  In such a case, it is possible to release correctly by setting one Field to Weaken Reference using <a href="#language-statement-weaken">weaken Statement</a>.
</p>
<pre>
{
  my $foo = new Foo;
  my $bar = new Bar;

  $foo->{bar} = $bar;
  $bar->{foo} = $foo;

  weaken $foo->{bar};
}
</pre>
<p>
  Before the weaken statement is executed, $foo has a Reference Count of 2 and $bar has a Reference Count of 2.
</p>
<p>
  If there is no weaken statement, the reference count of $foo and the reference count of $bar will not be 0 and will not be released even if the scope ends.
</p>
<p>
  When a weaken statement is executed, $foo has a Reference Count of 2 and $bar has a Reference Count of 1.
</p>
<p>
  When the Scope ends, the Reference Count of $bar is decremented by 1 and becomes 0, so it is released correctly.
</p>
<p>
  Even if there are 3 circular references, you can release them correctly by setting Weaken Reference in 1 Field.
</p>
<pre>
{
  my $foo = new Foo;
  my $bar = new Bar;
  my $baz = new Baz;

  $foo->{bar} = $bar;
  $bar->{baz} = $baz;
  $baz->{foo} = $foo;

  weaken $foo->{bar};
}
</pre>
<p>

As a syntax related to Weaken Reference, Weaken Reference can be released <a href="#language-statement-weaken">weaken Statement</a>, and it can be confirmed whether Field is Weaken Reference <a href = "#language- There is an operator-isweak ">isweak Operator</a>.
</p>

<h2 id="language-default-loaded-modules">Default loaded modules</h2>

SPVM loads the following modules just after the program start. These modules are deeply relataed to core features, such as type conversion.

<ul>
  <li><a href="https://metacpan.org/pod/SPVM::Byte">Byte</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Short">Short</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Int">Int</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Long">Long</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Float">Float</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Double">Double</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Bool">Bool</a></li>
</ul>

=end html
