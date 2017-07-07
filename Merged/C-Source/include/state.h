#ifndef		__STATE_H__
# define	__STATE_H__

enum            e_state
  {
    DECLARATIONB = 0,	// The encountered token is the begining of a variable.
    DECLARATIONE = 1,	// The encountered token is the ending of a variable.
    ASSIGNEMENT = 2,	// The encountered token means that the foolowing token and fraglents should be the content.
    ESNAME = 3,		// The last token implied that the surrent token is not a token but an alement name.
    VALUE = 4,		// The encountered token means that it's a value with no token.
    TYPETOKENB = 5,	// The encountered token is a type token begining.
    TYPETOKENE = 6,	// The encountered token is a type token ending.
    SEPARATOR = 7,	// The encountered token is a separator.
    LISTB = 8,		// The encountered token is the begining of a list.
    LISTE = 9,		// The encountered token is the ending of a list.
    TABB = 10,		// The encountered token is the begining of a tab.
    TABE = 11,		// The encountered token is the ending of a tab.
    NONE = 12,		// The encountered token is not knonw.
    ERROR = 13		// Supposed that there is a syntax error.
  };

#endif		/* __STATE_H__ */
