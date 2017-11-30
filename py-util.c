//#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nvml.h>

void fail()
{
  nvmlReturn_t result;
  result = nvmlShutdown();
  if (NVML_SUCCESS != result)
    printf("Failed to shutdown NVML: %s\n", nvmlErrorString(result));
  exit(-1);
}


void showUtilization(int deviceIndex,int sleepInterval, int iterations) 
{
  nvmlReturn_t result;
  nvmlDevice_t device;

  unsigned long long lastSeenTimeStamp=0;
  nvmlValueType_t sampleValType;
  unsigned int sampleCount=1;
  nvmlSample_t samples;


  result = nvmlDeviceGetHandleByIndex(deviceIndex, &device);
  if (NVML_SUCCESS != result) { 
      printf("Failed to get handle for device %i: %s\n", deviceIndex, nvmlErrorString(result));
      fail();
    }

  for(int i=0;i<iterations;i++) {
    printf("About to query device utilization. sampleCount=%d\n",sampleCount);
    result = nvmlDeviceGetSamples(device, NVML_GPU_UTILIZATION_SAMPLES,
				  lastSeenTimeStamp,&sampleValType,&sampleCount,&samples);
    if (NVML_SUCCESS != result) { 
      printf("Failed to get samples for device %i: %s\n", deviceIndex, nvmlErrorString(result));
      fail();
    }
    printf("Iteration %d. GPU utilization: %d\n",i, samples.sampleValue.uiVal );
    sleep(sleepInterval);
  }
}

int initDone=0;

int init()
{
    nvmlReturn_t result;
    unsigned int device_count, i;

    result = nvmlInit();
    if (NVML_SUCCESS != result) { 
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
	fail();
    }
    initDone=1;
}

int getUtil()
{
  printf("Hello world!\n");
  if(!initDone) init();
  showUtilization(0,1,5);
  
  return 111;
}
/*
static PyObject *
getUtil(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    printf("getUtil called!\n");
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    
    return Py_BuildValue("i", sts);
}

static PyMethodDef GPU_UtilMethods[] = {
    
    {"getUtil",  getUtil, METH_VARARGS,
     "Query GPU utilization."},
    
    {NULL, NULL, 0, NULL}       
};

static PyObject *GPU_UtilError;
*/
/*
PyMODINIT_FUNC
initGPU_Util(void)
{
    (void)Py_InitModule("GPU_Util", GPU_UtilMethods);
}
*/
/*


int main()
{
    nvmlReturn_t result;
    unsigned int device_count, i;

    // First initialize NVML library
    result = nvmlInit();
    if (NVML_SUCCESS != result) { 
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
	fail();
    }

    result = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result) { 
        printf("Failed to query device count: %s\n", nvmlErrorString(result));
        fail();
    }
    printf("Found %d device%s\n\n", device_count, device_count != 1 ? "s" : "");

    printf("Listing devices:\n");    
    for (i = 0; i < device_count; i++) {
        nvmlDevice_t device;
        char name[NVML_DEVICE_NAME_BUFFER_SIZE];

        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (NVML_SUCCESS != result) { 
            printf("Failed to get handle for device %i: %s\n", i, nvmlErrorString(result));
            fail();
        }

        result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
        if (NVML_SUCCESS != result) { 
            printf("Failed to get name of device %i: %s\n", i, nvmlErrorString(result));
            fail();
        }
        
        printf("%d. %s\n", i, name);

    }

    showUtilization(0,10,5);
    printf("All done.\n");

    result = nvmlShutdown();
    if (NVML_SUCCESS != result)
        printf("Failed to shutdown NVML: %s\n", nvmlErrorString(result));
    printf("Press ENTER to continue...\n");
    getchar();
    return 0;
}
*/
