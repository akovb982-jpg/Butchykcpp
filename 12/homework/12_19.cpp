#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

struct Point3 {
    long long x, y, z;
};
bool expect(std::istream &in, char sep){
    char c;
    if (!(in >> c)) return false;
    if (c != sep){
        in.putback(c);
        return false;
    }
    return true;
}

int main(){
    std::string name;
    std::cout << "File with points: ";
    std::cin >> name;
    std::ifstream fin(name);
    if (!fin){
        std::cout << "Cannot open " << name << '\n';
        return 1;
    }

    int cap = 16, n = 0;
    Point3 *p = new Point3[cap];
    while (true){
        Point3 t;
        if (!(fin >> t.x)){
            if (fin.eof()) break;
            std::cout << "Wrong file format near point " << n + 1 << '\n';
            delete[] p;
            return 1;
        }
        if (!expect(fin, ',') || !(fin >> t.y) || !expect(fin, ',') || !(fin >> t.z)){
            std::cout << "Wrong file format near point " << n + 1 << '\n';
            delete[] p;
            return 1;
        }
        if (n == cap){
            Point3 *b = new Point3[cap * 2];
            for (int i = 0; i < n; i++) b[i] = p[i];
            delete[] p;
            p = b;
            cap *= 2;
        }
        p[n++] = t;
        if (!expect(fin, ';')){ 
            fin.clear();
            std::string rest;
            if (fin >> rest){
                std::cout << "Wrong file format after point " << n << '\n';
                delete[] p;
                return 1;
            }
            break;
        }
    }

    if (n < 2){
        std::cout << "At least two points are needed\n";
        delete[] p;
        return 0;
    }
    int bi = 0, bj = 1;
    long long best = -1;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++){
            long long dx = p[i].x - p[j].x, dy = p[i].y - p[j].y, dz = p[i].z - p[j].z;
            long long d2 = dx * dx + dy * dy + dz * dz; 
            if (d2 > best){ best = d2; bi = i; bj = j; }
        }
    std::cout << "Points read: " << n << '\n';
    std::cout << "The longest segment: (" << p[bi].x << ", " << p[bi].y << ", " << p[bi].z
              << ") - (" << p[bj].x << ", " << p[bj].y << ", " << p[bj].z << ")\n";
    std::cout << "Length = " << std::sqrt(static_cast<double>(best)) << '\n';
    delete[] p;
    return 0;
}
