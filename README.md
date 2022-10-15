# minishell
Mudar a descrição depois

## nota de compilação
utilizar `-lreadline` como em `gcc -Wall -Wextra -Werror nomearquivo.c -lreadline -o nomebinario

## Glossário:
[Gnu Bash manual: 2 - Definitions](https://www.gnu.org/software/bash/manual/html_node/Definitions.html)


## metacharacters

- `|`	: pipe
- `$`	: dolla sign
- `>`	: overwrite
- `<`	: infile
- `'`	:
- `"`	:
- `>>`: append
- `<<`: heredoc
- `.` :
- `/` :

## pior caso
```<./infile.txt cmd1 'arg"' "arg'" 'apenas'"1"'arg'|cmd2 "arg||" "$var" '$notvar'>~/dir/outfile```

## pontos de atenção
- usuário dá unset na env PATH e roda comando: deve retornar No such file or directory.
- exit não é executado em um fork caso seja chamado como comando unico.
- exit é executado em um fork caso hajam pipes
- caso o usuário queira foder os manos: `< infile1 < infile2 cat`, apenas o segundo redir é considerado.
- `<< EOF < infile cat` abre o heredoc, mas pega infile como input.
- `<< EOF < test_expand_vars.c cat > this >> teste` abre o **heredoc**, pega **infile** como *input*, executa, cria **this**, cria e utiliza **teste** como *output*.

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
- \[0\]```<< EOF cat > out``` Toda token que venha DEPOIS de um redirecionador de IO (REDTOKEN) que não seja uma REDTOKEN é um FDTOKEN;
- \[0\]```<< EOF cat > out``` Se depois de uma WORDTOKEN quem venha depois de uma REDTOKEN, existir uma token, ela sera uma COMTOKEN;
- \[0\]```ls``` Toda token que não é um builtin(BITOKEN) OU REDIRTOKEN OU OPTOKEN que aparece sozinha é COMTOKEN;
- \[0\]```valgrind --trace-children=yes --leak-check=full --track-origins=yes ./a.out``` Não havendo uma REDTOKEN, a primeira token deverá ser considerada COMTOKEN;
- \[0\]```cat out > wc``` Toda token depois de uma REDTOKEN é uma WORDTOKEN;
- \[2\]```cat out >``` Caso não exista token depois de uma REDTOKEN, retorna erro: ```syntax error near unexpected token `newline'```
- \[2\]```cat << > out``` Duas REDTOKENS seguidas dá bosta: ```syntax error near unexpected token ` ```

## testes
O readline sempre vaza `still reachable: 204,580 bytes in 215 blocks`por padrão.
``` template ```

```not echo```
```echonot```
```echo$```

```echo```
```echo ```
```echo                     ```
```echo test001```
```echo test001             ```
```echo test             001```
```echo $```
```echo $PWD```
```echo $test000```
```echo test000 $PWD```
```echo "test000 $PWD"```
```echo 'test000 $PWD'```
```echo test000 "$PWD"```
```echo test000 '$PWD'```
```echo test000 $var_que_nao_existe```
```echo "test000 $var_que_nao_existe"```
```echo 'test000 $var_que_nao_existe'```
```echo test000 "$var_que_nao_existe"```
```echo test000 '$var_que_nao_existe'```
```echo test000$PWD```
```echo "test000$PWD"```
```echo 'test000$PWD'```
```echo test000"$PWD"```
```echo test000'$PWD'```
```echo "test000"$PWD```
```echo 'test000'$PWD```
```echo test000$var_que_nao_existe```
```echo "test000$var_que_nao_existe"```
```echo 'test000$var_que_nao_existe'```
```echo 'test000'$var_que_nao_existe```
```echo "test000"$var_que_nao_existe```
```echo test000'$var_que_nao_existe'```
```echo test000"$var_que_nao_existe"```
```echo exit```
./a.out init' 1 2 '" 3 4 "parseme
./a.out  a' 1 2 3 '" 4 5 6 "b

```exit```
exits with 0;
```exit 1```
exits with 1;
```exit a```
*exit*
*bash: exit: a: numeric argument required*
exits with 2;
```exit a b c d e f```
*exit*
*bash: exit: a: numeric argument required*
exits with 2;
```exit 1 2 3 4 5 6```
*exit*
*bash: exit: too many arguments*
RETURNS 1, does not exit;
```exit 1 a b c d e```
*exit*
*bash: exit: too many arguments*
RETURNS 1, does not exit;
```exit a 1 2 3 4 5```
*exit*
*bash: exit: a: numeric argument required*
exits with 2;
```exit 2147483647```
exits with 255;
```exit 2147483648```
exits with 0;
```exit 2147483649```
exits with 1;

```<< EOF < INFILE cdm arg1 arg2 >> APP > OW | < in << eof cdm arg3 arg4 > ow >> app```

echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options