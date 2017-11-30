# nvml-test
Playing around with how to wrap NVML c code that can query GPU utilization, into python3.
Since Nvidia releases Python2 bindings but not 3 yet.
Tried here 2 approaches - one using ctypes, and loading the library explicitly. 
The other, creating a module and importing directly in python.
