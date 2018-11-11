#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(){
    
    printf("1: %d\n", getpid());
    // pid_t p2 = fork();
    // if(p2){ //1
        pid_t p3 = fork();
        if(!p3){ //3
            printf("3: %d\n", getpid());
            pid_t p6 = fork();
            if(p6){ //3
                pid_t p7 = fork();
                if(!p7){ //7
                    printf("7: %d\n", getpid());
                    pid_t p12 = fork();
                    if(p12){ //7
                        pid_t p13 = fork();
                        if(!p13){ //13
                            printf("13: %d\n", getpid());
                            while(1);
                            exit(0);
                        }else{//7
                            waitpid(p12,NULL,0);
                            waitpid(p13,NULL,0);
                            exit(0);
                        }
                    }
                    else{ //12
                        printf("12: %d\n", getpid());
                        pid_t p20 = fork();
                        if(p20){ //12
                            pid_t p21 = fork();
                            if(!p21){ //21
                                printf("21: %d\n", getpid());
                                while(1);
                                exit(0);
                            }else{//12
                                waitpid(p20, NULL,0);
                                waitpid(p21, NULL,0);
                                exit(0);
                            }
                        }else{ //20
                            printf("20: %d\n", getpid());
                            while(1);
                            exit(0);
                        }
                    }
                }else{ //3
                    waitpid(p6,NULL,0);
                    waitpid(p7,NULL,0);
                    exit(0);
                }
            }else{ //6
                printf("6: %d\n", getpid());
                while(1);
                exit(0);
            }
        }else{ //1
            waitpid(p2,NULL,0);
            waitpid(p3,NULL,0);
            exit(0);
        }
    // }
    // else{ //2
    //     printf("2: %d\n", getpid());
        pid_t p5 = fork();
        if(!p5){ //5
            printf("5: %d\n", getpid());
            pid_t p10 = fork();
            if(p10){ //5
                pid_t p11 = fork();
                if(!p11){ //11
                    printf("11: %d\n", getpid());
                    pid_t p18 = fork();
                    if(p18){ //11
                        pid_t p19 = fork();
                        if(!p19){ //19
                            printf("19: %d\n", getpid());
                            while(1);
                            exit(0);
                        }else{//11
                            waitpid(p18,NULL,0);
                            waitpid(p19,NULL,0);
                            exit(0);
                        }
                    }
                    else{ //18
                        printf("18: %d\n", getpid());
                        pid_t p24 = fork();
                        if(p24){ //18
                            pid_t p25 = fork();
                            if(!p25){ //25
                                printf("25: %d\n", getpid());
                                while(1);
                                exit(0);
                            }else{//18
                                waitpid(p24, NULL,0);
                                waitpid(p25, NULL,0);
                                exit(0);
                            }
                        }else{ //24
                            printf("24: %d\n", getpid());
                            while(1);
                            exit(0);
                        }
                    }
                }else{ //5
                    waitpid(p10,NULL,0);
                    waitpid(p11,NULL,0);
                    exit(0);
                }
            }else{ //10
                printf("10: %d\n", getpid());
                while(1);
                exit(0);
            }
        }else{ //2
            // pid_t p4 = fork();
            // if(!p4){ //4
            //     printf("4: %d\n", getpid());
                pid_t p9 = fork();
                if(!p9){ //9
                    printf("9: %d\n", getpid());
                    pid_t p17 = fork();
                    if(!p17){ //17
                        printf("17: %d\n", getpid());
                        while(1);
                        exit(0);
                    }else{ //9
                        pid_t p16 = fork();
                        if(!p16){ //16
                            printf("16: %d\n", getpid());
                            pid_t p22 = fork();
                            if(p22){ //16
                                pid_t p23 = fork();
                                if(!p23){ //23
                                    printf("23: %d\n", getpid());
                                    while(1);
                                    exit(0);
                                }else{//16
                                    waitpid(p22,NULL,0);
                                    waitpid(p23,NULL,0);
                                    exit(0);
                                }
                            }
                            else{ //22
                                printf("22: %d\n", getpid());
                                pid_t p26 = fork();
                                if(p26){ //22
                                    pid_t p27 = fork();
                                    if(!p27){ //27
                                        printf("27: %d\n", getpid());
                                        while(1);
                                        exit(0);
                                    }else{//22
                                        waitpid(p26, NULL,0);
                                        waitpid(p27, NULL,0);
                                        exit(0);
                                    }
                                }else{ //26
                                    printf("26: %d\n", getpid());
                                    while(1);
                                    exit(0);
                                }
                            }
                        }else{ //9
                            waitpid(p16, NULL,0);
                            waitpid(p17, NULL,0);
                            exit(0);
                        }
                    }
                }else{ //4
                    // pid_t p8 = fork();
                    // if(!p8){//8
                    //     printf("8: %d\n", getpid());
                        pid_t p15 = fork();
                        if(!p15){ //15
                            printf("15: %d\n", getpid());
                            while(1);
                            exit(0);
                        }else{ //8
                            // pid_t p14 = fork();
                            // if(!p14){ //14
                            //     printf("14: %d\n", getpid());
                                // while(1);
                                // exit(0);
                            //}else{ //8
                                waitpid(p15, NULL,0);
                                //waitpid(p14, NULL,0);
                                exit(0);
                            }
                        }
                    }else{ //4
                        //waitpid(p8, NULL,0);
                        waitpid(p9, NULL,0);
                        exit(0);
                    }
                }
            }else{ //2
                //waitpid(p4, NULL,0);
                waitpid(p5, NULL,0);
                exit(0);
            }
        }
    //}
    while(1);
}