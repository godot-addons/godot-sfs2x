/* sfs2x.h */
#ifndef SFS2X_H
#define SFS2X_H

#include "reference.h"

class SmartFoxServer : public Reference {
    GDCLASS(SmartFoxServer, Reference);

    int count;

protected:
    static void _bind_methods();

public:
    void add(int value);
    void reset();
    int get_total() const;

    SmartFoxServer();
};

#endif
