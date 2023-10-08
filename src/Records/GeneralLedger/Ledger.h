#include <../Database/Database.h>  
#include <JournalEntry.h>

class Ledger{
    private:
        Database database;
    public:
        Ledger();
        void CreateJournalEntry(JournalEntry entry);



};