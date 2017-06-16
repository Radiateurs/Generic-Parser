#ifndef		__MODIFY_SEGMENT_C__
# define	__MODIFY_SEGMENT_C__

int		nfDeleteIDChild(int id)
{
}

int		nfDeleteNameChild(const char *name)
{
}

// Delete the pointed segment's child.
int		nfDeleteChild()
{
}

// Delete the list of the pointed segment and move to the parent of it.
int		nfDeleteAllChild()
{
}

int		nfModifyIDChildName(int id, const char *new_name)
{
}

int		nfModifyNameChildName(const char *name, const char *new_name)
{
}

int		nfModifyChildName(const char *new_name)
{
}

int		nfModifyIDChildID(int id, int new_id)
{
}

int		nfModifyNameChildID(const char *name, int new_id)
{
}

// Modify the pointed segment's ID by new_id
int		nfModifyChildID(int new_id)
{
}

// Add a segment at the right (next) of the pointed / ID / Name segment.
int		nfAddChildInChildID(int id, int new_id, const char *name)
{
}

int		nfAddChildInChildName(const char *name, int new_id, const char *name)
{
}

int		nfAddChildInChild(int new_id, const char *name)
{
}

#endif		/* __MODIFY_SEGMENT_C__ */
