#include "def.h"

int carve_png(unsigned char *src_data, size_t src_size, char *dst_file_path, int *count)
{
    int position = 0;
    while (1) {

        int header_index = -1;
        for (int i = position; i < src_size - sizeof(PNG_HEADER) + 1; i++) {
            if (memcmp(src_data + i, PNG_HEADER, sizeof(PNG_HEADER)) == 0) {
                header_index = i;
                break;
            }
        }
        if (header_index == -1) {
            break;
        }

        int footer_index = -1;
        for (int i = header_index + sizeof(PNG_HEADER); i < src_size - sizeof(PNG_FOOTER) + 1; i++) {
            if (memcmp(src_data + i, PNG_FOOTER, sizeof(PNG_FOOTER)) == 0) {
                footer_index = i;
                break;
            }
        }
        if (footer_index == -1) {
            break;
        }

        unsigned char *footer_end = src_data + footer_index + sizeof(PNG_FOOTER);

        if (header_index < footer_index) {
            (*count)++;
            char dst_file_name[256];
            sprintf(dst_file_name, "%s_%d.png", dst_file_path, *count);

            FILE *dst_file = fopen(dst_file_name, "wb");
            if (dst_file == NULL) {
                perror("Error opening destination file");
                return 1;
            }

            fwrite(src_data + header_index, 1, footer_end - src_data - header_index, dst_file);
            fclose(dst_file);

            printf("Carved: %s\n", dst_file_name);
        }
        position = footer_end - src_data;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_directory>\n", argv[0]);
        return 1;
    }

    FILE *src_file = fopen(argv[1], "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return 1;
    }

    fseek(src_file, 0, SEEK_END);
    size_t src_size = ftell(src_file);
    rewind(src_file);

    unsigned char *src_data = malloc(src_size);
    if (src_data == NULL) {
        perror("Error allocating memory for source data");
        fclose(src_file);
        return 1;
    }
    fread(src_data, 1, src_size, src_file);
    fclose(src_file);

    int count = 0;
    int result = carve_png(src_data, src_size, argv[2], &count);
    free(src_data);

    printf("Total carved files: %d\n", count);

    return result;
}
