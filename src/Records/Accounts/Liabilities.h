#include <string>
#include <Accounts.h>
using std::string;

class Liabilities : public Accounts {

    public:
        Liabilities(int accNum, string accName, string accDesc, string accType);

};