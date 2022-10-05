## Quotes
- [x] Error message for unclosed quotes.

## Exit code
- [ ] 127 for "command not found!"

## Built-ins
### Env
- [ ] error message if PATH is unset.
### Export
- [x] Error message if no arguments;
	obs.: does not appear if there's a space in the argument;
- [x] Replace variable if it already exists; 
- [x] Add (and replace) multiple variables at a time;
- [x] Does not add variables without values (without "=");
- [x] Adds variables with only "=" e.g.: `HELLO=`.

### Unset
- [x] Unsets the first variable in the list.
- [ ] Unsets all variables in the env list.
- [ ] No segfault if trying to unset all variables and then some.
- [ ] 

## Variable expansion
- [x]  (EXPORT) Checks if it works for variables with no parameters like `VARIABLE=`
- [x]  Checks `VAR=$VAR` expansions.