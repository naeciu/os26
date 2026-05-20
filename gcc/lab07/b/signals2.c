/*
    [Robachevsky ,2010; 199]
*/
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


void (*mysignal (int signo, void (*hndlr)(int)))(int)
{
    struct sigaction act, oact;
    //Утановим маску сигналов
    act.sa_handler = hndlr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo != SIGALRM)
        act.sa_flags |= SA_RESTART;
    /*Установим диспозицию*/
    if(sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}

static void sig_hndlr(int signo)
{
    /* Эта часть кода нам уже не нужна 
       mysignal(SIGINT, sig_hndlr);*/
    printf("Получен сигнал SIGINT\n");
}

int main(void)
{    
    /*Установим диспозицию*/
    mysignal(SIGINT, sig_hndlr);
    mysignal(SIGUSR1, SIG_DFL);
    mysignal(SIGUSR2, SIG_IGN);
    while(1)
        pause();
}
