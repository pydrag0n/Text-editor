#include <stdio.h>

#include <stdlib.h>
#include <string.h>

void readFileToBuffer(const char *filename, char **buffer) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("file open error");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file); 
    fseek(file, 0, SEEK_SET);


    *buffer = (char *)malloc(fileSize + 1);
    if (*buffer == NULL) {
        perror("MEM ERROR");
        fclose(file);
        return;
    }

    fread(*buffer, 1, fileSize, file);
    (*buffer)[fileSize] = '\0'; 

    fclose(file);
}

short readFile(const char *_Filename, char *_Buffer) {
    /* 
    читает файл, выводит с помощью printf,возможны модификации в дальнейшем /
    выводит примерный вес файла
    ошибка = -1
    все прошло успешно = 0
    */

    FILE *file = fopen(_Filename, "r");
    const int buff_size = 20;
    if(file) {
        int fs = 1; // с учетом  /0
        while((fgets(_Buffer, buff_size, file))!=NULL) { // читает по buff_size байтов
            printf("%s", _Buffer);
            size_t length = strlen(_Buffer);
            fs+=length;
        }
        fclose(file);
        printf("\n\n==================\n");
        printf("file size ~ %i", fs); // надо сделать более точную версию этой херни

        // printf("read: %i, fs: %i", buff_size, fs); //debug приколы
        printf("\n==================\n");
        return 0;
    }
    return -1;
}

int main() {
// -----------------------------TEST-----------------------------------
// УДАЛИТЬ КОГДА-НИБУДЬ

    char *message = "Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of de Finibus Bonorum et Malorum (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, Lorem ipsum dolor sit amet.., comes from a line in section 1.10.32.The standard chunk of Lorem Ipsum used since the 1500s is reproduced below for those interested. Sections 1.10.32 and 1.10.33 from de Finibus Bonorum et Malorum by Cicero are also reproduced in their exact original form, accompanied by English versions from the 1914 translation by H. Rackham.";

    // файл для записи
    char *filename = "test.txt";
    // запись в файл
    FILE *fp = fopen(filename, "w");
    if(fp)
    {
        // записываем строку
        fputs(message, fp);
        fclose(fp);
        printf("\nFile has been written\n\n");
    }

    char buffer[256];
    readFile(filename, buffer);

    char *buffer1 = NULL;

    // Читаем текст из файла в buffer
    readFileToBuffer(filename, &buffer1);

    // Проверяем, успешно ли считали данные
    if (buffer1) {
        printf("IN buffer:\n%s\n", buffer1);
        free(buffer1); // Освобождаем память после использования
    }

// -----------------------------TEST-----------------------------------
    return 0;
}