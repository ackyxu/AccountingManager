#include <string>
#include <Accounts.h>
using std::string;

class Assets : public Accounts {

    public:
        Assets(int accNum, string accName, string accDesc, string accType);

};