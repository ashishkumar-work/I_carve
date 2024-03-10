#include "def.h"

int carve_file(unsigned char *src_data, size_t src_size, char *dst_file_path, int *count, char *file_type)
{
    unsigned char *header;
    unsigned char *footer;
    size_t header_size, footer_size;

    // Select header and footer based on file type
    if (strcmp(file_type, "png") == 0) {
        header = PNG_HEADER;
        footer = PNG_FOOTER;
        header_size = sizeof(PNG_HEADER);
        footer_size = sizeof(PNG_FOOTER);
    } else if (strcmp(file_type, "jpg") == 0 || strcmp(file_type, "jpeg") == 0) {
        header = JPEG_HEADER;
        footer = JPEG_FOOTER;
        header_size = sizeof(JPEG_HEADER);
        footer_size = sizeof(JPEG_FOOTER);
    } else {
        fprintf(stderr, "Unsupported file type\n");
        return 1;
    }

    int position = 0;
    while (1) {
        int header_index = -1;
        for (int i = position; i < src_size - header_size + 1; i++) {
            if (memcmp(src_data + i, header, header_size) == 0) {
                header_index = i;
                break;
            }
        }
        if (header_index == -1) {
            break;
        }

        int footer_index = -1;
        for (int i = header_index + header_size; i < src_size - footer_size + 1; i++) {
            if (memcmp(src_data + i, footer, footer_size) == 0) {
                footer_index = i;
                break;
            }
        }
        if (footer_index == -1) {
            break;
        }

        unsigned char *footer_end = src_data + footer_index + footer_size;

        if (header_index < footer_index) {
            (*count)++;
            char dst_file_name[256];
            sprintf(dst_file_name, "%s_%d.%s", dst_file_path, *count, file_type);

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
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <destination_directory> <file_type>\n", argv[0]);
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
    int result = carve_file(src_data, src_size, argv[2], &count, argv[3]);
    free(src_data);

    printf("Total carved files: %d\n", count);

    return result;
}
