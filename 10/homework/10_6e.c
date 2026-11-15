#include <stdio.h>
#include <string.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char code[20];
    char author[60];
    char title[100];
} BookInfo;

typedef struct {
    unsigned card_number;
    char surname[40];
} ReaderInfo;

typedef struct {
    BookInfo book;
    ReaderInfo reader;
    Date order_date;
} BookRequest;
void read_line(const char *prompt, char *buf, int size){
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL){
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

int input_request(BookRequest *r){
    char line[100];
    read_line("Book code: ", r->book.code, sizeof r->book.code);
    read_line("Author: ", r->book.author, sizeof r->book.author);
    read_line("Title: ", r->book.title, sizeof r->book.title);
    read_line("Reader card number: ", line, sizeof line);
    if (sscanf(line, "%u", &r->reader.card_number) != 1) return 0;
    read_line("Reader surname: ", r->reader.surname, sizeof r->reader.surname);
    read_line("Order date (dd.mm.yyyy): ", line, sizeof line);
    if (sscanf(line, "%d.%d.%d", &r->order_date.day, &r->order_date.month,
               &r->order_date.year) != 3) return 0;
    return 1;
}

void print_request(const BookRequest *r){
    char date[16];
    sprintf(date, "%02d.%02d.%04d", r->order_date.day % 100, r->order_date.month % 100,
            r->order_date.year % 10000);
    printf("+---------------- BOOK REQUEST ----------------+\n");
    printf("| Code:   %-36s |\n", r->book.code);
    printf("| Author: %-36s |\n", r->book.author);
    printf("| Title:  %-36s |\n", r->book.title);
    printf("| Reader card: %-31u |\n", r->reader.card_number);
    printf("| Surname:     %-31s |\n", r->reader.surname);
    printf("| Order date:  %-31s |\n", date);
    printf("+----------------------------------------------+\n");
}

int main(){
    BookRequest r;
    if (!input_request(&r)){
        printf("Input error\n");
        return 0;
    }
    print_request(&r);
    return 0;
}
