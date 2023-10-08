#include <../Accounts/Accounts.h>


class JournalEntry{
    private:
        Accounts account;
        float amount;

    public:
        JournalEntry(Accounts account, float amount);
        void updateAmount(float amount);
    
};