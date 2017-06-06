import ics
for variable in [item for item in dir(ics) if not item.startswith("__") and item.isupper()]:
	print(".. py:data:: %s\n\t:annotation: = %s" % (variable, str(getattr(ics, variable))))
