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
- exit não é executado em um fork caso seja chamado como comando unico.
- exit é executado em um fork caso hajam pipes


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
- \[exit status\] ```exemplo do comando``` Descrição da regra;
- \[0\]```<< EOF cat > out``` Toda token que venha DEPOIS de um redirecionador de IO (REDTOKEN) que não seja uma REDTOKEN é uma palavra;
- \[0\]```<< EOF cat > out``` Se depois de uma WORDTOKEN quem venha depois de uma REDTOKEN, existir uma token, ela sera uma COMTOKEN;
- \[0\]```ls``` Toda token que não é um builtin(BITOKEN) OU REDIRTOKEN OU OPTOKEN que aparece sozinha é COMTOKEN;
- \[0\]```valgrind --trace-children=yes --leak-check=full --track-origins=yes ./a.out``` Não havendo uma REDTOKEN, a primeira token deverá ser considerada COMTOKEN;
- \[0\]```cat out > wc``` Toda token depois de uma REDTOKEN é uma WORDTOKEN;
- \[2\]```cat out >``` Caso não exista token depois de uma REDTOKEN, retorna erro: ```syntax error near unexpected token `newline'```
- \[2\]```cat << > out``` Duas REDTOKENS seguidas dá bosta: ```syntax error near unexpected token ` ```
