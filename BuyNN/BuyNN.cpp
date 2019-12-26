#include "pch.h"	//precompiled headers file
#include "BuyNN.h"
#include <stdio.h>
#include <conio.h>
#include <Python.h>


MT4_EXPFUNC int __stdcall Test(
    const double open, 
    const double close, 
    const double stoch,
    const double vol
)
{           

    PyObject* pInt;
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;   

    PyObject *openValue, *closeValue, *stochValue, *volValue;
    PyObject* prediction;     
    //const char* scriptDirectoryName = "C:/ProgramData/Anaconda3"; 
    
    Py_Initialize();

   // PyRun_SimpleString("sys.path = ['', 'C:\\Users\\Thembi\\.conda\\envs\\test32\\python36.zip', 'C:\\Users\\Thembi\\.conda\\envs\\test32\\DLLs', 'C:\\Users\\Thembi\\.conda\\envs\\test32\\lib', 'C:\\Users\\Thembi\\.conda\\envs\\test32', 'C:\\Users\\Thembi\\.conda\\envs\\test32\\lib\\site - packages']");
    PyRun_SimpleString("import sys");
    //PyRun_SimpleString("import numpy");    

//    PyObject* sysPath = PySys_GetObject((char*)"path");
  //  PyList_Append(sysPath, PyUnicode_FromString("."));
    
    openValue = PyFloat_FromDouble(open);
    closeValue = PyFloat_FromDouble(close);
    stochValue = PyFloat_FromDouble(stoch);
    volValue = PyFloat_FromDouble(vol);
  
    pModule = PyImport_ImportModule("misc32");
    pFunc = PyObject_GetAttrString(pModule, "goo");
    
    //Py_Finalize();
    
    //return 3;

    /*
    if (PyCallable_Check(pFunc))
    {
        return 9;
    }
    else
    {
        return 11;
    }        
    */
    
    if (PyCallable_Check(pFunc))
    {                       
        pArgs = PyTuple_New(4);

        PyTuple_SetItem(pArgs, 0, openValue);
        PyTuple_SetItem(pArgs, 1, closeValue);
        PyTuple_SetItem(pArgs, 2, stochValue);  
        PyTuple_SetItem(pArgs, 3, volValue);

        prediction = PyObject_CallObject(pFunc, pArgs);
        
        return PyLong_AsLong(prediction);
        
        //Py_DECREF(prediction);
    }
    
    //Py_Finalize();
    
    //if (!_getch()) _getch();
    //return 4;
    
}


MT4_EXPFUNC int __stdcall GetIntValue(const int ipar)
{   
    //SUCCESS!!!


	//printf("GetIntValue takes %d\n", ipar);
	return(ipar + 10);

	PyObject* pInt;

	Py_Initialize();

	PyRun_SimpleString("print('Hello World from Embedded Python!!!')");

	Py_Finalize();

	printf("\nPress any key to exit...\n");
	if (!_getch()) _getch();
	return 0;
}

MT4_EXPFUNC int __stdcall RunPythonFunc(int argc, char* argv[])
{
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: call.cpp pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();

    pName = PyUnicode_FromString(argv[1]);
    /* Error checking of pName left out */
    //cout << pName;

    pModule = PyImport_Import(pName);

    Py_DECREF(pName);

    pFunc = PyObject_GetAttrString(pModule, argv[2]);
    /* pFunc is a new reference */

    if (PyCallable_Check(pFunc))
    {
        // Prepare the argument list for the call
        if (argc > 3)
        {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; i++)
            {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue)
                {
                    PyErr_Print();
                    return 1;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }

            pValue = PyObject_CallObject(pFunc, pArgs);

            if (pArgs != NULL)
            {
                Py_DECREF(pArgs);
            }
        }
        else
        {
            pValue = PyObject_CallObject(pFunc, NULL);
        }

        if (pValue != NULL)
        {
            printf("Return of call : %d\n", PyLong_AsLong(pValue));
            return PyLong_AsLong(pValue);
            Py_DECREF(pValue);
        }
        else
        {
            PyErr_Print();
        }

        // some code omitted...
    }
    
    //Py_Finalize();
    
    //return 0;
}

