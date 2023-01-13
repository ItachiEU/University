1.

```bash=
$ sudo adduser jantest
cat /etc/passwd | grep jantest
```

2.

```bash=
$ groups jantest
$ sudo usermod -a -G cdrom,plugdev,netdev,audio,video, bluetooth jantest
$ groups jantest
```

3.

```bash=
$ sudo visudo
jantest ALL=(root) /usr/bin/ip
```

4.

```bash=
$ sudo groupadd projekt
$ sudo usermod -aG projekt itachi
$ sudo usermod -aG projekt jantest
$ touch opis.txt && chgrp projekt opis.txt && chmod 660 opis.txt
```

5.

```bash=
$ itachi > groups
$ jantest > groups
```

6.

```bash=
$ sudo visudo
dodajemy: jantest ALL=(itachi) /usr/bin/whoami
$ jantest> sudo -u itachi whoami

```

7.

```bash=
$ sudo visudo
jantest ALL=(root) /usr/bin/chfn
$jantest> sudo chfn -f "Jan Testowy" jantest
```
