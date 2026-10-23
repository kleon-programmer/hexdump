#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void printdata(unsigned char data[8], int offset, int bytes_in_data);
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("USAGE: ./hexdump <filename>\n");
        return 1;
    }
    char *filename = argv[1];

    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    unsigned char buffer;
    unsigned char data[8];
    int bytes_in_data = 0;
    int offset = 0;
    
    printf("\n");
    while (fread(&buffer, 1, 1, file) == 1)
    {

        // if array is full
        if (bytes_in_data == 8)
        {
            printdata(data, offset, bytes_in_data);

            bytes_in_data = 1;
            data[bytes_in_data - 1] = buffer;
        }
        // if array is not full
        else
        {
            data[bytes_in_data] = buffer;
            bytes_in_data++;
        }
        offset++;
    }

    // if array has any remaining data
    if (bytes_in_data > 0)
    {
        printdata(data, offset, bytes_in_data);
    }

    fclose(file);
}

// a function to print the current line with data
void printdata(unsigned char data[8], int offset, int bytes_in_data)
{
    int offset_start = offset - bytes_in_data;
    printf("  \033[38;5;141m%08x\033[0m  ", offset_start);

    for (int i = 0; i < bytes_in_data; i++)
    {
        printf("%02x ", data[i]);
    }

    printf("\033[38;5;245m   ");
    int padding = (8 - bytes_in_data) * 3;
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }

    for (int j = 0; j < bytes_in_data; j++)
    {
        // if it's a space
        if (data[j] == ' ')
        {
            printf(".");
        }
        else if (isprint(data[j]))
        {
            printf("%c", data[j]);
        }
        else
        {
            printf(".");
        }
    }
    printf("\033[0m\n");
}
