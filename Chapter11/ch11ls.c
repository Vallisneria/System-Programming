/*
    2019년 5월 23일
    시스템프로그래밍 실습과제

    (11장 70p)
    - list2.c를 수정하여 사용자 옵션에 따라 필요한 정보만을 출력하는 프로그램 ch11ls.c를 작성한다.
    - 적어도 -s, -F, -n 옵션은 처리되도록 한다.

    - 가능하면 ls -s, ls -F, ls -n과 같은 출력을 내도록 한다.
    - 출력되는 파일들의 순서는 상관없고, 날짜표시형식도 상과없다.

    -s 파일의 크기를 Kbyte 단위로 나타낸다. st_blocks는 512byte단위이므로 st_blocks/2 가 Kb 단위의 파일의 크기이다. 
    $ls –s를 치면 Kbyte단위로 디스크 자치 블록수가 나온다. 4Kbyte단위로 디스크를 차지함을 알 수 있다. 
    (매우 작은 크기의 디렉토리나 심볼릭링크는 디스크를 따로 차지하지 않는다).
    
    -F  파일형식을 알리는 문자를 각 파일 뒤에 추가한다. 
    실행파일 “*”, 디렉터리 “/”, 심볼릭링크 “@”, FIFO “|”, 소켓 ”=“

    -n 이름의 나열에서 UID, GID 번호를 사용한다. 
*/

#include "ch11ls.h"

int main(int argc, char *const argv[]) {
    DIR *dp;
    char *dir = ".";
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    int i;
    int opt;

    // getopt(): main 함수 파라미터를 파싱하는 함수.
    //           기본 라이브러리에 포함되어 있다.
    while ((opt = getopt(argc, argv, "snF")) != -1) {
        switch (opt) {
            case 's':
                s_option = 1;
                break;
            case 'n':
                n_option = 1;
                break;
            case 'F':
                F_option = 1;
                break;
        }
    }

    if (argv[argc - 1][0] != '-') {
        dir = argv[argc - 1];
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        }
        printStat(path, d->d_name, &st);
    }

    return 0;
}