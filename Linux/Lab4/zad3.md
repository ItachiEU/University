#### hostname

**hostname** pozwala skonfigurować lokalną nazwę systemu. Można ją zmienić konfigurując plik **/etc/hostname**

#### machine-id

Plik **/etc/machine-id** zawiera unikalne ID lokalnego systemu, generowane przy instalacji lub bootowaniu. Pozwala ono jednoznacznie identyfikować hosta i nie powinno być rozpowszechniane niezaufanym środowiskom.

#### os-release

Plik **/etc/os-release** oraz **/usr/lib/os-release** zawierają dane pozwalające zidentyfikować system operacyjny. Np. wersja, nazwa, codename wersji itp.

### Polecenia:

#### hostname:

- **-A, --all-fqdns** - wyświetla wszystkie pełne nazwy domenowe maszyny.
- **-d, --domain** - wyświetla nazwę domeny DNS
- **-i, --ip-address** - wyświetla adres sieciowy nazwy komputera
- **-I, --all-ip-addresses** - wyświetla wszystkie adresy IP komputera

#### hostnamectl

- **-H, --host=** - pozwala zmienić hostname remote komputera.
- **set-hostname NAME** - zmienia hostname na NAME
- **status** - wyświetla informacje o maszynie np.

#### uuid - Universally Unique Identifier

Pozwala wygenerować 128-bitowy unikalny identyfikator

#### uuidgen

- **-r** - zrandomizowany
- **-t** - na podstawie czasu

#### dbus-uuidgen

- **-ensure[=FILE]** - pozwala upewnić się że w pliku znajduje się UUID
- **-get[=FILE]** - zwraca UUID z pliku

#### uname

- **--all** - wyświetla wszystkie informacje
- **-s, --kernel-name** - wyświetla nazwę jądra
- **-n, --nodename** - wyświetla sieciową nazwę systemu
- **-m, --machine** - wyświetla nazwę (architekturę) komputera
- **-p, --processor** - wyświetla typ procesora
- **-o, --operating-system** - wyświetla system operacyjny

#### lsb_release

- **-d, --description** - wyświetla informacje o dystrybucji
- **-a, --all** - wyświetla wszystkie informacje o dystrybucji
