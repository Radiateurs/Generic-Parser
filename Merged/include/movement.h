#ifndef		__MOVEMENT_H__
# define	__MOVEMENT_H__

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
double		nfGoToRoot();
double		nfGoToParent();
double		nfGoToFirstSegment();
double		nfGoToLastSegment();
double		nfGoToNextSegment();
double		nfGoToPreviousSegment();
double		nfGoToIDSegment(int id);
double		nfGoToNameSegment(const char *name);
double		nfGoToFirstTab();
double		nfGoToFirstList();

/*
** Child movement functions :
*/
double		nfGoToChild();
double		nfGoToFirstChild();
double		nfGoToLastChild();
double		nfGoToNextChild();
double		nfGoToPreviousChild();
double		nfGoToIDChild(int id);
double		nfGoToNameChild(const char *name);

/*
** Element movement functions :
*/
double		nfGoToFirstElement();
double		nfGoToLastElement();
double		nfGoToNextElement();
double		nfGoToPreviousElement();
double		nfGoToIDElement(int id);
double		nfGoToNameElement(const char *name);

#endif		/* __MOVEMENT_H__ */
