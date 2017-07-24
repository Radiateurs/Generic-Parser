#ifndef		__MODIFY_H__
# define	__MODIFY_H__

/*
** The following functions are about modifying part of the tree.
*/

/*
** Message modifying functions
*/
// Delete part
double		nfDeleteMessages();
double		nfDeleteMessage();
double		nfDeleteIDMessage(int id);
// Copying part
double		nfCopyMessage();
double		nfMirrorMessage();
// Add part
double		nfAddMessage();
// Modify part
/* TO DO */

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
double		nfAddSegment(const char *new_name);
double		nfAddList(const char *name);
double		nfAddTab(const char *name);

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
double		nfAddChildInSegment(const char *new_name);
double		nfAddChildInSegmentID(int id, int new_id, const char *name);
double		nfAddChildInSegmentName(const char *name, const char *new_name);
double		nfAddChildInChild(int new_id, const char *new_name);
double		nfAddChildInChildID(int id, int new_id, const char *name);
double		nfAddChildInChildName(const char *name, const char *new_name);
double		nfAddChildList(const char *name);
double		nfAddChildList(const char *name);

/*
** Element Modifying functions
*/
// Delete part
double		nfDeleteElement();
double		nfDeleteAllElement();
double		nfDeleteIDElement(int id);
double		nfDeleteNameElement(const char *name);
// Modify part
double		nfModifyElement(const char *new_name, const char *new_content);
double		nfModifyElementContent(const char *new_content, int type);
double		nfModifyElementID(int new_id);
double		nfModifyElementName(const char *new_name);
double		nfModifyIDElementContent(int id, const char *new_content, int type);
double		nfModifyIDElementID(int id, int new_id);
double		nfModifyIDElementName(int id, const char *new_name);
double		nfModifyNameElementContent(const char *name, const char *new_content, int type);
double		nfModifyNameElementID(const char *name, int new_id);
double		nfModifyNameElementName(const char *name, const char *new_name);
// Add part
double		nfAddElementInSegment(const char *name, const char *content, int type);
double		nfAddElementInSegmentID(int id, int new_id, const char *name, const char *content, int type);
double		nfAddElementInSegmentName(const char *name, const char *new_name, \
					  const char *content, int type);
double		nfAddElementInChild(const char *name, const char *content, int type);
double		nfAddElementInChildID(int id, int new_id, const char *name, const char *content, int type);
double		nfAddElementInChildName(const char *name, const char *new_name, \
					const char *content, int type);
//Creation Part
double		nfAddNumeric(const char *name, int value);
double		nfAddString(const char *name, const char *value);
double		nfAddNullObject(const char *name);
double		nfAddBoolean(const char *name, int value);
double		nfAddDate(const char *name, const char *date);
double		nfAddTime(const char *name, const char *time);

#endif		/* __MODIFY_H__ */
