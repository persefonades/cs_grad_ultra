#include <stdio.h>
#include <string.h>

int isVowel(char c){
        switch(c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U': return 1;
                break;
        default:
                return 0;
        }
}

int main(int argc, char const *argv[]) {
        int i=0, count=0;
        char str[500];
        scanf("%[^\n]%*c", str);
        for(i=0; i<strlen(str); i++)
                if(isVowel(str[i]))
                        count++;
        printf("Count of Vowels = %d\n", count);
        return 0;
}
