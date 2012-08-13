#include <Python.h>

#include <xdgmime.h>


static PyObject *get_mime_type_for_data (PyObject *self, PyObject *args)
{
    const char* data;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &data, &len))
        return NULL;

    return PyString_FromString(xdg_mime_get_mime_type_for_data((const void*) data, (size_t) len, NULL));
}


static PyObject *get_mime_type_for_file (PyObject *self, PyObject *args)
{
    const char* file_name;

    if (!PyArg_ParseTuple(args, "s", &file_name))
        return NULL;

    return PyString_FromString(xdg_mime_get_mime_type_for_file(file_name, NULL));
}

static PyObject *get_mime_type_from_file_name (PyObject *self, PyObject *args)
{
    const char* file_name;

    if (!PyArg_ParseTuple(args, "s", &file_name))
        return NULL;

    return PyString_FromString(xdg_mime_get_mime_type_from_file_name(file_name));
}

static PyObject *get_mime_types_from_file_name (PyObject *self, PyObject *args)
{
    const char* file_name;

    if (!PyArg_ParseTuple(args, "s", &file_name))
        return NULL;

    const char *mime_types[5];

    int len = xdg_mime_get_mime_types_from_file_name(file_name, mime_types, 5);

    PyObject *result = PyList_New(len);

    Py_ssize_t i;

    for (i = 0; i < len; i++)
    {
        PyList_SetItem(result, i, PyString_FromString(mime_types[i]));
    }

    return result;
}

static PyObject* is_valid_mime_type (PyObject* self, PyObject* args)
{
    const char* mime_type;

    if (!PyArg_ParseTuple(args, "s", &mime_type))
        return NULL;

    return PyBool_FromLong(xdg_mime_is_valid_mime_type(mime_type));
}

static PyObject *mime_type_equal (PyObject *self, PyObject *args)
{
    const char *mime_a, *mime_b;

    if (!PyArg_ParseTuple(args, "ss", &mime_a, &mime_b))
        return NULL;

    return PyBool_FromLong(xdg_mime_mime_type_equal(mime_a, mime_b));
}

static PyObject *media_type_equal (PyObject *self, PyObject *args)
{
    const char *mime_a, *mime_b;

    if (!PyArg_ParseTuple(args, "ss", &mime_a, &mime_b))
        return NULL;

    return PyBool_FromLong(xdg_mime_media_type_equal(mime_a, mime_b));
}

static PyObject *mime_type_subclass (PyObject *self, PyObject *args)
{
    const char *mime_a, *mime_b;

    if (!PyArg_ParseTuple(args, "ss", &mime_a, &mime_b))
        return NULL;

    return PyBool_FromLong(xdg_mime_mime_type_subclass(mime_a, mime_b));
}

static PyObject *list_mime_parents (PyObject *self, PyObject *args)
{
    const char *mime;

    if (!PyArg_ParseTuple(args, "s", &mime))
        return NULL;

    char **temp = xdg_mime_list_mime_parents(mime);

    Py_ssize_t len;

    if (temp == NULL)
        len = 0;
    else
        for (len = 0; temp[len]; len++) ;

    PyObject *result = PyList_New(len);

    Py_ssize_t i;

    for (i = 0; i < len; i++)
    {
        PyList_SetItem(result, i, PyString_FromString(temp[i]));
    }

    free(temp);

    return result;
}

static PyObject *unalias_mime_type (PyObject *self, PyObject *args)
{
    const char* mime;

    if (!PyArg_ParseTuple(args, "s", &mime))
        return NULL;

    return PyString_FromString(xdg_mime_unalias_mime_type(mime));
}

static PyObject *get_icon (PyObject *self, PyObject *args)
{
    const char* mime;

    if (!PyArg_ParseTuple(args, "s", &mime))
        return NULL;

    const char* result = xdg_mime_get_icon(mime);

    if (result == NULL)
        Py_RETURN_NONE;

    return PyString_FromString(result);
}

static PyObject *get_generic_icon (PyObject *self, PyObject *args)
{
    const char* mime;

    if (!PyArg_ParseTuple(args, "s", &mime))
        return NULL;

    const char* result = xdg_mime_get_generic_icon(mime);

    if (result == NULL)
        Py_RETURN_NONE;

    return PyString_FromString(result);
}

static PyObject *shutdown (PyObject *self, PyObject *args)
{
    xdg_mime_shutdown();

    Py_RETURN_NONE;
}

static PyObject *dump (PyObject *self, PyObject *args)
{
    xdg_mime_dump();

    Py_RETURN_NONE;
}


static PyMethodDef XdgMimeMethods[] =
{
    {"get_mime_type_for_data", get_mime_type_for_data, METH_VARARGS, ""},
    {"get_mime_type_for_file", get_mime_type_for_file, METH_VARARGS, ""},
    {"get_mime_type_from_file_name", get_mime_type_from_file_name, METH_VARARGS, ""},
    {"get_mime_types_from_file_name", get_mime_types_from_file_name, METH_VARARGS, ""},
    {"is_valid_mime_type", is_valid_mime_type, METH_VARARGS, ""},
    {"mime_type_equal", mime_type_equal, METH_VARARGS, ""},
    {"media_type_equal", media_type_equal, METH_VARARGS, ""},
    {"mime_type_subclass", mime_type_subclass, METH_VARARGS, ""},
    {"list_mime_parents", list_mime_parents, METH_VARARGS, ""},
    {"unalias_mime_type", unalias_mime_type, METH_VARARGS, ""},
    {"get_icon", get_icon, METH_VARARGS, ""},
    {"get_generic_icon", get_generic_icon, METH_VARARGS, ""},
    {"shutdown", shutdown, METH_NOARGS, ""},
    {"dump", dump, METH_NOARGS, ""},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC

initxdgmime(void)
{
     (void) Py_InitModule("xdgmime", XdgMimeMethods);
}

