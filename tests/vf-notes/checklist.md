## Quotes
- [x] Error message for unclosed quotes.

## Built-ins
### Export
- [x] Error message if no arguments;
	obs.: does not appear if there's a space in the argument;
- [x] Replace variable if it already exists; 
- [x] Add (and replace) multiple variables at a time;
- [x] Does not add variables without values (without "=");
- [x] Adds variables with only "=" e.g.: `HELLO=`

### Unset
- [x] Unsets the first variable in the list.

## Variable expansion
- [ ]  (EXPORT) Checks if it works for variables with no parameters like `VARIABLE=`
- [ ]  Checks `VAR=$VAR` expansions (recursion).