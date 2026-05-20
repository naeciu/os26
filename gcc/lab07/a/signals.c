#include <stdio.h>
#include <signal.h>
#include <unistd.h>


static void sig_hndlr0(int signo)
{
    /*Восстановим диспозицию*/
    signal(SIGINT, sig_hndlr0);
    printf("Получен сигнал SIGINT\n");
}    

static void sig_hndlr1(int signo)
{
    /*Восстановим диспозицию*/
    signal(SIGKILL, sig_hndlr1);
    printf("Получен сигнал SIGKILL\n");
}    


int main(void)
{    
    /*Установим диспозицию*/
    signal(SIGINT,  sig_hndlr0);
    signal(SIGKILL, sig_hndlr1);
    signal(SIGUSR1, SIG_DFL);
    signal(SIGUSR2, SIG_IGN);
    while(1)
        pause();
}
