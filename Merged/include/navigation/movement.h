#ifndef		__MOVEMENT_H__
# define	__MOVEMENT_H__

#include	"tree/message.h"

/*
** The following functions allows you to move inside the tree
** created after the parsing time.
** You'll find movement in segment, child, parent and element.
** All of those for can move either to the first one (of the list) or the last one 
** (when said "one" understand the case of the list (segment / element)).
** You can move to the next or the previous one. 
** You can also move to a sepcifyed ID or specifyed name.
*/

/*
** Segment and parent movement functions :
*/
int             nfGoToRoot()
int             nfGoToParent();
int             nfGoToFirstSegment()
int             nfGoToLastSegment()
int             nfGoToNextSegment()
int             nfGoToPreviousSegment()
int             nfGoToIDSegment(int id);
int             nfGoToNameSegment(const char *name);
int             nfGoToNameChild(const char *name);
int             nfGoToFirstTab();
int             nfGoToFirstList();

/*
** Child movement functions :
*/
int             nfGoToFirstChild();
int             nfGoToLastChild();
int             nfGoToNextChild();
int             nfGoToPreviousChild();
int             nfGoToIDChild(int id);

/*
** Element movement functions :
*/
int             nfGoToFirstElement();
int             nfGoToLastElement();
int             nfGoToNextElement();
int             nfGoToPreviousElement();
int             nfGoToIDElement(int id);
int             nfGoToNameElement(const char *name);

#endif		/* __MOVEMENT_H__ */
