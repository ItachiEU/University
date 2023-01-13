### ls

- **-a, --all** - pokazywanie wszystkich plików w katalogu
- **-A, --almost-all** - pokazywanie wszystkich plików prócz . i ..
- **--author** - pokazuje autora pliku
- **-c** - wypisuje w kolumnach
- **--color** - koloruje wyniki
- **--directory** - wypisuje same katalogi, bez ich zawartości
- **-h, --human-readable**
- **-l** - długi format wyjścia
- **-R, --recursive** - wypisuje katalogi rekurencyjnie

### stat

- **-f, --file-system** - wyświetla status systemu plików, a nie pliku
- **-t, --terse** - wyświetla w bardzo zwięzłej formie
- **--printf=FORMAT** - pozwala użyć formatu wyjścia
- **Przykładowe opcje formatowania:**
  - **%b** - liczba zajętych bloków
  - **%f** - wyjście szesnastkowo
  - **%F** - typ pliku
  - **%G** - nazwa grupy właściciela pliku
  - **%m** - mountpoint
  - **%n** - nazwa pliku
  - **%u** - uid właściciela pliku
  - **%w** - human readable czas utworzenia pliku
  - **%y** - human readable czas ostatniej modyfikacji

### realpath

- **-l** - rozwija '..' przed dowiązaniami symbolicznymi
- **--relative-to=FILE** - wypisuje ścieżkę w odniesieniu do FILE
- **-s, --strip, --no-symlinks** - nie rozwija dowiązań symbolicznych

### readlink

realpath jest sugerowanym rozwiązaniem

- **-f, --canonicalize** - wypisuje kanoniczną nazwę pliku, podążając za każym dowiązaniem symbolicznym (wszytkie oprócz ostatniego muszą istnieć)
- **-e, --canonicalize-existing** -(wszytkie muszą istnieć)
- **-m, --canonicalize-missing** - (nie muszą istnieć)
