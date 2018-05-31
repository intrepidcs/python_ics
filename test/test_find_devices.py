import timeit

print(timeit.timeit("ics.find_devices()", setup="import ics", number=1000))