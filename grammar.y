%%
prog           : consts funcs
               ;

consts         : consts const
               |
               ;

const          : ID '=' expr    
               ;                                     

funcs          : funcs func
               |
               ;

func           : type ID '(' formals ')' ';' 
               | type ID '(' formals ')' block           
               ;

formals        : formal_list
               |                
               ;

formal_list    : formal_list ',' formal 
               | formal   
               ;

formal         : type ID  
               ;

type           : BOOL          
               | INT           
               | FLOAT         
               | type '[' ']'  
               ;

expr           : expr OR expr  
               | expr AND expr 
               | NOT expr      
               | expr EQ expr  
               | expr NE expr  
               | expr '<' expr 
               | expr LE expr  
               | expr '>' expr 
               | expr GE expr  
               | expr '+' expr 
               | expr '-' expr 
               | expr '*' expr 
               | expr '/' expr 
               | expr '%' expr 
               | '(' type ')' expr %prec CAST 
               | '-' expr  %prec UMINUS
               | '+' expr  %prec UMINUS
               | '(' expr ')'  
               | IF '(' expr ')' expr ELSE expr
               | LET '(' lexicals ')' block
               | ID '(' actuals ')' 
               | ID                 
               | expr '[' expr ']'  
               | LENGTH expr        
               | BOOL_LIT             
               | INT_LIT            
               | FLOAT_LIT          
               | array_lit          
               | block
               ;

array_lit      : '[' elem_list ']'  
               ;

elem_list      : elem_list ',' expr
               | expr
               ;

block          : '{' expr_list '}'   
               ;

expr_list      : expr_list ';' expr  
               | expr   
               ;

lexicals       : lexicals ',' lexical 
               | lexical  
               ;

lexical        : ID '=' expr 
               ;

actuals        : actual_list
               |    
               ;

actual_list    : actual_list ',' expr 
               | expr   
               ;

%%
