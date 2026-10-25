#   Setup!
mkdir -p ~/os-lab1 && cd ~/os-lab1
whoami      # who am I to the OS
uname -a    # which kernel is managing this machine
uptime      # how long has this OS been running

#   Part 1
pwd         # where am I
ls -la /    # root of the whole filesystem tree
ls -la ~    # home directory
cd /etc && ls | head

cd ~/os-lab1
mkdir demo && cd demo
echo "hello operating system" > note.txt
cp note.txt copy.txt
mv note.txt copy.txt
ls -l
rm renamed.txt

ls -l note.txt
chmod 600 note.txt
ls -l note.txt
chmod 644 note.txt


#   Part 2
ps aux | head
ps aux | wc -l
top

sleep 300 &
PID=$!
ls /proc/$PID/
cat /proc/$PID/status | head -20
kill $PID


#   Part 3
free -h
cat /proc/meminfo | head -6
sleep 300 & PID=$!
grep VmRSS /proc/$PID/status
kill $PID


#   Part 4
df -h
lsblk
du -sh ~/os-lab1
ls -l /dev | head
mount | head
