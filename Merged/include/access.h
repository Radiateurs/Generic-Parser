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
double		nfGetSegmentID();
double		nfGetNextSegmentID();
double		nfGetPreviousSegmentID();
double		nfGetFirstSegmentID();
double		nfGetLastSegmentID();

/*
** Child access functions :
*/
char		*tfGetChildName();
char		*tfGetNextChildName();
char		*tfGetPreviousChildName();
char		*tfGetFirstChildName();
char		*tfGetLastChildName();
double		nfGetChildID();
int		*nafGetAllChildID();
double		nfGetNextChildID();
double		nfGetPreviousChildID();
double		nfGetFirstChildID();
double		nfGetLastChildID();

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
double		nfGetElementType();
double		nfGetElementType();
double		nfGetElementType();
double		nfGetElementType();

#endif		/* __ACCESS_H__ */
