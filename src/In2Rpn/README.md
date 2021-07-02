# BNF

```BNF
<expression> := <term> { <binary> }*;

<binary> := ... { [ ( `+` | `-` | `*` | `/` | `^` ) ] <term> };

<term> := { <unary> }*;
<unary> := [ ( `+` | `~` | `-` ) ] ( <function> | <identifier> | <paren> ) [ `!` | `square` | `cube` | `inverse` | `%` ];

<function> := <function_name> [ ( `(` <expression> [ { `,` <expression> }+ ] `)` ] | <term> );

<paren> := `(` <expression> `)`;

<identifier> := ( <constant> | <memory> | <number> );
<constant> := ( `M_PI` | `M_E` );
<memory> := ( `MEMORY_ANS` | `MEMORY_A` | `MEMORY_B` | `MEMORY_C` | `MEMORY_D` | `MEMORY_M` | `MEMORY_X` | `MEMORY_Y` );
<number> := ( [0-9]+ | [0-9]*\.[0-9]+ | [0-9]*\.[0-9]+e\+[0-9]+ );
```
