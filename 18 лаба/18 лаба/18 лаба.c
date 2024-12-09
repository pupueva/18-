#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <stdio.h>
#include <math.h> // ��� ������� sqrt()
#include <time.h>
#include <string.h>

// ��������� ��� �����
typedef struct point {
    float x;
    float y;
    char name;
} Point;

// ��������� ��� ���������� � ������
typedef struct {
    int train_number;
    char direction[50];
    char arrival_time[6];
    char departure_time[6];
    int distance;
    int travel_time; // ����� � �������
} Train;

// ������� ����������� �����
void put_point(Point z) {
    printf("Point %c (%.1f, %.1f)\n", z.name, z.x, z.y);
}

// ������� ���������� ���������� ����� ����� �������
float dist(Point z, Point w) {
    return sqrt(pow(w.x - z.x, 2) + pow(w.y - z.y, 2));
}

// ������� ��������� �������� ������� ����� ����� �������
Point get_midpoint(Point z, Point w) {
    Point mid = { (z.x + w.x) / 2, (z.y + w.y) / 2, 'M' };
    return mid;
}

// ����������� ������������ ��������, � ������� ����������� �����
int get_quadrant(Point z) {
    if (z.x > 0 && z.y > 0) return 1;
    else if (z.x < 0 && z.y > 0) return 2;
    else if (z.x < 0 && z.y < 0) return 3;
    else if (z.x > 0 && z.y < 0) return 4;
    else return 0; // ���� ����� ��������� �� ����� �� ����
}

// ������� ��� ������ ���������� � ������
void put_train(Train train) {
    printf("Train �%d, Direction: %s\n", train.train_number, train.direction);
    printf("Arrival: %s, Departure: %s, Distance: %d km\n", train.arrival_time, train.departure_time, train.distance);
    printf("Travel time: %d hours %d minutes\n", train.travel_time / 60, train.travel_time % 60);
    printf("--------------------------------------\n");
}

// ������� ��� ������ �������, ����������� � ���� ����� �����
void find_trains_more_than_day(Train trains[], int n) {
    printf("\nTrains in travel for more than a day:\n");
    for (int i = 0; i < n; i++) {
        if (trains[i].travel_time > 24 * 60) {
            put_train(trains[i]);
        }
    }
}

// ������� ��� ������ �������� ������� � ���� �� �����������
void print_current_time() {
    struct tm* mytime;
    time_t t;

    // ��������� �������� ���������� �������
    t = time(NULL);
    mytime = localtime(&t);

    // ������ �������� �������
    char time_str[80];
    sprintf(time_str, "Current time: %02d:%02d:%02d", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
    printf("%*s\n", 40 + (int)strlen(time_str) / 2, time_str); // ��������� ������

    // ���������� ���� � ����� �� �����������
    int days_to_sunday = (7 - mytime->tm_wday) % 7;
    int hours_to_sunday = 24 - mytime->tm_hour;
    printf("To Sunday: %d days and %d hours\n", days_to_sunday, hours_to_sunday);
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    // ������� 1: ������ � �������
    Point a = { 1.f, 2.f, 'A' };
    Point b = { 5.f, -3.f, 'B' };

    // ����������� �����
    put_point(a);
    put_point(b);

    // ���������� ����� ����� �������
    float distance = dist(a, b);
    printf("Distance between points %c and %c: %.2f\n", a.name, b.name, distance);

    // �������� ������� ����� �������
    Point mid = get_midpoint(a, b);
    put_point(mid);

    // ����������� ������������ �������� ��� ������ �����
    printf("Point %c is in quadrant %d\n", a.name, get_quadrant(a));
    printf("Point %c is in quadrant %d\n", b.name, get_quadrant(b));

    // ������� 2: ������ � ��������
    print_current_time();

    // ������� 3: ������ � ��������
    Train trains[5] = {
        {101, "Moscow - Saint Petersburg", "10:30", "15:45", 700, 300}, // 5 hours
        {102, "Moscow - Vladivostok", "08:00", "12:00", 9288, 1440}, // 24 hours
        {103, "Moscow - Kazan", "06:00", "11:30", 816, 330}, // 5.5 hours
        {104, "Moscow - Novosibirsk", "15:00", "22:00", 2812, 2400}, // 40 hours
        {105, "Moscow - Sochi", "12:00", "18:30", 1600, 390} // 6.5 hours
    };

    for (int i = 0; i < 5; i++) {
        put_train(trains[i]);
    }

    find_trains_more_than_day(trains, 5);

    return 0;
}
