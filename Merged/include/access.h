#ifndef		__ACCESS_H__
# define	__ACCESS_H__

/*
** Every functions presented here help you to get access to every information
** inside a node of the tree. Segment, Child, Element, content, Everything.
**
** WARNING : 
**		By callig any of those functions, you'll receive the requested data from
**		the current pointed node (depending if you ask for a segment / child or element
**		this won't be a problem). You have to move to the wanted node then ask for the data.
*/

/*
** Message access functions :
*/
double		nfGetMessageID();
double		nfGetMessageType();
char		*tfGetMessageName();
double		nfGetIDMessageType(int id);
char		*tfGetIDMessageName(int id);
double		nfGetTypeMessageID(int type);
char		*tfGetTypeMessageName(int type);
double		nfGetNameMessageID(char *name);
double		nfGetNameMessageType(char *name);

/*
** Segment acces functions :
*/
char		*tfGetRootName();
char		*tfGetParentName();
double		nfGetParentID();
char		*tfGetSegmentName();
char		*tfGetNextSegmentName();
char		*tfGetPreviousSegmentName();
char		*tfGetFirstSegmentName();
char		*tfGetLastSegmentName();
double		nfGetSegmentID();
double		nfGetNextSegmentID();
double		nfGetPreviousSegmentID();
double		nfGetFirstSegmentID();
double		nfGetLastSegmentID();
double		nfGetSegmentDepth();
double		nfGetNextSegmentDepth();
double		nfGetPreviousSegmentDepth();
double		nfGetFirstSegmentDepth();
double		nfGetLastSegmentDepth();
double		nfGetSegmentType();
double		nfGetNextSegmentType();
double		nfGetPreviousSegmentType();
double		nfGetFirstSegmentType();
double		nfGetLastSegmentType();
double		bfIsSegmentSeg();
double		bfIsSegmentTab();
double		bfIsSegmentList();

/*
** Child access functions :
*/
char		*tfGetChildName();
char		*tfGetNextChildName();
char		*tfGetPreviousChildName();
char		*tfGetFirstChildName();
char		*tfGetLastChildName();
double		nfGetChildID();
double		nfGetNextChildID();
double		nfGetPreviousChildID();
double		nfGetFirstChildID();
double		nfGetLastChildID();
double		nfGetChildDepth();
double		nfGetNextChildDepth();
double		nfGetPreviousChildDepth();
double		nfGetFirstChildDepth();
double		nfGetLastChildDepth();

/*
** Element acces functions
*/
double		nfGetElementID();
double		nfGetNextElementID();
double		nfGetPreviousElementID();
double		nfGetFirstElementID();
double		nfGetLastElementID();
char		*tfGetElementName();
char		*tfGetNextElementName();
char		*tfGetPreviousElementName();
char		*tfGetFirstElementName();
char		*tfGetLastElementName();
char		*tfGetElementContent();
char		*tfGetNextElementContent();
char		*tfGetPreviousElementContent();
char		*tfGetFirstElementContent();
char		*tfGetLastElementContent();
double		nfGetElementType();
double		nfGetFirstElementType();
double		nfGetLastElementType();
double		nfGetNextElementType();
double		nfGetPrevElementType();

#endif		/* __ACCESS_H__ */
