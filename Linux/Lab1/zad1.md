## Zadanie 1

```bash
alias ll="ls -lAFbhv --color=always | less -XER"
```
### Flagi:
* ls:
    * **l** - używa długiego formatu wyjściowego
    * **A** - almost all (bez pokazywania . oraz ..)cat
    * **b** - cytuje znaki niegraficzne w stylu języka C (ósemkowo)
    * **h** - human readable jednostki np 1K 234M 2G itp
    * **v** - natural sort of (version) numbers within text
    
* less:
    * **X** - Disables sending the termcap initialization and deinitialization strings to the terminal. This is sometimes desirable if the deinitialization string does something unnecessary, like clearing the screen.
    * **E** - Causes less to automatically exit the first time it reaches end-of-file.
    * **R** - Causes "raw" control characters to be displayed. Unlike -r, the screen appearance is maintained correctly in most cases.


```bash
alias gentmp="echo tmp-$(date +%Y%m%d%H%M%S)"
```

```bash
alias genpwd="</dev/urandom tr -dc '3-9A-HJ-NP-Z' | head -c 32 | xargs echo $1"
```

