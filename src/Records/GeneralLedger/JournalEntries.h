#include <../Accounts/Accounts.h>
#include <JournalEntry.h>
#include <vector>

using std::vector;

class JournalEntries {

    private:
        float runningAmount = 0;
        vector<JournalEntry> entries;
        

    public:
        int addLineItem(JournalEntry entries);
        vector<JournalEntry> getAllEntries();
    
};