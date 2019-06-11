/*
    npAnswer.c와 npQuestion.c를 작성한다.

    npQuestion에서 숫자를 보내면 3을 더해서 돌려준다.
    예를 들어 npQuestion에서 3을 보내면 6을 받는다.
    파이프로 보내거나 받을 때마다 "... is send" "... is received"를 출력한다.
*/

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fp_r, fp_w, i;

    if (unlink("myPipeAsk") == -1) {
        perror("Failed to remove fifo");
    }

    if (unlink("myPipeRpl") == -1) {
        perror("Failed to remove fifo");
    }

    if (mkfifo("myPipeAsk", 0660) == -1) {
        perror("mkfifo error");
    }

    if (mkfifo("myPipeRpl", 0660) == -1) {
        perror("mkfifo error");
    }

    if ((fp_r = open("myPipeAsk", O_RDONLY)) == -1)
        perror("open error");

    if ((fp_w = open("myPipeRpl", O_WRONLY)) == -1)
        perror("open error");

    while (read(fp_r, &i, sizeof(int)) > 0) {
        fprintf(stdout, " %d is received.\n", i);
        i = i + 3;
        write(fp_w, &i, sizeof(int));
        fprintf(stdout, " %d is sended.\n", i);
    }

    if (unlink("myPipeAsk") == -1)
        perror("Failed to remove fifo");

    if (unlink("myPipeRpl") == -1)
        perror("Failed to remove fifo");
}