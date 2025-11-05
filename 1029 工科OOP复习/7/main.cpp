#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
// WARNING: NO more headers allowed!

using std::pair;
using std::string;
using std::vector;
using std::map;
using std::function;
namespace final {
    class arguments {
    private:
        // WARNING: You cannot add more member variables.
        int _argc;
        char** _argv;
    public:
        arguments() : _argc(0), _argv(nullptr) {}
        explicit arguments(const string& cmd) {
            // todo implement constructor
            string s = "";
            vector<string> v;
            for (char c : cmd) {
                if (c == ' ') {
                    if (s != "") {
                        v.emplace_back(s);
                        s = "";
                    }
                } else s += c;
            }
            if (s != "") v.emplace_back(s);
            _argc = static_cast<int>(v.size());
            _argv = new char*[_argc];
            for (int i = 0; i < _argc; i++) {
                _argv[i] = new char[v.at(i).size() + 1];
                for (int j = 0; j < v.at(i).size(); j++) _argv[i][j] = v.at(i).at(j);
                _argv[i][v.at(i).size()] = '\0';
            }
        }
        ~arguments() {
            // todo implement destructor
            for (int i = 0; i < _argc; i++) {
                delete[] _argv[i];
            }
            delete[] _argv;
        }
        // WARNING: You cannot modify the following functions
        int argc() const { return _argc; }
        char** argv() const { return _argv; }
    };

    // You don't need to modify shell.
    class shell {
    private:
        map<int, arguments> running_list;
    public:
        shell() = default;

        void run(int pid, const string& cmd, const function<void(int, char**)>& invoked) {
            running_list.emplace(pid, cmd);
            invoked(running_list[pid].argc(), running_list[pid].argv());
        }

        int subprocessExit(int pid, int return_value) {
            running_list.erase(pid);
            return return_value;
        }
        vector<int> getRunningList() const {
            vector<int> rt;
            for (auto& pair:running_list)rt.push_back(pair.first);
            return rt;
        }
    };
}