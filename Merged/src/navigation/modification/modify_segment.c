#ifndef		__MODIFY_SEGMENT_C__
# define	__MODIFY_SEGMENT_C__

int		nfDeleteIDSegment(int id)
{
}

int		nfDeleteNameSegment(const char *name)
{
}

// Delete the pointed segment and move to the parent of it.
int		nfDeleteSegment()
{
}

// Delete the list of the pointed segment and move to the parent of it.
int		nfDeleteAllSegment()
{
}

int		nfModifyIDSegmentName(int id, const char *new_name)
{
}

int		nfModifyNameSegmentName(const char *name, const char *new_name)
{
}

int		nfModifySegmentName(const char *new_name)
{
}

int		nfModifyIDSegmentID(int id, int new_id)
{
}

int		nfModifyNameSegmentID(const char *name, int new_id)
{
}

// Modify the pointed segment's ID by new_id
int		nfModifySegmentID(int new_id)
{
}

// Add a segment at the right (next) of the pointed / ID / Name segment.
int		nfAddSegmentInSegmentID(int id, int new_id, const char *name)
{
}

int		nfAddSegmentInSegmentName(const char *name, int new_id, const char *name)
{
}

int		nfAddSegmentInSegment(int new_id, const char *name)
{
}

#endif		/* __MODIFY_SEGMENT_C__ */
