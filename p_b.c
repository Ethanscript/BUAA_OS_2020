void
umain(void)
{
    u_int who, i;

    for (;;) {
    	
        i = ipc_recv(&who, 0, 0);

        writef("%x got %d from %x\n", syscall_getenvid(), i, who);

        //user_panic("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
        if (i == 10) {
            return;
        }

        i++;
        writef("\n@@@@@send %d from %x to %x\n",i, syscall_getenvid(), who);
        ipc_send(who, i, 0, 0);

        if (i == 10) {
            return;
        }
    }

}
