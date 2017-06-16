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
int		nfGetParentID();
char		*tfGetSegmentName();
char		**tafGetAllSegmentName();
char		*tfGetNextSegmentName();
char		*tfGetPreviousSegmentName();
char		*tfGetFirstSegmentName();
char		*tfGetLastSegmentName();
int		nfGetSegmentID();
int		*nafGetAllSegmentID();
int		nfGetNextSegmentID();
int		nfGetPreviousSegmentID();
int		nfGetFirstSegmentID();
int		nfGetLastSegmentID();
int		nfGetSegmentID();
int		nfGetNextSegmentID();
int		nfGetPreviousSegmentID();
int		nfGetFirstSegmentID();
int		nfGetLastSegmentID();

/*
** Element access functions :
*/
char		*tfGetChildName();
char		**tafGetAllChildName();
char		*tfGetNextChildName();
char		*tfGetPreviousChildName();
char		*tfGetFirstChildName();
char		*tfGetLastChildName();
int		nfGetChildID();
int		*nafGetAllChildID();
int		nfGetNextChildID();
int		nfGetPreviousChildID();
int		nfGetFirstChildID();
int		nfGetLastChildID();

#endif		/* __ACCESS_H__ */
