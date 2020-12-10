#include <stdio.h>

int storeLove(char** str){
        *str = "Programming in C is Fun";
}

int main(int argc, char const *argv[]) {
        char* str="Hello";
        storeLove(&str);
        printf("%s\n", str);
        return 0;
}
