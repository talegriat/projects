#include <ostream>
#include <string>       // std::string
#include <sstream>      // std::stringbuf
using namespace std;
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_YELLOW   = 33,
        FG_MAGENTA  = 35,
        FG_CYAN     = 36,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_YELLOW   = 43,
        BG_MAGENTA  = 45,
        BG_CYAN     = 46,
        BG_BLUE     = 44,
        BG_BLACK    = 40,
        BG_WHITE    = 47,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
        int x;
    public:
        Modifier(Code pCode) { x= pCode; }
        string str(){
            string s;
            return "\033["+ to_string(x) +"m";
        }
    };
}