1.

```bash=
$ systemctl status ssh

```

2.

```bash=
$ ssh-keygen

```

3.

```bash=
$ ssh-copy-id -i dojana.pub jantest@localhost
$ ssh -i dojana jantest@localhost
```

4.

```bash=
$ vim ~/.ssh/config
Host jantest
        HostName localhost
        User jantest
        IdentityFile /home/itaachi/.ssh/dojana
        IdentitiesOnly yes
```

5.

```bash=
$ eval $(ssh-agent)
$ ssh-add -t 300 dojana
$ ssh-add -d dojana
```

6.

```bash=
$ sudo passwd -l jantest

```

7.

```bash=
$ sudo usermod -aG sudo itachi
$ sudo -iu jantest
```

8.

```bash=
$ sudo passwd -u jantest
$ sudo usermod -e 1 jantest

```

9.

```bash=
$ sudo usermod -e "" jantest
$ usermod --shell /bin/false jantest
```

10.

```bash=
$ vim /etc/ssh/sshd_config
PermitRootLogin no
```
