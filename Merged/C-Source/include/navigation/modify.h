#ifndef		__MODIFY_H__
# define	__MODIFY_H__

// if included by navigation.h doesn't need message.h
# ifndef	__NAVIGATION_H__
#  include	"tree/message.h"
# endif		/* __NAVIGATION_H__ */

/*
** The following functions are about modifying part of the tree.
*/

/*
** Segment modifying functions
*/
// Delete Part
double		nfDeleteIDSegment(int id);
double		nfDeleteNameSegment(const char *name);
double		nfDeleteSegment();
double		nfDeleteAllSegment();
// Modify Part
double		nfModifyIDSegmentName(int id, const char *new_name);
double		nfModifyNameSegmentName(const char *name, const char *new_name);
double		nfModifySegmentName(const char *new_name);
double		nfModifyIDSegmentID(int id, int new_id);
double		nfModifyNameSegmentID(const char *name, int new_id);
double		nfModifySegmentID(int new_id);
// Add part
double		nfAddSegmentInSegmentID(int id, int new_id, const char *name);
double		nfAddSegmentInSegmentName(const char *name, int new_name, const char *new_name);
double		nfAddSegmentInSegment(int new_id, const char *new_name);

/*
** Child modifying functions
*/
// Delete Part
double		nfDeleteIDChild(int id);
double		nfDeleteNameChild(const char *name);
double		nfDeleteChild();
double		nfDeleteAllChild();
// Modify Part
double		nfModifyIDChildName(int id, const char *new_name);
double		nfModifyNameChildName(const char *name, const char *new_name);
double		nfModifyChildName(const char *new_name);
double		nfModifyIDChildID(int id, int new_id);
double		nfModifyNameChildID(const char *name, int new_id);
double		nfModifyChildID(int new_id);
// Add part
double		nfAddChildInSegment(int new_id, const char *new_name);
double		nfAddChildInSegmentID(int id, int new_id, const char *name);
double		nfAddChildInSegmentName(const char *name, int new_name, const char *new_name);
double		nfAddChildInChild(int new_id, const char *new_name);
double		nfAddChildInChildID(int id, int new_id, const char *name);
double		nfAddChildInChildName(const char *name, int new_name, const char *new_name);

/*
** Element Modifying functions
*/
// Delete part
double		nfDeleteElement();
double		nfDeleteAllElement();
double		nfDeleteIDElement(int id);
double		nfDeleteNameElement(const char *name);
// Modify part
double		nfModifyElement(int new_id, const char *new_name, const char *new_content);
double		nfModifyElementID(int new_id);
double		nfModifyIDElementID(int id, int new_id);
double		nfModifyNameElementID(const char *name, int new_id);
double		nfModifyElementName(const char *new_name);
double		nfModifyIDElementName(int id, const char *new_name);
double		nfModifyNameElementName(const char *name, const char *new_name);
double		nfModifyElementContent(const char *new_content, int type);
double		nfModifyIDElementContent(int id, const char *new_content, int type);
double		nfModifyNameElementContent(const char *name, const char *new_content, int type);
// Add part
double		nfAddElementInSegment(int new_id, const char *name, const char *content, int type);
double		nfAddElementInSegmentID(int id, int new_id, const char *name, const char *content, int type);
double		nfAddElementInSegmentName(const char *name, int new_id, const char *name, \
					  const char *content, int type);
double		nfAddElementInChild(int new_id, const char *name, const char *content, int type);
double		nfAddElementInChildID(int id, int new_id, const char *name, const char *content, int type);
double		nfAddElementInChildName(const char *name , int new_id, const char *name, \
					const char *content, int type);

#endif		/* __MODIFY_H__ */
