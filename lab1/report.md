# Report for laboratory nr. 1
This laboratory work will cover the overview of the OS as the intermediate layer between the user and the hardware. In this lab, such tasks as managing files, processes, memory, and devices, are executed in order to observ and understand the way these procedures work and the actions they imply.

## Initial setup

As a starting point, the following commands are executed in order to create an environment for exercising with the above mentioned procedures.

```shell
# Setup!
mkdir -p ~/Documents/cursuri/sisteme-operare/os-lab1 && cd ~/Documents/cursuri/sisteme-operare/os-lab1
whoami      # who am I to the OS
uname -a    # which kernel is managing this machine
uptime      # how long has this OS been running
```

## Part 1: files and directories (Filesystem)

```shell
pwd
ls -la /
ls -la ~
cd /etc && ls | head
```

With the above commands, the working directory (`/home/lungus/Documents/cursuri/sisteme-operare/os-lab1`) is shown. Next, `ls -la /` displays the directories and files from the root directory of the file system, with their access rights, owner, size in bytes, and so on. After this, command `ls -la ~` shows all directories and files that are located in the home directory, as well as the previously mentioned details. The last command, `cd /etc && ls | head` moves to the /etc directory and shows the first 10 outputs of the `ls` command (pipeline operations).

```shell
cd ~/Documents/cursuri/sisteme-operare/os-lab1
mkdir demo && cd demo
echo "hello operating system" > note.txt
cp note.txt copy.txt
mv note.txt renamed.txt
ls -l
rm renamed.txt
```

Next commands have the following workflow. Shell switches back to the laboratory's directory, where a new directory called `demo` is created and moved into. After this, a string is outputed via the `echo` command and wrote to a file called `note.txt`. Then, `note.txt` is copied as `copy.txt`, after which it's renamed via `mv` command as `renamed.txt`. Finally, the contents of the `demo` directory are shown, and the `renamed.txt` file is removed via the `rm` command.

```shell
ls -l copy.txt
chmod 600 copy.txt
ls -l copy.txt
chmod 644 copy.txt
```

The rwx of the `copy.txt` transitioned as follows:

```console
-rw-rw-r--
-rw-------
-rw-r--r--
```

In the process, and in my case, the owner and group columns remained the same during the `chmod`-ing. These characters display the permissions for reading, writing, and executing the files and directories. In the case of `chmod 600`, the rwx column is `-rw-------`, which only allows reading and writing by the owner (600 shows that the owner has the 6 = 4 + 2 rights, which mean read and write rights, while group and others have no right for to the file).

## Part 2: processes (Process management)

```shell
ps aux | head
ps aux | wc -l
top
```

`ps aux | head` command displays the first 10 entries from the processes list. `ps aux | wc -l` writes the number of active processes that are running in the OS. `top` command shows the active list of processes, including their PID, user, memory footprint, processing usage, time and so on.

```shell
sleep 300 &
jobs
ps -ef | grep sleep
kill <PID>
```

In this bash snippet, sleep process is called with the sleeping period of 300 seconds, `&` specifying that it runs in background, and returns it's PID, which is 5752 in the current session. `jobs` displays the background jobs and their status. `ps -ef` returns the processes list, after which `grep sleep` selects those processes that contain the `sleep` keyword. This way, the above mentioned command is shown with the corresponding data. Finally, the `kill 5752` command terminated this task.

```shell
sleep 300 &
PID=$!
ls /proc/$PID/
cat /proc/$PID/status | head -20
kill $PID
```

Similar to the previous snippet, a process that sleeps for 300 seconds is started. Then, `PID` variable is defined and contains the PID value of the process mentioned above, which is 5842. Next, the process' pseudo-filesystem is shown. From it, the first 20 entries from the status directory are returned. My OS currently has 298 processes according to the `ps aux | wc -l` command. The status command shows that the process has the `S (sleeping)` state.

## Part 3: memory (Memory management)

```shell
free -h
cat /proc/meminfo | head -6
sleep 300 & PID=$!
grep VmRSS /proc/$PID/status
kill $PID
```

Using the `free -h` command, systems memory usage is displayed, both for the regular one and the `swap` file. In the case of the host OS, it is as follows:

```console
               total        used        free      shared  buff/cache   available
Mem:            15Gi       4.3Gi       8.4Gi       754Mi       3.8Gi        11Gi
Swap:          2.0Gi          0B       2.0Gi
```

On the output of the `cat /proc/meminfo | head -6`, a similar output is printed, specifically for the memory. 

For the sleeper process, its VmRSS size from `grep VmRSS /proc/$PID/status` is `2132kB`. This represents the memory that a process uses given the stack, heap, systems overhead and so on.

## Part 4: devices and storage (I/O management)

```shell
df -h
lsblk
du -sh ~/Documents/cursuri/sisteme-operare/os-lab1
ls -l /dev | head
mount | head
```

Starting with `df -h`, the filesystem hierarchy is shows as follows:

```console
Filesystem      Size  Used Avail Use% Mounted on
tmpfs           1.6G  1.9M  1.6G   1% /run
efivarfs        374K  274K   96K  75% /sys/firmware/efi/efivars
/dev/sda2       109G   74G   30G  72% /
tmpfs           7.7G   28M  7.7G   1% /dev/shm
tmpfs           5.0M  8.0K  5.0M   1% /run/lock
/dev/sda1       511M   20M  492M   4% /boot/efi
tmpfs           1.6G  244K  1.6G   1% /run/user/1000
```

Reading the above output, it's observed that the root `/` is mounted on the `/dev/sda2`, which is a partition of the SSD on which the system is installed (the other part of the storage is allocated for the efi boot structure: `/dev/sda1`). 

For the `du -sh` command, the size of the working directory is `12K`.

Command `ls -l /dev | head`, which displays the devices that are presented as files, as for example `console` in:

```console
crw--w----   1 root tty         5,     1 Oct  4 09:38 console
```

This represents a key philosophy of the UNIX-like systems, "everything is a file". This means that storage, memory, devices, peripherals, and so on, are represented as files through which the OS communicates with them. 

Finally, `mount | head` shows the other filesystems that are mounted to the main one, as for example the `/dev/sda2`, which is storage that is used by the users for their needs.