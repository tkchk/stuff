Assumptions: Host machine is linux.

1. Download virtualbox
2. Install a linux flavour. Preference for Debian since distro-dependent commands in the following steps will be debian-dependent
3. Run your VM.
4. Inside VM, download last kernel code from kernel.org
5. Extract linux src code
6. Copy your configuration file from `/boot/config-$(uname -r)` to `.config` in the extract linux src code folder.
7. Make sure `.config` has the following options: CONFIG_FRAME_POINTER=y , CONFIG_KGDB=y , CONFIG_KGDB_SERIAL_CONSOLE=y , CONFIG_KGDB_KDB=y , CONFIG_KDB_KEYBOARD=y. Change if necessary. Alternatively use `make xconfig` to configure in UI.
8. Install compilation dependencies (debian: `sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev`)
9. Compile the kernel: `make -j8`
10. Compile kernel modules: `sudo make modules_install`
11. Install kernel to `/boot`: `sudo make install`
12. Output will be in `/boot` directory. GRUB needs to be updated. On debian, run: `sudo update-initramfs -c -k <KERNEL VERSION>`. Example: `sudo update-initramfs -c -k 5.6.9`
13. After that, run `sudo update-grub`.
14. For more info about the compilation part, here: https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html
15. Go back to linux src folder and find the compiled file `vmlinux`. Send this file to your host machine, either using `scp` or virtualbox shared folders.
16. Reboot the VM. Afterwards, run `uname -rms`. You should see the new just-compiled version.
17. Run `sudo vim /etc/default/grub`
18. Append to `GRUB_CMDLINE_LINUX_DEFAULT` the following parameters: `kgdboc=ttyS0,115200 nokaslr`. The first parameter tells the debugger to be active on serial port `/dev/ttyS0`. The second one tells to load the kernel without address space layout randomization, so the debugger can find the function addresses properly. Example: `GRUB_CMDLINE_LINUX_DEFAULT=quiet splash kgdboc=ttyS0,115200 nokaslr`.
19. Run `sudo update-grub`.
20. Turn off the VM.
21. On the host machine, open VM settings and go to Serial Ports. Go to tab `Port 1`. Mark `Enable serial port`. Choose `Port Number=COM1`, `Port Mode=Host Pipe` and Path/Address=`/tmp/pipe`. Don't mark `Connect to existing pipe/socket.`
22. Run the VM again.
23. Open a terminal in the VM and go to su mode by running `sudo su`
24. Run `echo g > /proc/sysrq-trigger` to make the kernel execution stop and wait for the debugger to be attached. Note that once you run this command, the VM will be frozen until you continue the execution using GDB later.
25. On the host machine, run `socat -d /tmp/pipe TCP4-LISTEN:65335`. This will create a TCP connection from the `/tmp/pipe`. Even though GDB supports connecting directly to serial ports, the `/tmp/pipe` is a UNIX socket, so GDB does not recognize it as a serial port. Using `socat` we can create a TCP connection and connect using GDB.
26. Now run GDB via `gdb ./vmlinux` where `./vmlinux` is the path to the kernel binary file that you copied before.
27. In GDB run `target remote localhost:65335`.
28. At this point the debugger should be attached. Put breakpoints using `break` and type `continue` to resume the kernel execution in the VM.
