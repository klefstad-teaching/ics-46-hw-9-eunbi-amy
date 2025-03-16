#include "ladder.h"
#include <algorithm>
#include <cctype>
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cout << "Error: Cannot find a ladder from " << word1 << " to " << word2  << ". " << msg << endl;
}

string to_lower(const string& s) {
    string lower(s);
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    string s1 = to_lower(str1);
    string s2 = to_lower(str2);

    int len1 = s1.length();
    int len2 = s2.length();
    
    if (abs(len1 - len2) > d) return false;

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                }
            }
        }
    }
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string begin_lower = to_lower(begin_word);
    string end_lower = to_lower(end_word);

    if (begin_lower == end_lower) {
        error(begin_word, end_word, "Start and end words are the same.");
        return {};
    }

    if (word_list.find(end_lower) == word_list.end()) {
        error(begin_word, end_word, "End word is not in the dictionary.");
        return {};
    }

    queue<vector<string>> q;
    q.push({begin_lower});
    unordered_set<string> visited;
    visited.insert(begin_lower);

    while (!q.empty()) {
        int level_size = q.size();
        unordered_set<string> level_visited;

        for (int i = 0; i < level_size; ++i) {
            vector<string> ladder = q.front();
            q.pop();
            string last_word = ladder.back();

            for (int pos = last_word.size() - 1; pos >= 0; --pos) {
                string new_word = last_word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (new_word[pos] == c) continue;
                    new_word[pos] = c;
                    if (new_word == end_lower) {
                        ladder.push_back(new_word);
                        return ladder;
                    }
                    if (word_list.count(new_word) && !visited.count(new_word) && !level_visited.count(new_word)) {
                        level_visited.insert(new_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(new_word);
                        q.push(new_ladder);
                    }
                }
            }

            for (int pos = 0; pos <= last_word.size(); ++pos) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    string new_word = last_word.substr(0, pos) + c + last_word.substr(pos);
                    if (new_word == end_lower) {
                        ladder.push_back(new_word);
                        return ladder;
                    }
                    if (word_list.count(new_word) && !visited.count(new_word) && !level_visited.count(new_word)) {
                        level_visited.insert(new_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(new_word);
                        q.push(new_ladder);
                    }
                }
            }

            for (int pos = 0; pos < last_word.size(); ++pos) {
                string new_word = last_word.substr(0, pos) + last_word.substr(pos + 1);
                if (new_word.empty()) continue;
                if (new_word == end_lower) {
                    ladder.push_back(new_word);
                    return ladder;
                }
                if (word_list.count(new_word) && !visited.count(new_word) && !level_visited.count(new_word)) {
                    level_visited.insert(new_word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(new_word);
                    q.push(new_ladder);
                }
            }
        }

        visited.insert(level_visited.begin(), level_visited.end());
    }

    error(begin_word, end_word, "No ladder found.");
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream inputFile;
    inputFile.open(file_name);
    if (!inputFile.is_open()) {
        cout << "Error: Failed to open the file." << endl;
        return;
    }
    string word;
    while (getline(inputFile, word)) {
        word = to_lower(word);
        word_list.insert(word);
    }
    inputFile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (auto& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
