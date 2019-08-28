/**
 * 修改 frequencyCounter ，打印出现频率最高的所有单词，而非其中之一。提示：请用 queue。
 */

#include <vector>
#include <string>
using std::vector;
using std::string;

void search() {
    string max = "";
    vector<string> queue;

    // st 是符号表，懒得实现了
    st.put(max, 0);
    vector<string> keys = st.keys();

    for (int i = 0; i < keys.size(); i++)
    {
        string key = keys[i];

        if (st.get(key) > st.get(max))
        
        {
            max = key;
            vt.clear();
            vt.push_back(key);
        } else if (st.get(key) == st.get(max))
        {
            vt.push_back(key);
        }
        
    }
    
}
