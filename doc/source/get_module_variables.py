import ics

header = \
"""
Documentation
======================================
.. automodule:: ics
   :members:
   :show-inheritance:
   :undoc-members:

Variables
======================================
"""

print(header)
for variable in [item for item in dir(ics) if not item.startswith("__") and item.isupper()]:
	print(".. py:data:: %s\n\t:annotation: = %s" % (variable, str(getattr(ics, variable))))
