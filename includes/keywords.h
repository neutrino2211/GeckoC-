#ifndef G_KEYWORDS_H
#define G_KEYWORDS_H

#include "./keyword.h"

class GeckoConst : public Keyword {

    public:
    GeckoConst();

    Keyword* New() override;
};

class GeckoPrivateModifier : public Keyword {
    public:
    GeckoPrivateModifier();

    Keyword* New() override;
};

class GeckoPublicModifier : public Keyword {
    public:
    GeckoPublicModifier();

    Keyword* New() override;
};

class GeckoProtectedModifier : public Keyword {
    public:
    GeckoProtectedModifier();

    Keyword* New() override;
};


#endif