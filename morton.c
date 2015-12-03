
#include <x86intrin.h>
#include <Python.h>

static char xy2d_docstr[] = "Calculates the morton index of a two-dimensional index.";
static char d2xy_docstr[] = "Reverse of xy2d.";
static char xyz2d_docstr[] = "Calculates the morton index of a three-dimensional index.";
static char d2xyz_docstr[] = "Reverse of xyz2d.";

static const unsigned mask1_2d = 0xAAAAAAAA;
static const unsigned mask2_2d = 0x55555555;

static const unsigned mask1_3d = 0x24924924;
static const unsigned mask2_3d = 0x92492492;
static const unsigned mask3_3d = 0x49249249;

static unsigned
_xy2d(unsigned x, unsigned y)
{
	return _pdep_u32(x, mask1_2d) + _pdep_u32(y, mask2_2d);
}

static unsigned
_xyz2d(unsigned x, unsigned y, unsigned z)
{
	return _pdep_u32(x, mask1_3d)
		+ _pdep_u32(y, mask2_3d)
		+ _pdep_u32(z, mask3_3d);
}

static unsigned
_d2x(unsigned d, unsigned mask)
{
	return _pext_u32(d, mask);
}

static PyObject *
xy2d(PyObject *self, PyObject *args)
{
	int x, y;

	if (!PyArg_ParseTuple(args, "ii", &x, &y))
		return NULL;

	return Py_BuildValue("i", _xy2d(x, y));
}

static PyObject *
d2xy(PyObject *self, PyObject *args)
{
	int d;

	if (!PyArg_ParseTuple(args, "i", &d))
		return NULL;

	return Py_BuildValue("ii", _d2x(d, mask1_2d), _d2x(d, mask2_2d));
}

static PyObject *
xyz2d(PyObject *self, PyObject *args)
{
	int x, y, z;

	if (!PyArg_ParseTuple(args, "iii", &x, &y, &z))
		return NULL;

	return Py_BuildValue("i", _xyz2d(x, y, z));
}

static PyObject *
d2xyz(PyObject *self, PyObject *args)
{
	int d;

	if (!PyArg_ParseTuple(args, "i", &d))
		return NULL;

	return Py_BuildValue("iii", 
			     _d2x(d, mask1_3d),
			     _d2x(d, mask2_3d),
			     _d2x(d, mask3_3d));
}

static PyMethodDef morton_methods[] = {
	{"xy2d", xy2d, METH_VARARGS, xy2d_docstr },
	{"d2xy", d2xy, METH_VARARGS, d2xy_docstr },
	{"xyz2d", xyz2d, METH_VARARGS, xyz2d_docstr },
	{"d2xyz", d2xyz, METH_VARARGS, d2xyz_docstr },
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initmorton(void)
{
	Py_InitModule("morton", morton_methods);
}
