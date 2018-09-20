/*
    pygame - Python Game Library
    Copyright (C) 2000-2001  Pete Shinners

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Pete Shinners
    pete@shinners.org
*/
#define NO_PYGAME_C_API
#include "pygame.h"

#include "pgcompat.h"

#include "scrap.h"

/* macros used to create each constant */
#if IS_SDLv2
#define STRINGIFY(x) #x
#define ADD_ERROR           \
    {                       \
        DECREF_MOD(module); \
        MODINIT_ERROR;      \
    }
#define DEC_CONSTS(x, y)                             \
    if (PyModule_AddIntConstant(module, #x, (int)y)) \
    ADD_ERROR
#define DEC_CONST(x) DEC_CONSTS(x, SDL_##x)
#define DEC_CONSTKS(x, y) DEC_CONSTS(K_##x, SDL_SCANCODE_##y)
#define DEC_CONSTK(x) DEC_CONSTKS(x, x)
#define DEC_CONSTKSYMS(x, y) DEC_CONSTS(KSYM_##x, SDLK_##y)
#define DEC_CONSTKSYM(x) DEC_CONSTKSYMS(x, x)
#define DEC_CONSTN(x) DEC_CONSTS(x, x)
#define DEC_CONSTSF(x) DEC_CONSTS(x, PGS_##x)

#else /* IS_SDLv1 */
#define ADD_ERROR           \
    {                       \
        DECREF_MOD(module); \
        MODINIT_ERROR;      \
    }
#define DEC_CONST(x)                                       \
    if (PyModule_AddIntConstant(module, #x, (int)SDL_##x)) \
    ADD_ERROR
#define DEC_CONSTK(x)                                     \
    if (PyModule_AddIntConstant(module, #x, (int)SDL##x)) \
    ADD_ERROR
#define DEC_CONSTN(x)                                \
    if (PyModule_AddIntConstant(module, #x, (int)x)) \
    ADD_ERROR
#define DEC_CONSTS(x, y)                             \
    if (PyModule_AddIntConstant(module, #x, (int)y)) \
    ADD_ERROR

#endif /* IS_SDLv1 */

#define ADD_STRING_CONST(x)                        \
    if (PyModule_AddStringConstant(module, #x, x)) \
    ADD_ERROR

static PyMethodDef _constant_methods[] = {{NULL}};

/*DOC*/ static char _constants_doc[] =
    /*DOC*/ "Constants defined by SDL and needed in Pygame.\n";

MODINIT_DEFINE(constants)
{
    PyObject *module;

#if PY3
    static struct PyModuleDef _module = {PyModuleDef_HEAD_INIT,
                                         "constants",
                                         _constants_doc,
                                         -1,
                                         _constant_methods,
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL};
#endif

#if PY3
    module = PyModule_Create(&_module);
#else
    module = Py_InitModule3(MODPREFIX "constants", _constant_methods,
                            _constants_doc);
#endif
    if (module == NULL) {
        MODINIT_ERROR;
    }

    DEC_CONST(LIL_ENDIAN);
    DEC_CONST(BIG_ENDIAN);

#if IS_SDLv1
    DEC_CONST(YV12_OVERLAY);
    DEC_CONST(IYUV_OVERLAY);
    DEC_CONST(YUY2_OVERLAY);
    DEC_CONST(UYVY_OVERLAY);
    DEC_CONST(YVYU_OVERLAY);

    DEC_CONST(SWSURFACE);
    DEC_CONST(HWSURFACE);
    DEC_CONST(RESIZABLE);
    DEC_CONST(ASYNCBLIT);
    DEC_CONST(OPENGL);
    DEC_CONST(OPENGLBLIT);
    DEC_CONST(ANYFORMAT);
    DEC_CONST(HWPALETTE);
    DEC_CONST(DOUBLEBUF);
    DEC_CONST(FULLSCREEN);
    DEC_CONST(HWACCEL);
    DEC_CONST(SRCCOLORKEY);
    DEC_CONST(RLEACCELOK);
    DEC_CONST(RLEACCEL);
    DEC_CONST(SRCALPHA);
    DEC_CONST(PREALLOC);
    DEC_CONST(NOFRAME);
#else  /* IS_SDLv2 */
    DEC_CONSTSF(SWSURFACE);
    DEC_CONSTSF(HWSURFACE);
    DEC_CONSTSF(RESIZABLE);
    DEC_CONSTSF(ASYNCBLIT);
    DEC_CONSTSF(OPENGL);
    DEC_CONSTSF(OPENGLBLIT);
    DEC_CONSTSF(ANYFORMAT);
    DEC_CONSTSF(HWPALETTE);
    DEC_CONSTSF(DOUBLEBUF);
    DEC_CONSTSF(FULLSCREEN);
    DEC_CONSTSF(HWACCEL);
    DEC_CONSTSF(SRCCOLORKEY);
    DEC_CONSTSF(RLEACCELOK);
    DEC_CONSTSF(RLEACCEL);
    DEC_CONSTSF(SRCALPHA);
    DEC_CONSTSF(PREALLOC);
    DEC_CONSTSF(NOFRAME);
    DEC_CONSTSF(SHOWN);
    DEC_CONSTSF(HIDDEN);
#endif /* IS_SDLv2 */

    DEC_CONST(GL_RED_SIZE);
    DEC_CONST(GL_GREEN_SIZE);
    DEC_CONST(GL_BLUE_SIZE);
    DEC_CONST(GL_ALPHA_SIZE);
    DEC_CONST(GL_BUFFER_SIZE);
    DEC_CONST(GL_DOUBLEBUFFER);
    DEC_CONST(GL_DEPTH_SIZE);
    DEC_CONST(GL_STENCIL_SIZE);
    DEC_CONST(GL_ACCUM_RED_SIZE);
    DEC_CONST(GL_ACCUM_GREEN_SIZE);
    DEC_CONST(GL_ACCUM_BLUE_SIZE);
    DEC_CONST(GL_ACCUM_ALPHA_SIZE);

#if IS_SDLv2
    DEC_CONST(BLENDMODE_NONE);
    DEC_CONST(BLENDMODE_BLEND);
    DEC_CONST(BLENDMODE_ADD);
    DEC_CONST(BLENDMODE_MOD);

#endif /* IS_SDLv2 */
#if SDL_VERSION_ATLEAST(1, 2, 5)
    DEC_CONST(GL_STEREO);
#else
    PyModule_AddIntConstant(module, "GL_STEREO", -1);
#endif

#if SDL_VERSION_ATLEAST(1, 2, 6)
    DEC_CONST(GL_MULTISAMPLEBUFFERS);
    DEC_CONST(GL_MULTISAMPLESAMPLES);
#else
    PyModule_AddIntConstant(module, "GL_MULTISAMPLEBUFFERS", -1);
    PyModule_AddIntConstant(module, "GL_MULTISAMPLESAMPLES", -1);
#endif

#if SDL_VERSION_ATLEAST(1, 2, 10)
    DEC_CONST(GL_SWAP_CONTROL);
    DEC_CONST(GL_ACCELERATED_VISUAL);
#else
    PyModule_AddIntConstant(module, "GL_SWAP_CONTROL", -1);
    PyModule_AddIntConstant(module, "GL_ACCELERATED_VISUAL", -1);
#endif

#if SDL_VERSION_ATLEAST(1, 2, 13)
    DEC_CONST(BUTTON_X1);
    DEC_CONST(BUTTON_X2);
#else
    PyModule_AddIntConstant(module, "BUTTON_X1", -1);
    PyModule_AddIntConstant(module, "BUTTON_X2", -1);
#endif

    DEC_CONSTN(TIMER_RESOLUTION);

    DEC_CONSTN(AUDIO_U8);
    DEC_CONSTN(AUDIO_S8);
    DEC_CONSTN(AUDIO_U16LSB);
    DEC_CONSTN(AUDIO_S16LSB);
    DEC_CONSTN(AUDIO_U16MSB);
    DEC_CONSTN(AUDIO_S16MSB);
    DEC_CONSTN(AUDIO_U16);
    DEC_CONSTN(AUDIO_S16);
    DEC_CONSTN(AUDIO_U16SYS);
    DEC_CONSTN(AUDIO_S16SYS);

#define SCRAP_TEXT PYGAME_SCRAP_TEXT
#define SCRAP_BMP PYGAME_SCRAP_BMP
#define SCRAP_PPM PYGAME_SCRAP_PPM
#define SCRAP_PBM PYGAME_SCRAP_PBM

    ADD_STRING_CONST(SCRAP_TEXT);
    ADD_STRING_CONST(SCRAP_BMP);
    ADD_STRING_CONST(SCRAP_PPM);
    ADD_STRING_CONST(SCRAP_PBM);
    PyModule_AddIntConstant(module, "SCRAP_CLIPBOARD", 0);
    PyModule_AddIntConstant(module, "SCRAP_SELECTION", 1);

/* BLEND_ADD is an alias for BLEND_RGB_ADD
 */
#define PYGAME_BLEND_RGB_ADD 0x1
#define PYGAME_BLEND_RGB_SUB 0x2
#define PYGAME_BLEND_RGB_MULT 0x3
#define PYGAME_BLEND_RGB_MIN 0x4
#define PYGAME_BLEND_RGB_MAX 0x5

#define PYGAME_BLEND_ADD PYGAME_BLEND_RGB_ADD
#define PYGAME_BLEND_SUB PYGAME_BLEND_RGB_SUB
#define PYGAME_BLEND_MULT PYGAME_BLEND_RGB_MULT
#define PYGAME_BLEND_MIN PYGAME_BLEND_RGB_MIN
#define PYGAME_BLEND_MAX PYGAME_BLEND_RGB_MAX

#define PYGAME_BLEND_RGBA_ADD 0x6
#define PYGAME_BLEND_RGBA_SUB 0x7
#define PYGAME_BLEND_RGBA_MULT 0x8
#define PYGAME_BLEND_RGBA_MIN 0x9
#define PYGAME_BLEND_RGBA_MAX 0x10

#define PYGAME_BLEND_PREMULTIPLIED 0x11

    DEC_CONSTS(BLEND_ADD, PYGAME_BLEND_ADD);
    DEC_CONSTS(BLEND_SUB, PYGAME_BLEND_SUB);
    DEC_CONSTS(BLEND_MULT, PYGAME_BLEND_MULT);
    DEC_CONSTS(BLEND_MIN, PYGAME_BLEND_MIN);
    DEC_CONSTS(BLEND_MAX, PYGAME_BLEND_MAX);

    DEC_CONSTS(BLEND_RGB_ADD, PYGAME_BLEND_RGB_ADD);
    DEC_CONSTS(BLEND_RGB_SUB, PYGAME_BLEND_RGB_SUB);
    DEC_CONSTS(BLEND_RGB_MULT, PYGAME_BLEND_RGB_MULT);
    DEC_CONSTS(BLEND_RGB_MIN, PYGAME_BLEND_RGB_MIN);
    DEC_CONSTS(BLEND_RGB_MAX, PYGAME_BLEND_RGB_MAX);

    DEC_CONSTS(BLEND_RGBA_ADD, PYGAME_BLEND_RGBA_ADD);
    DEC_CONSTS(BLEND_RGBA_SUB, PYGAME_BLEND_RGBA_SUB);
    DEC_CONSTS(BLEND_RGBA_MULT, PYGAME_BLEND_RGBA_MULT);
    DEC_CONSTS(BLEND_RGBA_MIN, PYGAME_BLEND_RGBA_MIN);
    DEC_CONSTS(BLEND_RGBA_MAX, PYGAME_BLEND_RGBA_MAX);
    DEC_CONSTS(BLEND_PREMULTIPLIED, PYGAME_BLEND_PREMULTIPLIED);

    /* Event types
     */
    DEC_CONST(NOEVENT);
    DEC_CONST(ACTIVEEVENT);
    DEC_CONST(KEYDOWN);
    DEC_CONST(KEYUP);
    DEC_CONST(MOUSEMOTION);
    DEC_CONST(MOUSEBUTTONDOWN);
    DEC_CONST(MOUSEBUTTONUP);
    DEC_CONST(JOYAXISMOTION);
    DEC_CONST(JOYBALLMOTION);
    DEC_CONST(JOYHATMOTION);
    DEC_CONST(JOYBUTTONDOWN);
    DEC_CONST(JOYBUTTONUP);
    DEC_CONST(VIDEORESIZE);
    DEC_CONST(VIDEOEXPOSE);
    DEC_CONST(QUIT);
    DEC_CONST(SYSWMEVENT);
    DEC_CONST(USEREVENT);
    DEC_CONST(NUMEVENTS);

    DEC_CONST(HAT_CENTERED);
    DEC_CONST(HAT_UP);
    DEC_CONST(HAT_RIGHTUP);
    DEC_CONST(HAT_RIGHT);
    DEC_CONST(HAT_RIGHTDOWN);
    DEC_CONST(HAT_DOWN);
    DEC_CONST(HAT_LEFTDOWN);
    DEC_CONST(HAT_LEFT);
    DEC_CONST(HAT_LEFTUP);

#if IS_SDLv1
    DEC_CONSTK(K_UNKNOWN);
    DEC_CONSTK(K_FIRST);
    DEC_CONSTK(K_BACKSPACE);
    DEC_CONSTK(K_TAB);
    DEC_CONSTK(K_CLEAR);
    DEC_CONSTK(K_RETURN);
    DEC_CONSTK(K_PAUSE);
    DEC_CONSTK(K_ESCAPE);
    DEC_CONSTK(K_SPACE);
    DEC_CONSTK(K_EXCLAIM);
    DEC_CONSTK(K_QUOTEDBL);
    DEC_CONSTK(K_HASH);
    DEC_CONSTK(K_DOLLAR);
    DEC_CONSTK(K_AMPERSAND);
    DEC_CONSTK(K_QUOTE);
    DEC_CONSTK(K_LEFTPAREN);
    DEC_CONSTK(K_RIGHTPAREN);
    DEC_CONSTK(K_ASTERISK);
    DEC_CONSTK(K_PLUS);
    DEC_CONSTK(K_COMMA);
    DEC_CONSTK(K_MINUS);
    DEC_CONSTK(K_PERIOD);
    DEC_CONSTK(K_SLASH);
    DEC_CONSTK(K_0);
    DEC_CONSTK(K_1);
    DEC_CONSTK(K_2);
    DEC_CONSTK(K_3);
    DEC_CONSTK(K_4);
    DEC_CONSTK(K_5);
    DEC_CONSTK(K_6);
    DEC_CONSTK(K_7);
    DEC_CONSTK(K_8);
    DEC_CONSTK(K_9);
    DEC_CONSTK(K_COLON);
    DEC_CONSTK(K_SEMICOLON);
    DEC_CONSTK(K_LESS);
    DEC_CONSTK(K_EQUALS);
    DEC_CONSTK(K_GREATER);
    DEC_CONSTK(K_QUESTION);
    DEC_CONSTK(K_AT);
    DEC_CONSTK(K_LEFTBRACKET);
    DEC_CONSTK(K_BACKSLASH);
    DEC_CONSTK(K_RIGHTBRACKET);
    DEC_CONSTK(K_CARET);
    DEC_CONSTK(K_UNDERSCORE);
    DEC_CONSTK(K_BACKQUOTE);
    DEC_CONSTK(K_a);
    DEC_CONSTK(K_b);
    DEC_CONSTK(K_c);
    DEC_CONSTK(K_d);
    DEC_CONSTK(K_e);
    DEC_CONSTK(K_f);
    DEC_CONSTK(K_g);
    DEC_CONSTK(K_h);
    DEC_CONSTK(K_i);
    DEC_CONSTK(K_j);
    DEC_CONSTK(K_k);
    DEC_CONSTK(K_l);
    DEC_CONSTK(K_m);
    DEC_CONSTK(K_n);
    DEC_CONSTK(K_o);
    DEC_CONSTK(K_p);
    DEC_CONSTK(K_q);
    DEC_CONSTK(K_r);
    DEC_CONSTK(K_s);
    DEC_CONSTK(K_t);
    DEC_CONSTK(K_u);
    DEC_CONSTK(K_v);
    DEC_CONSTK(K_w);
    DEC_CONSTK(K_x);
    DEC_CONSTK(K_y);
    DEC_CONSTK(K_z);
    DEC_CONSTK(K_DELETE);

    DEC_CONSTK(K_KP0);
    DEC_CONSTK(K_KP1);
    DEC_CONSTK(K_KP2);
    DEC_CONSTK(K_KP3);
    DEC_CONSTK(K_KP4);
    DEC_CONSTK(K_KP5);
    DEC_CONSTK(K_KP6);
    DEC_CONSTK(K_KP7);
    DEC_CONSTK(K_KP8);
    DEC_CONSTK(K_KP9);
    DEC_CONSTK(K_KP_PERIOD);
    DEC_CONSTK(K_KP_DIVIDE);
    DEC_CONSTK(K_KP_MULTIPLY);
    DEC_CONSTK(K_KP_MINUS);
    DEC_CONSTK(K_KP_PLUS);
    DEC_CONSTK(K_KP_ENTER);
    DEC_CONSTK(K_KP_EQUALS);
    DEC_CONSTK(K_UP);
    DEC_CONSTK(K_DOWN);
    DEC_CONSTK(K_RIGHT);
    DEC_CONSTK(K_LEFT);
    DEC_CONSTK(K_INSERT);
    DEC_CONSTK(K_HOME);
    DEC_CONSTK(K_END);
    DEC_CONSTK(K_PAGEUP);
    DEC_CONSTK(K_PAGEDOWN);
    DEC_CONSTK(K_F1);
    DEC_CONSTK(K_F2);
    DEC_CONSTK(K_F3);
    DEC_CONSTK(K_F4);
    DEC_CONSTK(K_F5);
    DEC_CONSTK(K_F6);
    DEC_CONSTK(K_F7);
    DEC_CONSTK(K_F8);
    DEC_CONSTK(K_F9);
    DEC_CONSTK(K_F10);
    DEC_CONSTK(K_F11);
    DEC_CONSTK(K_F12);
    DEC_CONSTK(K_F13);
    DEC_CONSTK(K_F14);
    DEC_CONSTK(K_F15);

    DEC_CONSTK(K_NUMLOCK);
    DEC_CONSTK(K_CAPSLOCK);
    DEC_CONSTK(K_SCROLLOCK);
    DEC_CONSTK(K_RSHIFT);
    DEC_CONSTK(K_LSHIFT);
    DEC_CONSTK(K_RCTRL);
    DEC_CONSTK(K_LCTRL);
    DEC_CONSTK(K_RALT);
    DEC_CONSTK(K_LALT);
    DEC_CONSTK(K_RMETA);
    DEC_CONSTK(K_LMETA);
    DEC_CONSTK(K_LSUPER);
    DEC_CONSTK(K_RSUPER);
    DEC_CONSTK(K_MODE);

    DEC_CONSTK(K_HELP);
    DEC_CONSTK(K_PRINT);
    DEC_CONSTK(K_SYSREQ);
    DEC_CONSTK(K_BREAK);
    DEC_CONSTK(K_MENU);
    DEC_CONSTK(K_POWER);
    DEC_CONSTK(K_EURO);
    DEC_CONSTK(K_LAST);
#else  /* IS_SDLv2 */
    /* Keyboard scan codes: Pygame K_ constants
     */
    DEC_CONSTK(UNKNOWN);
    DEC_CONSTK(BACKSPACE);
    DEC_CONSTK(TAB);
    DEC_CONSTK(CLEAR);
    DEC_CONSTK(RETURN);
    DEC_CONSTK(PAUSE);
    DEC_CONSTK(ESCAPE);
    DEC_CONSTK(SPACE);
    DEC_CONSTKS(QUOTE, APOSTROPHE);
    DEC_CONSTK(COMMA);
    DEC_CONSTK(MINUS);
    DEC_CONSTK(PERIOD);
    DEC_CONSTK(SLASH);
    DEC_CONSTK(0);
    DEC_CONSTK(1);
    DEC_CONSTK(2);
    DEC_CONSTK(3);
    DEC_CONSTK(4);
    DEC_CONSTK(5);
    DEC_CONSTK(6);
    DEC_CONSTK(7);
    DEC_CONSTK(8);
    DEC_CONSTK(9);
    DEC_CONSTK(SEMICOLON);
    DEC_CONSTK(EQUALS);
    DEC_CONSTK(LEFTBRACKET);
    DEC_CONSTK(BACKSLASH);
    DEC_CONSTK(RIGHTBRACKET);
    DEC_CONSTKS(BACKQUOTE, GRAVE);
    DEC_CONSTKS(a, A);
    DEC_CONSTKS(b, B);
    DEC_CONSTKS(c, C);
    DEC_CONSTKS(d, D);
    DEC_CONSTKS(e, E);
    DEC_CONSTKS(f, F);
    DEC_CONSTKS(g, G);
    DEC_CONSTKS(h, H);
    DEC_CONSTKS(i, I);
    DEC_CONSTKS(j, J);
    DEC_CONSTKS(k, K);
    DEC_CONSTKS(l, L);
    DEC_CONSTKS(m, M);
    DEC_CONSTKS(n, N);
    DEC_CONSTKS(o, O);
    DEC_CONSTKS(p, P);
    DEC_CONSTKS(q, Q);
    DEC_CONSTKS(r, R);
    DEC_CONSTKS(s, S);
    DEC_CONSTKS(t, T);
    DEC_CONSTKS(u, U);
    DEC_CONSTKS(v, V);
    DEC_CONSTKS(w, W);
    DEC_CONSTKS(x, X);
    DEC_CONSTKS(y, Y);
    DEC_CONSTKS(z, Z);
    DEC_CONSTK(DELETE);

    DEC_CONSTK(KP_0);
    DEC_CONSTK(KP_0);
    DEC_CONSTK(KP_1);
    DEC_CONSTK(KP_2);
    DEC_CONSTK(KP_3);
    DEC_CONSTK(KP_4);
    DEC_CONSTK(KP_5);
    DEC_CONSTK(KP_6);
    DEC_CONSTK(KP_7);
    DEC_CONSTK(KP_8);
    DEC_CONSTK(KP_9);
    DEC_CONSTKS(KP1, KP_1);
    DEC_CONSTKS(KP2, KP_2);
    DEC_CONSTKS(KP3, KP_3);
    DEC_CONSTKS(KP4, KP_4);
    DEC_CONSTKS(KP5, KP_5);
    DEC_CONSTKS(KP6, KP_6);
    DEC_CONSTKS(KP7, KP_7);
    DEC_CONSTKS(KP8, KP_8);
    DEC_CONSTKS(KP9, KP_9);
    DEC_CONSTK(KP_PERIOD);
    DEC_CONSTK(KP_DIVIDE);
    DEC_CONSTK(KP_MULTIPLY);
    DEC_CONSTK(KP_MINUS);
    DEC_CONSTK(KP_PLUS);
    DEC_CONSTK(KP_ENTER);
    DEC_CONSTK(KP_EQUALS);
    DEC_CONSTK(UP);
    DEC_CONSTK(DOWN);
    DEC_CONSTK(RIGHT);
    DEC_CONSTK(LEFT);
    DEC_CONSTK(INSERT);
    DEC_CONSTK(HOME);
    DEC_CONSTK(END);
    DEC_CONSTK(PAGEUP);
    DEC_CONSTK(PAGEDOWN);
    DEC_CONSTK(F1);
    DEC_CONSTK(F2);
    DEC_CONSTK(F3);
    DEC_CONSTK(F4);
    DEC_CONSTK(F5);
    DEC_CONSTK(F6);
    DEC_CONSTK(F7);
    DEC_CONSTK(F8);
    DEC_CONSTK(F9);
    DEC_CONSTK(F10);
    DEC_CONSTK(F11);
    DEC_CONSTK(F12);
    DEC_CONSTK(F13);
    DEC_CONSTK(F14);
    DEC_CONSTK(F15);

    DEC_CONSTK(NUMLOCKCLEAR)
    DEC_CONSTKS(NUMLOCK, NUMLOCKCLEAR);
    DEC_CONSTK(CAPSLOCK);
    DEC_CONSTK(SCROLLLOCK);
    DEC_CONSTKS(SCROLLOCK, SCROLLLOCK);
    DEC_CONSTK(RSHIFT);
    DEC_CONSTK(LSHIFT);
    DEC_CONSTK(RCTRL);
    DEC_CONSTK(LCTRL);
    DEC_CONSTK(RALT);
    DEC_CONSTK(LALT);
    DEC_CONSTK(RGUI);
    DEC_CONSTKS(RMETA, RGUI);
    DEC_CONSTK(LGUI);
    DEC_CONSTKS(LMETA, LGUI);
    DEC_CONSTKS(LSUPER, LGUI);
    DEC_CONSTKS(RSUPER, RGUI);
    DEC_CONSTK(MODE);

    DEC_CONSTK(HELP);
    DEC_CONSTK(PRINTSCREEN);
    DEC_CONSTKS(PRINT, PRINTSCREEN);
    DEC_CONSTK(SYSREQ);
    DEC_CONSTKS(BREAK, PAUSE);
    DEC_CONSTK(MENU);
    DEC_CONSTK(POWER);
    DEC_CONSTK(CURRENCYUNIT);
    DEC_CONSTK(CURRENCYSUBUNIT);
    DEC_CONSTKS(EURO, CURRENCYUNIT);

    DEC_CONSTK(INTERNATIONAL1);
    DEC_CONSTK(INTERNATIONAL2);
    DEC_CONSTK(INTERNATIONAL3);
    DEC_CONSTK(INTERNATIONAL4);
    DEC_CONSTK(INTERNATIONAL5);
    DEC_CONSTK(INTERNATIONAL6);
    DEC_CONSTK(INTERNATIONAL7);
    DEC_CONSTK(INTERNATIONAL8);
    DEC_CONSTK(INTERNATIONAL9);
    DEC_CONSTK(LANG1);
    DEC_CONSTK(LANG2);
    DEC_CONSTK(LANG3);
    DEC_CONSTK(LANG4);
    DEC_CONSTK(LANG5);
    DEC_CONSTK(LANG6);
    DEC_CONSTK(LANG7);
    DEC_CONSTK(LANG8);
    DEC_CONSTK(LANG9);
    DEC_CONSTK(NONUSBACKSLASH);
    DEC_CONSTK(NONUSHASH);

    /* Keyboard keycodes: Pygame KSYM_ constants.
     */
    DEC_CONSTKSYM(UNKNOWN);
    DEC_CONSTKSYM(BACKSPACE);
    DEC_CONSTKSYM(TAB);
    DEC_CONSTKSYM(CLEAR);
    DEC_CONSTKSYM(RETURN);
    DEC_CONSTKSYM(PAUSE);
    DEC_CONSTKSYM(ESCAPE);
    DEC_CONSTKSYM(SPACE);
    DEC_CONSTKSYM(EXCLAIM);
    DEC_CONSTKSYM(QUOTEDBL);
    DEC_CONSTKSYM(HASH);
    DEC_CONSTKSYM(DOLLAR);
    DEC_CONSTKSYM(AMPERSAND);
    DEC_CONSTKSYM(PERCENT);
    DEC_CONSTKSYM(QUOTE);
    DEC_CONSTKSYM(LEFTPAREN);
    DEC_CONSTKSYM(RIGHTPAREN);
    DEC_CONSTKSYM(ASTERISK);
    DEC_CONSTKSYM(PLUS);
    DEC_CONSTKSYM(COMMA);
    DEC_CONSTKSYM(MINUS);
    DEC_CONSTKSYM(PERIOD);
    DEC_CONSTKSYM(SLASH);
    DEC_CONSTKSYM(0);
    DEC_CONSTKSYM(1);
    DEC_CONSTKSYM(2);
    DEC_CONSTKSYM(3);
    DEC_CONSTKSYM(4);
    DEC_CONSTKSYM(5);
    DEC_CONSTKSYM(6);
    DEC_CONSTKSYM(7);
    DEC_CONSTKSYM(8);
    DEC_CONSTKSYM(9);
    DEC_CONSTKSYM(COLON);
    DEC_CONSTKSYM(SEMICOLON);
    DEC_CONSTKSYM(LESS);
    DEC_CONSTKSYM(EQUALS);
    DEC_CONSTKSYM(GREATER);
    DEC_CONSTKSYM(QUESTION);
    DEC_CONSTKSYM(AT);
    DEC_CONSTKSYM(LEFTBRACKET);
    DEC_CONSTKSYM(BACKSLASH);
    DEC_CONSTKSYM(RIGHTBRACKET);
    DEC_CONSTKSYM(CARET);
    DEC_CONSTKSYM(UNDERSCORE);
    DEC_CONSTKSYM(BACKQUOTE);
    DEC_CONSTKSYM(a);
    DEC_CONSTKSYM(b);
    DEC_CONSTKSYM(c);
    DEC_CONSTKSYM(d);
    DEC_CONSTKSYM(e);
    DEC_CONSTKSYM(f);
    DEC_CONSTKSYM(g);
    DEC_CONSTKSYM(h);
    DEC_CONSTKSYM(i);
    DEC_CONSTKSYM(j);
    DEC_CONSTKSYM(k);
    DEC_CONSTKSYM(l);
    DEC_CONSTKSYM(m);
    DEC_CONSTKSYM(n);
    DEC_CONSTKSYM(o);
    DEC_CONSTKSYM(p);
    DEC_CONSTKSYM(q);
    DEC_CONSTKSYM(r);
    DEC_CONSTKSYM(s);
    DEC_CONSTKSYM(t);
    DEC_CONSTKSYM(u);
    DEC_CONSTKSYM(v);
    DEC_CONSTKSYM(w);
    DEC_CONSTKSYM(x);
    DEC_CONSTKSYM(y);
    DEC_CONSTKSYM(z);
    DEC_CONSTKSYM(DELETE);

    DEC_CONSTKSYM(KP_0);
    DEC_CONSTKSYM(KP_0);
    DEC_CONSTKSYM(KP_1);
    DEC_CONSTKSYM(KP_2);
    DEC_CONSTKSYM(KP_3);
    DEC_CONSTKSYM(KP_4);
    DEC_CONSTKSYM(KP_5);
    DEC_CONSTKSYM(KP_6);
    DEC_CONSTKSYM(KP_7);
    DEC_CONSTKSYM(KP_8);
    DEC_CONSTKSYM(KP_9);
    DEC_CONSTKSYMS(KP1, KP_1);
    DEC_CONSTKSYMS(KP2, KP_2);
    DEC_CONSTKSYMS(KP3, KP_3);
    DEC_CONSTKSYMS(KP4, KP_4);
    DEC_CONSTKSYMS(KP5, KP_5);
    DEC_CONSTKSYMS(KP6, KP_6);
    DEC_CONSTKSYMS(KP7, KP_7);
    DEC_CONSTKSYMS(KP8, KP_8);
    DEC_CONSTKSYMS(KP9, KP_9);
    DEC_CONSTKSYM(KP_PERIOD);
    DEC_CONSTKSYM(KP_DIVIDE);
    DEC_CONSTKSYM(KP_MULTIPLY);
    DEC_CONSTKSYM(KP_MINUS);
    DEC_CONSTKSYM(KP_PLUS);
    DEC_CONSTKSYM(KP_ENTER);
    DEC_CONSTKSYM(KP_EQUALS);
    DEC_CONSTKSYM(UP);
    DEC_CONSTKSYM(DOWN);
    DEC_CONSTKSYM(RIGHT);
    DEC_CONSTKSYM(LEFT);
    DEC_CONSTKSYM(INSERT);
    DEC_CONSTKSYM(HOME);
    DEC_CONSTKSYM(END);
    DEC_CONSTKSYM(PAGEUP);
    DEC_CONSTKSYM(PAGEDOWN);
    DEC_CONSTKSYM(F1);
    DEC_CONSTKSYM(F2);
    DEC_CONSTKSYM(F3);
    DEC_CONSTKSYM(F4);
    DEC_CONSTKSYM(F5);
    DEC_CONSTKSYM(F6);
    DEC_CONSTKSYM(F7);
    DEC_CONSTKSYM(F8);
    DEC_CONSTKSYM(F9);
    DEC_CONSTKSYM(F10);
    DEC_CONSTKSYM(F11);
    DEC_CONSTKSYM(F12);
    DEC_CONSTKSYM(F13);
    DEC_CONSTKSYM(F14);
    DEC_CONSTKSYM(F15);

    DEC_CONSTKSYM(NUMLOCKCLEAR)
    DEC_CONSTKSYMS(NUMLOCK, NUMLOCKCLEAR);
    DEC_CONSTKSYM(CAPSLOCK);
    DEC_CONSTKSYM(SCROLLLOCK);
    DEC_CONSTKSYMS(SCROLLOCK, SCROLLLOCK);
    DEC_CONSTKSYM(RSHIFT);
    DEC_CONSTKSYM(LSHIFT);
    DEC_CONSTKSYM(RCTRL);
    DEC_CONSTKSYM(LCTRL);
    DEC_CONSTKSYM(RALT);
    DEC_CONSTKSYM(LALT);
    DEC_CONSTKSYM(RGUI);
    DEC_CONSTKSYMS(RMETA, RGUI);
    DEC_CONSTKSYM(LGUI);
    DEC_CONSTKSYMS(LMETA, LGUI);
    DEC_CONSTKSYMS(LSUPER, LGUI);
    DEC_CONSTKSYMS(RSUPER, RGUI);
    DEC_CONSTKSYM(MODE);

    DEC_CONSTKSYM(HELP);
    DEC_CONSTKSYM(PRINTSCREEN);
    DEC_CONSTKSYMS(PRINT, PRINTSCREEN);
    DEC_CONSTKSYM(SYSREQ);
    DEC_CONSTKSYMS(BREAK, PAUSE);
    DEC_CONSTKSYM(MENU);
    DEC_CONSTKSYM(POWER);
    DEC_CONSTKSYM(CURRENCYUNIT);
    DEC_CONSTKSYM(CURRENCYSUBUNIT);
    DEC_CONSTKSYMS(EURO, CURRENCYUNIT);
#endif /* IS_SDLv2 */

    /* Keyboard key modifiers: Pygame KMOD_ constants.
     */
    DEC_CONSTN(KMOD_NONE);
    DEC_CONSTN(KMOD_LSHIFT);
    DEC_CONSTN(KMOD_RSHIFT);
    DEC_CONSTN(KMOD_LCTRL);
    DEC_CONSTN(KMOD_RCTRL);
    DEC_CONSTN(KMOD_LALT);
    DEC_CONSTN(KMOD_RALT);
#if IS_SDLv1
    DEC_CONSTN(KMOD_LMETA);
    DEC_CONSTN(KMOD_RMETA);
#else  /* IS_SDLv2 */
    DEC_CONSTN(KMOD_LGUI);
    DEC_CONSTS(KMOD_LMETA, KMOD_LGUI);
    DEC_CONSTN(KMOD_RGUI);
    DEC_CONSTS(KMOD_RMETA, KMOD_RGUI);
#endif /* IS_SDLv2 */
    DEC_CONSTN(KMOD_NUM);
    DEC_CONSTN(KMOD_CAPS);
    DEC_CONSTN(KMOD_MODE);

    DEC_CONSTN(KMOD_CTRL);
    DEC_CONSTN(KMOD_SHIFT);
    DEC_CONSTN(KMOD_ALT);
#if IS_SDLv1
    DEC_CONSTN(KMOD_META);
#else  /* IS_SDLv2 */
    DEC_CONSTN(KMOD_GUI);
    DEC_CONSTS(KMOD_META, KMOD_GUI);

    DEC_CONST(APPFOCUSMOUSE);
    DEC_CONST(APPINPUTFOCUS);
    DEC_CONST(APPACTIVE);
#endif /* IS_SDLv2 */

#define PYGAME_USEREVENT_DROPFILE 0x1000
    DEC_CONSTS(USEREVENT_DROPFILE, PYGAME_USEREVENT_DROPFILE);

    MODINIT_RETURN(module);
}
