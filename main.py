

from ctypes import cdll
mylib = cdll.LoadLibrary('/home/gpeled/nvml-test/gpuutil.so')


print("Starting to use gpuutil.so through ctypes");
mylib.getUtil()
print("Done")

