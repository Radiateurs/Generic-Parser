#ifndef		__TREE_TYPE_H__
# define	__TREE_TYPE_H__

enum            e_tree_type
  {
    MESSAGE = 0,	// Should add a message in the tree
    SEGMENT = 1,	// Should add a segment in the tree
    CLOSEGROUP = 2,	// Should close the current group (list or tab)
    LIST = 3,		// Should add a list in the tree
    TAB = 4,		// Should add a tab in the tree
    ELEMENT = 5,	// Should add an element in the tree
    ATTRIBUT = 6,	// Should add an attribut (content without name or attribut with a name) in the tree
    NAME = 7,		// The encountered token means that this is a variable name for the tree
    CONTENT = 8,	// The encountered token means that this is a variable name for the tree
    NOPE = 9		// Unknown tree type token. Might be a variable, content type or just something else.
  };

#endif		/* __TREE_TYPE_H__ */
