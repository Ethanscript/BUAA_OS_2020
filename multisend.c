LEAF(syscall_ipc_can_multi_send)
                addiu t0,a0,0		//第一个参数 
                addiu t1,a1,0		//第二个参数 
                addiu t2,a2,0		//第三个参数 
                addiu a0,zero,9543	//设置第一个为id 
                addiu t3,a3,0       // num of env
                addiu a1,t3,4		//num+4为总参数个数 
                addiu a2,t0,0		//本来的第一个参数 
                addiu a3,t1,0		//本来的第二个参数 

                sw t3,12(sp)		//本来的第四个参数 
                sw t2,8(sp)			//本来的第三个参数 
                addiu sp,sp,-8		//sp-8，预留空位置 
                sw ra,0(sp)			//保存ra寄存器的值 

                jal msyscall
                nop

                lw ra,0(sp)			//恢复ra寄存器的值 
                addiu sp,sp,8		//恢复sp 

                jr ra
                nop
END(syscall_ipc_can_multi_send)

LEAF(syscall_ipc_can_multi_send)
                addiu t0,a0,0		//第一个参数 
                addiu t1,a1,0		//第二个参数 
                addiu t2,a2,0		//第三个参数 
                addiu a0,zero,9543	//设置第一个为id 
                addiu t3,a3,0       // num of env
                addiu a1,t3,4		//num+4为总参数个数 
                addiu a2,t0,0		//本来的第一个参数 
                addiu a3,t1,0		//本来的第二个参数 
				
				addiu s0,sp,0		//s0保留sp的初始位置 
				li t4,0				//循环次数 
				li t5,0				//记录+4 
				get_top_addr:
					beq t4,t3,end_get_top_addr
					nop
					addiu t5,t5,4
					addiu t4,t4,1
					j get_top_addr
					nop
					
				end_get_top_addr:
					addiu t5,t5,16	//栈中最上方参数偏移 
					addiu t5,t5,sp	//栈中最上方参数的位置 
				
				li t4,0
				addiu sp,sp,-4		//预备向下复制 
				copy_from_top:
					beq t4,t3,end_copy_from_top
					nop
					lw t6,(t5)
					sw t6,(sp) 		//拷贝到当前sp位置 
					addiu sp,sp,-4	//sp下移 
					addiu t5,t5,-4	//t5下移 
					j copy_from_top
					nop
				
				end_copy_from_top:
					sw t3,(sp)		//原本第四个参数 
					addiu sp,sp,-4	 
					sw t2,(sp)		//原本第三个参数 
					addiu sp,sp,-16	//预留空间 
					sw s0,(sp)		//保留sp本来的数 
					sw ra,4(sp)		//保留ra 
				
                jal msyscall
                nop
				
                lw ra,4(sp)			//恢复ra寄存器的值 
                lw t0,0(sp)			//取出sp本来的数
                addiu sp,sp,t0		//恢复sp 

                jr ra
                nop	
				
END(syscall_ipc_can_multi_send)
