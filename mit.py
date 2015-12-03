
import morton

def mortonIter2D(end, start=0):
    """Simple generator for two-dimensional indices along the Z curve from
    morton indices [start, end)---start included, end excluded."""
    for i in xrange(start, end):
        yield morton.d2xy(i)

def mortonIter3D(end, start=0):
    """Simple generator for two-dimensional indices along the Z curve from
    morton indices [start, end)---start included, end excluded."""
    for i in xrange(start, end):
        yield morton.d2xyz(i)

