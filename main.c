#include <stdio.h>
#include <string.h>

short createFile(const char *_Filename) {
     /* 
    создает файл, возможны модификации в дальнейшем 
    ошибка = -1
    все прошло успешно = 0
    */

    FILE *file = fopen(_Filename, "w");
    if (file) {
        fclose(file);
        return 0;
    }
    return -1;
}


short readFile(const char *_Filename, char *_Buffer, const int  buff_size) {
    /* 
    читает файл, выводит с помощью printf, возможны модификации в дальнейшем /
    выводит примерный вес файла
    ошибка = -1
    все прошло успешно = 0
    */

    FILE *file = fopen(_Filename, "r");
    if(file)
    {
        int fs = 0;
        while((fgets(_Buffer, buff_size, file))!=NULL) // читает по buff_size байтов
        {
            fs+=1;
        }
        fclose(file);
        printf("\n==================\n");
        printf("file size ~ %i", fs*buff_size); // надо сделать более точную версию этой херни

        // printf("read: %i, fs: %i", buff_size, fs); //debug приколы
        printf("\n==================\n");
        return 0;
    }
    return -1;
}

int main()
{
    short err = createFile("noname.txt");
    if (err<0) {
        printf("Fatal error");
        return -1;
    }
// -----------------------------TEST-----------------------------------
// УДАЛИТЬ СЛЕДУЮЩИМ КОММИТОМ

    char * message = "ap''asmxlmakncbayegygqwponnacnzxcm,naknqpwodk\nAn apple adasasdasdasdasda day keeps the doctor away\nasidiasdjoasdjiajdsioajsdiojasdiojaisodjaisdjaisdjoasidjwiojqiodjiaosjdioajsda asdasd asdaopwkqpo[riu[iqwur0 -32-0-1 -3490-1 3]]\na dasdasd asd asda as";

    // файл для записи
    char * filename = "noname.txt";
    // запись в файл
    FILE *fp = fopen(filename, "w");
    if(fp)
    {
        // записываем строку
        fputs(message, fp);
        fclose(fp);
        printf("\nFile has been written\n");
    }
    char buffer[256];
    readFile("noname.txt", buffer, 256);

// -----------------------------TEST-----------------------------------
    return 0;
}