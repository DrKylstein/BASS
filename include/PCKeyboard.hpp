#ifndef PCKEYBOARD_HPP
#define PCKEYBOARD_HPP





struct KeySym {
    typedef enum {
        none,
        escape,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        zero,
        minus,
        equals,
        backspace,
        tab,
        q,
        w,
        e,
        r,
        t,
        y,
        u,
        i,
        o,
        p,
        left_bracket,
        right_bracket,
        enter,
        left_control,
        a,
        s,
        d,
        f,
        g,
        h,
        j,
        k,
        l,
        semicolon,
        quote,
        accent,
        left_shift,
        unknown,
        z,
        x,
        c,
        v,
        b,
        n,
        m,
        comma,
        period,
        slash,
        right_shift,
        kp_star,
        left_alt,
        space,
        caps_lock,
        f1,
        f2,
        f3,
        f4,
        f5,
        f6,
        f7,
        f8,
        f9,
        f10,
        num_lock,
        scroll_lock,
        kp_home,
        kp_up,
        kp_page_up,
        kp_minus,
        kp_left,
        kp_five,
        kp_right,
        kp_plus,
        kp_end,
        kp_down,
        kp_page_down,
        kp_insert,
        kp_delete,
        f11,
        f12,
        
        kp_enter,
        right_control,
        kp_slash,
        right_alt,
        home,
        up,
        page_up,
        left,
        right,
        end,
        down,
        page_down,
        insert,
        delete_
    } type;
};


typedef void (__interrupt __far *interrupt_ptr)();

class PCKeyboard {
    public:
        bool isHeld(KeySym::type);
        bool wasPressed(KeySym::type);
        bool anyKey();
        PCKeyboard();
        ~PCKeyboard();
    private:
        static const int NUM_STATES = 101;
    
        static volatile bool _state[NUM_STATES];
        static volatile bool _pressed[NUM_STATES];
        static volatile bool _anyKey;
        static volatile bool _codeEscaped;
        static interrupt_ptr prev_int_9;
    
        static void __interrupt __far keyboard_int();
};
#endif