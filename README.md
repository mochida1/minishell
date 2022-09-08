# minishell
Mudar a descrição depois

## nota de compilação
utilizar `-lreadline` como em `gcc -Wall -Wextra -Werror nomearquivo.c -lreadline -o nomebinario

## Glossário:
[Gnu Bash manual: 2 - Definitions](https://www.gnu.org/software/bash/manual/html_node/Definitions.html)


## metacharacters

- `|`	: pipe
- `$`	: dolla sign
- `>`	:
- `<`	:
- `'`	:
- `"`	:
- `>>`:
- `<<`:
- `.` :
- `/` :

## pior caso
```<./infile.txt cmd1 'arg"' "arg'" 'apenas'"1"'arg'|cmd2 "arg||" "$var" '$notvar'>~/dir/outfile```

## pontos de atenção
- usuário dá unset na env PATH e roda comando: deve retornar No such file or directory.


## testes para regras de parsing
```
> diff "tfile1"'tfile2'
< diff: missing operand after 'tfile1tfile2'
```
```
> MEUECHO="cat tfile1 > outfile"
> MEUECHO
< 111111111111111111
< cat: '>': No such file or directory
```
```
> echo teste | cat readline.c >>> teste
< syntax error near unexpected token `>'
```

## regras para categorização de tokens
- \[exit status\] ```exemplo do comando```descrição da regra
- \[0\]```<< EOF cat > out``` toda token que venha DEPOIS de um redirecionador de IO (REDTOKEN) é uma palavra
- \[0\]```<< EOF cat > out``` Se depois de uma WORDTOKEN quem venha depois de uma REDTOKEN, existir uma token, ela sera uma COMTOKEN
- \[0\]```ls``` Toda token que não é um builtin(BITOKEN) OU REDIRTOKEN OU OPTOKEN que aparece sozinha é COMTOKEN
- \[0\]```valgrind --trace-children=yes --leak-check=full --track-origins=yes ./a.out``` não havendo uma REDTOKEN, a primeira token deverá ser considerada COMTOKEN
- \[0\]```cat out > wc``` toda token depois de uma REDTOKEN é uma WORDTOKEN
- \[2\]```cat out >```caso não exista token depois de uma REDTOKEN, retorna erro: ```syntax error near unexpected token `newline'```
- \[2\]```cat << > out``` duas REDTOKENS seguidas dá bosta: ```syntax error near unexpected token ` ```
