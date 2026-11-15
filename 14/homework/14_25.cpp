#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int text_length(const std::string &s){
    int n = 0;
    for (size_t i = 0; i < s.size(); i++)
        if ((static_cast<unsigned char>(s[i]) & 0xC0) != 0x80) n++;
    return n;
}
std::vector<int> best_breaks(const std::vector<std::string> &words, int W){
    int n = static_cast<int>(words.size());
    std::vector<int> len(n);
    for (int i = 0; i < n; i++) len[i] = text_length(words[i]);

    const long long INF = -1;
    std::vector<long long> cost(n + 1, INF);
    std::vector<int> next(n + 1, n);
    cost[n] = 0;
    for (int i = n - 1; i >= 0; i--){
        int line_len = -1;
        for (int j = i; j < n; j++){
            line_len += len[j] + 1;
            if (line_len > W && j > i) break;
            long long slack = (j == n - 1 || line_len > W) ? 0 : W - line_len;
            long long c = slack * slack + cost[j + 1];
            if (cost[i] == INF || c < cost[i]){
                cost[i] = c;
                next[i] = j + 1;
            }
        }
    }
    std::vector<int> breaks;
    for (int i = 0; i < n; i = next[i]) breaks.push_back(i);
    breaks.push_back(n);
    return breaks;
}

void write_paragraph(std::ostream &out, const std::vector<std::string> &words, int W){
    std::vector<int> br = best_breaks(words, W);
    for (size_t k = 0; k + 1 < br.size(); k++){
        int from = br[k], to = br[k + 1];
        int gaps = to - from - 1;
        bool last = (k + 2 == br.size());
        if (last || gaps == 0){
            for (int i = from; i < to; i++){
                if (i > from) out << ' ';
                out << words[i];
            }
        } else {
            int letters = 0;
            for (int i = from; i < to; i++) letters += text_length(words[i]);
            int spaces = W - letters;
            int base = spaces / gaps, extra = spaces % gaps;
            for (int i = from; i < to; i++){
                out << words[i];
                if (i < to - 1)
                    out << std::string(base + (i - from < extra ? 1 : 0), ' ');
            }
        }
        out << '\n';
    }
}

int main(){
    std::string in_name, out_name;
    int W;
    std::cout << "Input file: ";
    std::cin >> in_name;
    std::cout << "Output file: ";
    std::cin >> out_name;
    std::cout << "Line width W: ";
    if (!(std::cin >> W) || W < 10){
        std::cout << "Width must be at least 10\n";
        return 1;
    }

    std::ifstream fin(in_name);
    if (!fin){
        std::cout << "Cannot open " << in_name << '\n';
        return 1;
    }
    std::ofstream fout(out_name);
    if (!fout){
        std::cout << "Cannot create " << out_name << '\n';
        return 1;
    }

    std::string line, w;
    std::vector<std::string> words;
    int paragraphs = 0;
    while (true){
        bool ok = static_cast<bool>(std::getline(fin, line));
        bool blank = line.find_first_not_of(" \t\r") == std::string::npos;
        if (!ok || blank){
            if (!words.empty()){
                if (paragraphs > 0) fout << '\n';
                write_paragraph(fout, words, W);
                words.clear();
                paragraphs++;
            }
            if (!ok) break;
            continue;
        }
        std::istringstream in(line);
        while (in >> w) words.push_back(w);
    }
    std::cout << "Done: " << paragraphs << " paragraph(s) written to " << out_name << '\n';
    return 0;
}
