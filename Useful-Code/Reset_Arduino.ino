void Reset_Arduino() {
 // Restart arduino by software
    asm volatile ("jmp 0x0000");
}
