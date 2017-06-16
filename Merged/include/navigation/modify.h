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
int		nfAddChildInChildID(int id, int new_id, const char *name);
int		nfAddChildInChildName(const char *name, int new_name, const char *new_name);
int		nfAddChildInChild(int new_id, const char *new_name);

#endif		/* __MODIFY_H__ */
