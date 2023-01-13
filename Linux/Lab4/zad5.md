### strace - pozwala śledzić wszystki sygnały oraz syscalle procesu

- **-p** - pozwala podpiąć się pod any proces i obserwować go
- **-f** - śledzi wszystkie procesy potomne procesu
- **-t** - dodaje timestampy
- **-c** - formatuje wyjście w kolumny
- **-T** - podaje czas wykonania każdego syscalla
- **-e trace=TYPE** - wyświetla calle tylko tego typu, np. write, open
