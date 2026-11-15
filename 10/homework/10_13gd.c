#include <stdio.h>
#include <time.h>
#define MAXN 100

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char surname[40];
    char name[40];
    char sex;
    Date birth;
} Employee;

int date_cmp(Date a, Date b){
    if (a.year != b.year) return a.year < b.year ? -1 : 1;
    if (a.month != b.month) return a.month < b.month ? -1 : 1;
    if (a.day != b.day) return a.day < b.day ? -1 : 1;
    return 0;
}

int age_on(Date birth, Date today){
    int age = today.year - birth.year;
    if (today.month < birth.month || (today.month == birth.month && today.day < birth.day))
        age--;
    return age;
}

Date get_today(void){
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    Date d;
    d.day = lt->tm_mday;
    d.month = lt->tm_mon + 1;
    d.year = lt->tm_year + 1900;
    return d;
}

int input_employees(Employee p[], int n){
    int i;
    for (i = 0; i < n; i++){
        printf("Employee %d (surname name sex(M/F) dd.mm.yyyy): ", i + 1);
        if (scanf("%39s %39s %c %d.%d.%d", p[i].surname, p[i].name, &p[i].sex,
                  &p[i].birth.day, &p[i].birth.month, &p[i].birth.year) != 6)
            return 0;
        if (p[i].sex == 'm') p[i].sex = 'M';
        if (p[i].sex == 'f') p[i].sex = 'F';
    }
    return 1;
}

int oldest_man(const Employee p[], int n){
    int i, best = -1;
    for (i = 0; i < n; i++)
        if (p[i].sex == 'M' && (best < 0 || date_cmp(p[i].birth, p[best].birth) < 0))
            best = i;
    return best;
}
int younger_than_average(const Employee p[], int n, Date today){
    double avg = 0;
    int i, count = 0;
    for (i = 0; i < n; i++) avg += age_on(p[i].birth, today);
    avg /= n;
    printf("d) Average age: %.2f. Employees younger than average:\n", avg);
    for (i = 0; i < n; i++){
        int a = age_on(p[i].birth, today);
        if (a < avg){
            printf("  %s %s, age %d\n", p[i].surname, p[i].name, a);
            count++;
        }
    }
    return count;
}

int main(){
    Employee p[MAXN];
    int n, k;
    Date today = get_today();

    printf("N = ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN){
        printf("Wrong N\n");
        return 0;
    }
    if (!input_employees(p, n)){
        printf("Input error\n");
        return 0;
    }
    printf("Today: %02d.%02d.%04d\n", today.day, today.month, today.year);

    k = oldest_man(p, n);
    if (k < 0) printf("g) There are no men\n");
    else printf("g) The oldest man: %s %s, born %02d.%02d.%04d (age %d)\n",
                p[k].surname, p[k].name, p[k].birth.day, p[k].birth.month,
                p[k].birth.year, age_on(p[k].birth, today));

    if (younger_than_average(p, n, today) == 0) printf("  nobody\n");
    return 0;
}
