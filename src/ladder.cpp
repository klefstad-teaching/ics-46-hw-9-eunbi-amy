#include "ladder.h"
#include <algorithm>
#include <cctype>

void error(string word1, string word2, string msg) {
    cout << "Error: Cannot find a ladder from " << word1 << " to " << word2  << ". " << msg << endl;
}

char toLowerCase(unsigned char c) {
    return tolower(c);
}

bool edit_distance_within(const string& str1, string& str2, int d) {
    // true if str1 can be transformed to str2 in d edits
    string s1 = str1, s2 = str2;
    transform(s1.begin(), s1.end(), s1.begin(), toLowerCase);
    transform(s2.begin(), s2.end(), s2.begin(), toLowerCase);

    int len1 = s1.length();
    int len2 = s2.length();
    
    if (abs(len1 - len2) > d) return false;

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i=0; i<=len1; ++i) {
        for (int j=0; j<=len2; ++j) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j],
                            dp[i][j-1],
                            dp[i-1][j-1]});
        }
    }
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> q;
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!q.empty()) {
        vector<string> ladder = q.front();
        q.pop();
        string last_word = ladder.back();
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!visited.count(word)) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    q.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "No ladder found.");
    return {};
}
