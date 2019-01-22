#if !defined(CALDERA_LAYER_H_INCLUDED)
#define CALDERA_LAYER_H_INCLUDED 1

struct CaLayer
{
    void (*onAttach)(struct CaLayer *);
    void (*onDetatch)(struct CaLayer *);
    void (*onUpdate)(struct CaLayer *);
    void (*onEvent)(struct CaLayer *, struct CaEvent *);
    char const * debugName;
};


#endif
