#ifndef		__MODIFY_H__
# define	__MODIFY_H__

# include	"tree/message.h"

/*
** The following functions are about modifying part of the tree.
*/

/*
** Segment modifying functions
*/
// Delete Part
int		nfDeleteIDSegment(int id);
int		nfDeleteNameSegment(const char *name);
int		nfDeleteSegment();
int		nfDeleteAllSegment();
// Modify Part
int		nfModifyIDSegmentName(int id, const char *new_name);
int		nfModifyNameSegmentName(const char *name, const char *new_name);
int		nfModifySegmentName(const char *new_name);
int		nfModifyIDSegmentID(int id, int new_id);
int		nfModifyNameSegmentID(const char *name, int new_id);
int		nfModifySegmentID(int new_id);
// Add part
int		nfAddSegmentInSegmentID(int id, int new_id, const char *name);
int		nfAddSegmentInSegmentName(const char *name, int new_name, const char *new_name);
int		nfAddSegmentInSegment(int new_id, const char *new_name);

/*
** Child modifying functions
*/
// Delete Part
int		nfDeleteIDChild(int id);
int		nfDeleteNameChild(const char *name);
int		nfDeleteChild();
int		nfDeleteAllChild();
// Modify Part
int		nfModifyIDChildName(int id, const char *new_name);
int		nfModifyNameChildName(const char *name, const char *new_name);
int		nfModifyChildName(const char *new_name);
int		nfModifyIDChildID(int id, int new_id);
int		nfModifyNameChildID(const char *name, int new_id);
int		nfModifyChildID(int new_id);
// Add part
int		nfAddChildInSegment(int new_id, const char *new_name);
int		nfAddChildInSegmentID(int id, int new_id, const char *name);
int		nfAddChildInSegmentName(const char *name, int new_name, const char *new_name);
int		nfAddChildInChild(int new_id, const char *new_name);
int		nfAddChildInChildID(int id, int new_id, const char *name);
int		nfAddChildInChildName(const char *name, int new_name, const char *new_name);

/*
** Element Modifying functions
*/
// Delete part
int		nfDeleteElement();
int		nfDeleteAllElement();
int		nfDeleteIDElement(int id);
int		nfDeleteNameElement(const char *name);
// Modify part
int		nfModifyElement(int new_id, const char *new_name, const char *new_content);
int		nfModifyElementID(int new_id);
int		nfModifyIDElementID(int id, int new_id);
int		nfModifyNameElementID(const char *name, int new_id);
int		nfModifyElementName(const char *new_name);
int		nfModifyIDElementName(int id, const char *new_name);
int		nfModifyNameElementName(const char *name, const char *new_name);
int		nfModifyElementContent(const char *new_content, int type);
int		nfModifyIDElementContent(int id, const char *new_content, int type);
int		nfModifyNameElementContent(const char *name, const char *new_content, int type);
// Add part
int		nfAddElementInSegment(int new_id, const char *name, const char *content, int type);
int		nfAddElementInSegmentID(int id, int new_id, const char *name, const char *content, int type);
int		nfAddElementInSegmentName(const char *name, int new_id, const char *name, \
					  const char *content, int type);
int		nfAddElementInChild(int new_id, const char *name, const char *content, int type);
int		nfAddElementInChildID(int id, int new_id, const char *name, const char *content, int type);
int		nfAddElementInChildName(const char *name , int new_id, const char *name, \
					const char *content, int type);

#endif		/* __MODIFY_H__ */
