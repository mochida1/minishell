# minishell
Mudar a descrição depois

## nota de compilação
utilizar `-lreadline` como em `gcc -Wall -Wextra -Werror nomearquivo.c -lreadline -o nomebinario

## Glossário:
[Gnu Bash manual: 2 - Definitions](https://www.gnu.org/software/bash/manual/html_node/Definitions.html)


## metacharacters

`|`	: pipe
`$`	: dolla sign
`>`	:
`<`	:
`'`	:
`"`	:
`>>`:
`<<`:
`.` :
`/` :

## pior caso
```<./infile.txt cmd1 'arg"' "arg'" 'apenas'"1"'arg'|cmd2 "arg||" "$var" '$notvar'>~/dir/outfile```


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
